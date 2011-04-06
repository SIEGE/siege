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

#ifndef __SIEGE_UTIL_CONV_H__
#define __SIEGE_UTIL_CONV_H__

#include "../common.h"

#ifdef SG_BUILD_LIBRARY
#endif // SG_BUILD_LIBRARY

typedef struct SGConv
{
	void* handle;
} SGConv;

SGConv* SG_EXPORT sgConvCreate(const char* from, const char* to);
void SG_EXPORT sgConvDestroy(SGConv* conv);
void* SG_EXPORT sgConv(SGConv* conv, size_t* outlen, const void* str, size_t len);

void* SG_EXPORT sgConv2s(const char* from, const char* to, size_t* outlen, const void* str, size_t len);

#endif // __SIEGE_UTIL_CONV_H__
