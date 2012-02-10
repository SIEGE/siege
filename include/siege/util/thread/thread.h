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

#ifndef __SIEGE_UTIL_THREAD_H__
#define __SIEGE_UTIL_THREAD_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define SG_THREAD_INITIAL   0
#define SG_THREAD_RUNNING   1
#define SG_THREAD_SUSPENDED 2
#define SG_THREAD_EXITED    3

struct SGThread;

typedef void SG_EXPORT (SGThreadDestroy)(void);
typedef SGint SG_EXPORT (SGThreadFunction)(void* data);
typedef struct SGThread
{
    void* handle;
    SGThreadFunction* func;
    void* data;
    SGenum status; /* TODO: make status work properly */
    size_t numdtors;
    SGThreadDestroy** dtors;
    // these are used for pthreads
    SGint ret;
    void* sem;
    SGuint susp;
} SGThread;

SGThread* SG_EXPORT sgThreadCreate(size_t ssize, SGThreadFunction* func, void* data);
void SG_EXPORT sgThreadDestroy(SGThread* thread);

void SG_EXPORT sgThreadStart(SGThread* thread);
SGuint SG_EXPORT sgThreadResume(SGThread* thread); /* TODO: make suspend/resume work properly in POSIX systems */
SGuint SG_EXPORT sgThreadSuspend(SGThread* thread);

void SG_EXPORT sgThreadAtExit(SGThreadDestroy* dtor);
//void SG_EXPORT sgThreadYield(void);
void SG_EXPORT sgThreadExit(SGint ret);
SGThread* SG_EXPORT sgThreadGetCurrent(void);

SGint SG_EXPORT sgThreadJoin(SGThread* thread);
void SG_EXPORT sgThreadKill(SGThread* thread, SGint ret);

SGenum SG_EXPORT sgThreadGetStatus(SGThread* thread);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_THREAD_H__
