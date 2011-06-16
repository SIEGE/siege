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
#include <siege/input/joystick.h>
#include <siege/core/window.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

void SG_EXPORT _sg_cbJoystickButton(void* joystick, SGuint button, SGbool down)
{
    SGuint joy = 0;
    if(sgmCoreJoystickGetID != NULL)
        sgmCoreJoystickGetID(joystick, &joy);

    SGbool pressed = _sg_joyJoys[joy]->bcurr[button] && !_sg_joyJoys[joy]->bprev[button];

    _sg_joyJoys[joy]->bprev[button] = _sg_joyJoys[joy]->bcurr[button];
    _sg_joyJoys[joy]->bcurr[button] = down;

    SGenum events[2];
    memset(events, 0, sizeof(events));
    events[0] = SG_EVF_JOYSTICKBUTH;
    if(pressed)
        events[1] = SG_EVF_JOYSTICKBUTP;
    else if(!down)
        events[1] = SG_EVF_JOYSTICKBUTR;

    sgEventCall(SG_EV_INTERNAL, (SGuint)2, events[0], joy, button, events[1], joy, button);
}
void SG_EXPORT _sg_cbJoystickMove(void* joystick, float* axis)
{
    SGuint joy = 0;
    if(sgmCoreJoystickGetID != NULL)
        sgmCoreJoystickGetID(joystick, &joy);

    size_t numaxis = 0;
    if(sgmCoreJoystickGetNumAxis != NULL)
        sgmCoreJoystickGetNumAxis(joystick, &numaxis);

    sgEventCall(SG_EV_INTERNAL, (SGuint)1, (SGenum)SG_EVF_JOYSTICKMOVE, joy, axis, numaxis);
}

SGbool SG_EXPORT _sgJoystickInit(void)
{
    SGuint i;
    _sg_joyNum = 0;

    if(sgmCoreJoystickGetNumJoysticks != NULL)
        sgmCoreJoystickGetNumJoysticks(_sg_winHandle, &_sg_joyNum);

    _sg_joyJoys = malloc(_sg_joyNum * sizeof(_SGJoystick*));
    for(i = 0; i < _sg_joyNum; i++)
        _sg_joyJoys[i] = _sgJoystickCreate(i);

    _sg_joyCallbacks.button = _sg_cbJoystickButton;
    _sg_joyCallbacks.move = _sg_cbJoystickMove;
    memset(&_sg_joyCallbacks, 0, sizeof(SGCoreJoystickCallbacks));

    return SG_TRUE;
}
SGbool SG_EXPORT _sgJoystickDeinit(void)
{
    SGuint i;
    for(i = 0; i < _sg_joyNum; i++)
        _sgJoystickDestroy(_sg_joyJoys[i]);
    free(_sg_joyJoys);

    return SG_TRUE;
}

_SGJoystick* SG_EXPORT _sgJoystickCreate(SGuint id)
{
    _SGJoystick* joy = malloc(sizeof(_SGJoystick));
    if(joy == NULL)
        return NULL;

    joy->id = id;
    joy->numbuttons = 0;
    joy->numaxis = 0;

    if(sgmCoreJoystickCreate != NULL)
        sgmCoreJoystickCreate(&joy->handle, _sg_winHandle, id);
    if(sgmCoreJoystickSetCallbacks != NULL)
        sgmCoreJoystickSetCallbacks(joy->handle, &_sg_joyCallbacks);

    if(sgmCoreJoystickGetNumButtons != NULL)
        sgmCoreJoystickGetNumButtons(joy->handle, &joy->numbuttons);
    joy->bprev = malloc(joy->numbuttons * sizeof(SGbool));
    joy->bcurr = malloc(joy->numbuttons * sizeof(SGbool));

    if(sgmCoreJoystickGetNumAxis != NULL)
        sgmCoreJoystickGetNumAxis(joy->handle, &joy->numaxis);
    joy->aprev = malloc(joy->numaxis * sizeof(SGbool));
    joy->acurr = malloc(joy->numaxis * sizeof(SGbool));
    joy->adelt = malloc(joy->numaxis * sizeof(SGbool));

    return joy;
}
void SG_EXPORT _sgJoystickDestroy(_SGJoystick* joy)
{
    if(joy == NULL)
        return;

    free(joy->aprev);
    free(joy->acurr);
    free(joy->adelt);
    free(joy->bprev);
    free(joy->bcurr);

    if(sgmCoreJoystickDestroy != NULL)
        sgmCoreJoystickDestroy(joy->handle);

    free(joy);
}

SGbool SG_EXPORT sgJoystickGetButtonPrev(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bprev[button];
}
SGbool SG_EXPORT sgJoystickGetButton(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bcurr[button];
}
SGbool SG_EXPORT sgJoystickGetButtonPress(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bcurr[button] && !_sg_joyJoys[joy]->bprev[button];
}
SGbool SG_EXPORT sgJoystickGetButtonRelease(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bprev[button] && !_sg_joyJoys[joy]->bcurr[button];
}

float* SG_EXPORT sgJoystickGetAxisPrev(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->aprev;
}
float SG_EXPORT sgJoystickGetAxisIndexPrev(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->aprev[axis];
}

float* SG_EXPORT sgJoystickGetAxis(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->acurr;
}
float SG_EXPORT sgJoystickGetAxisIndex(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->acurr[axis];
}

float* SG_EXPORT sgJoystickGetAxisDelta(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->adelt;
}
float SG_EXPORT sgJoystickGetAxisIndexDelta(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->adelt[axis];
}
