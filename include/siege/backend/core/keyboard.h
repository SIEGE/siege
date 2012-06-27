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

#ifndef __SIEGE_BACKEND_CORE_KEYBOARD_H__
#define __SIEGE_BACKEND_CORE_KEYBOARD_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGCoreKeyboardCallbacks
    {
        void SG_EXPORT (*key)(void* keyboard, SGuint key, SGbool down);
        void SG_EXPORT (*chr)(void* keyboard, SGuint chr);
    } SGCoreKeyboardCallbacks;

    SGuint SG_EXPORT SG_FPTR(sgmCoreKeyboardCreate)(void** keyboard, void* window);
    SGuint SG_EXPORT SG_FPTR(sgmCoreKeyboardDestroy)(void* keyboard);

    SGuint SG_EXPORT SG_FPTR(sgmCoreKeyboardSetCallbacks)(void* keyboard, SGCoreKeyboardCallbacks* callbacks);
    //SGuint SG_EXPORT SG_FPTR(sgmCoreKeyboardGetCallbacks)(void* keyboard, SGCoreKeyboardCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_CORE_KEYBOARD_H__
