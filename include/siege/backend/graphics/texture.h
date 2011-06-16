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

#ifndef __SIEGE_BACKEND_GRAPHICS_TEXTURE_H__
#define __SIEGE_BACKEND_GRAPHICS_TEXTURE_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsTextureCreate)(void** texture, void* context);
	//SGuint SG_EXPORT SG_FPTR(sgmGraphicsTextureCreateData)(void** texture, void* context, SGuint width, SGuint height, SGuint bpp, void* data);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsTextureDestroy)(void* texture);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsTextureSetData)(void* texture, SGuint width, SGuint height, SGuint bpp, void* data);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsTextureGetData)(void* texture, SGuint* width, SGuint* height, SGuint* bpp, void** data);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsTextureFreeData)(void* data);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsTextureGetSize)(void* texture, SGuint* width, SGuint* height);
	SGuint SG_EXPORT SG_FPTR(sgmGraphicsTextureDraw)(void* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_GRAPHICS_TEXTURE_H__
