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

#ifndef __SIEGE_BACKEND_CORE_JOYSTICK_H__
#define __SIEGE_BACKEND_CORE_JOYSTICK_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGCoreJoystickCallbacks
    {
        void SG_EXPORT (*button)(void* joystick, SGuint button, SGbool down);
        //void SG_EXPORT (*button)(void* joystick, SGbool* buttons);
        //void SG_EXPORT (*move)(void* joystick, SGuint axis, float position);
        void SG_EXPORT (*move)(void* joystick, float* axis);
    } SGCoreJoystickCallbacks;

    /**
        WARNING: Subject to change
    */
    SGuint SG_EXPORT sgmCoreJoystickGetFlags(SGenum** flags);
    SGuint SG_EXPORT sgmCoreJoystickFreeFlags(SGenum* flags);

    SGuint SG_EXPORT sgmCoreJoystickGetNumJoysticks(void* window, size_t* numjoys);
    SGuint SG_EXPORT sgmCoreJoystickCreate(void** joystick, void* window, SGuint id);
    SGuint SG_EXPORT sgmCoreJoystickDestroy(void* joystick);
    SGuint SG_EXPORT sgmCoreJoystickGetID(void* joystick, SGuint* id);
    SGuint SG_EXPORT sgmCoreJoystickGetNumButtons(void* joystick, size_t* numbuttons);
    //SGuint SG_EXPORT sgmCoreJoystickSetButtons(void* joystick, SGbool* state);
    SGuint SG_EXPORT sgmCoreJoystickGetButtons(void* joystick, SGbool* state);
    SGuint SG_EXPORT sgmCoreJoystickGetNumAxis(void* joystick, size_t* numaxis);
    //SGuint SG_EXPORT sgmCoreJoystickSetAxis(void* joystick, float* position);
    SGuint SG_EXPORT sgmCoreJoystickGetAxis(void* joystick, float* position);

    SGuint SG_EXPORT sgmCoreJoystickSetCallbacks(void* joystick, SGCoreJoystickCallbacks* callbacks);
    //SGuint SG_EXPORT sgmCoreJoystickGetCallbacks(void* joystick, SGCoreJoystickCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_CORE_JOYSTICK_H__
