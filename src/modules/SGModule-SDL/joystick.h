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

#define JOY_MAX 256

typedef struct Joystick
{
    size_t ref;
    SDL_Joystick* sdl;
    float* axis;
} Joystick;
Joystick joylist[JOY_MAX];

#endif // __JOYSTICK_H__
