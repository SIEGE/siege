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
#endif

SGbool SG_EXPORT _sgLibraryInit(void)
{
    return SG_TRUE;
}
SGbool SG_EXPORT _sgLibraryDeinit(void)
{
    return SG_TRUE;
}
SGLibrary* SG_EXPORT sgLibraryLoad(char* fname)
{
#ifdef __WIN32__
    HMODULE handle = LoadLibrary(fname);
    /*if(!handle)
    {
        int err = GetLastError();
        printf("Error loading %s: %d\n", fname, err);
    }*/
#else
    void* handle = dlopen(fname, RTLD_LAZY | RTLD_LOCAL);
#endif
    if(handle == NULL)
        return NULL;
    SGLibrary* lib = malloc(sizeof(SGLibrary));
    lib->fname = malloc(strlen(fname) + 1);
    strcpy(lib->fname, fname);
    lib->handle = (void*)handle;
    return lib;
}
void SG_EXPORT sgLibraryUnload(SGLibrary* lib)
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
SGLibraryFunction* SG_EXPORT sgGetProcAddress(SGLibrary* lib, const char* proc)
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
void* SG_EXPORT sgGetVarAddress(SGLibrary* lib, const char* var)
{
    if(lib == NULL)
        return NULL;
#ifdef __WIN32__
    return GetProcAddress(lib->handle, var);
#else
    return dlsym(lib->handle, var);
#endif
}
