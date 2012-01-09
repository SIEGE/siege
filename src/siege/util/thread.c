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
#include <siege/util/threadkey.h>

#include <stdlib.h>

static SGbool _sg_thrInited = SG_FALSE;
static SGThread _sg_thrMain = { NULL, NULL, NULL, SG_THREAD_RUNNING, 0, NULL, 0 };
static SGThreadKey _sg_thrKey = { NULL };

static void _sgThreadAtExit(void)
{
    SGThread* thread = sgThreadGetCurrent();
    if(!thread)
        return;

    size_t i;
    for(i = thread->numdtors; i > 0; i--)
        thread->dtors[i-1]();
    thread->numdtors = 0;
    free(thread->dtors);
    thread->dtors = NULL;
}

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
static DWORD WINAPI _sgThreadEntry(LPVOID param)
{
    sgThreadKeySetVal(&_sg_thrKey, param);
    SGThread* thread = param;
    SGint ret = thread->func(thread->data);
    thread->status = SG_THREAD_EXITED;
    return ret;
}
#else
#include <sys/types.h>
#include <semaphore.h>  // sem_t
#include <pthread.h>
#include <signal.h>
//#include <sched.h>
/*#include <string.h>
static void _sgThreadSuspended(int sig)
{
	SGThread* thread = pthread_getspecific(0);
	thread->status = SG_THREAD_SUSPENDED;
	sem_wait(thread->sem);
	thread->status = SG_THREAD_RUNNING;
}*/
static void* _sgThreadEntry(void* param)
{
	/*pthread_setspecific(0, param);

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = _sgThreadSuspended;
	//sa.sa_mask = SIGRTMAX;
	sa.sa_flags = 0;

	sigaction(SIGRTMAX, &sa, NULL);*/

    sgThreadKeySetVal(&_sg_thrKey, param);
	SGThread* thread = param;
	sem_wait(thread->sem);
	thread->ret = thread->func(thread->data);
    _sgThreadAtExit();
	thread->status = SG_THREAD_EXITED;
	return &thread->ret;
}
#endif

static void _sgThreadInit(void)
{
#ifdef __WIN32__
    static DWORD key;
    HANDLE handle = GetCurrentThread();
    _sg_thrMain.handle = handle;
    key = TlsAlloc();
    _sg_thrKey.handle = &key;
#else
    static pthread_t handle;
    static pthread_key_t key;
    handle = pthread_self();
    _sg_thrMain.handle = &handle;
    pthread_key_create(&key, NULL);
    _sg_thrKey.handle = &key;
#endif
    sgThreadKeySetVal(&_sg_thrKey, &_sg_thrMain);
    atexit(_sgThreadAtExit);
}

SGThread* SG_EXPORT sgThreadCreate(size_t ssize, SGThreadFunction* func, void* data)
{
    if(!_sg_thrInited)
    {
        _sgThreadInit();
        _sg_thrInited = SG_TRUE;
    }

    SGThread* thread = malloc(sizeof(SGThread));
    if(!thread)
        return NULL;

    thread->func = func;
    thread->data = data;
    thread->status = SG_THREAD_INITIAL;
    thread->numdtors = 0;
    thread->dtors = NULL;

    thread->ret = 0;
    thread->sem = NULL;
    thread->susp = 0;

#ifdef __WIN32__
    thread->handle = CreateThread(NULL, ssize, _sgThreadEntry, thread, CREATE_SUSPENDED, NULL);
#else
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if(ssize)
		pthread_attr_setstacksize(&attr, ssize);

	thread->sem = malloc(sizeof(sem_t));
    sem_init(thread->sem, 0, 0);

    thread->handle = malloc(sizeof(pthread_t));
    pthread_create(thread->handle, &attr, _sgThreadEntry, thread);
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
	pthread_join(*(pthread_t*)thread->handle, NULL);
    free(thread->handle);
    sem_destroy(thread->sem);
    free(thread->sem);
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
    sem_post(thread->sem);
#endif
}
SGuint SG_EXPORT sgThreadResume(SGThread* thread)
{
	if(thread->status == SG_THREAD_INITIAL)
		return -1;
	SGuint ret;
#ifdef __WIN32__
    ret = ResumeThread(thread->handle);
#else
	if(thread->susp)
		pthread_kill(*(pthread_t*)thread->handle, SIGCONT);
	ret = thread->susp--;
    //pthread_kill(thread->handle, SIGRTMAX);
#endif
    if(ret <= 1)
        thread->status = SG_THREAD_RUNNING;
    return ret;
}
SGuint SG_EXPORT sgThreadSuspend(SGThread* thread)
{
	SGuint ret;
#ifdef __WIN32__
    ret = SuspendThread(thread->handle);
#else
	pthread_kill(*(pthread_t*)thread->handle, SIGSTOP);
	ret = thread->susp++;
#endif
	thread->status = SG_THREAD_SUSPENDED;
	return ret;
}

void SG_EXPORT sgThreadAtExit(SGThreadDestroy* dtor)
{
    SGThread* thread = sgThreadGetCurrent();
    if(!thread)
        return;
    thread->dtors = realloc(thread->dtors, (thread->numdtors + 1) * sizeof(SGThreadDestroy*));
    thread->dtors[thread->numdtors++] = dtor;
}
/*void SG_EXPORT sgThreadYield(void)
{
#ifdef __WIN32__
    SwitchToThread();
#else
    sched_yeild();
#endif
}*/
void SG_EXPORT sgThreadExit(SGint ret)
{
    SGThread* thread = sgThreadGetCurrent();
    _sgThreadAtExit();
    if(thread)
        thread->status = SG_THREAD_EXITED;
#ifdef __WIN32__
    ExitThread(ret);
#else
    if(thread)
    {
        thread->ret = ret;
        pthread_exit(&thread->ret);
    }
    else
        pthread_exit(NULL);
#endif
}
SGThread* SG_EXPORT sgThreadGetCurrent(void)
{
    if(!_sg_thrInited)
    {
        _sgThreadInit();
        _sg_thrInited = SG_TRUE;
    }

    return sgThreadKeyGetVal(&_sg_thrKey);
}

SGint SG_EXPORT sgThreadJoin(SGThread* thread)
{
	SGint ret;
#ifdef __WIN32__
    WaitForSingleObject(thread->handle, INFINITE);
    DWORD dret;
    GetExitCodeThread(thread->handle, &dret);
    ret = dret;
#else
	//SGint* pret;
    //pthread_join(thread->handle, (void**)&pret);
    //ret = *pret;
    pthread_join(*(pthread_t*)thread->handle, NULL);
    ret = thread->ret;
#endif
	thread->status = SG_THREAD_EXITED;
	return ret;
}
void SG_EXPORT sgThreadKill(SGThread* thread, SGint ret)
{
	thread->status = SG_THREAD_EXITED;
#ifdef __WIN32__
    TerminateThread(thread->handle, ret);
#else
    thread->ret = ret;
    pthread_kill(*(pthread_t*)thread->handle, SIGABRT);
#endif
}

SGenum SG_EXPORT sgThreadGetStatus(SGThread* thread)
{
    return thread->status;
}
