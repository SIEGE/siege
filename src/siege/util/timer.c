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
#define SG_BUILD_LIBRARY
#include <siege/util/timer.h>
#include <siege/util/time.h>

#include <stdlib.h>

static SGListNode* addTimer(SGList** list, SGTimer* timer)
{
    if(!*list) *list = sgListCreate();
    return sgListAppend(*list, timer);
}
static void remTimer(SGList** list, SGListNode* node)
{
    sgListRemoveNode(*list, node);
    if(!(*list)->head)
    {
        sgListDestroy(*list);
        *list = NULL;
    }
}

SGTimer* SG_EXPORT sgTimerCreate(SGbool pausable)
{
    SGTimer* timer = malloc(sizeof(SGTimer));
    if(!timer) return NULL;

    timer->snode = NULL;
    timer->tnode = NULL;

    timer->interval = 0;
    timer->age = 0;
    timer->prev = sgGetTime();
    timer->func = NULL;
    timer->data = NULL;
    timer->pausable = pausable;
    timer->useTicks = SG_FALSE;

    return timer;
}
void SG_EXPORT sgTimerDestroy(SGTimer* timer)
{
    if(timer->snode)
        remTimer(&_sg_stimerList, timer->tnode);
    if(timer->tnode)
        remTimer(&_sg_timerList, timer->tnode);
    free(timer);
}

void SG_EXPORT sgTimerSetFunction(SGTimer* timer, SGTimerFunction* func, void* data)
{
    timer->func = func;
    timer->data = data;
}

void SG_EXPORT sgTimerPause(SGTimer* timer, SGbool pause)
{
    if(pause && timer->tnode)
    {
        remTimer(&_sg_timerList, timer->tnode);
        timer->tnode = NULL;
    }
    else if(!pause && !timer->tnode)
    {
        timer->tnode = addTimer(&_sg_timerList, timer);
        timer->prev = sgGetTime();
    }
}
void SG_EXPORT sgTimerStop(SGTimer* timer)
{
    sgTimerPause(timer, SG_TRUE);
    timer->age = 0;
}

void SG_EXPORT sgTimerStart(SGTimer* timer, SGulong secs)
{
    sgTimerStart(timer, secs * 1000);
}
void SG_EXPORT sgTimerMStart(SGTimer* timer, SGulong msecs)
{
    sgTimerUStart(timer, msecs * 1000);
}
void SG_EXPORT sgTimerUStart(SGTimer* timer, SGulong usecs)
{
    sgTimerNStart(timer, usecs * 1000);
}
void SG_EXPORT sgTimerNStart(SGTimer* timer, SGulong nsecs)
{
    timer->interval = nsecs;
    timer->age = 0;
    timer->prev = sgGetTime();
    timer->useTicks = SG_FALSE;

    sgTimerPause(timer, SG_FALSE);
}
void SG_EXPORT sgTimerTickStart(SGTimer* timer, SGulong ticks)
{
    timer->interval = ticks;
    timer->age = 0;
    timer->useTicks = SG_TRUE;

    sgTimerPause(timer, SG_FALSE);
}

void SG_EXPORT sgTimerSingle(SGulong secs, SGTimerFunction* func, void* data, SGbool pausable)
{
    sgTimerMSingle(secs * 1000, func, data, pausable);
}
void SG_EXPORT sgTimerMSingle(SGulong msecs, SGTimerFunction* func, void* data, SGbool pausable)
{
    sgTimerUSingle(msecs * 1000, func, data, pausable);
}
void SG_EXPORT sgTimerUSingle(SGulong usecs, SGTimerFunction* func, void* data, SGbool pausable)
{
    sgTimerNSingle(usecs * 1000, func, data, pausable);
}
void SG_EXPORT sgTimerNSingle(SGulong nsecs, SGTimerFunction* func, void* data, SGbool pausable)
{
    SGTimer* timer = sgTimerCreate(pausable);
    if(!timer) return;

    timer->snode = addTimer(&_sg_stimerList, timer);
    sgTimerSetFunction(timer, func, data);
    sgTimerNStart(timer, nsecs);
}
void SG_EXPORT sgTimerTickSingle(SGulong ticks, SGTimerFunction* func, void* data, SGbool pausable)
{
    SGTimer* timer = sgTimerCreate(pausable);
    if(!timer) return;

    timer->snode = addTimer(&_sg_stimerList, timer);
    sgTimerSetFunction(timer, func, data);
    sgTimerTickStart(timer, ticks);
}

void SG_EXPORT sgTimerUpdate(SGTimer* timer, SGbool paused, SGbool tick)
{
    SGulong time = sgGetTime();

    if(paused && timer->pausable)
    {
        timer->prev = time;
        return;
    }

    if(timer->useTicks)
    {
        if(tick)
            timer->age++;
    }
    else
    {
        timer->age += time - timer->prev;
        timer->prev = time;
    }

    if(timer->age >= timer->interval)
    {
        if(timer->func)
            timer->func(timer, timer->data);
        if(timer->snode) /* if it's a single-shot timer, then destroy it */
            sgTimerDestroy(timer);
        else if(timer->interval)
            timer->age = timer->age % timer->interval;
    }
}
void SG_EXPORT sgTimerUpdateAll(SGbool paused, SGbool tick)
{
    if(!_sg_timerList)
        return;

    SGListNode* node;
    SGListNode* next;
    for(node = _sg_timerList->head; node; node = next)
    {
        next = node->next;
        sgTimerUpdate(node->item, paused, tick);
    }
}
