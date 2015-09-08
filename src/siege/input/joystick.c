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
#include <siege/input/vinput.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>
#include "../internal/bitop.h"

void SG_CALL _sg_cbJoystickButton(SGuint joy, SGuint button, SGbool down)
{
    SET_BITARR(_sg_joyJoys[joy]->bcurr, button, down);
    _sgVInputUpdateJoystick(joy);
    SGbool pressed = sgJoystickGetButtonPress(joy, button);

    SGenum event = 0;
    if(pressed)
        event = SG_EVF_INPUTBUTP;
    else if(!down)
        event = SG_EVF_INPUTBUTR;
    else
        return;

    sgEntityEventSignal(1, event, SG_INPUT_ID_JOYSTICK(joy), button);
}
void SG_CALL _sg_cbJoystickMove(SGuint joy, SGuint axis, float pos)
{
    memcpy(_sg_joyJoys[joy]->aprev, _sg_joyJoys[joy]->acurr, _sg_joyJoys[joy]->numaxis * sizeof(float));
    _sg_joyJoys[joy]->acurr[axis] = pos;
    size_t i;
    for(i = 0; i < _sg_joyJoys[joy]->numaxis; i++)
        _sg_joyJoys[joy]->adelt[i] = _sg_joyJoys[joy]->acurr[i] - _sg_joyJoys[joy]->aprev[i];

    sgEntityEventSignal(1, (SGenum)SG_EVF_INPUTAMOVE, SG_INPUT_ID_JOYSTICK(joy), _sg_joyJoys[joy]->acurr, _sg_joyJoys[joy]->numaxis);
}

static SGIJoystick* SG_CALL _sgJoystickCreate(SGuint id)
{
    SGIJoystick* joy = malloc(sizeof(SGIJoystick));
    if(joy == NULL)
        return NULL;

    joy->id = id;
    joy->handle = SDL_JoystickOpen(id);
    joy->numbuttons = SDL_JoystickNumButtons(joy->handle);
    joy->numaxis = SDL_JoystickNumAxes(joy->handle);

    joy->bprev = malloc(ARR_BITLENGTH(joy->numbuttons) * sizeof(*joy->bprev));
    memset(joy->bprev, 0, ARR_BITLENGTH(joy->numbuttons) * sizeof(*joy->bprev));
    joy->bcurr = malloc(ARR_BITLENGTH(joy->numbuttons) * sizeof(*joy->bcurr));
    memset(joy->bcurr, 0, ARR_BITLENGTH(joy->numbuttons) * sizeof(*joy->bcurr));

    joy->taxis = malloc(joy->numaxis * sizeof(float));
    joy->aprev = malloc(joy->numaxis * sizeof(float));
    joy->acurr = malloc(joy->numaxis * sizeof(float));
    joy->adelt = malloc(joy->numaxis * sizeof(float));
    size_t i;
    for(i = 0; i < joy->numaxis; i++)
        joy->aprev[i] = joy->acurr[i] = joy->adelt[i] = 0.0;

    return joy;
}
static void SG_CALL _sgJoystickDestroy(SGIJoystick* joy)
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

void SG_CALL _sgJoystickUpdate(void)
{
    SGenum i, j;
    for(i = 0; i < _sg_joyNum; i++)
    {
        for(j = 0; j < _sg_joyJoys[i]->numbuttons; j++)
            if(_sg_joyJoys[i]->bcurr[j])
                sgEntityEventSignal(1, (SGenum)SG_EVF_INPUTBUTH, SG_INPUT_ID_JOYSTICK(i), j);
        memcpy(_sg_joyJoys[i]->bprev, _sg_joyJoys[i]->bcurr, ARR_BITLENGTH(_sg_joyJoys[i]->numbuttons) * sizeof(*_sg_joyJoys[i]->bcurr));
    }
}

SGbool SG_CALL _sgJoystickInit(void)
{
    size_t i;
    _sg_joyNum = SDL_NumJoysticks();
    if(_sg_joyNum > 14) _sg_joyNum = 14;

    _sg_joyJoys = malloc(_sg_joyNum * sizeof(SGIJoystick*));
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
