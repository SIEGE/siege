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

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGCoreKeyboardCallbacks
    {
        void SG_EXPORT (*key)(void* keyboard, SGuint key, SGbool down);
        void SG_EXPORT (*chr)(void* keyboard, SGuint chr, SGbool down);
    } SGCoreKeyboardCallbacks;

    SGuint SG_EXPORT sgmCoreKeyboardCreate(void** keyboard, void* window);
    SGuint SG_EXPORT sgmCoreKeyboardDestroy(void* keyboard);
    //SGuint SG_EXPORT sgmCoreKeyboardSetKey(void* keyboard, SGuint key, SGbool down);
    SGuint SG_EXPORT sgmCoreKeyboardGetKey(void* keyboard, SGuint key, SGbool* down);
    //SGuint SG_EXPORT sgmCoreKeyboardSetChr(void* keyboard, SGuint chr, SGbool down);
    //SGuint SG_EXPORT sgmCoreKeyboardGetChr(void* keyboard, SGuint chr, SGbool* down);

    SGuint SG_EXPORT sgmCoreKeyboardSetCallbacks(void* keyboard, SGCoreKeyboardCallbacks* callbacks);
    //SGuint SG_EXPORT sgmCoreKeyboardGetCallbacks(void* keyboard, SGCoreKeyboardCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_CORE_KEYBOARD_H__
