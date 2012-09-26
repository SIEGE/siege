/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "common.h"

typedef struct Window
{
    SDL_Surface* surface;
    SGbool opened;

    SGCoreWindowCallbacks* cbWindow;
    SGCoreJoystickCallbacks* cbJoystick;
    SGCoreKeyboardCallbacks* cbKeyboard;
    SGCoreMouseCallbacks* cbMouse;
} Window;
Window* main_window;

void windowOpen();
int windowClose();
void windowResize(int x, int y);

#endif // __WINDOW_H__
