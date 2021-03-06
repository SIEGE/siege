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

#define SG_BUILD_LIBRARY
#include <siege/util/link.h>

#include <stdlib.h>
#include <string.h>
#ifdef __WIN32__
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <dlfcn.h>
    #include <stdio.h>
#endif

SGLibrary* SG_CALL sgLibraryLoad(const char* fname)
{
#ifdef __WIN32__
    HMODULE handle = LoadLibrary(fname);
    /*if(!handle)
    {
        int err = GetLastError();
        printf("Error loading %s: %d\n", fname, err);
    }*/
#else
    char buf[512];
    snprintf(buf, sizeof(buf), "%s.so", fname);
    void* handle = dlopen(buf, RTLD_LAZY | RTLD_LOCAL);
#endif
    if(handle == NULL)
        return NULL;
    SGLibrary* lib = malloc(sizeof(SGLibrary));
    lib->fname = malloc(strlen(fname) + 1);
    strcpy(lib->fname, fname);
    lib->handle = (void*)handle;
    return lib;
}
void SG_CALL sgLibraryUnload(SGLibrary* lib)
{
    if(lib == NULL)
        return;
#ifdef __WIN32__
    FreeLibrary(lib->handle);
#else
    dlclose(lib->handle);
#endif
    free(lib->fname);
    free(lib);
}
SGLibraryFunction* SG_CALL sgGetProcAddress(SGLibrary* lib, const char* proc)
{
    if(lib == NULL)
        return NULL;
#ifdef __WIN32__
    return (SGLibraryFunction*)GetProcAddress(lib->handle, proc);
#else
    union
    {
        SGLibraryFunction* fptr;
        void* ptr;
    } tmp;
    tmp.ptr = dlsym(lib->handle, proc);
    return tmp.fptr;
#endif
}
void* SG_CALL sgGetVarAddress(SGLibrary* lib, const char* var)
{
    if(lib == NULL)
        return NULL;
#ifdef __WIN32__
    return GetProcAddress(lib->handle, var);
#else
    return dlsym(lib->handle, var);
#endif
}
