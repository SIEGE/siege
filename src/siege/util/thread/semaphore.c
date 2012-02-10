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
#include <siege/util/thread/semaphore.h>

#include <stdlib.h>

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/types.h>
#include <semaphore.h>
#endif

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

SGbool SG_EXPORT sgSemaphoreTryWait(SGSemaphore* sem)
{
#ifdef __WIN32__
    return !WaitForSingleObject(sem->handle, 0);
#else
    return !sem_trywait(sem->handle);
#endif
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
