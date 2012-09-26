/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "main.h"
#include "context.h"
#include "texture.h"
#include "draw.h"

#include <stdio.h>
#include <stdlib.h>

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

static void enableAll(ContextData* cdata, TextureData* tdata)
{
    if(tdata)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tdata->texid);
    }

    //if(cdata->vact)
        glEnableClientState(GL_VERTEX_ARRAY);
    if(cdata->cact)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glPushAttrib(GL_CURRENT_BIT);
    }
    if(cdata->tact)
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    if(cdata->iact)
        glEnableClientState(GL_INDEX_ARRAY);
}
static void disableAll(ContextData* cdata, TextureData* tdata)
{
    if(cdata->iact)
        glDisableClientState(GL_INDEX_ARRAY);
    if(cdata->tact)
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    if(cdata->cact)
    {
        glDisableClientState(GL_COLOR_ARRAY);
        glPopAttrib();
    }
    //if(cdata->vact)
        glDisableClientState(GL_VERTEX_ARRAY);

    if(tdata)
    {
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

SGenum SG_EXPORT sgmGraphicsSetVertexPointer(void* context, SGubyte size, SGenum type, size_t stride, const void* ptr)
{
    GLenum gltype = typeSGtoGL(type);
    if(!gltype) return SG_INVALID_ENUM;

    ContextData* cdata = context;
    cdata->vact = ptr != NULL;
    cdata->vptr = NULL;
    glVertexPointer(size, gltype, stride, ptr);
    return SG_OK;
}
SGenum SG_EXPORT sgmGraphicsSetColorPointer(void* context, SGubyte size, SGenum type, size_t stride, const void* ptr)
{
    GLenum gltype = typeSGtoGL(type);
    if(!gltype) return SG_INVALID_ENUM;

    ContextData* cdata = context;
    cdata->cact = ptr != NULL;
    cdata->cptr = NULL;
    glColorPointer(size, gltype, stride, ptr);
    return SG_OK;
}
SGenum SG_EXPORT sgmGraphicsSetTexCoordPointer(void* context, SGenum type, size_t stride, const void* ptr)
{
    GLenum gltype = typeSGtoGL(type);
    if(!gltype) return SG_INVALID_ENUM;

    ContextData* cdata = context;
    cdata->tact = ptr != NULL;
    cdata->tptr = NULL;
    glTexCoordPointer(2, gltype, stride, ptr);
    return SG_OK;
}
SGenum SG_EXPORT sgmGraphicsSetIndexPointer(void* context, SGenum type, size_t stride, const void* ptr)
{
    GLenum gltype = typeSGtoGL(type);
    if(!gltype) return SG_INVALID_ENUM;

    ContextData* cdata = context;
    cdata->iact = ptr != NULL;
    cdata->iptr = NULL;
    glIndexPointer(gltype, stride, ptr);
    return SG_OK;
}
SGenum SG_EXPORT sgmGraphicsDrawArrays(void* context, void* texture, SGenum mode, size_t first, size_t count)
{
    GLenum glmode = modeSGtoGL(mode);
    if(!glmode) return SG_INVALID_ENUM;

    enableAll(context, texture);
    glDrawArrays(glmode, first, count);
    disableAll(context, texture);

    return SG_OK;
}
SGenum SG_EXPORT sgmGraphicsDrawElements(void* context, void* texture, SGenum mode, size_t count, SGenum type, const void* indices)
{
    GLenum glmode = modeSGtoGL(mode);
    if(!glmode) return SG_INVALID_ENUM;

    GLenum gltype = typeSGtoGL(type);
    if(!gltype) return SG_INVALID_ENUM;

    enableAll(context, texture);
    glDrawElements(mode, count, gltype, indices);
    disableAll(context, texture);

    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsDrawPrimitive(void* context, void* texture, SGenum mode, size_t numverts, float* vertices, float* texcoords, float* colors)
{
    sgmGraphicsSetVertexPointer(context, 3, SG_FLOAT, 0, vertices);
    if(texcoords)
        sgmGraphicsSetTexCoordPointer(context, SG_FLOAT, 0, texcoords);
    if(colors)
        sgmGraphicsSetColorPointer(context, 4, SG_FLOAT, 0, colors);

    SGenum ret = sgmGraphicsDrawArrays(context, texture, mode, 0, numverts);

    if(colors)
        sgmGraphicsSetColorPointer(context, 4, SG_FLOAT, 0, NULL);
    if(texcoords)
        sgmGraphicsSetTexCoordPointer(context, SG_FLOAT, 0, NULL);

    return ret;
}
SGuint SG_EXPORT sgmGraphicsDrawSetColor(void* context, float* color)
{
    glColor4fv(color);
    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsDrawPointSetSize(void* context, float size)
{
    glPointSize(size);
    return SG_OK;
}
SGuint SG_EXPORT sgmGraphicsDrawLineSetWidth(void* context, float size)
{
    glLineWidth(size);
    return SG_OK;
}

/*#define SG_GRAPHICS_FUNC_ZERO                   0x00
#define SG_GRAPHICS_FUNC_ONE                    0x01
#define SG_GRAPHICS_FUNC_SRC_COLOR              0x02
#define SG_GRAPHICS_FUNC_ONE_MINUS_SRC_COLOR    0x03
#define SG_GRAPHICS_FUNC_DST_COLOR              0x04
#define SG_GRAPHICS_FUNC_ONE_MINUS_DST_COLOR    0x05
#define SG_GRAPHICS_FUNC_SRC_ALPHA              0x06
#define SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA    0x07
#define SG_GRAPHICS_FUNC_DST_ALPHA              0x08
#define SG_GRAPHICS_FUNC_ONE_MINUS_DST_ALPHA    0x09

#define SG_GRAPHICS_EQUATION_ADD                0x00
#define SG_GRAPHICS_EQUATION_SUBTRACT           0x01
#define SG_GRAPHICS_EQUATION_REVERSE_SUBTRACT   0x02
#define SG_GRAPHICS_EQUATION_MIN                0x03
#define SG_GRAPHICS_EQUATION_MAX                0x04*/
SGuint SG_EXPORT sgmGraphicsDrawSetBlendFunc(void* context, SGenum src, SGenum dst)
{
    static GLenum table[] = {GL_ZERO, GL_ONE,
                             GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR,
                             GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR,
                             GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                             GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,};

    if(src >= sizeof(table) / sizeof(GLenum)
    || dst >= sizeof(table) / sizeof(GLenum))
        return SG_OK; // SG_INVALID_ENUM

    glBlendFunc(table[src], table[dst]);

    return SG_OK;
}
// todo
SGuint SG_EXPORT sgmGraphicsDrawSetBlendEquation(void* context, SGenum equation)
{
    static GLenum table[] = {GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX};

    if(equation >= sizeof(table) / sizeof(GLenum))
        return SG_OK; // SG_INVALID_ENUM

    return SG_UNKNOWN_ERROR;
    //glBlendEquation(table[equation]);

    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsDrawSetDepthFunc(void* context, SGenum func)
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
            return SG_INVALID_ENUM;
    }
    glDepthFunc(glfunc);
    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsDrawSetDepthTest(void* context, SGbool test)
{
    if(test)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsDrawSetAlphaFunc(void* context, SGenum func, float ref)
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
            return SG_INVALID_ENUM;
    }
    glAlphaFunc(glfunc, ref);
    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsDrawSetAlphaTest(void* context, SGbool test)
{
    if(test)
        glEnable(GL_ALPHA_TEST);
    else
        glDisable(GL_ALPHA_TEST);
    return SG_OK;
}

SGenum SG_EXPORT sgmGraphicsDrawSetPointSmooth(void* context, SGbool smooth)
{
    GLenum mode = smooth ? GL_NICEST : GL_FASTEST;

    glHint(GL_POINT_SMOOTH_HINT, mode);

    if(smooth)
        glEnable(GL_POINT_SMOOTH);
    else
        glDisable(GL_POINT_SMOOTH);

    return SG_OK;
}
SGenum SG_EXPORT sgmGraphicsDrawSetLineSmooth(void* context, SGbool smooth)
{
    GLenum mode = smooth ? GL_NICEST : GL_FASTEST;

    glHint(GL_LINE_SMOOTH_HINT, mode);

    if(smooth)
        glEnable(GL_LINE_SMOOTH);
    else
        glDisable(GL_LINE_SMOOTH);

    return SG_OK;
}
SGenum SG_EXPORT sgmGraphicsDrawSetPolygonSmooth(void* context, SGbool smooth)
{
    GLenum mode = smooth ? GL_NICEST : GL_FASTEST;

    glHint(GL_LINE_SMOOTH_HINT   , mode);

    if(smooth)
        glEnable(GL_POLYGON_SMOOTH);
    else
        glDisable(GL_POLYGON_SMOOTH);

    return SG_OK;
}
