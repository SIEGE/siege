/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "copying.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_UTIL_DIRECTORY_H__
#define __SIEGE_UTIL_DIRECTORY_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGDirectory
{
    char* name;
    void* handle;
    size_t buflen;
    char* buf;
    void* ibuf;
} SGDirectory;

SGDirectory* SG_CALL sgDirectoryOpen(const char* fname);
void SG_CALL sgDirectoryClose(SGDirectory* dir);

char* SG_CALL sgDirectoryNext(SGDirectory* dir, char* buf, size_t buflen);
void SG_CALL sgDirectoryRewind(SGDirectory* dir);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_DIRECTORY_H__
