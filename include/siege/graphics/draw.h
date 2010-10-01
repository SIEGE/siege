/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_GRAPHICS_DRAW_H__
#define __SIEGE_GRAPHICS_DRAW_H__

#include "../common.h"
#include "../util/plist.h"
#include "texture.h"

#define _SG_COLOR_OVERLOADS_FUNC(func)                                      \
    void SG_EXPORT func##3f(float r, float g, float b)                      \
    {                                                                       \
        func##4f(r, g, b, 1.0f);                                            \
    }                                                                       \
    void SG_EXPORT func##2f(float g, float a)                               \
    {                                                                       \
        func##4f(g, g, g, a);                                               \
    }                                                                       \
    void SG_EXPORT func##1f(float g)                                        \
    {                                                                       \
        func##4f(g, g, g, 1.0f);                                            \
    }                                                                       \
    void SG_EXPORT func##4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a)    \
    {                                                                       \
        func##4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);           \
    }                                                                       \
    void SG_EXPORT func##3ub(SGubyte r, SGubyte g, SGubyte b)               \
    {                                                                       \
        func##4f(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);                 \
    }                                                                       \
    void SG_EXPORT func##2ub(SGubyte g, SGubyte a)                          \
    {                                                                       \
        func##4f(g / 255.0f, g / 255.0f, g / 255.0f, a / 255.0f);           \
    }                                                                       \
    void SG_EXPORT func##1ub(SGubyte g)                                     \
    {                                                                       \
        func##4f(g / 255.0f, g / 255.0f, g / 255.0f, 1.0f);                 \
    }
#define _SG_COLOR_OVERLOADS_DECL(func)                                    \
    void SG_EXPORT func##3f(float r, float g, float b);                   \
    void SG_EXPORT func##2f(float g, float a);                            \
    void SG_EXPORT func##1f(float g);                                     \
    void SG_EXPORT func##4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a); \
    void SG_EXPORT func##3ub(SGubyte r, SGubyte g, SGubyte b);            \
    void SG_EXPORT func##2ub(SGubyte g, SGubyte a);                       \
    void SG_EXPORT func##1ub(SGubyte g);

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_BUILD_LIBRARY
SGenum _sg_drawType;
SGTexture* _sg_drawTexture;
float _sg_drawCurPoint[3];
float _sg_drawCurTexCoord[2];
float _sg_drawCurColor[4];

float* _sg_drawPoints;
float* _sg_drawTexCoords;
float* _sg_drawColors;
SGuint _sg_drawNumPoints;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgDrawInit(void);
SGbool SG_EXPORT _sgDrawDeinit(void);

/**
    \name Procedural drawing
*/
// @{
/**
    \brief Begin drawing a textured primitive
    \param type Type of the primitive to draw
    \param texture The texture to use for the primitive
*/
void SG_EXPORT sgDrawBeginT(SGenum type, SGTexture* texture);
/**
    \brief Begin drawing an untextured primitive
    \param type Type of the primitive to draw
*/
void SG_EXPORT sgDrawBegin(SGenum type);
/**
    \brief Finish drawing the primitive
*/
void SG_EXPORT sgDrawEnd(void);
/**
    \brief Set the draw color
    \param r Red
    \param g Green
    \param b Blue
    \param a Alpha
*/
void SG_EXPORT sgDrawColor4f(float r, float g, float b, float a);
_SG_COLOR_OVERLOADS_DECL(sgDrawColor);
/**
    \brief Set the texture coordinate of the following vertex
    \param s Horizontal (x) coordinate
    \param t Vertical (y) coordinate
    \note
        Texture coordinates generally span from 0.0 to 1.0 - values outside this range can sometimes (depending on the texture clipping mode) indicate flipping or tiling.
*/
void SG_EXPORT sgDrawTexCoord2f(float s, float t);
/**
    \brief Place a vertex at a specific depth
    \param x X coordinate
    \param y Y coordinate
    \param z Z coordinate (the depth)
*/
void SG_EXPORT sgDrawVertex3f(float x, float y, float z);
/**
    \brief Place a vertex at depth 0
    \param x X coordinate
    \param y Y coordinate

    This function places a vertex at the coordinates and at depth 0.
*/
void SG_EXPORT sgDrawVertex2f(float x, float y);
// @}

/**
    \name Clearing the drawable
*/
// @{
/**
    \brief Clear the drawable
    \param r Red
    \param g Green
    \param b Blue
    \param a Alpha
*/
void SG_EXPORT sgDrawClear4f(float r, float g, float b, float a);
_SG_COLOR_OVERLOADS_DECL(sgDrawClear);
/**
    \brief Clear the drawable with black color
*/
void SG_EXPORT sgDrawClear(void);
// @}

/**
    \name Points
*/
// @{
/**
    \brief Draw a point
    \param x X coordinate
    \param y Y coordinate
*/
void SG_EXPORT sgDrawPoint(float x, float y);
/**
    \brief Set the point size
    \param size New point size
*/
void SG_EXPORT sgDrawPointSetSize(float size);
//float SG_EXPORT sgDrawPointGetSize(void);
// @}

/**
    \name Lines
*/
// @{
/**
    \brief Draw a line
    \param x1 Start x coordinate
    \param y1 Start y coordinate
    \param x2 End x coordinate
    \param y2 End y coordinate
*/
void SG_EXPORT sgDrawLine(float x1, float y1, float x2, float y2);
/**
    \brief Set the line width
    \param width New line width
*/
void SG_EXPORT sgDrawLineSetWidth(float width);
//float SG_EXPORT sgDrawLineGetWidth(void);
// @}

/**
    \name Triangles
*/
// @{
void SG_EXPORT sgDrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, SGbool fill);
// @}

/**
    \name Quads
*/
// @{
void SG_EXPORT sgDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SGbool fill);
// @}

/**
    \name Rectangles
*/
// @{
void SG_EXPORT sgDrawRectangle(float x1, float y1, float x2, float y2, SGbool fill);
// @}

/**
    \name Ellipses
*/
// @{
void SG_EXPORT sgDrawEllipse2R(float x, float y, float rx, float ry, SGbool fill);
// @}

/**
    \name Circles
*/
// @{
void SG_EXPORT sgDrawCircle(float x, float y, float radius, SGbool fill);
// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_DRAW_H__
