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

#ifndef __SIEGE_BACKEND_CORE_WINDOW_H__
#define __SIEGE_BACKEND_CORE_WINDOW_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGCoreWindowCallbacks
    {
        void SG_EXPORT (*open)(void* window);
        void SG_EXPORT (*close)(void* window);
        void SG_EXPORT (*resize)(void* window, SGuint width, SGuint height);
    } SGCoreWindowCallbacks;

    SGuint SG_EXPORT sgmCoreWindowCreate(void** window);
    SGuint SG_EXPORT sgmCoreWindowDestroy(void* window);
    SGuint SG_EXPORT sgmCoreWindowOpen(void* window, SGuint width, SGuint height, SGubyte bpp, SGenum flags);
    SGuint SG_EXPORT sgmCoreWindowIsOpened(void* window, SGbool* opened);
    SGuint SG_EXPORT sgmCoreWindowClose(void* window);
    //SGuint SG_EXPORT sgmCoreWindowIsClosed(void* window, SGbool* closed);
    SGuint SG_EXPORT sgmCoreWindowSetTitle(void* window, char* title);
    //SGuint SG_EXPORT sgmCoreWindowGetTitle(void* window, char** title);
    //SGuint SG_EXPORT sgmCoreWindowFreeTitle(char* title);
    SGuint SG_EXPORT sgmCoreWindowSetSize(void* window, SGuint width, SGuint height);
    SGuint SG_EXPORT sgmCoreWindowGetSize(void* window, SGuint* width, SGuint* height);
    //SGuint SG_EXPORT sgmCoreWindowPollEvents(void* window);
    SGuint SG_EXPORT sgmCoreWindowSwapBuffers(void* window);

    SGuint SG_EXPORT sgmCoreWindowSetCallbacks(void* window, SGCoreWindowCallbacks* callbacks);
    //SGuint SG_EXPORT sgmCoreWindowGetCallbacks(void* window, SGCoreWindowCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_CORE_WINDOW_H__
