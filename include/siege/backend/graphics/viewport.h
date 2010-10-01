/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_BACKEND_GRAPHICS_VIEWPORT_H__
#define __SIEGE_BACKEND_GRAPHICS_VIEWPORT_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmGraphicsViewportCreate(void** viewport, void* context);
    //SGuint SG_EXPORT sgmGraphicsViewportCreateView(void** viewport, void* context, SGuint wx, SGuint wy, SGuint wwidth, SGuint wheight, float x, float y, float width, float height);
    SGuint SG_EXPORT sgmGraphicsViewportDestroy(void* viewport);
    SGuint SG_EXPORT sgmGraphicsViewportSetView(void* viewport, SGuint wx, SGuint wy, SGuint wwidth, SGuint wheight, float x, float y, float width, float height);
    //SGuint SG_EXPORT sgmGraphicsViewportGetView(void* viewport, SGuint* wx, SGuint* wy, SGuint* wwidth, SGuint* wheight, float* x, float* y, float* width, float* height);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_GRAPHICS_VIEWPORT_H__
