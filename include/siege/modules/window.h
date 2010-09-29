#ifndef __SIEGE_MODULES_WINDOW_H__
#define __SIEGE_MODULES_WINDOW_H__
#include "../common.h"
#include "../util/link.h"
#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


    typedef struct SGCoreWindowCallbacks
    {
        void SG_EXPORT (*open)(void* window);
        void SG_EXPORT (*close)(void* window);
        void SG_EXPORT (*resize)(void* window, SGuint width, SGuint height);
    } SGCoreWindowCallbacks;

typedef struct SGModuleWindow
{
    /// Windowing
    SGuint SG_EXPORT (*sgmCoreWindowCreate)(void** window);
    SGuint SG_EXPORT (*sgmCoreWindowDestroy)(void* window);
    SGuint SG_EXPORT (*sgmCoreWindowOpen)(void* window, SGuint width, SGuint height, SGubyte bpp, SGuint flags);
    SGuint SG_EXPORT (*sgmCoreWindowIsOpened)(void* window, SGbool* opened);
    SGuint SG_EXPORT (*sgmCoreWindowClose)(void* window);
    //SGuint SG_EXPORT (*sgmCoreWindowIsClosed)(void* window, SGbool* closed);
    SGuint SG_EXPORT (*sgmCoreWindowSetTitle)(void* window, char* title);
    //SGuint SG_EXPORT (*sgmCoreWindowGetTitle)(void* window, char** title);
    //SGuint SG_EXPORT (*sgmCoreWindowFreeTitle)(char* title);
    SGuint SG_EXPORT (*sgmCoreWindowSetSize)(void* window, SGuint width, SGuint height);
    SGuint SG_EXPORT (*sgmCoreWindowGetSize)(void* window, SGuint* width, SGuint* height);
    //SGuint SG_EXPORT (*sgmCoreWindowPollEvents)(void* window);
    SGuint SG_EXPORT (*sgmCoreWindowSwapBuffers)(void* window);

    SGuint SG_EXPORT (*sgmCoreWindowSetCallbacks)(void* window, SGCoreWindowCallbacks* callbacks);
    //SGuint SG_EXPORT (*sgmCoreWindowGetCallbacks)(void* window, SGCoreWindowCallbacks** callbacks);

    SGuint SG_EXPORT (*sgmCoreWindowMatchGraphics)(SGModuleInfo* other, SGubyte* level);
} SGModuleWindow;

#ifdef SG_BUILD_LIBRARY
SGModuleWindow _sg_modWindow;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sgModuleLoadWindow(SGLibrary* lib);

SGModuleWindow* SG_EXPORT sgModuleGetWindow(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_MODULES_WINDOW_H__
