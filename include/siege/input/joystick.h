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

#ifndef __SIEGE_INPUT_JOYSTICK_H__
#define __SIEGE_INPUT_JOYSTICK_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// TODO: Complete overhaul

#ifdef SG_BUILD_LIBRARY
typedef struct SGIJoystick
{
    SGuint id;
    void* handle;
    size_t numbuttons;
    size_t numaxis;

    SGulong* bprev;
    SGulong* bcurr;

    float* taxis;
    float* aprev;
    float* acurr;
    float* adelt;
} SGIJoystick;

size_t _sg_joyNum;
SGIJoystick** _sg_joyJoys;
#endif // SG_BUILD_LIBRARY

void SG_CALL _sg_cbJoystickButton(SGuint joy, SGuint button, SGbool down);
void SG_CALL _sg_cbJoystickMove(SGuint joy, SGuint axis, float pos);

void SG_CALL _sgJoystickUpdate(void);

SGbool SG_CALL _sgJoystickInit(void);
SGbool SG_CALL _sgJoystickDeinit(void);

size_t SG_CALL sgJoystickGetNumJoysticks(void);
size_t SG_CALL sgJoystickGetNumButtons(SGuint joy);
size_t SG_CALL sgJoystickGetNumAxis(SGuint joy);

SGbool SG_CALL sgJoystickGetButtonPrev(SGuint joy, SGuint button);
SGbool SG_CALL sgJoystickGetButton(SGuint joy, SGuint button);
SGbool SG_CALL sgJoystickGetButtonPress(SGuint joy, SGuint button);
SGbool SG_CALL sgJoystickGetButtonRelease(SGuint joy, SGuint button);

float* SG_CALL sgJoystickGetAxisPrev(SGuint joy);
float SG_CALL sgJoystickGetAxisIndexPrev(SGuint joy, SGuint axis);
float* SG_CALL sgJoystickGetAxis(SGuint joy);
float SG_CALL sgJoystickGetAxisIndex(SGuint joy, SGuint axis);
float* SG_CALL sgJoystickGetAxisDelta(SGuint joy);
float SG_CALL sgJoystickGetAxisIndexDelta(SGuint joy, SGuint axis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_INPUT_JOYSTICK_H__
