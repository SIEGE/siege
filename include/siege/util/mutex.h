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

#ifndef __SIEGE_UTIL_MUTEX_H__
#define __SIEGE_UTIL_MUTEX_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGMutex
{
    void* handle;
} SGMutex;

SGMutex* SG_EXPORT sgMutexCreate(void);
void SG_EXPORT sgMutexDestroy(SGMutex* mutex);

SGbool SG_EXPORT sgMutexTryLock(SGMutex* mutex);
void SG_EXPORT sgMutexLock(SGMutex* mutex);
void SG_EXPORT sgMutexUnlock(SGMutex* mutex);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_MUTEX_H__
