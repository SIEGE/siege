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
#include <siege/util/thread/key.h>

#include <stdlib.h>

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/types.h>
#include <pthread.h>
#endif

SGThreadKey* SG_CALL sgThreadKeyCreate(void)
{
    SGThreadKey* key = malloc(sizeof(SGThreadKey));

#ifdef __WIN32__
    key->handle = malloc(sizeof(DWORD));
    *(DWORD*)key->handle = TlsAlloc();
    if(*(DWORD*)key->handle == TLS_OUT_OF_INDEXES)
    {
        free(key->handle);
        free(key);
        return NULL;
    }
#else
    key->handle = malloc(sizeof(pthread_key_t));
    if(pthread_key_create(key->handle, NULL))
    {
        free(key->handle);
        free(key);
        return NULL;
    }
#endif

    return key;
}
void SG_CALL sgThreadKeyDestroy(SGThreadKey* key)
{
    if(!key)
        return;
#ifdef __WIN32__
    TlsFree(*(DWORD*)key->handle);
#else
    pthread_key_delete(*(pthread_key_t*)key->handle);
#endif
    free(key->handle);
    free(key);
}

void SG_CALL sgThreadKeySetVal(SGThreadKey* key, void* val)
{
#ifdef __WIN32__
    TlsSetValue(*(DWORD*)key->handle, val);
#else
    pthread_setspecific(*(pthread_key_t*)key->handle, val);
#endif
}
void* SG_CALL sgThreadKeyGetVal(SGThreadKey* key)
{
#ifdef __WIN32__
    return TlsGetValue(*(DWORD*)key->handle);
#else
    return pthread_getspecific(*(pthread_key_t*)key->handle);
#endif
}
