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

#ifndef __SIEGE_MODULES_GRAPHICS_H__
#define __SIEGE_MODULES_GRAPHICS_H__
#include "../common.h"
#include "../util/link.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_BUILD_LIBRARY

#define SG_FPTR(name) (*p##name)
#include "../backend/graphics/context.h"
#include "../backend/graphics/draw.h"
#include "../backend/graphics/surface.h"
#include "../backend/graphics/texture.h"
#include "../backend/graphics/viewport.h"
#include "../backend/graphics/load.h"
#undef SG_FPTR

#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sgModuleLoadGraphics(SGLibrary* lib);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_MODULES_GRAPHICS_H__
