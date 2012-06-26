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

#ifndef __SIEGE_BACKEND_GRAPHICS_SURFACE_H__
#define __SIEGE_BACKEND_GRAPHICS_SURFACE_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceCreate)(void** surface, void* context);
	//SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceCreateTexture)(void** surface, void* context, void* texture);
	//SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceCreateData)(void** surface, void* context, SGuint width, SGuint height, SGuint bpp, void* data);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceDestroy)(void* surface);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceSetTexture)(void* surface, void* texture);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceGetTexture)(void* surface, void** texture);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceSetData)(void* surface, SGuint width, SGuint height, SGuint bpp, void* data);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsSurfaceSetSubData)(void* surface, SGuint x, SGuint y, SGuint width, SGuint height, SGenum bpp, void* data);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceGetData)(void* surface, SGuint* width, SGuint* height, SGuint* bpp, void** data);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceFreeData)(void* data);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceGetSize)(void* surface, SGuint* width, SGuint* height);
    SGenum SG_EXPORT SG_FPTR(sgmGraphicsSurfaceGetBPP)(void* surface, SGenum* bpp);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceDraw)(void* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceTarget)(void* surface);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsSurfaceUntarget)(void* surface);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_GRAPHICS_SURFACE_H__
