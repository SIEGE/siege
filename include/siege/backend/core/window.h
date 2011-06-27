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

#ifndef __SIEGE_BACKEND_CORE_WINDOW_H__
#define __SIEGE_BACKEND_CORE_WINDOW_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

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

    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowCreate)(void** window);
    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowDestroy)(void* window);
    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowOpen)(void* window, SGuint width, SGuint height, SGubyte bpp, SGenum flags);
    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowIsOpened)(void* window, SGbool* opened);
    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowClose)(void* window);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreWindowIsClosed)(void* window, SGbool* closed);
    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowSetTitle)(void* window, const char* title);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreWindowGetTitle)(void* window, char** title);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreWindowFreeTitle)(char* title);
    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowSetSize)(void* window, SGuint width, SGuint height);
    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowGetSize)(void* window, SGuint* width, SGuint* height);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreWindowPollEvents)(void* window);
    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowSwapBuffers)(void* window);

    SGuint SG_EXPORT SG_FPTR(sgmCoreWindowSetCallbacks)(void* window, SGCoreWindowCallbacks* callbacks);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreWindowGetCallbacks)(void* window, SGCoreWindowCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_CORE_WINDOW_H__
