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

#ifndef __SIEGE_BACKEND_CORE_MOUSE_H__
#define __SIEGE_BACKEND_CORE_MOUSE_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGCoreMouseCallbacks
    {
        void SG_EXPORT (*button)(void* mouse, SGuint button, SGbool action);
        void SG_EXPORT (*move)(void* mouse, SGint x, SGint y);
        void SG_EXPORT (*wheel)(void* mouse, SGint w);
    } SGCoreMouseCallbacks;
    /**
        WARNING: Subject to change
    */
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseCreate)(void** mouse, void* window);
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseDestroy)(void* mouse);
    // should these two [sgCoreMouseShow,sgCoreMouseHide] be put into a single function?
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseShow)(void* mouse);
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseHide)(void* mouse);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreMouseIsShown)(void* mouse, SGbool* shown);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreMouseIsHidden)(void* mouse, SGbool* hidden);
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseGetNumButtons)(void* mouse, size_t* numbuttons);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreMouseSetButtons)(void* mouse, SGbool* state);
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseGetButtons)(void* mouse, SGbool* state);
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseSetPosition)(void* mouse, SGint x, SGint y);
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseGetPosition)(void* mouse, SGint* x, SGint* y);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreMouseSetWheel)(void* mouse, SGint w);
    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseGetWheel)(void* mouse, SGint* w);

    SGuint SG_EXPORT SG_FPTR(sgmCoreMouseSetCallbacks)(void* mouse, SGCoreMouseCallbacks* callbacks);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreMouseGetCallbacks)(void* mouse, SGCoreMouseCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_CORE_MOUSE_H__
