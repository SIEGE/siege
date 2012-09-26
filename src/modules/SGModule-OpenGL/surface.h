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

#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "common.h"
#include "texture.h"

typedef struct SurfaceData
{
    void* context;

    struct TextureData* texture;

    int isFBO;
    GLuint fboid;
    GLuint rbid;
} SurfaceData;

#endif // __SURFACE_H__
