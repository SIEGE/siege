/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_MODULES_H__
#define __SIEGE_MODULES_H__
#include "../common.h"
#include "../util/list.h"
#include "../util/link.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define _SG_BIND(name) \
    fptr = sgGetProcAddress(lib, #name);   \
    if(fptr != NULL)    \
        (p##name) = fptr; // not completely valid C99, but blame POSIX for that

typedef struct SGModule
{
    char* name;
    SGLibrary* lib;
    SGListNode* node;
} SGModule;

char* SG_CALL _sgModuleGetFile(const char* module);

SGModule* SG_CALL sgModuleLoad(const char* name);
void SG_CALL sgModuleUnload(SGModule* module);

void SG_CALL sgModuleSetLoadDirsv(size_t ndirs, va_list args);
void SG_CALL sgModuleSetLoadDirs(size_t ndirs, ...);
void SG_CALL sgModuleSetLoadDir(const char* dir);
char** SG_CALL sgModuleGetLoadDirs(size_t* ndirs);

void SG_CALL sgModuleSetLoadPrefixesv(size_t nprefs, va_list args);
void SG_CALL sgModuleSetLoadPrefixes(size_t nprefs, ...);
void SG_CALL sgModuleSetLoadPrefix(const char* prefix);
char** SG_CALL sgModuleGetLoadPrefixes(size_t* nprefs);

SGList* SG_CALL sgModuleGetList(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_MODULES_H__
