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

#ifndef __SIEGE_GRAPHICS_ATLAS_H__
#define __SIEGE_GRAPHICS_ATLAS_H__

#include "../common.h"
#include "texture.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGAtlas
{
    size_t width;
    size_t height;
    SGenum bpp;
    void* data;
} SGAtlas;

void SG_EXPORT sgAtlasGetSize(SGAtlas* atlas, size_t* width, size_t* height);
size_t SG_EXPORT sgAtlasGetWidth(SGAtlas* atlas);
size_t SG_EXPORT sgAtlasGetHeight(SGAtlas* atlas);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_ATLAS_H__
