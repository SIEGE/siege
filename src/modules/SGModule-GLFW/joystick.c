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

#include "main.h"
#include "window.h"
#include "joystick.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

void _swapPtr(void** a, void** b)
{
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}

SGuint SG_EXPORT sgmCoreJoystickGetNumJoysticks(void* window, size_t* numjoys)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numjoys = 0;
    while(glfwGetJoystickParam(GLFW_JOYSTICK_1 + *numjoys, GLFW_PRESENT))
        (*numjoys)++;

    return SG_OK;
}

SGuint SG_EXPORT sgmCoreJoystickCreate(void** joystick, void* window, SGuint id)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick** cjoystick = (Joystick**)joystick;

    *cjoystick = malloc(sizeof(Joystick));
    (*cjoystick)->id = GLFW_JOYSTICK_1 + id;
    (*cjoystick)->active = glfwGetJoystickParam((*cjoystick)->id, GLFW_PRESENT);

    (*cjoystick)->numaxis = glfwGetJoystickParam((*cjoystick)->id, GLFW_AXES);
    (*cjoystick)->paxis = calloc((*cjoystick)->numaxis, sizeof(float));
    (*cjoystick)->axis = calloc((*cjoystick)->numaxis, sizeof(float));
    (*cjoystick)->numbuttons = glfwGetJoystickParam((*cjoystick)->id, GLFW_BUTTONS);
    (*cjoystick)->pbuttons = calloc((*cjoystick)->numbuttons, sizeof(SGbool));
    (*cjoystick)->buttons = calloc((*cjoystick)->numbuttons, sizeof(SGbool));

    joylist = realloc(joylist, (joylen + 1) * sizeof(Joystick*));
    joylist[joylen++] = *cjoystick;

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickDestroy(void* joystick)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    size_t i;
    for(i = 0; i < joylen; i++)
    {
        if(joylist[i] == cjoystick)
        {
            memmove(joylist + i, joylist + i + 1, (joylen - i - 1) * sizeof(Joystick));
            if(!--joylen)
            {
                free(joylist);
                joylist = NULL;
            }
            break;
        }
    }

    free(cjoystick->paxis);
    free(cjoystick->axis);
    free(cjoystick->pbuttons);
    free(cjoystick->buttons);
    free(cjoystick);

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetID(void* joystick, SGuint* id)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *id = cjoystick->id - GLFW_JOYSTICK_1;

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetNumButtons(void* joystick, size_t* numbuttons)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *numbuttons = cjoystick->numbuttons;

    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreJoystickButtonSetState(void* joystick, SGbool* state)
SGuint SG_EXPORT sgmCoreJoystickButtonGetState(void* joystick, SGbool* state)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    glfwGetJoystickButtons(cjoystick->id, cjoystick->buttons, cjoystick->numbuttons);
    state = memcpy(state, cjoystick->buttons, cjoystick->numbuttons * sizeof(SGbool));

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetNumAxis(void* joystick, size_t* numaxis)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *numaxis = cjoystick->numaxis;

    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreJoystickAxisSetPosition(void* joystick, float* position);
SGuint SG_EXPORT sgmCoreJoystickAxisGetPosition(void* joystick, float* position)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    glfwGetJoystickPos(cjoystick->id, cjoystick->axis, cjoystick->numaxis);
    position = memcpy(position, cjoystick->axis, cjoystick->numaxis * sizeof(float));

    return SG_OK;
}

SGuint SG_EXPORT sgmCoreJoystickSetCallbacks(void* joystick, SGCoreJoystickCallbacks* callbacks)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    Window* cwindow = main_window;
    if(!callbacks)
        cwindow->cbJoystick = NULL;
    else
        memcpy(cwindow->cbJoystick, callbacks, sizeof(SGCoreJoystickCallbacks));

    return SG_OK; // SG_INVALID_VALUE
}
//SGuint SG_EXPORT sgmCoreJoystickGetCallbacks(void* joystick, SGCoreJoystickCallbacks** callbacks);
