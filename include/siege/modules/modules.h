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

#ifndef __SIEGE_MODULES_H__
#define __SIEGE_MODULES_H__
#include "../common.h"
#include "../util/list.h"
#include "../util/link.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define _SG_BINDS(str, name) \
    fptr = sgGetProcAddress(lib, #name);   \
    if((fptr != NULL) || _sg_modFirst)     \
        (str.name) = fptr;

#ifdef SG_BUILD_LIBRARY
SGLinkedList* _sg_modList;
SGbool _sg_modFirst;
#endif // SG_BUILD_LIBRARY

typedef struct SGModule
{
    char* name;
    SGLibrary* lib;
    SGModuleInfo* minfo;
    SGLinkedNode* node;

    SGuint SG_EXPORT (*sgmModuleInit)(SGModuleInfo** minfo);
    SGuint SG_EXPORT (*sgmModuleExit)(SGModuleInfo* minfo);
    SGuint SG_EXPORT (*sgmModuleMatch)(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok);
} SGModule;

char* SG_EXPORT _sgModuleGetFile(const char* module);
SGbool SG_EXPORT _sgModuleInit(void);
SGbool SG_EXPORT _sgModuleDeinit(void);

SGModule* SG_EXPORT sgModuleLoad(const char* name);
void SG_EXPORT sgModuleUnload(SGModule* module);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_MODULES_H__
