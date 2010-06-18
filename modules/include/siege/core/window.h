#ifndef __SIEGE_CORE_WINDOW_H__
#define __SIEGE_CORE_WINDOW_H__

#include "../common.h"

typedef struct SGCoreWindowCallbacks
{
    void SG_EXPORT (*open)(void* window);
    void SG_EXPORT (*close)(void* window);
    void SG_EXPORT (*resize)(void* window, SGuint width, SGuint height);
} SGCoreWindowCallbacks;

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgCoreWindowCreate(void** window);
    SGuint SG_EXPORT sgCoreWindowDestroy(void* window);
    SGuint SG_EXPORT sgCoreWindowOpen(void* window, SGuint width, SGuint height, SGubyte bpp, SGenum flags);
    SGuint SG_EXPORT sgCoreWindowIsOpened(void* window, SGbool* opened);
    SGuint SG_EXPORT sgCoreWindowClose(void* window);
    //SGuint SG_EXPORT sgCoreWindowIsClosed(void* window, SGbool* closed);
    SGuint SG_EXPORT sgCoreWindowSetTitle(void* window, char* title);
    //SGuint SG_EXPORT sgCoreWindowGetTitle(void* window, char** title);
    //SGuint SG_EXPORT sgCoreWindowFreeTitle(char* title);
    SGuint SG_EXPORT sgCoreWindowSetSize(void* window, SGuint width, SGuint height);
    SGuint SG_EXPORT sgCoreWindowGetSize(void* window, SGuint* width, SGuint* height);
    //SGuint SG_EXPORT sgCoreWindowPollEvents(void* window);
    SGuint SG_EXPORT sgCoreWindowSwapBuffers(void* window);

    SGuint SG_EXPORT sgCoreWindowSetCallbacks(void* window, SGCoreWindowCallbacks* callbacks);
    //SGuint SG_EXPORT sgCoreWindowGetCallbacks(void* window, SGCoreWindowCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_CORE_WINDOW_H__
