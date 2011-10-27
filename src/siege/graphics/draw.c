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

	if(psgmGraphicsDrawPrimitive != NULL)
		psgmGraphicsDrawPrimitive(_sg_gfxHandle, texture, _sg_drawType, _sg_drawNumPoints, _sg_drawPoints, _sg_drawTexCoords, _sg_drawColors);
	_sg_drawNumPoints = 0;
}
void SG_EXPORT sgDrawColor4f(float r, float g, float b, float a)
{
	_sg_drawCurColor[0] = r;
	_sg_drawCurColor[1] = g;
	_sg_drawCurColor[2] = b;
	_sg_drawCurColor[3] = a;
	if(psgmGraphicsDrawSetColor != NULL)
		psgmGraphicsDrawSetColor(_sg_gfxHandle, _sg_drawCurColor);
}
void SG_EXPORT sgDrawColor3f(float r, float g, float b)
{
	sgDrawColor4f(r, g, b, 1.0);
}
void SG_EXPORT sgDrawColor2f(float g, float a)
{
	sgDrawColor4f(g, g, g, a);
}
void SG_EXPORT sgDrawColor1f(float g)
{
	sgDrawColor4f(g, g, g, 1.0);
}
void SG_EXPORT sgDrawColor4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
	sgDrawColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
void SG_EXPORT sgDrawColor3ub(SGubyte r, SGubyte g, SGubyte b)
{
	sgDrawColor4ub(r, g, b, 255);
}
void SG_EXPORT sgDrawColor2ub(SGubyte g, SGubyte a)
{
	sgDrawColor4ub(g, g, g, a);
}
void SG_EXPORT sgDrawColor1ub(SGubyte g)
{
	sgDrawColor4ub(g, g, g, 255);
}
void SG_EXPORT sgDrawColor4fv(float* rgba)
{
	sgDrawColor4f(rgba[0], rgba[1], rgba[2], rgba[3]);
}
void SG_EXPORT sgDrawColor3fv(float* rgb)
{
	sgDrawColor3f(rgb[0], rgb[1], rgb[2]);
}
void SG_EXPORT sgDrawColor2fv(float* ga)
{
	sgDrawColor2f(ga[0], ga[1]);
}
void SG_EXPORT sgDrawColor1fv(float* g)
{
	sgDrawColor1f(g[0]);
}
void SG_EXPORT sgDrawColor4ubv(SGubyte* rgba)
{
	sgDrawColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
}
void SG_EXPORT sgDrawColor3ubv(SGubyte* rgb)
{
	sgDrawColor3ub(rgb[0], rgb[1], rgb[2]);
}
void SG_EXPORT sgDrawColor2ubv(SGubyte* ga)
{
	sgDrawColor2ub(ga[0], ga[1]);
}
void SG_EXPORT sgDrawColor1ubv(SGubyte* g)
{
	sgDrawColor1ub(g[0]);
}
void SG_EXPORT sgDrawTexCoord2f(float s, float t)
{
	_sg_drawCurTexCoord[0] = s;
	_sg_drawCurTexCoord[1] = t;
}
void SG_EXPORT sgDrawTexCoord2fv(float* st)
{
	sgDrawTexCoord2f(st[0], st[1]);
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
void SG_EXPORT sgDrawVertex3fv(float* xyz)
{
	sgDrawVertex3f(xyz[0], xyz[1], xyz[2]);
}
void SG_EXPORT sgDrawVertex2fv(float* xy)
{
	sgDrawVertex2f(xy[0], xy[1]);
}
void SG_EXPORT sgDrawClear4f(float r, float g, float b, float a)
{
	float col[4];
	col[0] = r;
	col[1] = g;
	col[2] = b;
	col[3] = a;
	if(psgmGraphicsContextClear != NULL)
		psgmGraphicsContextClear(_sg_gfxHandle, col);
}
void SG_EXPORT sgDrawClear3f(float r, float g, float b)
{
	sgDrawClear4f(r, g, b, 1.0);
}
void SG_EXPORT sgDrawClear2f(float g, float a)
{
	sgDrawClear4f(g, g, g, a);
}
void SG_EXPORT sgDrawClear1f(float g)
{
	sgDrawClear4f(g, g, g, 1.0);
}
void SG_EXPORT sgDrawClear4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
	sgDrawClear4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}
void SG_EXPORT sgDrawClear3ub(SGubyte r, SGubyte g, SGubyte b)
{
	sgDrawClear4ub(r, g, b, 255);
}
void SG_EXPORT sgDrawClear2ub(SGubyte g, SGubyte a)
{
	sgDrawClear4ub(g, g, g, a);
}
void SG_EXPORT sgDrawClear1ub(SGubyte g)
{
	sgDrawClear4ub(g, g, g, 255);
}
void SG_EXPORT sgDrawClear4fv(float* rgba)
{
	sgDrawClear4f(rgba[0], rgba[1], rgba[2], rgba[3]);
}
void SG_EXPORT sgDrawClear3fv(float* rgb)
{
	sgDrawClear3f(rgb[0], rgb[1], rgb[2]);
}
void SG_EXPORT sgDrawClear2fv(float* ga)
{
	sgDrawClear2f(ga[0], ga[1]);
}
void SG_EXPORT sgDrawClear1fv(float* g)
{
	sgDrawClear1f(g[0]);
}
void SG_EXPORT sgDrawClear4ubv(SGubyte* rgba)
{
	sgDrawClear4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
}
void SG_EXPORT sgDrawClear3ubv(SGubyte* rgb)
{
	sgDrawClear3ub(rgb[0], rgb[1], rgb[2]);
}
void SG_EXPORT sgDrawClear2ubv(SGubyte* ga)
{
	sgDrawClear2ub(ga[0], ga[1]);
}
void SG_EXPORT sgDrawClear1ubv(SGubyte* g)
{
	sgDrawClear1ub(g[0]);
}
void SG_EXPORT sgDrawClear(void)
{
	sgDrawClear4f(0.0f, 0.0f, 0.0f, 0.0f);
}

void SG_EXPORT sgDrawSetBlendFunc(SGenum src, SGenum dst)
{
    if(psgmGraphicsDrawSetBlendFunc != NULL)
        psgmGraphicsDrawSetBlendFunc(_sg_gfxHandle, src, dst);
}
void SG_EXPORT sgDrawSetBlendEquation(SGenum equation)
{
    if(psgmGraphicsDrawSetBlendEquation != NULL)
        psgmGraphicsDrawSetBlendEquation(_sg_gfxHandle, equation);
}

void SG_EXPORT sgDrawSetDepthTest(SGbool test)
{
    if(psgmGraphicsDrawSetDepthTest)
        psgmGraphicsDrawSetDepthTest(_sg_gfxHandle, test);
}
void SG_EXPORT sgDrawSetSmooth(SGbool smooth)
{
    if(psgmGraphicsDrawSetSmooth)
        psgmGraphicsDrawSetSmooth(_sg_gfxHandle, smooth);
}

void SG_EXPORT sgDrawPoint(float x, float y)
{
	sgDrawBegin(SG_GRAPHICS_PRIMITIVE_POINTS);
		sgDrawVertex2f(x, y);
	sgDrawEnd();
}
void SG_EXPORT sgDrawPointSetSize(float size)
{
	if(psgmGraphicsDrawPointSetSize != NULL)
		psgmGraphicsDrawPointSetSize(_sg_gfxHandle, size);
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
	if(psgmGraphicsDrawLineSetWidth != NULL)
		psgmGraphicsDrawLineSetWidth(_sg_gfxHandle, width);
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
void SG_EXPORT sgDrawRectangleWH(float x, float y, float w, float h, SGbool fill)
{
	sgDrawRectangle(x, y, x + w, y + h, fill);
}

void SG_EXPORT sgDrawRectangleRound(float x1, float y1, float x2, float y2, float rx, float ry, SGbool fill)
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
void SG_EXPORT sgDrawRectangleRoundWH(float x1, float y1, float w, float h, float rx, float ry, SGbool fill)
{
    sgDrawRectangleRound(x1, y1, x1 + w, y1 + h, rx, ry, fill);
}

void SG_EXPORT sgDrawEllipse2R(float x, float y, float rx, float ry, SGbool fill)
{
	sgDrawEArcRads(x, y, rx, ry, 0, 2 * SG_PI, SG_FALSE, fill);
}

void SG_EXPORT sgDrawCircle(float x, float y, float radius, SGbool fill)
{
	sgDrawEllipse2R(x, y, radius, radius, fill);
}

void SG_EXPORT sgDrawEArcRads(float x, float y, float rx, float ry, float a1, float a2, SGbool ccw, SGbool fill)
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
		sgDrawBegin(SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN);
		sgDrawVertex2f(x, y);
	}
	else
		sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_STRIP);

	for(i = 0; i <= numsides; i++)
	{
		float a = a1 + i * adiff;
		sgDrawVertex2f(x + cos(a) * rx, y + sin(a) * ry);
	}

	sgDrawEnd();
}
void SG_EXPORT sgDrawEArcDegs(float x, float y, float rx, float ry, float a1, float a2, SGbool ccw, SGbool fill)
{
	sgDrawEArcRads(x, y, rx, ry, a1 * SG_PI / 180.0, a2 * SG_PI / 180.0, ccw, fill);
}

void SG_EXPORT sgDrawArcRads(float x, float y, float r, float a1, float a2, SGbool ccw, SGbool fill)
{
	sgDrawEArcRads(x, y, r, r, a1, a2, ccw, fill);
}
void SG_EXPORT sgDrawArcDegs(float x, float y, float r, float a1, float a2, SGbool ccw, SGbool fill)
{
	sgDrawEArcDegs(x, y, r, r, a1, a2, ccw, fill);
}
