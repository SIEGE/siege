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

#ifndef __SIEGE_UTIL_THREADKEY_H__
#define __SIEGE_UTIL_THREADKEY_H__

#include "../common.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct SGThreadKey
{
    void* handle;
} SGThreadKey;

SGThreadKey* SG_EXPORT sgThreadKeyCreate(void);
void SG_EXPORT sgThreadKeyDestroy(SGThreadKey* key);

void SG_EXPORT sgThreadKeySetVal(SGThreadKey* key, void* val);
void* SG_EXPORT sgThreadKeyGetVal(SGThreadKey* key);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_THREADKEY_H__
