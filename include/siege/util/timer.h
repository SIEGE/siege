/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_UTIL_TIMER_H__
#define __SIEGE_UTIL_TIMER_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

struct SGTimer;

typedef void SG_EXPORT SGTimerFunction(struct SGTimer* timer, void* data);

typedef struct SGTimer
{
    char buf[1]; /* placeholder */
} SGTimer;

SGTimer* sgTimerCreate(SGbool pausable); //< pausable not related to sgTimerPause() down below

void sgTimerSetFunction(SGTimer* timer, SGTimerFunction* func, void* data);
void sgTimerPause(SGTimer* timer, SGbool pause);

void sgTimerStop(SGTimer* timer);

void sgTimerSingle(SGulong secs, SGTimerFunction* func, void* data);
void sgTimerMSingle(SGulong msecs, SGTimerFunction* func, void* data);
void sgTimerUSingle(SGulong usecs, SGTimerFunction* func, void* data);
void sgTimerNSingle(SGulong nsecs, SGTimerFunction* func, void* data);

void sgTimerStart(SGTimer* timer, SGulong secs);
void sgTimerMStart(SGTimer* timer, SGulong msecs);
void sgTimerUStart(SGTimer* timer, SGulong usecs);
void sgTimerNStart(SGTimer* timer, SGulong nsecs);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_TIMER_H__
