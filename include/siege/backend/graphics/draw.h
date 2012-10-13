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

#ifndef __SIEGE_BACKEND_GRAPHICS_DRAW_H__
#define __SIEGE_BACKEND_GRAPHICS_DRAW_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsSetVertexPointer)(void* context, SGubyte size, SGenum type, size_t stride, const void* ptr);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsSetColorPointer)(void* context, SGubyte size, SGenum type, size_t stride, const void* ptr);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsSetTexCoordPointer)(void* context, SGenum type, size_t stride, const void* ptr);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsSetIndexPointer)(void* context, SGenum type, size_t stride, const void* ptr);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawArrays)(void* context, void* texture, SGenum mode, size_t first, size_t count);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawElements)(void* context, void* texture, SGenum mode, size_t count, SGenum type, const void* indices);

    SGuint SG_EXPORT SG_HINT_DEPRECATED SG_FPTR(sgmGraphicsDrawPrimitive)(void* context, void* texture, SGenum type, size_t numverts, float* vertices, float* texcoords, float* colors);
    SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawSetColor)(void* context, float* color);
    SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawPointSetSize)(void* context, float size);
    //SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawPointGetSize)(void* context, float* size);
    SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawLineSetWidth)(void* context, float size);
    //SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawLineGetWidth)(void* context, float* size);
    //SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawLineSetStipple)(void* context, SGuint factor, SGuint pattern);
    //SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawLineGetStipple)(void* context, SGuint* factor, SGuint* pattern);
    //SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawPolygonSetStipple)(void* context, SGubyte* pattern);
    //SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawPolygonGetStipple)(void* context*, SGubyte** pattern);
    SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawSetBlendFunc)(void* context, SGenum src, SGenum dst);
    SGuint SG_EXPORT SG_FPTR(sgmGraphicsDrawSetBlendEquation)(void* context, SGenum equation);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetDepthFunc)(void* context, SGenum func);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetDepthTest)(void* context, SGbool test);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetAlphaFunc)(void* context, SGenum func, float ref);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetAlphaTest)(void* context, SGbool test);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetPointSmooth)(void* context, SGbool smooth);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetLineSmooth)(void* context, SGbool smooth);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsDrawSetPolygonSmooth)(void* context, SGbool smooth);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_GRAPHICS_DRAW_H__
