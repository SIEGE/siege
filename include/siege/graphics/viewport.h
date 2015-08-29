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
#include "../util/irect.h"
#include "camera.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGViewport
{
    SGCamera* camera;
    SGIRect rect;
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
SGViewport* _sg_viewCurr;
#endif // SG_BUILD_LIBRARY

SGbool SG_CALL _sgViewportInit(void);
SGbool SG_CALL _sgViewportDeinit(void);

SGViewport* SG_CALL sgViewportCreateR(SGCamera* camera, SGIRect rect);
void SG_CALL sgViewportDestroy(SGViewport* viewport);

void SG_CALL sgViewportSetRect(SGViewport* viewport, SGIRect rect);
SGIRect SG_CALL sgViewportGetRect(SGViewport* viewport);

void SG_CALL sgViewportSetPos2iv(SGViewport* viewport, SGIVec2 pos);
void SG_CALL sgViewportSetSize2iv(SGViewport* viewport, SGIVec2 size);

void SG_CALL sgViewportUse(SGViewport* viewport);

SGbool SG_CALL sgViewportPointInside2fv(SGViewport* viewport, SGVec2 point);

SGVec2 SG_CALL sgViewportNormalToWindow2fv(SGViewport* viewport, SGVec2 npoint);
SGVec2 SG_CALL sgViewportWindowToNormal2fv(SGViewport* viewport, SGVec2 wpoint);

// TODO: Move these out of viewport?
SGVec2 SG_CALL sgViewportLocalToWindow2fv(SGViewport* viewport, SGVec2 lpoint);
SGVec2 SG_CALL sgViewportWindowToLocal2fv(SGViewport* viewport, SGVec2 wpoint);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_VIEWPORT_H__
