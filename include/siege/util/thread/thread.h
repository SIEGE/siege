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

typedef void SG_CALL (SGThreadDestroy)(void);
typedef SGint SG_CALL (SGThreadFunction)(void* data);
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

SGThread* SG_CALL sgThreadCreate(size_t ssize, SGThreadFunction* func, void* data);
void SG_CALL sgThreadDestroy(SGThread* thread);

void SG_CALL sgThreadStart(SGThread* thread);
SGuint SG_CALL sgThreadResume(SGThread* thread); /* TODO: make suspend/resume work properly in POSIX systems */
SGuint SG_CALL sgThreadSuspend(SGThread* thread);

void SG_CALL sgThreadAtExit(SGThreadDestroy* dtor);
//void SG_CALL sgThreadYield(void);
void SG_CALL sgThreadExit(SGint ret);
SGThread* SG_CALL sgThreadGetMain(void);
SGThread* SG_CALL sgThreadGetCurrent(void);

SGint SG_CALL sgThreadJoin(SGThread* thread);
void SG_CALL sgThreadKill(SGThread* thread, SGint ret);

SGenum SG_CALL sgThreadGetStatus(SGThread* thread);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_THREAD_H__
