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

#ifndef __SIEGE_BACKEND_FONTS_FACE_H__
#define __SIEGE_BACKEND_FONTS_FACE_H__

#include "../../common.h"
#include "../util/stream.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    SGenum SG_EXPORT SG_FPTR(sgmFontsFaceCreate)(void** face, SGStream* stream);
    SGenum SG_EXPORT SG_FPTR(sgmFontsFaceDestroy)(void* face);
    SGenum SG_EXPORT SG_FPTR(sgmFontsFaceSetHeight)(void* face, float height, SGuint dpi);
    SGenum SG_EXPORT SG_FPTR(sgmFontsFaceGetMetrics)(void* face, float* ascent, float* descent, float* linegap);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_FONTS_FACE_H__
