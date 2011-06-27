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

#ifndef __SIEGE_BACKEND_FONTS_CONV_H__
#define __SIEGE_BACKEND_FONTS_CONV_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
	SGenum SG_EXPORT SG_FPTR(sgmFontsConvCreate)(void** conv, const char* from, const char* to);
	SGenum SG_EXPORT SG_FPTR(sgmFontsConvDestroy)(void* conv);
	SGenum SG_EXPORT SG_FPTR(sgmFontsConv)(void* conv, void** outbuf, size_t* outlen, void* inbuf, size_t inlen);
	SGenum SG_EXPORT SG_FPTR(sgmFontsConvFreeData)(void* ptr);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_FONTS_CONV_H__