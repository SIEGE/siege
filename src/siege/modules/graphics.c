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
	_SG_BINDS(_sg_modGraphics, sgmGraphicsContextCreate);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsContextDestroy);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsContextResize);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsContextClear);

	_SG_BINDS(_sg_modGraphics, sgmGraphicsViewportCreate);
	//_SG_BINDS(_sg_modGraphics, sgmGraphicsViewportCreateView);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsViewportDestroy);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsViewportSetView);
	//_SG_BINDS(_sg_modGraphics, sgmGraphicsViewportGetView);

	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceCreate);
	//_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceCreateTexture);
	//_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceCreateData);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceDestroy);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceSetTexture);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceGetTexture);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceSetData);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceGetData);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceFreeData);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceGetSize);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceDraw);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceSetTarget);
	//_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceGetTarget);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsSurfaceResetTarget);

	_SG_BINDS(_sg_modGraphics, sgmGraphicsTextureCreate);
	//_SG_BINDS(_sg_modGraphics, sgmGraphicsTextureCreateData);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsTextureDestroy);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsTextureSetData);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsTextureGetData);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsTextureFreeData);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsTextureGetSize);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsTextureDraw);

	_SG_BINDS(_sg_modGraphics, sgmGraphicsDrawPrimitive);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsDrawSetColor);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsDrawPointSetSize);
	//bindFunc(sgmGraphicsDrawPointGetSize)("sgmGraphicsDrawPointGetSize", lib);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsDrawLineSetWidth);
	//bindFunc(sgmGraphicsDrawLineGetWidth)("sgmGraphicsDrawLineGetWidth", lib);
	//bindFunc(sgmGraphicsDrawLineSetStipple)("sgmGraphicsDrawLineSetStipple", lib);
	//bindFunc(sgmGraphicsDrawLineGetStipple)("sgmGraphicsDrawLineGetStipple", lib);
	//bindFunc(sgmGraphicsDrawPolygonSetStipple)("sgmGraphicsDrawPolygonSetStipple", lib);
	//bindFunc(sgmGraphicsDrawPolygonGetStipple)("sgmGraphicsDrawPolygonGetStipple", lib);

	/// Graphics Load
	_SG_BINDS(_sg_modGraphics, sgmGraphicsLoadFile);
	//_SG_BINDS(_sg_modGraphics, sgmGraphicsLoadStream);
	_SG_BINDS(_sg_modGraphics, sgmGraphicsLoadFreeData);
}

SGModuleGraphics* SG_EXPORT sgModuleGetGraphics(void)
{
	return &_sg_modGraphics;
}

SGuint SG_EXPORT _sgNextPower2(SGuint num)
{
	SGuint i;
	for(i = 2; i < num; i <<= 1)
	{
	}
	return i;
}

SGubyte* SG_EXPORT _sgGraphicsToCanvasSize(SGuint width, SGuint height, SGuint bpp, SGubyte* data)
{
	SGuint awidth = _sgNextPower2(width);
	SGuint aheight = _sgNextPower2(height);
	SGuint bypp;
	switch(bpp)
	{
		case 0:
			fprintf(stderr, "Getting bpp from window unimplemented, using 24\n");
			bypp = 3;
			break;
		case 8:
			bypp = 1;
			break;
		case 15:
			bypp = 2;
			break;
		case 16:
			bypp = 2;
			break;
		case 24:
			bypp = 3;
			break;
		case 32:
			bypp = 4;
			break;
		default:
			fprintf(stderr, "Bad bid depth\n");
			return NULL;
	}
	SGubyte* newData = malloc(awidth * aheight * bypp);
	if((awidth == width) && (aheight == height))
		return memcpy(newData, data, width * height * bypp);

	SGuint x;
	SGuint y;
	for(y = 0; y < height; y++)
		for(x = 0; x < width; x++)
			memcpy(&newData[bypp * (x + y * awidth)], &data[bypp * (x + y * width)], bypp);
	return newData;
}

