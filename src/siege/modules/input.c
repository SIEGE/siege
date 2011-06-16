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

#define SG_BUILD_LIBRARY
#include <siege/modules/modules.h>
#include <siege/modules/input.h>

void SG_EXPORT _sgModuleLoadInput(SGLibrary* lib)
{
    void* fptr;

    /// Input - Joystick
    _SG_BIND(sgmCoreJoystickGetNumJoysticks);
    _SG_BIND(sgmCoreJoystickCreate);
    _SG_BIND(sgmCoreJoystickDestroy);
    _SG_BIND(sgmCoreJoystickGetID);
    _SG_BIND(sgmCoreJoystickGetNumButtons);
    //_SG_BIND(sgmCoreJoystickSetButtons);
    _SG_BIND(sgmCoreJoystickGetButtons);
    _SG_BIND(sgmCoreJoystickGetNumAxis);
    //_SG_BIND(sgmCoreJoystickSetAxis);
    _SG_BIND(sgmCoreJoystickGetAxis);

    _SG_BIND(sgmCoreJoystickSetCallbacks);
    //_SG_BIND(sgmCoreJoystickGetCallbacks);

    /// Input - Keyboard
    _SG_BIND(sgmCoreKeyboardCreate);
    _SG_BIND(sgmCoreKeyboardDestroy);
    //_SG_BIND(sgmCoreKeyboardSetKey);
    _SG_BIND(sgmCoreKeyboardGetKey);
    //_SG_BIND(sgmCoreKeyboardSetChr);
    //_SG_BIND(sgmCoreKeyboardGetChr);

    _SG_BIND(sgmCoreKeyboardSetCallbacks);
    //_SG_BIND(sgmCoreKeyboardGetCallbacks);

    /// Input - Mouse
    _SG_BIND(sgmCoreMouseCreate);
    _SG_BIND(sgmCoreMouseDestroy);
    // should these two [sgmCoreMouseShow,sgmCoreMouseHide] be put into a single function?
    _SG_BIND(sgmCoreMouseShow);
    _SG_BIND(sgmCoreMouseHide);
    //_SG_BIND(sgmCoreMouseIsShown);
    //_SG_BIND(sgmCoreMouseIsHidden);
    _SG_BIND(sgmCoreMouseGetNumButtons);
    //_SG_BIND(sgmCoreMouseSetButtons);
    _SG_BIND(sgmCoreMouseGetButtons);
    _SG_BIND(sgmCoreMouseSetPosition);
    _SG_BIND(sgmCoreMouseGetPosition);
    //_SG_BIND(sgmCoreMouseSetWheel);
    _SG_BIND(sgmCoreMouseGetWheel);

    _SG_BIND(sgmCoreMouseSetCallbacks);
    //_SG_BIND(sgmCoreMouseGetCallbacks);
}
