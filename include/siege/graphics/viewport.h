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

#ifndef __SIEGE_GRAPHICS_VIEWPORT_H__
#define __SIEGE_GRAPHICS_VIEWPORT_H__
#include "../common.h"
#include "../util/list.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGViewport
{
	void* handle;

	SGuint wposx;
	SGuint wposy;
	SGuint wsizex;
	SGuint wsizey;
	float posx;
	float posy;
	float sizex;
	float sizey;
} SGViewport;

#ifdef SG_BUILD_LIBRARY
SGList* _sg_viewList;
SGViewport* _sg_viewMain;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgViewportInit(void);
SGbool SG_EXPORT _sgViewportDeinit(void);

SGViewport* SG_EXPORT sgViewportCreate4i4f(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey);
SGViewport* SG_EXPORT sgViewportCreate4i(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey);
SGViewport* SG_EXPORT sgViewportCreate(void);
void SG_EXPORT sgViewportDestroy(SGViewport* viewport);
void SG_EXPORT sgViewportSet4i4f(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey);
void SG_EXPORT sgViewportSet4i(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey);
void SG_EXPORT sgViewportReset(SGViewport* viewport);

void SG_EXPORT sgViewportSetWPos(SGViewport* viewport, SGuint wposx, SGuint wposy);
void SG_EXPORT sgViewportSetWSize(SGViewport* viewport, SGuint wsizex, SGuint wsizey);
void SG_EXPORT sgViewportSetPos(SGViewport* viewport, float posx, float posy);
void SG_EXPORT sgViewportSetSize(SGViewport* viewport, float sizex, float sizey);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_VIEWPORT_H__
