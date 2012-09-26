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

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "common.h"

typedef struct Joystick
{
    SGuint id;
    SGbool active;

    SGuint numaxis;
    float* paxis;
    float* axis;
    SGuint numbuttons;
    SGbool* pbuttons;
    SGbool* buttons;
} Joystick;
size_t joylen;
Joystick** joylist;

void _swapPtr(void** a, void** b);

#endif // __JOYSTICK_H__
