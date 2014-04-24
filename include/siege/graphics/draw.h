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
#include "../util/list.h"
#include "texture.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

SGbool SG_CALL _sgDrawInit(void);
SGbool SG_CALL _sgDrawDeinit(void);

void SG_CALL sgVertexPointer(SGubyte size, SGenum type, size_t stride, const void* ptr);
void SG_CALL sgColorPointer(SGubyte size, SGenum type, size_t stride, const void* ptr);
void SG_CALL sgTexCoordPointer(SGenum type, size_t stride, const void* ptr);
void SG_CALL sgIndexPointer(SGenum type, size_t stride, const void* ptr);

void SG_CALL sgResetPointers(SGbool color, SGbool texcoord, SGbool index);

void SG_CALL sgDrawArraysT(SGenum mode, SGTexture* texture, size_t first, size_t count);
void SG_CALL sgDrawElementsT(SGenum mode, SGTexture* texture, size_t count, SGenum type, const void* indices);
void SG_CALL sgDrawArrays(SGenum mode, size_t first, size_t count);
void SG_CALL sgDrawElements(SGenum mode, size_t count, SGenum type, const void* indices);

/**
 * \name Procedural drawing
 */
/// @{
/**
 * \brief Begin drawing a textured primitive
 *
 * \param mode Type of the primitive to draw
 * \param texture The texture to use for the primitive
 */
void SG_CALL sgDrawBeginT(SGenum mode, SGTexture* texture);
/**
 * \brief Begin drawing an untextured primitive
 *
 * \param mode Type of the primitive to draw
 */
void SG_CALL sgDrawBegin(SGenum mode);
/**
 * \brief Finish drawing the primitive
 */
void SG_CALL sgDrawEnd(void);
/**
 * \brief Set the draw color
 *
 * \param r Red
 * \param g Green
 * \param b Blue
 * \param a Alpha
 */
void SG_CALL sgDrawColor4f(float r, float g, float b, float a);
void SG_CALL sgDrawColor3f(float r, float g, float b);
void SG_CALL sgDrawColor2f(float g, float a);
void SG_CALL sgDrawColor1f(float g);
void SG_CALL sgDrawColor4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a);
void SG_CALL sgDrawColor3ub(SGubyte r, SGubyte g, SGubyte b);
void SG_CALL sgDrawColor2ub(SGubyte g, SGubyte a);
void SG_CALL sgDrawColor1ub(SGubyte g);
void SG_CALL sgDrawColor4fv(const float* rgba);
void SG_CALL sgDrawColor3fv(const float* rgb);
void SG_CALL sgDrawColor2fv(const float* ga);
void SG_CALL sgDrawColor1fv(const float* g);
void SG_CALL sgDrawColor4ubv(const SGubyte* rgba);
void SG_CALL sgDrawColor3ubv(const SGubyte* rgb);
void SG_CALL sgDrawColor2ubv(const SGubyte* ga);
void SG_CALL sgDrawColor1ubv(const SGubyte* g);

void SG_CALL sgDrawGetColor4f(float* r, float* g, float* b, float* a);
void SG_CALL sgDrawGetColor4ub(SGubyte* r, SGubyte* g, SGubyte* b, SGubyte* a);
void SG_CALL sgDrawGetColor4fv(float* rgba);
void SG_CALL sgDrawGetColor4ubv(SGubyte* rgba);

/**
 * \brief Set the texture coordinate of the following vertex
 *
 * \param s Horizontal (x) coordinate
 * \param t Vertical (y) coordinate
 *
 * \note
 *    Texture coordinates generally span from 0.0 to 1.0 - values
 *    outside this range can sometimes (depending on the texture
 *    clipping mode) indicate flipping or tiling.
 */
void SG_CALL sgDrawTexCoord2f(float s, float t);
void SG_CALL sgDrawTexCoord2fv(const float* st);
/**
 * \brief Place a vertex at a specific depth
 *
 * \param x X coordinate
 * \param y Y coordinate
 * \param z Z coordinate (the depth)
 */
void SG_CALL sgDrawVertex3f(float x, float y, float z);
void SG_CALL sgDrawVertex2f(float x, float y);
void SG_CALL sgDrawVertex3fv(const float* xyz);
void SG_CALL sgDrawVertex2fv(const float* xy);
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
void SG_CALL sgDrawClear4f(float r, float g, float b, float a);
void SG_CALL sgDrawClear3f(float r, float g, float b);
void SG_CALL sgDrawClear2f(float g, float a);
void SG_CALL sgDrawClear1f(float g);
void SG_CALL sgDrawClear4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a);
void SG_CALL sgDrawClear3ub(SGubyte r, SGubyte g, SGubyte b);
void SG_CALL sgDrawClear2ub(SGubyte g, SGubyte a);
void SG_CALL sgDrawClear1ub(SGubyte g);
void SG_CALL sgDrawClear4fv(const float* rgba);
void SG_CALL sgDrawClear3fv(const float* rgb);
void SG_CALL sgDrawClear2fv(const float* ga);
void SG_CALL sgDrawClear1fv(const float* g);
void SG_CALL sgDrawClear4ubv(const SGubyte* rgba);
void SG_CALL sgDrawClear3ubv(const SGubyte* rgb);
void SG_CALL sgDrawClear2ubv(const SGubyte* ga);
void SG_CALL sgDrawClear1ubv(const SGubyte* g);
/**
 * \brief Clear the drawable with black color
 */
void SG_CALL sgDrawClear(void);
/// @}

void SG_CALL sgDrawSetBlendFunc(SGenum src, SGenum dst);
void SG_CALL sgDrawSetBlendEquation(SGenum equation);

void SG_CALL sgDrawSetDepthFunc(SGenum func);
void SG_CALL sgDrawSetDepthTest(SGbool test);

void SG_CALL sgDrawSetAlphaFunc(SGenum func, float ref);
void SG_CALL sgDrawSetAlphaTest(SGbool test);

void SG_CALL sgDrawSetPointSmooth(SGbool smooth);
void SG_CALL sgDrawSetLineSmooth(SGbool smooth);
void SG_CALL sgDrawSetPolygonSmooth(SGbool smooth);

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
void SG_CALL sgDrawPoint(float x, float y);
/**
 * \brief Set the point size
 *
 * \param size New point size
 */
void SG_CALL sgDrawSetPointSize(float size);
//float SG_CALL sgDrawGetPointSize(void);
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
void SG_CALL sgDrawLine(float x1, float y1, float x2, float y2);
/**
 * \brief Set the line width
 *
 * \param width New line width
 */
void SG_CALL sgDrawSetLineWidth(float width);
//float SG_CALL sgDrawGetLineWidth(void);
/// @}

/**
 * \name Triangles
 */
/// @{
void SG_CALL sgDrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, SGbool fill);
/// @}

/**
 * \name Quads
 */
/// @{
void SG_CALL sgDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SGbool fill);
/// @}

/**
 * \name Rectangles
 */
/// @{
void SG_CALL sgDrawRectangle(float x1, float y1, float x2, float y2, SGbool fill);
void SG_CALL sgDrawRectangleWH(float x, float y, float w, float h, SGbool fill);
/// @}

void SG_CALL sgDrawRectangleRound(float x1, float y1, float x2, float y2, float rx, float ry, SGbool fill);
void SG_CALL sgDrawRectangleRoundWH(float x1, float y1, float w, float h, float rx, float ry, SGbool fill);

/**
 * \name Ellipses
 */
/// @{
void SG_CALL sgDrawEllipse2R(float x, float y, float rx, float ry, SGbool fill);
/// @}

/**
 * \name Circles
 */
/// @{
void SG_CALL sgDrawCircle(float x, float y, float radius, SGbool fill);
/// @}

/**
 * \name Elliptic Arcs
 */
/// @{
void SG_CALL sgDrawEArcRads(float x, float y, float rx, float ry, float a1, float a2, SGbool ccw, SGbool fill);
void SG_CALL sgDrawEArcDegs(float x, float y, float rx, float ry, float a1, float a2, SGbool ccw, SGbool fill);
/// @}

/**
 * \name Circle arcs
 */
/// @{
void SG_CALL sgDrawArcRads(float x, float y, float r, float a1, float a2, SGbool ccw, SGbool fill);
void SG_CALL sgDrawArcDegs(float x, float y, float r, float a1, float a2, SGbool ccw, SGbool fill);
/// @}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgDrawPointSetSize(float size);
void SG_CALL SG_HINT_DEPRECATED sgDrawLineSetWidth(float width);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_DRAW_H__
