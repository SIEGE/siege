#ifndef __CORE_H__
#define __CORE_H__

#include "dl.h"
#include <siege/common.h>

void* module;
void loadCore(char* name);
void freeCore(void);

typedef struct SGCoreWindowCallbacks
{
    void (*open)(void* window);
    void (*close)(void* window);
    void (*resize)(void* window, SGuint width, SGuint height);
} SGCoreWindowCallbacks;

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint (*sgModuleInit)(void* gc, SGModuleInfo** minfo);
    SGuint (*sgModuleExit)(SGModuleInfo* minfo);
    //SGuint (*sgModuleFree)(void* data);

    SGuint (*sgCoreWindowCreate)(void** window);
    SGuint (*sgCoreWindowDestroy)(void* window);
    SGuint (*sgCoreWindowOpen)(void* window, SGuint width, SGuint height, SGubyte bpp, SGenum flags);
    SGuint (*sgCoreWindowIsOpened)(void* window, SGbool* opened);
    SGuint (*sgCoreWindowClose)(void* window);
    //SGuint (*sgCoreWindowIsClosed)(void* window, SGbool* closed);
    SGuint (*sgCoreWindowSetTitle)(void* window, char* title);
    //SGuint (*sgCoreWindowGetTitle)(void* window, char** title);
    //SGuint (*sgCoreWindowFreeTitle)(char* title);
    SGuint (*sgCoreWindowSetSize)(void* window, SGuint width, SGuint height);
    SGuint (*sgCoreWindowGetSize)(void* window, SGuint* width, SGuint* height);
    //SGuint (*sgCoreWindowPollEvents)(void* window);
    SGuint (*sgCoreWindowSwapBuffers)(void* window);

    SGuint (*sgCoreWindowSetCallbacks)(void* window, SGCoreWindowCallbacks* callbacks);
    //SGuint (*sgCoreWindowGetCallbacks)(void* window, SGCoreWindowCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __CORE_H__
