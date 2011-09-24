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

#define SG_BUILD_LIBRARY
#include <siege/util/link.h>
#include <siege/modules/modules.h>
#include <siege/modules/graphics.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void SG_EXPORT _sgModuleLoadGraphics(SGLibrary* lib)
{
	void* fptr;
	/// Graphics
	_SG_BIND(sgmGraphicsContextCreate);
	_SG_BIND(sgmGraphicsContextDestroy);
	_SG_BIND(sgmGraphicsContextResize);
	_SG_BIND(sgmGraphicsContextClear);

	_SG_BIND(sgmGraphicsViewportCreate);
	//_SG_BIND(sgmGraphicsViewportCreateView);
	_SG_BIND(sgmGraphicsViewportDestroy);
	_SG_BIND(sgmGraphicsViewportSetView);
	//_SG_BIND(sgmGraphicsViewportGetView);

	_SG_BIND(sgmGraphicsSurfaceCreate);
	//_SG_BIND(sgmGraphicsSurfaceCreateTexture);
	//_SG_BIND(sgmGraphicsSurfaceCreateData);
	_SG_BIND(sgmGraphicsSurfaceDestroy);
	_SG_BIND(sgmGraphicsSurfaceSetTexture);
	_SG_BIND(sgmGraphicsSurfaceGetTexture);
	_SG_BIND(sgmGraphicsSurfaceSetData);
	_SG_BIND(sgmGraphicsSurfaceGetData);
	_SG_BIND(sgmGraphicsSurfaceFreeData);
	_SG_BIND(sgmGraphicsSurfaceGetSize);
	_SG_BIND(sgmGraphicsSurfaceDraw);
	_SG_BIND(sgmGraphicsSurfaceSetTarget);
	//_SG_BIND(sgmGraphicsSurfaceGetTarget);
	_SG_BIND(sgmGraphicsSurfaceResetTarget);

	_SG_BIND(sgmGraphicsTextureCreate);
	//_SG_BIND(sgmGraphicsTextureCreateData);
	_SG_BIND(sgmGraphicsTextureDestroy);
	_SG_BIND(sgmGraphicsTextureSetData);
	_SG_BIND(sgmGraphicsTextureGetData);
	_SG_BIND(sgmGraphicsTextureFreeData);
	_SG_BIND(sgmGraphicsTextureGetSize);
	_SG_BIND(sgmGraphicsTextureDraw);

    _SG_BIND(sgmGraphicsTextureSetWrap);
    _SG_BIND(sgmGraphicsTextureSetInterpolation);

	_SG_BIND(sgmGraphicsDrawPrimitive);
	_SG_BIND(sgmGraphicsDrawSetColor);
	_SG_BIND(sgmGraphicsDrawPointSetSize);
	//bindFunc(sgmGraphicsDrawPointGetSize)("sgmGraphicsDrawPointGetSize", lib);
	_SG_BIND(sgmGraphicsDrawLineSetWidth);
	//bindFunc(sgmGraphicsDrawLineGetWidth)("sgmGraphicsDrawLineGetWidth", lib);
	//bindFunc(sgmGraphicsDrawLineSetStipple)("sgmGraphicsDrawLineSetStipple", lib);
	//bindFunc(sgmGraphicsDrawLineGetStipple)("sgmGraphicsDrawLineGetStipple", lib);
	//bindFunc(sgmGraphicsDrawPolygonSetStipple)("sgmGraphicsDrawPolygonSetStipple", lib);
	//bindFunc(sgmGraphicsDrawPolygonGetStipple)("sgmGraphicsDrawPolygonGetStipple", lib);

    _SG_BIND(sgmGraphicsDrawSetBlendFunc);
    _SG_BIND(sgmGraphicsDrawSetBlendEquation);

    _SG_BIND(sgmGraphicsDrawSetDepthTest);
    _SG_BIND(sgmGraphicsDrawSetSmooth);

	/// Graphics Load
	_SG_BIND(sgmGraphicsLoadFile);
	//_SG_BIND(sgmGraphicsLoadStream);
	_SG_BIND(sgmGraphicsLoadFreeData);
}

