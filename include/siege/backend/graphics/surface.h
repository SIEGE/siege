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

#ifndef __SIEGE_BACKEND_GRAPHICS_SURFACE_H__
#define __SIEGE_BACKEND_GRAPHICS_SURFACE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmGraphicsSurfaceCreate(void** surface, void* context);
    //SGuint SG_EXPORT sgmGraphicsSurfaceCreateTexture(void** surface, void* context, void* texture);
    //SGuint SG_EXPORT sgmGraphicsSurfaceCreateData(void** surface, void* context, SGuint width, SGuint height, SGuint bpp, void* data);
    SGuint SG_EXPORT sgmGraphicsSurfaceDestroy(void* surface);
    SGuint SG_EXPORT sgmGraphicsSurfaceSetTexture(void* surface, void* texture);
    SGuint SG_EXPORT sgmGraphicsSurfaceGetTexture(void* surface, void** texture);
    SGuint SG_EXPORT sgmGraphicsSurfaceSetData(void* surface, SGuint width, SGuint height, SGuint bpp, void* data);
    //SGuint SG_EXPORT sgmGraphicsSurfaceGetData(void* surface, SGuint* width, SGuint* height, SGuint* bpp, void** data);
    //SGuint SG_EXPORT sgmGraphicsSurfaceFreeData(void* data);
    SGuint SG_EXPORT sgmGraphicsSurfaceGetSize(void* surface, SGuint* width, SGuint* height);
    SGuint SG_EXPORT sgmGraphicsSurfaceDraw(void* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
    SGuint SG_EXPORT sgmGraphicsSurfaceSetTarget(void* surface);
    //SGuint SG_EXPORT sgmGraphicsSurfaceGetTarget(void** surface);
    SGuint SG_EXPORT sgmGraphicsSurfaceResetTarget(void* surface);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_GRAPHICS_SURFACE_H__
