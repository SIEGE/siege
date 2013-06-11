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
#include <siege/util/thread/mutex.h>

#include <stdlib.h>

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/types.h>
#include <pthread.h>
#endif

SGMutex* SG_CALL sgMutexCreate(void)
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
void SG_CALL sgMutexDestroy(SGMutex* mutex)
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

SGbool SG_CALL sgMutexTryLock(SGMutex* mutex)
{
#ifdef __WIN32__
    return !WaitForSingleObject(mutex->handle, 0);
#else
    return !pthread_mutex_trylock(mutex->handle);
#endif
}
void SG_CALL sgMutexLock(SGMutex* mutex)
{
#ifdef __WIN32__
    WaitForSingleObject(mutex->handle, INFINITE);
#else
    pthread_mutex_lock(mutex->handle);
#endif
}
void SG_CALL sgMutexUnlock(SGMutex* mutex)
{
#ifdef __WIN32__
    ReleaseMutex(mutex->handle);
#else
    pthread_mutex_unlock(mutex->handle);
#endif
}
