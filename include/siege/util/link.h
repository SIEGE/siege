/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#ifndef __SIEGE_UTIL_LINK_H__
#define __SIEGE_UTIL_LINK_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGLibrary
{
    char* fname;
    void* handle;
} SGLibrary;

typedef void (SGLibraryFunction)(void);

SGLibrary* SG_CALL sgLibraryLoad(const char* fname);
void SG_CALL sgLibraryUnload(SGLibrary* lib);
SGLibraryFunction* SG_CALL sgGetProcAddress(SGLibrary* lib, const char* proc);
void* SG_CALL sgGetVarAddress(SGLibrary* lib, const char* var);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_LINK_H__
