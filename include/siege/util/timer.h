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
#include "list.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

struct SGTimer;

typedef void SG_EXPORT SGTimerFunction(struct SGTimer* timer, void* data);

typedef struct SGTimer
{
    SGListNode* snode;
    SGListNode* tnode;
    SGulong interval;
    SGulong age;
    SGulong prev;
    SGTimerFunction* func;
    void* data;
    SGbool pausable;
    SGbool useTicks;
} SGTimer;

#ifdef SG_BUILD_LIBRARY
SGList* _sg_stimerList;
SGList* _sg_timerList;
#endif /* SG_BUILD_LIBRARY */

SGTimer* SG_EXPORT sgTimerCreate(SGbool pausable); //< pausable not related to sgTimerPause() down below
void SG_EXPORT sgTimerDestroy(SGTimer* timer);

void SG_EXPORT sgTimerSetFunction(SGTimer* timer, SGTimerFunction* func, void* data);

void SG_EXPORT sgTimerPause(SGTimer* timer, SGbool pause);
void SG_EXPORT sgTimerStop(SGTimer* timer);

void SG_EXPORT sgTimerStart(SGTimer* timer, SGulong secs);
void SG_EXPORT sgTimerMStart(SGTimer* timer, SGulong msecs);
void SG_EXPORT sgTimerUStart(SGTimer* timer, SGulong usecs);
void SG_EXPORT sgTimerNStart(SGTimer* timer, SGulong nsecs);
void SG_EXPORT sgTimerTickStart(SGTimer* timer, SGulong ticks);

void SG_EXPORT sgTimerSingle(SGulong secs, SGTimerFunction* func, void* data, SGbool pausable);
void SG_EXPORT sgTimerMSingle(SGulong msecs, SGTimerFunction* func, void* data, SGbool pausable);
void SG_EXPORT sgTimerUSingle(SGulong usecs, SGTimerFunction* func, void* data, SGbool pausable);
void SG_EXPORT sgTimerNSingle(SGulong nsecs, SGTimerFunction* func, void* data, SGbool pausable);
void SG_EXPORT sgTimerTickSingle(SGulong ticks, SGTimerFunction* func, void* data, SGbool pausable);

/*
 * TODO: Invoke timer->func(...) on their respective threads.
 *
 * TODO: If, say, interval is 1 and age is 10, should this call the timer 10
 * times or only once? In other words, should it attempt to "catch up"?
 * Currently, it does NOT attempt to do so.
 */
void SG_EXPORT sgTimerUpdate(SGTimer* timer, SGbool paused, SGbool tick);
void SG_EXPORT sgTimerUpdateAll(SGbool paused, SGbool tick);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_TIMER_H__
