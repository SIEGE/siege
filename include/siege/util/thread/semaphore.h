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

#ifndef __SIEGE_UTIL_THREAD_SEMAPHORE_H__
#define __SIEGE_UTIL_THREAD_SEMAPHORE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGSemaphore
{
    void* handle;
} SGSemaphore;

SGSemaphore* SG_EXPORT sgSemaphoreCreate(SGuint init, SGuint max);
void SG_EXPORT sgSemaphoreDestroy(SGSemaphore* sem);

SGbool SG_EXPORT sgSemaphoreTryWait(SGSemaphore* sem);
void SG_EXPORT sgSemaphoreWait(SGSemaphore* sem);
void SG_EXPORT sgSemaphorePost(SGSemaphore* sem);
void SG_EXPORT sgSemaphoreSignal(SGSemaphore* sem);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_SEMAPHORE_H__
