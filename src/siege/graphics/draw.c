/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#define SG_BUILD_LIBRARY
#include <siege/graphics/draw.h>
#include <siege/core/window.h>
#include <siege/util/thread/thread.h>
#include <siege/util/thread/key.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <SDL/SDL.h>
#include "../internal/gl.h"

static const SGenum sgtypes[] = {
    SG_BYTE, SG_UBYTE,
    SG_SHORT, SG_USHORT,
    SG_INT, SG_UINT,
    SG_FLOAT, SG_DOUBLE,
};
static const GLenum gltypes[] = {
    GL_BYTE, GL_UNSIGNED_BYTE,
    GL_SHORT, GL_UNSIGNED_SHORT,
    GL_INT, GL_UNSIGNED_INT,
    GL_FLOAT, GL_DOUBLE,
};

static GLenum typeSGtoGL(SGenum type)
{
    size_t i;
    for(i = 0; i < sizeof(sgtypes) / sizeof(*sgtypes); i++)
        if(sgtypes[i] == type)
            return gltypes[i];
    return 0;
}

static GLenum modeSGtoGL(SGenum mode)
{
    switch(mode)
    {
        case SG_POINTS:     return GL_POINTS;
        case SG_LINES:      return GL_LINES;
        case SG_LINE_STRIP: return GL_LINE_STRIP;
        case SG_LINE_FAN: /* TODO */
            /*
            *out = malloc((numverts - 1) * sizeof(GLuint) * 2);
            for(i = 0; i < numverts - 1; i++)
            {
                out[2*i  ] = 0;
                out[2*i+1] = i+1;
            }
            return GL_LINES;*/
            return 0;
        case SG_LINE_LOOP:      return GL_LINE_LOOP;
        case SG_TRIANGLES:      return GL_TRIANGLES;
        case SG_TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
        case SG_TRIANGLE_FAN:   return GL_TRIANGLE_FAN;
        //case SG_TRIANGLE_LOOP:
        case SG_QUADS:          return GL_QUADS;
        case SG_QUAD_STRIP:     return GL_QUAD_STRIP;
        //case SG_QUAD_FAN:
        //case SG_QUAD_LOOP:
        case SG_CONVEX_POLYGON: return GL_POLYGON;

        /* TODO -- convert! */
        case SG_CONCAVE_POLYGON:
        case SG_INTERSECTING_POLYGON:   return GL_POLYGON;

        default: return 0;
    }
}

typedef struct SGDrawContext
{
    SGenum mode;
    SGTexture* texture;
    float point[3];
    float texCoord[2];
    float color[4];

    float* points;
    float* texCoords;
    float* colors;
    size_t numPoints;

    struct
    {
        SGubyte size;
        SGenum type;
        size_t stride;
        const void* ptr;
    } vdata;
    struct
    {
        SGubyte size;
        SGenum type;
        size_t stride;
        const void* ptr;
    } cdata;
    struct
    {
        SGenum type;
        size_t stride;
        const void* ptr;
    } tdata;
    struct
    {
        SGenum type;
        size_t stride;
        const void* ptr;
    } idata;
} SGDrawContext;

static SGDrawContext drawCtx;

static void enableAll(SGbool cd, SGbool td, SGbool id, SGTexture* texture)
{
    if(texture)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, GLTEX(texture));
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    if(cd)
    {
        glPushAttrib(GL_CURRENT_BIT);
        glEnableClientState(GL_COLOR_ARRAY);
    }
    if(td)
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    if(id)
        glEnableClientState(GL_INDEX_ARRAY);
}
static void disableAll(SGbool cd, SGbool td, SGbool id, SGTexture* texture)
{
    if(id)
        glDisableClientState(GL_INDEX_ARRAY);
    if(td)
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    if(cd)
    {
        glDisableClientState(GL_COLOR_ARRAY);
        glPopAttrib();
    }
    glDisableClientState(GL_VERTEX_ARRAY);

    if(texture)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
}
static void enablePointers(void)
{
    //GLuint size, GLenum type, GLuint stride, const void* ptr
    glVertexPointer(drawCtx.vdata.size, typeSGtoGL(drawCtx.vdata.type), drawCtx.vdata.stride, drawCtx.vdata.ptr);
    glColorPointer(drawCtx.cdata.size, typeSGtoGL(drawCtx.cdata.type), drawCtx.cdata.stride, drawCtx.cdata.ptr);
    glTexCoordPointer(2, typeSGtoGL(drawCtx.tdata.type), drawCtx.tdata.stride, drawCtx.tdata.ptr);
    glIndexPointer(typeSGtoGL(drawCtx.idata.type), drawCtx.idata.stride, drawCtx.idata.ptr);
}
static void drawArraysRaw(SGenum mode, SGbool cd, SGbool td, SGbool id, SGTexture* texture, size_t first, size_t count)
{
    enableAll(cd, td, id, texture);
    glDrawArrays(modeSGtoGL(mode), first, count);
    disableAll(cd, td, id, texture);
}
static void drawElementsRaw(SGenum mode, SGbool cd, SGbool td, SGbool id, SGTexture* texture, size_t count, SGenum type, const void* indices)
{
    enableAll(cd, td, id, texture);
    glDrawElements(modeSGtoGL(mode), count, typeSGtoGL(type), indices);
    disableAll(cd, td, id, texture);
}

SGbool SG_CALL _sgDrawInit(void)
{
    drawCtx.texCoord[0] = 0.0f;
    drawCtx.texCoord[1] = 0.0f;
    drawCtx.color[0] = 1.0f;
    drawCtx.color[1] = 1.0f;
    drawCtx.color[2] = 1.0f;
    drawCtx.color[3] = 1.0f;

    drawCtx.points = NULL;
    drawCtx.texCoords = NULL;
    drawCtx.colors = NULL;
    drawCtx.numPoints = 0;

    drawCtx.vdata.ptr = NULL;
    drawCtx.cdata.ptr = NULL;
    drawCtx.tdata.ptr = NULL;
    drawCtx.idata.ptr = NULL;
    return SG_TRUE;
}
SGbool SG_CALL _sgDrawDeinit(void)
{
    free(drawCtx.points);
    free(drawCtx.texCoords);
    free(drawCtx.colors);
    return SG_TRUE;
}

void SG_CALL sgVertexPointer(SGubyte size, SGenum type, size_t stride, const void* ptr)
{
    drawCtx.vdata.size = size;
    drawCtx.vdata.type = type;
    drawCtx.vdata.stride = stride;
    drawCtx.vdata.ptr = ptr;
}
void SG_CALL sgColorPointer(SGubyte size, SGenum type, size_t stride, const void* ptr)
{
    drawCtx.cdata.size = size;
    drawCtx.cdata.type = type;
    drawCtx.cdata.stride = stride;
    drawCtx.cdata.ptr = ptr;
}
void SG_CALL sgTexCoordPointer(SGenum type, size_t stride, const void* ptr)
{
    drawCtx.tdata.type = type;
    drawCtx.tdata.stride = stride;
    drawCtx.tdata.ptr = ptr;
}
void SG_CALL sgIndexPointer(SGenum type, size_t stride, const void* ptr)
{
    drawCtx.idata.type = type;
    drawCtx.idata.stride = stride;
    drawCtx.idata.ptr = ptr;
}

void SG_CALL sgResetPointers(SGbool color, SGbool texcoord, SGbool index)
{
    if(color)    drawCtx.cdata.ptr = NULL;
    if(texcoord) drawCtx.tdata.ptr = NULL;
    if(index)    drawCtx.idata.ptr = NULL;
}

void SG_CALL sgDrawArraysT(SGenum mode, SGTexture* texture, size_t first, size_t count)
{
    enablePointers();
    drawArraysRaw(mode, !!drawCtx.cdata.ptr, !!drawCtx.tdata.ptr, !!drawCtx.idata.ptr, texture, first, count);
}
void SG_CALL sgDrawElementsT(SGenum mode, SGTexture* texture, size_t count, SGenum type, const void* indices)
{
    enablePointers();
    drawElementsRaw(mode, !!drawCtx.cdata.ptr, !!drawCtx.tdata.ptr, !!drawCtx.idata.ptr, texture, count, type, indices);
}
void SG_CALL sgDrawArrays(SGenum mode, size_t first, size_t count)
{
    sgDrawArraysT(mode, NULL, first, count);
}
void SG_CALL sgDrawElements(SGenum mode, size_t count, SGenum type, const void* indices)
{
    sgDrawElementsT(mode, NULL, count, type, indices);
}

void SG_CALL sgDrawBeginT(SGenum mode, SGTexture* texture)
{
    if(drawCtx.numPoints)
    {
        fprintf(stderr, "Warning: sgDrawBegin called without sgDrawEnd\n");
        return;
    }

    drawCtx.mode = mode;
    drawCtx.texture = texture;
}
void SG_CALL sgDrawBegin(SGenum mode)
{
    sgDrawBeginT(mode, NULL);
}
void SG_CALL sgDrawEnd(void)
{
    glVertexPointer(3, GL_FLOAT, 0, drawCtx.points);
    glColorPointer(4, GL_FLOAT, 0, drawCtx.colors);
    glTexCoordPointer(2, GL_FLOAT, 0, drawCtx.texCoords);
    glIndexPointer(GL_FLOAT, 0, NULL);

    drawArraysRaw(drawCtx.mode, SG_TRUE, SG_TRUE, SG_FALSE, drawCtx.texture, 0, drawCtx.numPoints);
    drawCtx.numPoints = 0;
}
void SG_CALL sgDrawColor4f(float r, float g, float b, float a)
{
    drawCtx.color[0] = r;
    drawCtx.color[1] = g;
    drawCtx.color[2] = b;
    drawCtx.color[3] = a;
    glColor4fv(drawCtx.color);
}
void SG_CALL sgDrawColor3f(float r, float g, float b)
{
    sgDrawColor4f(r, g, b, 1.0);
}
void SG_CALL sgDrawColor2f(float g, float a)
{
    sgDrawColor4f(g, g, g, a);
}
void SG_CALL sgDrawColor1f(float g)
{
    sgDrawColor4f(g, g, g, 1.0);
}
void SG_CALL sgDrawColor4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    sgDrawColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
void SG_CALL sgDrawColor3ub(SGubyte r, SGubyte g, SGubyte b)
{
    sgDrawColor4ub(r, g, b, 255);
}
void SG_CALL sgDrawColor2ub(SGubyte g, SGubyte a)
{
    sgDrawColor4ub(g, g, g, a);
}
void SG_CALL sgDrawColor1ub(SGubyte g)
{
    sgDrawColor4ub(g, g, g, 255);
}
void SG_CALL sgDrawColor4fv(const float* rgba)
{
    sgDrawColor4f(rgba[0], rgba[1], rgba[2], rgba[3]);
}
void SG_CALL sgDrawColor3fv(const float* rgb)
{
    sgDrawColor3f(rgb[0], rgb[1], rgb[2]);
}
void SG_CALL sgDrawColor2fv(const float* ga)
{
    sgDrawColor2f(ga[0], ga[1]);
}
void SG_CALL sgDrawColor1fv(const float* g)
{
    sgDrawColor1f(g[0]);
}
void SG_CALL sgDrawColor4ubv(const SGubyte* rgba)
{
    sgDrawColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
}
void SG_CALL sgDrawColor3ubv(const SGubyte* rgb)
{
    sgDrawColor3ub(rgb[0], rgb[1], rgb[2]);
}
void SG_CALL sgDrawColor2ubv(const SGubyte* ga)
{
    sgDrawColor2ub(ga[0], ga[1]);
}
void SG_CALL sgDrawColor1ubv(const SGubyte* g)
{
    sgDrawColor1ub(g[0]);
}

void SG_CALL sgDrawGetColor4f(float* r, float* g, float* b, float* a)
{
    if(r) *r = drawCtx.color[0];
    if(g) *g = drawCtx.color[1];
    if(b) *b = drawCtx.color[2];
    if(a) *a = drawCtx.color[3];
}
void SG_CALL sgDrawGetColor4ub(SGubyte* r, SGubyte* g, SGubyte* b, SGubyte* a)
{
    float fr, fg, fb, fa;
    sgDrawGetColor4f(&fr, &fg, &fb, &fa);
    if(r) *r = (SGubyte)fr * 255.0;
    if(g) *g = (SGubyte)fg * 255.0;
    if(b) *b = (SGubyte)fb * 255.0;
    if(a) *a = (SGubyte)fa * 255.0;
}
void SG_CALL sgDrawGetColor4fv(float* rgba)
{
    sgDrawGetColor4f(&rgba[0], &rgba[1], &rgba[2], &rgba[3]);
}
void SG_CALL sgDrawGetColor4ubv(SGubyte* rgba)
{
    sgDrawGetColor4ub(&rgba[0], &rgba[1], &rgba[2], &rgba[3]);
}

void SG_CALL sgDrawTexCoord2f(float s, float t)
{
    drawCtx.texCoord[0] = s;
    drawCtx.texCoord[1] = t;
}
void SG_CALL sgDrawTexCoord2fv(const float* st)
{
    sgDrawTexCoord2f(st[0], st[1]);
}
void SG_CALL sgDrawVertex3f(float x, float y, float z)
{
    drawCtx.point[0] = x;
    drawCtx.point[1] = y;
    drawCtx.point[2] = z;

    drawCtx.numPoints++;
    drawCtx.points = realloc(drawCtx.points, drawCtx.numPoints * sizeof(drawCtx.point));
    drawCtx.texCoords = realloc(drawCtx.texCoords, drawCtx.numPoints * sizeof(drawCtx.texCoord));
    drawCtx.colors = realloc(drawCtx.colors, drawCtx.numPoints * sizeof(drawCtx.color));
    memcpy(&drawCtx.points[(drawCtx.numPoints - 1) * 3], drawCtx.point, sizeof(drawCtx.point));
    memcpy(&drawCtx.texCoords[(drawCtx.numPoints - 1) * 2], drawCtx.texCoord, sizeof(drawCtx.texCoord));
    memcpy(&drawCtx.colors[(drawCtx.numPoints - 1) * 4], drawCtx.color, sizeof(drawCtx.color));
}
void SG_CALL sgDrawVertex2f(float x, float y)
{
    sgDrawVertex3f(x, y, 0.0f);
}
void SG_CALL sgDrawVertex3fv(const float* xyz)
{
    sgDrawVertex3f(xyz[0], xyz[1], xyz[2]);
}
void SG_CALL sgDrawVertex2fv(const float* xy)
{
    sgDrawVertex2f(xy[0], xy[1]);
}
void SG_CALL sgDrawClear4f(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT/* | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT*/);
}
void SG_CALL sgDrawClear3f(float r, float g, float b)
{
    sgDrawClear4f(r, g, b, 1.0);
}
void SG_CALL sgDrawClear2f(float g, float a)
{
    sgDrawClear4f(g, g, g, a);
}
void SG_CALL sgDrawClear1f(float g)
{
    sgDrawClear4f(g, g, g, 1.0);
}
void SG_CALL sgDrawClear4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    sgDrawClear4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
void SG_CALL sgDrawClear3ub(SGubyte r, SGubyte g, SGubyte b)
{
    sgDrawClear4ub(r, g, b, 255);
}
void SG_CALL sgDrawClear2ub(SGubyte g, SGubyte a)
{
    sgDrawClear4ub(g, g, g, a);
}
void SG_CALL sgDrawClear1ub(SGubyte g)
{
    sgDrawClear4ub(g, g, g, 255);
}
void SG_CALL sgDrawClear4fv(const float* rgba)
{
    sgDrawClear4f(rgba[0], rgba[1], rgba[2], rgba[3]);
}
void SG_CALL sgDrawClear3fv(const float* rgb)
{
    sgDrawClear3f(rgb[0], rgb[1], rgb[2]);
}
void SG_CALL sgDrawClear2fv(const float* ga)
{
    sgDrawClear2f(ga[0], ga[1]);
}
void SG_CALL sgDrawClear1fv(const float* g)
{
    sgDrawClear1f(g[0]);
}
void SG_CALL sgDrawClear4ubv(const SGubyte* rgba)
{
    sgDrawClear4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
}
void SG_CALL sgDrawClear3ubv(const SGubyte* rgb)
{
    sgDrawClear3ub(rgb[0], rgb[1], rgb[2]);
}
void SG_CALL sgDrawClear2ubv(const SGubyte* ga)
{
    sgDrawClear2ub(ga[0], ga[1]);
}
void SG_CALL sgDrawClear1ubv(const SGubyte* g)
{
    sgDrawClear1ub(g[0]);
}
void SG_CALL sgDrawClear(void)
{
    sgDrawClear4f(0.0f, 0.0f, 0.0f, 0.0f);
}

void SG_CALL sgDrawSetBlendFunc(SGenum src, SGenum dst)
{
    static const GLenum table[] = {
            GL_ZERO, GL_ONE,
            GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR,
            GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
            GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
            GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,
        };
    if(src >= sizeof(table) / sizeof(GLenum)
    || dst >= sizeof(table) / sizeof(GLenum))
        return;

    glBlendFunc(table[src], table[dst]);
}
void SG_CALL sgDrawSetBlendEquation(SGenum equation)
{
    static const GLenum table[] = {
            GL_FUNC_ADD,
            GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT,
            GL_MIN, GL_MAX,
        };
    if(equation >= sizeof(table) / sizeof(GLenum))
        return;
    glBlendEquationEXT(table[equation]);
}

void SG_CALL sgDrawSetDepthFunc(SGenum func)
{
    GLenum glfunc = 0;
    switch(func)
    {
        case SG_CMP_NEVER:    glfunc = GL_NEVER;    break;
        case SG_CMP_EQUAL:    glfunc = GL_EQUAL;    break;
        case SG_CMP_NOTEQUAL: glfunc = GL_NOTEQUAL; break;
        case SG_CMP_LESS:     glfunc = GL_LESS;     break;
        case SG_CMP_LEQUAL:   glfunc = GL_LEQUAL;   break;
        case SG_CMP_GREATER:  glfunc = GL_GREATER;  break;
        case SG_CMP_GEQUAL:   glfunc = GL_GEQUAL;   break;
        case SG_CMP_ALWAYS:   glfunc = GL_ALWAYS;   break;
        default:
            return;
    }
    glDepthFunc(glfunc);
}
void SG_CALL sgDrawSetDepthTest(SGbool test)
{
    if(test)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

void SG_CALL sgDrawSetAlphaFunc(SGenum func, float ref)
{
    GLenum glfunc = 0;
    switch(func)
    {
        case SG_CMP_NEVER:    glfunc = GL_NEVER;    break;
        case SG_CMP_EQUAL:    glfunc = GL_EQUAL;    break;
        case SG_CMP_NOTEQUAL: glfunc = GL_NOTEQUAL; break;
        case SG_CMP_LESS:     glfunc = GL_LESS;     break;
        case SG_CMP_LEQUAL:   glfunc = GL_LEQUAL;   break;
        case SG_CMP_GREATER:  glfunc = GL_GREATER;  break;
        case SG_CMP_GEQUAL:   glfunc = GL_GEQUAL;   break;
        case SG_CMP_ALWAYS:   glfunc = GL_ALWAYS;   break;
        default:
            return;
    }
    glAlphaFunc(glfunc, ref);
}
void SG_CALL sgDrawSetAlphaTest(SGbool test)
{
    if(test)
        glEnable(GL_ALPHA_TEST);
    else
        glDisable(GL_ALPHA_TEST);
}

void SG_CALL sgDrawSetPointSmooth(SGbool smooth)
{
    GLenum mode = smooth ? GL_NICEST : GL_FASTEST;

    glHint(GL_POINT_SMOOTH_HINT, mode);

    if(smooth)
        glEnable(GL_POINT_SMOOTH);
    else
        glDisable(GL_POINT_SMOOTH);
}
void SG_CALL sgDrawSetLineSmooth(SGbool smooth)
{
    GLenum mode = smooth ? GL_NICEST : GL_FASTEST;

    glHint(GL_LINE_SMOOTH_HINT, mode);

    if(smooth)
        glEnable(GL_LINE_SMOOTH);
    else
        glDisable(GL_LINE_SMOOTH);
}
void SG_CALL sgDrawSetPolygonSmooth(SGbool smooth)
{
    GLenum mode = smooth ? GL_NICEST : GL_FASTEST;

    glHint(GL_POLYGON_SMOOTH_HINT, mode); // was GL_LINE_SMOOTH_HINT -- bug?

    if(smooth)
        glEnable(GL_POLYGON_SMOOTH);
    else
        glDisable(GL_POLYGON_SMOOTH);
}

void SG_CALL sgDrawPoint(float x, float y)
{
    sgDrawBegin(SG_POINTS);
        sgDrawVertex2f(x, y);
    sgDrawEnd();
}
void SG_CALL sgDrawSetPointSize(float size)
{
    glPointSize(size);
}
//float SG_CALL sgDrawGetPointSize(void);

void SG_CALL sgDrawLine(float x1, float y1, float x2, float y2)
{
    sgDrawBegin(SG_LINES);
        sgDrawVertex2f(x1, y1);
        sgDrawVertex2f(x2, y2);
    sgDrawEnd();
}
void SG_CALL sgDrawSetLineWidth(float width)
{
    glLineWidth(width);
}
//float SG_CALL sgDrawGetLineWidth(void);

void SG_CALL sgDrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, SGbool fill)
{
    if(fill)
        sgDrawBegin(SG_TRIANGLES);
    else
        sgDrawBegin(SG_LINE_LOOP);

        sgDrawVertex2f(x1, y1);
        sgDrawVertex2f(x2, y2);
        sgDrawVertex2f(x3, y3);
    sgDrawEnd();
}

void SG_CALL sgDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SGbool fill)
{
    if(fill)
        sgDrawBegin(SG_QUADS);
    else
        sgDrawBegin(SG_LINE_LOOP);

    sgDrawVertex2f(x1, y1);
    sgDrawVertex2f(x2, y2);
    sgDrawVertex2f(x3, y3);
    sgDrawVertex2f(x4, y4);
    sgDrawEnd();
}

void SG_CALL sgDrawRectangle(float x1, float y1, float x2, float y2, SGbool fill)
{
    sgDrawQuad(x1, y1, x2, y1, x2, y2, x1, y2, fill);
}
void SG_CALL sgDrawRectangleWH(float x, float y, float w, float h, SGbool fill)
{
    sgDrawRectangle(x, y, x + w, y + h, fill);
}

void SG_CALL sgDrawRectangleRound(float x1, float y1, float x2, float y2, float rx, float ry, SGbool fill)
{
    float tmp;
    if(x1 > x2)
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if(y1 > y2)
    {
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    sgDrawEArcRads(x1 + rx, y1 + ry, rx, ry,-SG_PI    ,-SG_PI / 2, SG_FALSE, fill);
    sgDrawEArcRads(x2 - rx, y1 + ry, rx, ry,-SG_PI / 2,         0, SG_FALSE, fill);
    sgDrawEArcRads(x2 - rx, y2 - ry, rx, ry,         0, SG_PI / 2, SG_FALSE, fill);
    sgDrawEArcRads(x1 + rx, y2 - ry, rx, ry, SG_PI / 2,-SG_PI    , SG_FALSE, fill);
    if(fill)
    {
        sgDrawRectangle(x1 + rx, y1, x2 - rx, y1 + ry, SG_TRUE);
        sgDrawRectangle(x1, y1 + ry, x2, y2 - ry, SG_TRUE);
        sgDrawRectangle(x1 + rx, y2, x2 - rx, y2 - ry, SG_TRUE);
    }
    else
    {
        sgDrawLine(x1 + rx, y1, x2 - rx, y1);
        sgDrawLine(x1, y1 + ry, x1, y2 - ry);
        sgDrawLine(x2, y1 + ry, x2, y2 - ry);
        sgDrawLine(x1 + rx, y2, x2 - rx, y2);
    }
}
void SG_CALL sgDrawRectangleRoundWH(float x1, float y1, float w, float h, float rx, float ry, SGbool fill)
{
    sgDrawRectangleRound(x1, y1, x1 + w, y1 + h, rx, ry, fill);
}

void SG_CALL sgDrawEllipse2R(float x, float y, float rx, float ry, SGbool fill)
{
    sgDrawEArcRads(x, y, rx, ry, 0, 2 * SG_PI, SG_FALSE, fill);
}

void SG_CALL sgDrawCircle(float x, float y, float radius, SGbool fill)
{
    sgDrawEllipse2R(x, y, radius, radius, fill);
}

void SG_CALL sgDrawEArcRads(float x, float y, float rx, float ry, float a1, float a2, SGbool ccw, SGbool fill)
{
    float adiff = a2 - a1;

    if(!ccw && adiff < 0)
        adiff = adiff + 2 * SG_PI;
    else if(ccw && adiff > 0)
        adiff = adiff - 2 * SG_PI;

    float ra = (rx + ry) / 2.0;
    SGuint numsides = (SGuint)(ra * SG_ABS(adiff) / 2 / SG_PI * 4);
    adiff /= numsides;
    SGuint i;

    if(fill)
    {
        sgDrawBegin(SG_TRIANGLE_FAN);
        sgDrawVertex2f(x, y);
    }
    else
        sgDrawBegin(SG_LINE_STRIP);

    for(i = 0; i <= numsides; i++)
    {
        float a = a1 + i * adiff;
        sgDrawVertex2f(x + cos(a) * rx, y + sin(a) * ry);
    }

    sgDrawEnd();
}
void SG_CALL sgDrawEArcDegs(float x, float y, float rx, float ry, float a1, float a2, SGbool ccw, SGbool fill)
{
    sgDrawEArcRads(x, y, rx, ry, a1 * SG_PI / 180.0, a2 * SG_PI / 180.0, ccw, fill);
}

void SG_CALL sgDrawArcRads(float x, float y, float r, float a1, float a2, SGbool ccw, SGbool fill)
{
    sgDrawEArcRads(x, y, r, r, a1, a2, ccw, fill);
}
void SG_CALL sgDrawArcDegs(float x, float y, float r, float a1, float a2, SGbool ccw, SGbool fill)
{
    sgDrawEArcDegs(x, y, r, r, a1, a2, ccw, fill);
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgDrawPointSetSize(float size)
{
    sgDrawSetPointSize(size);
}
void SG_CALL SG_HINT_DEPRECATED sgDrawLineSetWidth(float width)
{
    sgDrawSetLineWidth(width);
}
