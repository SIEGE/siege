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
#include <siege/util/thread.h>

#include <stdlib.h>

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
static DWORD WINAPI _sgThreadEntry(LPVOID param)
{
    SGThread* thread = param;
    return thread->func(thread, thread->data);
}
#else
#endif

SGThread* SG_EXPORT sgThreadCreate(size_t ssize, SGThreadFunction* func, void* data)
{
    SGThread* thread = malloc(sizeof(SGThread));
    if(!thread)
        return NULL;

    thread->func = func;
    thread->data = data;
    thread->status = SG_THREAD_INITIAL;
    thread->rbuf = 0;

#ifdef __WIN32__
    thread->handle = CreateThread(NULL, ssize, _sgThreadEntry, thread, CREATE_SUSPENDED, NULL);
#else
    /* TODO */
#endif

    return thread;
}
void SG_EXPORT sgThreadDestroy(SGThread* thread)
{
    if(!thread)
        return;
#ifdef __WIN32__
    CloseHandle(thread->handle);
#else
    /* TODO */
#endif
    free(thread);
}

void SG_EXPORT sgThreadStart(SGThread* thread)
{
    if(thread->status != SG_THREAD_INITIAL)
        return;

#ifdef __WIN32__
    ResumeThread(thread->handle);
    thread->status = SG_THREAD_RUNNING;
#else
    /* TODO */
#endif
}
SGuint SG_EXPORT sgThreadResume(SGThread* thread)
{
#ifdef __WIN32__
    SGuint ret = ResumeThread(thread->handle);
    if(ret <= 1)
        thread->status = SG_THREAD_RUNNING;
    return ret;
#else
    /* TODO */
#endif
}
SGuint SG_EXPORT sgThreadSuspend(SGThread* thread)
{
#ifdef __WIN32__
    SGuint ret = SuspendThread(thread->handle);
    thread->status = SG_THREAD_SUSPENDED;
    return ret;
#else
    /* TODO */
#endif
}

void SG_EXPORT sgThreadYield(SGThread* thread)
{
#ifdef __WIN32__
    SwitchToThread();
#else
    /* TODO */
#endif
}
void SG_EXPORT sgThreadExit(SGThread* thread, SGint ret)
{
#ifdef __WIN32__
    thread->status = SG_THREAD_EXITED;
    ExitThread(ret);
#else
    /* TODO */
#endif
}

SGint SG_EXPORT sgThreadJoin(SGThread* thread)
{
#ifdef __WIN32__
    WaitForSingleObject(thread->handle, INFINITE);
    thread->status = SG_THREAD_EXITED;
    DWORD ret;
    GetExitCodeThread(thread->handle, &ret);
    return ret;
#else
    /* TODO */
#endif
}
void SG_EXPORT sgThreadKill(SGThread* thread, SGint ret)
{
#ifdef __WIN32__
    thread->status = SG_THREAD_EXITED;
    TerminateThread(thread->handle, ret);
#else
    /* TODO */
#endif
}
/*SGenum SG_EXPORT sgThreadGetStatus(SGThread* thread)
{
    return thread->status;
}*/

SGMutex* SG_EXPORT sgMutexCreate(void)
{
    SGMutex* mutex = malloc(sizeof(SGMutex));
    if(!mutex)
        return NULL;

#ifdef __WIN32__
    mutex->handle = CreateMutex(NULL, FALSE, NULL);
#else
    /* TODO */
#endif

    return mutex;
}
void SG_EXPORT sgMutexDestroy(SGMutex* mutex)
{
    if(!mutex)
        return;
#ifdef __WIN32__
    CloseHandle(mutex->handle);
#else
    /* TODO */
#endif
    free(mutex);
}

void SG_EXPORT sgMutexLock(SGMutex* mutex)
{
#ifdef __WIN32__
    WaitForSingleObject(mutex->handle, INFINITE);
#else
    /* TODO */
#endif
}
void SG_EXPORT sgMutexUnlock(SGMutex* mutex)
{
#ifdef __WIN32__
    ReleaseMutex(mutex->handle);
#else
    /* TODO */
#endif
}

SGSemaphore* SG_EXPORT sgSemaphoreCreate(SGint init, SGint max)
{
    SGSemaphore* sem = malloc(sizeof(SGSemaphore));
    if(!sem)
        return NULL;

#ifdef __WIN32__
    sem->handle = CreateSemaphore(NULL, init, max, NULL);
#else
    /* TODO */
#endif

    return sem;
}
void SG_EXPORT sgSemaphoreDestroy(SGSemaphore* sem)
{
    if(!sem)
        return;
#ifdef __WIN32__
    CloseHandle(sem->handle);
#else
    /* TODO */
#endif
    free(sem);
}

void SG_EXPORT sgSemaphoreWait(SGSemaphore* sem)
{
#ifdef __WIN32__
    WaitForSingleObject(sem->handle, INFINITE);
#else
    /* TODO */
#endif
}
void SG_EXPORT sgSemaphorePost(SGSemaphore* sem)
{
#ifdef __WIN32__
    ReleaseSemaphore(sem->handle, 1, NULL);
#else
    /* TODO */
#endif
}
