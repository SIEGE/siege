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

#ifndef __SIEGE_BACKEND_GRAPHICS_CONTEXT_H__
#define __SIEGE_BACKEND_GRAPHICS_CONTEXT_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmGraphicsContextCreate(void** context, SGuint width, SGuint height, SGuint bpp);
    SGuint SG_EXPORT sgmGraphicsContextDestroy(void* context);
    SGuint SG_EXPORT sgmGraphicsContextResize(void* context, SGuint width, SGuint height);
    //SGuint SG_EXPORT sgmGraphicsContextClear(void* context);
    SGuint SG_EXPORT sgmGraphicsContextClearColor(void* context, float* color);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_GRAPHICS_CONTEXT_H__
