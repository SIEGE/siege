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

#ifndef __SIEGE_UTIL_ARRAY_H__
#define __SIEGE_UTIL_ARRAY_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef void SG_EXPORT (*SGMapFunction)(void* result, void* ptr);
typedef void SG_EXPORT (*SGFoldFunction)(void* result, void* ptr1, void* ptr2);

void* SG_EXPORT sgMap(void* to, size_t tosize, void* base, size_t size, size_t num, SGMapFunction func);

void* SG_EXPORT sgRFold(void* base, size_t size, size_t num, SGFoldFunction func);
void* SG_EXPORT sgLFold(void* base, size_t size, size_t num, SGFoldFunction func);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_ARRAY_H__
