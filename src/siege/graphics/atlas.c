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

#define SG_BUILD_LIBRARY
#include <siege/graphics/atlas.h>

#include <stdlib.h>
#include <stdio.h>

void SG_EXPORT sgAtlasGetSize(SGAtlas* atlas, size_t* width, size_t* height)
{
    if(width) *width = atlas->width;
    if(height) *height = atlas->height;
}
size_t SG_EXPORT sgAtlasGetWidth(SGAtlas* atlas)
{
    return atlas->width;
}
size_t SG_EXPORT sgAtlasGetHeight(SGAtlas* atlas)
{
    return atlas->height;
}
