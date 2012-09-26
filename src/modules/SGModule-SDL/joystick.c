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

#include "common.h"
#include "window.h"
#include "joystick.h"

SGenum SG_EXPORT sgmCoreJoystickGetNumJoysticks(void* window, size_t* numjoys)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numjoys = SDL_NumJoysticks();

    return SG_OK;
}

SGenum SG_EXPORT sgmCoreJoystickCreate(void** joystick, void* window, SGuint id)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    if(id >= JOY_MAX)
        return SG_OK; // SG_INVALID_VALUE -- later something else

    *joystick = &joylist[id];

    if(!joylist[id].ref++)
    {
        joylist[id].sdl = SDL_JoystickOpen(id);
        joylist[id].axis = malloc(SDL_JoystickNumAxes(joylist[id].sdl) * sizeof(float));
    }

    return SG_OK;
}
SGenum SG_EXPORT sgmCoreJoystickDestroy(void* joystick)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = joystick;

    if(!--cjoystick->ref)
    {
        SDL_JoystickClose(cjoystick->sdl);
        free(cjoystick->axis);
    }

    return SG_OK;
}
SGenum SG_EXPORT sgmCoreJoystickGetID(void* joystick, SGuint* id)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = joystick;

    *id = SDL_JoystickIndex(cjoystick->sdl);

    return SG_OK;
}
SGenum SG_EXPORT sgmCoreJoystickGetNumButtons(void* joystick, size_t* numbuttons)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = joystick;

    *numbuttons = SDL_JoystickNumButtons(cjoystick->sdl);

    return SG_OK;
}
//SGenum SG_EXPORT sgmCoreJoystickButtonSetState(void* joystick, SGbool* state)
SGenum SG_EXPORT sgmCoreJoystickButtonGetState(void* joystick, SGbool* state)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = joystick;

    int numb = SDL_JoystickNumButtons(cjoystick->sdl);
    int i;
    for(i = 0; i < numb; i++)
        state[i] = SDL_JoystickGetButton(cjoystick->sdl, i);

    return SG_OK;
}
SGenum SG_EXPORT sgmCoreJoystickGetNumAxis(void* joystick, size_t* numaxis)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = joystick;

    *numaxis = SDL_JoystickNumAxes(cjoystick->sdl);

    return SG_OK;
}
//SGenum SG_EXPORT sgmCoreJoystickAxisSetPosition(void* joystick, float* position);
SGenum SG_EXPORT sgmCoreJoystickAxisGetPosition(void* joystick, float* position)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = joystick;

    int numa = SDL_JoystickNumAxes(cjoystick->sdl);
    int i;
    for(i = 0; i < numa; i++)
        position[i] = (SDL_JoystickGetAxis(cjoystick->sdl, i) + 0.5) / 32767.5;

    return SG_OK;
}

SGenum SG_EXPORT sgmCoreJoystickSetCallbacks(void* joystick, SGCoreJoystickCallbacks* callbacks)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    Window* cwindow = main_window;
    if(!callbacks)
        cwindow->cbJoystick = NULL;
    else
        memcpy(cwindow->cbJoystick, callbacks, sizeof(SGCoreJoystickCallbacks));

    return SG_OK;
}
//SGenum SG_EXPORT sgmCoreJoystickGetCallbacks(void* joystick, SGCoreJoystickCallbacks** callbacks);
