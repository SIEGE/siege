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

SGbool SG_EXPORT _sgLibraryInit(void);
SGbool SG_EXPORT _sgLibraryDeinit(void);
SGLibrary* SG_EXPORT sgLibraryLoad(char* fname);
void SG_EXPORT sgLibraryUnload(SGLibrary* lib);
void* SG_EXPORT sgGetProcAddress(SGLibrary* lib, char* proc);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_LINK_H__
