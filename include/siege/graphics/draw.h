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

#define SG_BYTE     0
#define SG_UBYTE    1
#define SG_SHORT    2
#define SG_USHORT   3
#define SG_INT      4
#define SG_UINT     5
#define SG_FLOAT    6
#define SG_DOUBLE   7

/**
 * \name Graphics primitives types
 */
/// @{
/**
 * Each vertex makes a point.
 */
#define SG_POINTS           0x01
/**
 * Each 2 vertices make a line. The number of passed vertices must be even.
 */
#define SG_LINES            0x02
/**
 * Last vertex of previous line becomes the first vertex of the next one, drawing a connected line defined by the set of vertices.
 * \sa
 *    SG_TRIANGLE_STRIP
 *    SG_QUAD_STRIP
 */
#define SG_LINE_STRIP       0x03
/**
 * The first vertex is the "origin" for all the lines.
 * \sa
 *    SG_TRIANGLE_FAN
 */
#define SG_LINE_FAN         0x04
/**
 * Lines are created in a loop. This is similar to \ref SG_LINE_STRIP "SG_LINE_STRIP", except that the last and first vertex become connected by a line.
 * \sa
 *    SG_LINE_STRIP
 */
#define SG_LINE_LOOP        0x05
/**
 * Each 3 vertices make a triangle. The number of passed vertices must be a multiple of 3.
 */
#define SG_TRIANGLES        0x06
/**
 * Last 2 vertices of the previous triangle become the first two vertices of the next one, making a connected hull. This is analogous to \ref SG_LINE_STRIP "SG_LINE_STRIP".
 * \sa
 *    SG_LINE_STRIP
 */
#define SG_TRIANGLE_STRIP   0x07
/**
 * The first vertex becomes a "common point" between all the triangles. This is analogous to \ref SG_LINE_FAN "SG_LINE_FAN".
 * \sa
 *    SG_LINE_FAN
 */
#define SG_TRIANGLE_FAN     0x08
//#define SG_TRIANGLE_LOOP        0x09
/**
 * Each 4 vertices make a quad. The number of passed vertices must be a multiple of 4.
 */
#define SG_QUADS                0x0A
/**
 * Last 2 vertices of the previous quad become the first two vertices of the next one. This is analogous to \ref SG_LINE_STRIP "SG_LINE_STRIP" and \ref SG_TRIANGLE_STRIP "SG_TRIANGLE_STRIP".
 * \sa
 *    SG_LINE_STRIP
 *    SG_TRIANGLE_STRIP
 */
#define SG_QUAD_STRIP           0x0B
//#define SG_QUAD_FAN             0x0C
//#define SG_QUAD_LOOP            0x0D

/**
 * Create a convex polygon - the vertices passed are assumed to form one.
 */
#define SG_CONVEX_POLYGON       0x10
/**
 * Create polygon that is possibly concave (but not self-intersecting).
 * \note
 *    The vertices passed may be implicitly converted to a series of convex polygons.
 * \note
 *    It is perfectly fine (if not best for performance) to pass a convex polygon as a concave one.
 */
#define SG_CONCAVE_POLYGON      0x20
/**
 * Create a polygon that is possibly self-intersecting.
 * \note
 *    The vertices passed may be implicitly converted to a series of convex polygons.
 * \note
 *    It is perfectly fine (if not best for performance) to pass non-intersecting polygon as an intersecting one.
 */
#define SG_INTERSECTING_POLYGON 0x30
/// @}

#define SG_FUNC_ZERO                    0x00
#define SG_FUNC_ONE                     0x01
#define SG_FUNC_SRC_COLOR               0x02
#define SG_FUNC_ONE_MINUS_SRC_COLOR     0x03
#define SG_FUNC_DST_COLOR               0x04
#define SG_FUNC_ONE_MINUS_DST_COLOR     0x05
#define SG_FUNC_SRC_ALPHA               0x06
#define SG_FUNC_ONE_MINUS_SRC_ALPHA     0x07
#define SG_FUNC_DST_ALPHA               0x08
#define SG_FUNC_ONE_MINUS_DST_ALPHA     0x09

#define SG_EQUATION_ADD                 0x00
#define SG_EQUATION_SUBTRACT            0x01
#define SG_EQUATION_REVERSE_SUBTRACT    0x02
#define SG_EQUATION_MIN                 0x03
#define SG_EQUATION_MAX                 0x04

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
