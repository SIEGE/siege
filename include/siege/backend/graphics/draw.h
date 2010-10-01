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

#ifndef __SIEGE_BACKEND_GRAPHICS_PRIMITIVE_H__
#define __SIEGE_BACKEND_GRAPHICS_PRIMITIVE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmGraphicsDrawPrimitive(void* context, void* texture, SGuint type, SGuint numverts, float* vertices, float* texcoords, float* colors);
    SGuint SG_EXPORT sgmGraphicsDrawSetColor(void* context, float* color);
    SGuint SG_EXPORT sgmGraphicsDrawPointSetSize(void* context, float size);
    //SGuint SG_EXPORT sgmGraphicsDrawPointGetSize(void* context, float* size);
    SGuint SG_EXPORT sgmGraphicsDrawLineSetWidth(void* context, float size);
    //SGuint SG_EXPORT sgmGraphicsDrawLineGetWidth(void* context, float* size);
    //SGuint SG_EXPORT sgmGraphicsDrawLineSetStipple(void* context, SGuint factor, SGuint pattern);
    //SGuint SG_EXPORT sgmGraphicsDrawLineGetStipple(void* context, SGuint* factor, SGuint* pattern);
    //SGuint SG_EXPORT sgmGraphicsDrawPolygonSetStipple(void* context, SGubyte* pattern);
    //SGuint SG_EXPORT sgmGraphicsDrawPolygonGetStipple(void* context*, SGubyte** pattern);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_GRAPHICS_PRIMITIVE_H__
