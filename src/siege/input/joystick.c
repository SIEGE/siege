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
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>

void SG_CALL _sg_cbJoystickButton(SGuint joy, SGuint button, SGbool down)
{
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
void SG_CALL _sg_cbJoystickMove(SGuint joy, SGuint axis, float pos)
{
    memcpy(_sg_joyJoys[joy]->aprev, _sg_joyJoys[joy]->acurr, _sg_joyJoys[joy]->numaxis * sizeof(float));
    _sg_joyJoys[joy]->acurr[axis] = pos;
    size_t i;
    for(i = 0; i < _sg_joyJoys[joy]->numaxis; i++)
        _sg_joyJoys[joy]->adelt[i] = _sg_joyJoys[joy]->acurr[i] - _sg_joyJoys[joy]->aprev[i];

    sgEntityEventSignal(1, (SGenum)SG_EVF_JOYSTICKMOVE, joy, _sg_joyJoys[joy]->acurr, _sg_joyJoys[joy]->numaxis);
}

void SG_CALL _sgJoystickUpdate(void)
{
    SGenum i, j;
    for(i = 0; i < _sg_joyNum; i++)
        for(j = 0; j < _sg_joyJoys[i]->numbuttons; j++)
            if(_sg_joyJoys[i]->bcurr[j])
                sgEntityEventSignal(1, (SGenum)SG_EVF_JOYSTICKBUTH, i, j);
}

SGbool SG_CALL _sgJoystickInit(void)
{
    size_t i;
    _sg_joyNum = SDL_NumJoysticks();

    _sg_joyJoys = malloc(_sg_joyNum * sizeof(_SGJoystick*));
    for(i = 0; i < _sg_joyNum; i++)
        _sg_joyJoys[i] = _sgJoystickCreate(i);

    return SG_TRUE;
}
SGbool SG_CALL _sgJoystickDeinit(void)
{
    SGuint i;
    for(i = 0; i < _sg_joyNum; i++)
        _sgJoystickDestroy(_sg_joyJoys[i]);
    free(_sg_joyJoys);

    return SG_TRUE;
}

_SGJoystick* SG_CALL _sgJoystickCreate(SGuint id)
{
    _SGJoystick* joy = malloc(sizeof(_SGJoystick));
    if(joy == NULL)
        return NULL;

    joy->id = id;
    joy->numbuttons = 0;
    joy->numaxis = 0;

    joy->handle = SDL_JoystickOpen(id);
    joy->taxis = malloc(SDL_JoystickNumAxes(joy->handle) * sizeof(float));

    joy->numbuttons = SDL_JoystickNumButtons(joy->handle);
    joy->bprev = malloc(joy->numbuttons * sizeof(SGbool));
    memset(joy->bprev, 0, joy->numbuttons * sizeof(SGbool));
    joy->bcurr = malloc(joy->numbuttons * sizeof(SGbool));
    memset(joy->bcurr, 0, joy->numbuttons * sizeof(SGbool));

    joy->numaxis = SDL_JoystickNumAxes(joy->handle);
    joy->aprev = malloc(joy->numaxis * sizeof(float));
    joy->acurr = malloc(joy->numaxis * sizeof(float));
    joy->adelt = malloc(joy->numaxis * sizeof(float));
    size_t i;
    for(i = 0; i < joy->numaxis; i++)
        joy->aprev[i] = joy->acurr[i] = joy->adelt[i] = 0.0;

    return joy;
}
void SG_CALL _sgJoystickDestroy(_SGJoystick* joy)
{
    if(joy == NULL)
        return;

    SDL_JoystickClose(joy->handle);
    free(joy->taxis);

    free(joy->aprev);
    free(joy->acurr);
    free(joy->adelt);
    free(joy->bprev);
    free(joy->bcurr);

    free(joy);
}

size_t SG_CALL sgJoystickGetNumJoysticks(void)
{
    return _sg_joyNum;
}
size_t SG_CALL sgJoystickGetNumButtons(SGuint joy)
{
    if(joy > _sg_joyNum) return 0;
    return _sg_joyJoys[joy]->numbuttons;
}
size_t SG_CALL sgJoystickGetNumAxis(SGuint joy)
{
    if(joy > _sg_joyNum) return 0;
    return _sg_joyJoys[joy]->numaxis;
}

SGbool SG_CALL sgJoystickGetButtonPrev(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bprev[button];
}
SGbool SG_CALL sgJoystickGetButton(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bcurr[button];
}
SGbool SG_CALL sgJoystickGetButtonPress(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bcurr[button] && !_sg_joyJoys[joy]->bprev[button];
}
SGbool SG_CALL sgJoystickGetButtonRelease(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bprev[button] && !_sg_joyJoys[joy]->bcurr[button];
}

float* SG_CALL sgJoystickGetAxisPrev(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->aprev;
}
float SG_CALL sgJoystickGetAxisIndexPrev(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->aprev[axis];
}

float* SG_CALL sgJoystickGetAxis(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->acurr;
}
float SG_CALL sgJoystickGetAxisIndex(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->acurr[axis];
}

float* SG_CALL sgJoystickGetAxisDelta(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->adelt;
}
float SG_CALL sgJoystickGetAxisIndexDelta(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->adelt[axis];
}
