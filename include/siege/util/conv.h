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

#ifndef __SIEGE_UTIL_CONV_H__
#define __SIEGE_UTIL_CONV_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_BUILD_LIBRARY
#endif // SG_BUILD_LIBRARY

#define SG_CONV_TYPE_UNKNOWN 0
#define SG_CONV_TYPE_CHAR    1
#define SG_CONV_TYPE_WCHAR_T 2
#define SG_CONV_TYPE_UTF8    3
#define SG_CONV_TYPE_UTF16LE 4
#define SG_CONV_TYPE_UTF16BE 5
#define SG_CONV_TYPE_UTF16   SG_CONV_TYPE_UTF16LE /* TODO: should depend on system */
#define SG_CONV_TYPE_UTF32LE 6
#define SG_CONV_TYPE_UTF32BE 7
#define SG_CONV_TYPE_UTF32   SG_CONV_TYPE_UTF32LE /* TODO: should depend on system */
#define SG_CONV_TYPE_LAST    8

//typedef size_t (SGNormalizeFunction)(void* out, const void* in, size_t* inlen);
typedef size_t SG_EXPORT (SGConvFunction)(void* out, const void* in, size_t* inlen, SGbool strict);

typedef struct SGConv
{
    SGConvFunction* func;
    SGenum dst;
    SGenum src;
} SGConv;

SGConv* SG_EXPORT sgConvCreate(SGenum dst, SGenum src);
void SG_EXPORT sgConvDestroy(SGConv* conv);

size_t SG_EXPORT sgConvEstimate(SGConv* conv, size_t inlen);

size_t SG_EXPORT sgConv(SGConv* conv, void* out, size_t outlen, const void* in, size_t inlen, SGbool strict);
size_t SG_EXPORT sgConv2s(SGenum dst, SGenum src, void* out, size_t outlen, const void* in, size_t inlen, SGbool strict);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_CONV_H__
