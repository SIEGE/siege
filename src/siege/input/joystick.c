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
    if(psgmCoreJoystickGetID != NULL)
        psgmCoreJoystickGetID(joystick, &joy);

    _sg_joyJoys[joy]->bprev[button] = _sg_joyJoys[joy]->bcurr[button];
    _sg_joyJoys[joy]->bcurr[button] = down;

    SGbool pressed = _sg_joyJoys[joy]->bcurr[button] && !_sg_joyJoys[joy]->bprev[button];

    SGenum evt = 0;
    if(pressed)
        evt = SG_EVF_JOYSTICKBUTP;
    else if(!down)
        evt = SG_EVF_JOYSTICKBUTR;
    else
        return;

    sgEntityEventSignal(1, evt, joy, button);
}
void SG_EXPORT _sg_cbJoystickMove(void* joystick, float* axis)
{
    SGuint joy = 0;
    if(psgmCoreJoystickGetID != NULL)
        psgmCoreJoystickGetID(joystick, &joy);

    memcpy(_sg_joyJoys[joy]->aprev, _sg_joyJoys[joy]->acurr, _sg_joyJoys[joy]->numaxis * sizeof(float));
    memcpy(_sg_joyJoys[joy]->acurr, axis, _sg_joyJoys[joy]->numaxis * sizeof(float));
    size_t i;
    for(i = 0; i < _sg_joyJoys[joy]->numaxis; i++)
        _sg_joyJoys[joy]->adelt[i] = _sg_joyJoys[joy]->acurr[i] - _sg_joyJoys[joy]->aprev[i];

    sgEntityEventSignal(1, (SGenum)SG_EVF_JOYSTICKMOVE, joy, axis, _sg_joyJoys[joy]->numaxis);
}

void SG_EXPORT _sgJoystickUpdate(void)
{
    SGenum i, j;
    for(i = 0; i < _sg_joyNum; i++)
        for(j = 0; j < _sg_joyJoys[i]->numbuttons; j++)
            if(_sg_joyJoys[i]->bcurr[j])
                sgEntityEventSignal(1, (SGenum)SG_EVF_JOYSTICKBUTH, i, j);
}

SGbool SG_EXPORT _sgJoystickInit(void)
{
    _sg_joyCallbacks.button = _sg_cbJoystickButton;
    _sg_joyCallbacks.move = _sg_cbJoystickMove;

    size_t i;
    _sg_joyNum = 0;

    if(psgmCoreJoystickGetNumJoysticks != NULL)
        psgmCoreJoystickGetNumJoysticks(_sg_winHandle, &_sg_joyNum);

    _sg_joyJoys = malloc(_sg_joyNum * sizeof(_SGJoystick*));
    for(i = 0; i < _sg_joyNum; i++)
        _sg_joyJoys[i] = _sgJoystickCreate(i);

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

    if(psgmCoreJoystickCreate != NULL)
        psgmCoreJoystickCreate(&joy->handle, _sg_winHandle, id);
    if(psgmCoreJoystickSetCallbacks != NULL)
        psgmCoreJoystickSetCallbacks(joy->handle, &_sg_joyCallbacks);

    if(psgmCoreJoystickGetNumButtons != NULL)
        psgmCoreJoystickGetNumButtons(joy->handle, &joy->numbuttons);
    joy->bprev = malloc(joy->numbuttons * sizeof(SGbool));
    memset(joy->bprev, 0, joy->numbuttons * sizeof(SGbool));
    joy->bcurr = malloc(joy->numbuttons * sizeof(SGbool));
    memset(joy->bcurr, 0, joy->numbuttons * sizeof(SGbool));

    if(psgmCoreJoystickGetNumAxis != NULL)
        psgmCoreJoystickGetNumAxis(joy->handle, &joy->numaxis);
    joy->aprev = malloc(joy->numaxis * sizeof(float));
    joy->acurr = malloc(joy->numaxis * sizeof(float));
    joy->adelt = malloc(joy->numaxis * sizeof(float));
    size_t i;
    for(i = 0; i < joy->numaxis; i++)
        joy->aprev[i] = joy->acurr[i] = joy->adelt[i] = 0.0;

    return joy;
}
void SG_EXPORT _sgJoystickDestroy(_SGJoystick* joy)
{
    if(joy == NULL)
        return;

    if(psgmCoreJoystickDestroy != NULL)
        psgmCoreJoystickDestroy(joy->handle);

    free(joy->aprev);
    free(joy->acurr);
    free(joy->adelt);
    free(joy->bprev);
    free(joy->bcurr);

    free(joy);
}

size_t SG_EXPORT sgJoystickGetNumJoysticks(void)
{
    return _sg_joyNum;
}
size_t SG_EXPORT sgJoystickGetNumButtons(SGuint joy)
{
    if(joy > _sg_joyNum) return 0;
    return _sg_joyJoys[joy]->numbuttons;
}
size_t SG_EXPORT sgJoystickGetNumAxis(SGuint joy)
{
    if(joy > _sg_joyNum) return 0;
    return _sg_joyJoys[joy]->numaxis;
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
