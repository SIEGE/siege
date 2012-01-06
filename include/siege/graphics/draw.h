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
/**
 * \file siege/graphics/draw.h
 * \brief Drawing-related functions
 *
 * \ingroup Graphics
 */

#ifndef __SIEGE_GRAPHICS_DRAW_H__
#define __SIEGE_GRAPHICS_DRAW_H__

#include "../common.h"
#include "../util/plist.h"
#include "texture.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

SGbool SG_EXPORT _sgDrawInit(void);
SGbool SG_EXPORT _sgDrawDeinit(void);

/**
 * \name Procedural drawing
 */
/// @{
/**
 * \brief Begin drawing a textured primitive
 *
 * \param type Type of the primitive to draw
 * \param texture The texture to use for the primitive
 */
void SG_EXPORT sgDrawBeginT(SGenum type, SGTexture* texture);
/**
 * \brief Begin drawing an untextured primitive
 *
 * \param type Type of the primitive to draw
 */
void SG_EXPORT sgDrawBegin(SGenum type);
/**
 * \brief Finish drawing the primitive
 */
void SG_EXPORT sgDrawEnd(void);
/**
 * \brief Set the draw color
 *
 * \param r Red
 * \param g Green
 * \param b Blue
 * \param a Alpha
 */
void SG_EXPORT sgDrawColor4f(float r, float g, float b, float a);
void SG_EXPORT sgDrawColor3f(float r, float g, float b);
void SG_EXPORT sgDrawColor2f(float g, float a);
void SG_EXPORT sgDrawColor1f(float g);
void SG_EXPORT sgDrawColor4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a);
void SG_EXPORT sgDrawColor3ub(SGubyte r, SGubyte g, SGubyte b);
void SG_EXPORT sgDrawColor2ub(SGubyte g, SGubyte a);
void SG_EXPORT sgDrawColor1ub(SGubyte g);
void SG_EXPORT sgDrawColor4fv(const float* rgba);
void SG_EXPORT sgDrawColor3fv(const float* rgb);
void SG_EXPORT sgDrawColor2fv(const float* ga);
void SG_EXPORT sgDrawColor1fv(const float* g);
void SG_EXPORT sgDrawColor4ubv(const SGubyte* rgba);
void SG_EXPORT sgDrawColor3ubv(const SGubyte* rgb);
void SG_EXPORT sgDrawColor2ubv(const SGubyte* ga);
void SG_EXPORT sgDrawColor1ubv(const SGubyte* g);

void SG_EXPORT sgDrawGetColor4f(float* r, float* g, float* b, float* a);
void SG_EXPORT sgDrawGetColor4ub(SGubyte* r, SGubyte* g, SGubyte* b, SGubyte* a);
void SG_EXPORT sgDrawGetColor4fv(float* rgba);
void SG_EXPORT sgDrawGetColor4ubv(SGubyte* rgba);

/**
 * \brief Set the texture coordinate of the following vertex
 *
 * \param s Horizontal (x) coordinate
 * \param t Vertical (y) coordinate
 *
 * \note
 *	Texture coordinates generally span from 0.0 to 1.0 - values
 *	outside this range can sometimes (depending on the texture
 *	clipping mode) indicate flipping or tiling.
 */
void SG_EXPORT sgDrawTexCoord2f(float s, float t);
void SG_EXPORT sgDrawTexCoord2fv(const float* st);
/**
 * \brief Place a vertex at a specific depth
 *
 * \param x X coordinate
 * \param y Y coordinate
 * \param z Z coordinate (the depth)
 */
void SG_EXPORT sgDrawVertex3f(float x, float y, float z);
void SG_EXPORT sgDrawVertex2f(float x, float y);
void SG_EXPORT sgDrawVertex3fv(const float* xyz);
void SG_EXPORT sgDrawVertex2fv(const float* xy);
/// @}

/**
 * \name Clearing the drawable
 */
/// @{
/**
 * \brief Clear the drawable
 *
 * \param r Red
 * \param g Green
 * \param b Blue
 * \param a Alpha
 */
void SG_EXPORT sgDrawClear4f(float r, float g, float b, float a);
void SG_EXPORT sgDrawClear3f(float r, float g, float b);
void SG_EXPORT sgDrawClear2f(float g, float a);
void SG_EXPORT sgDrawClear1f(float g);
void SG_EXPORT sgDrawClear4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a);
void SG_EXPORT sgDrawClear3ub(SGubyte r, SGubyte g, SGubyte b);
void SG_EXPORT sgDrawClear2ub(SGubyte g, SGubyte a);
void SG_EXPORT sgDrawClear1ub(SGubyte g);
void SG_EXPORT sgDrawClear4fv(const float* rgba);
void SG_EXPORT sgDrawClear3fv(const float* rgb);
void SG_EXPORT sgDrawClear2fv(const float* ga);
void SG_EXPORT sgDrawClear1fv(const float* g);
void SG_EXPORT sgDrawClear4ubv(const SGubyte* rgba);
void SG_EXPORT sgDrawClear3ubv(const SGubyte* rgb);
void SG_EXPORT sgDrawClear2ubv(const SGubyte* ga);
void SG_EXPORT sgDrawClear1ubv(const SGubyte* g);
/**
 * \brief Clear the drawable with black color
 */
void SG_EXPORT sgDrawClear(void);
/// @}

void SG_EXPORT sgDrawSetBlendFunc(SGenum src, SGenum dst);
void SG_EXPORT sgDrawSetBlendEquation(SGenum equation);

void SG_EXPORT sgDrawSetDepthTest(SGbool test);
void SG_EXPORT sgDrawSetSmooth(SGbool smooth);

/**
 * \name Points
 */
/// @{
/**
 * \brief Draw a point
 *
 * \param x X coordinate
 * \param y Y coordinate
 */
void SG_EXPORT sgDrawPoint(float x, float y);
/**
 * \brief Set the point size
 *
 * \param size New point size
 */
void SG_EXPORT sgDrawPointSetSize(float size);
//float SG_EXPORT sgDrawPointGetSize(void);
/// @}

/**
 * \name Lines
 */
/// @{
/**
 * \brief Draw a line
 *
 * \param x1 Start x coordinate
 * \param y1 Start y coordinate
 * \param x2 End x coordinate
 * \param y2 End y coordinate
 */
void SG_EXPORT sgDrawLine(float x1, float y1, float x2, float y2);
/**
 * \brief Set the line width
 *
 * \param width New line width
 */
void SG_EXPORT sgDrawLineSetWidth(float width);
//float SG_EXPORT sgDrawLineGetWidth(void);
/// @}

/**
 * \name Triangles
 */
/// @{
void SG_EXPORT sgDrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, SGbool fill);
/// @}

/**
 * \name Quads
 */
/// @{
void SG_EXPORT sgDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SGbool fill);
/// @}

/**
 * \name Rectangles
 */
/// @{
void SG_EXPORT sgDrawRectangle(float x1, float y1, float x2, float y2, SGbool fill);
void SG_EXPORT sgDrawRectangleWH(float x, float y, float w, float h, SGbool fill);
/// @}

void SG_EXPORT sgDrawRectangleRound(float x1, float y1, float x2, float y2, float rx, float ry, SGbool fill);
void SG_EXPORT sgDrawRectangleRoundWH(float x1, float y1, float w, float h, float rx, float ry, SGbool fill);

/**
 * \name Ellipses
 */
/// @{
void SG_EXPORT sgDrawEllipse2R(float x, float y, float rx, float ry, SGbool fill);
/// @}

/**
 * \name Circles
 */
/// @{
void SG_EXPORT sgDrawCircle(float x, float y, float radius, SGbool fill);
/// @}

/**
 * \name Elliptic Arcs
 */
/// @{
void SG_EXPORT sgDrawEArcRads(float x, float y, float rx, float ry, float a1, float a2, SGbool ccw, SGbool fill);
void SG_EXPORT sgDrawEArcDegs(float x, float y, float rx, float ry, float a1, float a2, SGbool ccw, SGbool fill);
/// @}

/**
 * \name Circle arcs
 */
/// @{
void SG_EXPORT sgDrawArcRads(float x, float y, float r, float a1, float a2, SGbool ccw, SGbool fill);
void SG_EXPORT sgDrawArcDegs(float x, float y, float r, float a1, float a2, SGbool ccw, SGbool fill);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_DRAW_H__
