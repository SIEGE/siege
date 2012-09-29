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

#ifndef __SIEGE_BACKEND_FONTS_CHARS_H__
#define __SIEGE_BACKEND_FONTS_CHARS_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    SGenum SG_EXPORT SG_FPTR(sgmFontsCharsCreate)(void* face, const SGdchar* chars, size_t numchars, float* width, float* height, float* prex, float* prey, float* postx, float* posty, size_t* datawidth, size_t* dataheight, void** data);
    SGenum SG_EXPORT SG_FPTR(sgmFontsCharsFreeData)(void* data);
    SGenum SG_EXPORT SG_FPTR(sgmFontsCharsGetKerning)(void* face, const SGdchar* chars, size_t numchars, float* kerning);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_FONTS_CHARS_H__
