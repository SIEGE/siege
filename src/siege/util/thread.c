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
    SGint ret = thread->func(thread, thread->data);
    thread->status = SG_THREAD_EXITED;
    return ret;
}
#else
#include <sys/types.h>
#include <semaphore.h>
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

	SGThread* thread = param;

	sem_wait(thread->sem);
	thread->ret = thread->func(thread, thread->data);
	thread->status = SG_THREAD_EXITED;
	return &thread->ret;
}
#endif

SGThread* SG_EXPORT sgThreadCreate(size_t ssize, SGThreadFunction* func, void* data)
{
    SGThread* thread = malloc(sizeof(SGThread));
    if(!thread)
        return NULL;

    thread->func = func;
    thread->data = data;
    thread->status = SG_THREAD_INITIAL;
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

/*void SG_EXPORT sgThreadYield(SGThread* thread)
{
#ifdef __WIN32__
    SwitchToThread();
#else
    sched_yeild();
#endif
}*/
void SG_EXPORT sgThreadExit(SGThread* thread, SGint ret)
{
	thread->status = SG_THREAD_EXITED;
#ifdef __WIN32__
    ExitThread(ret);
#else
    thread->ret = ret;
    pthread_exit(&thread->ret);
#endif
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
    mutex->handle = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex->handle, NULL);
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
    pthread_mutex_destroy(mutex->handle);
    free(mutex->handle);
#endif
    free(mutex);
}

void SG_EXPORT sgMutexLock(SGMutex* mutex)
{
#ifdef __WIN32__
    WaitForSingleObject(mutex->handle, INFINITE);
#else
    pthread_mutex_lock(mutex->handle);
#endif
}
void SG_EXPORT sgMutexUnlock(SGMutex* mutex)
{
#ifdef __WIN32__
    ReleaseMutex(mutex->handle);
#else
    pthread_mutex_unlock(mutex->handle);
#endif
}

SGSemaphore* SG_EXPORT sgSemaphoreCreate(SGuint init, SGuint max)
{
    SGSemaphore* sem = malloc(sizeof(SGSemaphore));
    if(!sem)
        return NULL;

#ifdef __WIN32__
    sem->handle = CreateSemaphore(NULL, init, max, NULL);
#else
    sem->handle = malloc(sizeof(sem_t));
    sem_init(sem->handle, 0, init);
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
    sem_destroy(sem->handle);
    free(sem->handle);
#endif
    free(sem);
}

void SG_EXPORT sgSemaphoreWait(SGSemaphore* sem)
{
#ifdef __WIN32__
    WaitForSingleObject(sem->handle, INFINITE);
#else
    sem_wait(sem->handle);
#endif
}
void SG_EXPORT sgSemaphorePost(SGSemaphore* sem)
{
#ifdef __WIN32__
    ReleaseSemaphore(sem->handle, 1, NULL);
#else
    sem_post(sem->handle);
#endif
}
