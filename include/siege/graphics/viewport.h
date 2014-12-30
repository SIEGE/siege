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

#ifndef __SIEGE_GRAPHICS_VIEWPORT_H__
#define __SIEGE_GRAPHICS_VIEWPORT_H__
#include "../common.h"
#include "../util/list.h"
#include "../util/rcount.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGViewport
{
    SGRCount cnt;

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

SGbool SG_CALL _sgViewportInit(void);
SGbool SG_CALL _sgViewportDeinit(void);

SGViewport* SG_CALL sgViewportCreate4i4f(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey);
SGViewport* SG_CALL sgViewportCreate4i(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey);
SGViewport* SG_CALL sgViewportCreate(void);
void SG_CALL sgViewportForceDestroy(SGViewport* viewport);

void SG_CALL sgViewportRelease(SGViewport* viewport);
void SG_CALL sgViewportLock(SGViewport* viewport);
void SG_CALL sgViewportUnlock(SGViewport* viewport);

void SG_CALL sgViewportSet4i4f(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey);
void SG_CALL sgViewportSet4i(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey);
void SG_CALL sgViewportReset(SGViewport* viewport);

void SG_CALL sgViewportSetWPos(SGViewport* viewport, SGuint wposx, SGuint wposy);
void SG_CALL sgViewportSetWSize(SGViewport* viewport, SGuint wsizex, SGuint wsizey);
void SG_CALL sgViewportSetPos(SGViewport* viewport, float posx, float posy);
void SG_CALL sgViewportSetSize(SGViewport* viewport, float sizex, float sizey);
void SG_CALL sgViewportZoomCentered(SGViewport* viewport, float factor);

SGbool SG_CALL sgViewportInsideWindow(SGViewport* viewport, float x, float y);
SGbool SG_CALL sgViewportInsideLocal(SGViewport* viewport, float x, float y);

void SG_CALL sgViewportLocalToWindow(SGViewport* viewport, float* wx, float* wy, float lx, float ly);
void SG_CALL sgViewportWindowToLocal(SGViewport* viewport, float* lx, float* ly, float wx, float wy);

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgViewportDestroy(SGViewport* viewport);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_VIEWPORT_H__
