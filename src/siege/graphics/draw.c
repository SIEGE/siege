#define SG_BUILD_LIBRARY
#include <siege/graphics/draw.h>
#include <siege/core/window.h>
#include <siege/modules/graphics.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

SGbool SG_EXPORT _sgDrawInit(void)
{
    _sg_drawCurTexCoord[0] = 0.0f;
    _sg_drawCurTexCoord[1] = 0.0f;
    _sg_drawCurColor[0] = 1.0f;
    _sg_drawCurColor[1] = 1.0f;
    _sg_drawCurColor[2] = 1.0f;
    _sg_drawCurColor[3] = 1.0f;

    _sg_drawPoints = NULL;
    _sg_drawTexCoords = NULL;
    _sg_drawColors = NULL;
    _sg_drawNumPoints = 0;
    return SG_TRUE;
}
SGbool SG_EXPORT _sgDrawDeinit(void)
{
    free(_sg_drawPoints);
    free(_sg_drawTexCoords);
    free(_sg_drawColors);
    return SG_TRUE;
}

void SG_EXPORT sgDrawBeginT(SGenum type, SGTexture* texture)
{
    if(_sg_drawNumPoints != 0)
        fprintf(stderr, "sgDrawBegin called without sgDrawEnd.");

    _sg_drawType = type;
    _sg_drawTexture = texture;
}
void SG_EXPORT sgDrawBegin(SGenum type)
{
    sgDrawBeginT(type, NULL);
}
void SG_EXPORT sgDrawEnd(void)
{
    void* texture = NULL;
    if(_sg_drawTexture != NULL)
        texture = _sg_drawTexture->handle;

    if(_sg_modGraphics.sgmGraphicsDrawPrimitive != NULL)
        _sg_modGraphics.sgmGraphicsDrawPrimitive(_sg_gfxHandle, texture, _sg_drawType, _sg_drawNumPoints, _sg_drawPoints, _sg_drawTexCoords, _sg_drawColors);
    _sg_drawNumPoints = 0;
}
void SG_EXPORT sgDrawColor4f(float r, float g, float b, float a)
{
    _sg_drawCurColor[0] = r;
    _sg_drawCurColor[1] = g;
    _sg_drawCurColor[2] = b;
    _sg_drawCurColor[3] = a;
    if(_sg_modGraphics.sgmGraphicsDrawSetColor != NULL)
        _sg_modGraphics.sgmGraphicsDrawSetColor(_sg_gfxHandle, _sg_drawCurColor);
}
_SG_COLOR_OVERLOADS_FUNC(sgDrawColor);
void SG_EXPORT sgDrawTexCoord2f(float s, float t)
{
    _sg_drawCurTexCoord[0] = s;
    _sg_drawCurTexCoord[1] = t;
}
void SG_EXPORT sgDrawVertex3f(float x, float y, float z)
{
    _sg_drawCurPoint[0] = x;
    _sg_drawCurPoint[1] = y;
    _sg_drawCurPoint[2] = z;

    _sg_drawNumPoints++;
    _sg_drawPoints = realloc(_sg_drawPoints, _sg_drawNumPoints * sizeof(_sg_drawCurPoint));
    _sg_drawTexCoords = realloc(_sg_drawTexCoords, _sg_drawNumPoints * sizeof(_sg_drawCurTexCoord));
    _sg_drawColors = realloc(_sg_drawColors, _sg_drawNumPoints * sizeof(_sg_drawCurColor));
    memcpy(&_sg_drawPoints[(_sg_drawNumPoints - 1) * 3], _sg_drawCurPoint, sizeof(_sg_drawCurPoint));
    memcpy(&_sg_drawTexCoords[(_sg_drawNumPoints - 1) * 2], _sg_drawCurTexCoord, sizeof(_sg_drawCurTexCoord));
    memcpy(&_sg_drawColors[(_sg_drawNumPoints - 1) * 4], _sg_drawCurColor, sizeof(_sg_drawCurColor));
}
void SG_EXPORT sgDrawVertex2f(float x, float y)
{
    sgDrawVertex3f(x, y, 0.0f);
}
void SG_EXPORT sgDrawClear4f(float r, float g, float b, float a)
{
    float col[4];
    col[0] = r;
    col[1] = g;
    col[2] = b;
    col[3] = a;
    if(_sg_modGraphics.sgmGraphicsContextClear != NULL)
        _sg_modGraphics.sgmGraphicsContextClear(_sg_gfxHandle, col);
}
_SG_COLOR_OVERLOADS_FUNC(sgDrawClear);
void SG_EXPORT sgDrawClear(void)
{
    sgDrawClear4f(0.0f, 0.0f, 0.0f, 0.0f);
}

void SG_EXPORT sgDrawPoint(float x, float y)
{
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_POINTS);
        sgDrawVertex2f(x, y);
    sgDrawEnd();
}
void SG_EXPORT sgDrawPointSetSize(float size)
{
    if(_sg_modGraphics.sgmGraphicsDrawPointSetSize != NULL)
        _sg_modGraphics.sgmGraphicsDrawPointSetSize(_sg_gfxHandle, size);
}
//float SG_EXPORT sgDrawPointGetSize(void);

void SG_EXPORT sgDrawLine(float x1, float y1, float x2, float y2)
{
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINES);
        sgDrawVertex2f(x1, y1);
        sgDrawVertex2f(x2, y2);
    sgDrawEnd();
}
void SG_EXPORT sgDrawLineSetWidth(float width)
{
    if(_sg_modGraphics.sgmGraphicsDrawLineSetWidth != NULL)
        _sg_modGraphics.sgmGraphicsDrawLineSetWidth(_sg_gfxHandle, width);
}
//float SG_EXPORT sgDrawLineGetWidth(void);

void SG_EXPORT sgDrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, SGbool fill)
{
    if(fill)
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_TRIANGLES);
    else
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);

        sgDrawVertex2f(x1, y1);
        sgDrawVertex2f(x2, y2);
        sgDrawVertex2f(x3, y3);
    sgDrawEnd();
}

void SG_EXPORT sgDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SGbool fill)
{
    if(fill)
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_QUADS);
    else
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);

        sgDrawVertex2f(x1, y1);
        sgDrawVertex2f(x2, y2);
        sgDrawVertex2f(x3, y3);
        sgDrawVertex2f(x4, y4);
    sgDrawEnd();
}

void SG_EXPORT sgDrawRectangle(float x1, float y1, float x2, float y2, SGbool fill)
{
    sgDrawQuad(x1, y1, x2, y1, x2, y2, x1, y2, fill);
}

void SG_EXPORT sgDrawEllipse2R(float x, float y, float rx, float ry, SGbool fill)
{
    float ra = (rx + ry) / 2.0;
    SGuint numsides = (SGuint)(ra * 1.4);
    SGuint i;

    if(fill)
    {
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN);
        sgDrawVertex2f(x, y);
    }
    else
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);

    for(i = 0; i < numsides + (fill ? 1 : 0); i++)
    {
        float a = 2.0 * M_PI * i / (float)numsides;
        sgDrawVertex2f(x + cos(a) * rx, y + sin(a) * ry);
    }

    sgDrawEnd();
}

void SG_EXPORT sgDrawCircle(float x, float y, float radius, SGbool fill)
{
    sgDrawEllipse2R(x, y, radius, radius, fill);
}
