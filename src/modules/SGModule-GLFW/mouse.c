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
#include "mouse.h"
#include "window.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

void GLFWCALL mouseButton(int button, int action)
{
    if(main_window->cbMouse->button != NULL)
        main_window->cbMouse->button((void*)1, button - GLFW_MOUSE_BUTTON_1 + 1, action);
}

void GLFWCALL mouseMove(int x, int y)
{
    if(main_window->cbMouse->move != NULL)
        main_window->cbMouse->move((void*)1, x, y);
}

void GLFWCALL mouseWheel(int w)
{
    if(main_window->cbMouse->wheel != NULL)
        main_window->cbMouse->wheel((void*)1, w);
}

SGenum SG_EXPORT sgmCoreMouseCreate(void** mouse, void* window)
{
    *mouse = (void*)1;
    return SG_OK;
}
SGenum SG_EXPORT sgmCoreMouseDestroy(void* mouse)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    return SG_OK;
}
// should these two [sgmCoreMouseShow,sgmCoreMouseHide] be put into a single function?
SGenum SG_EXPORT sgmCoreMouseShow(void* mouse)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    glfwEnable(GLFW_MOUSE_CURSOR);
    return SG_OK;
}
SGenum SG_EXPORT sgmCoreMouseHide(void* mouse)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    glfwDisable(GLFW_MOUSE_CURSOR);
    return SG_OK;
}
//SGenum SG_EXPORT sgmCoreMouseIsShown(void* mouse, SGbool* shown);
//SGenum SG_EXPORT sgmCoreMouseIsHidden(void* mouse, SGbool* hidden);
SGenum SG_EXPORT sgmCoreMouseGetNumButtons(void* mouse, size_t* numbuttons)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numbuttons = GLFW_MOUSE_BUTTON_LAST - GLFW_MOUSE_BUTTON_1 + 1;
    return SG_OK;
}
//SGenum SG_EXPORT sgmCoreMouseButtonSetState(void* mouse, SGbool* state);
SGenum SG_EXPORT sgmCoreMouseButtonGetState(void* mouse, SGbool* state)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    size_t numbuttons;
    sgmCoreMouseGetNumButtons(mouse, &numbuttons);
    size_t i;
    for(i = 0; i < numbuttons; i++)
        state[i] = glfwGetMouseButton(GLFW_MOUSE_BUTTON_1 + i);

    return SG_OK;
}
SGenum SG_EXPORT sgmCoreMouseSetPosition(void* mouse, SGint x, SGint y)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    glfwSetMousePos(x, y);

    return SG_OK;
}
SGenum SG_EXPORT sgmCoreMouseGetPosition(void* mouse, SGint* x, SGint* y)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    glfwGetMousePos(x, y);

    return SG_OK;
}
//SGenum SG_EXPORT sgmCoreMouseSetWheel(void* mouse, SGint w);
SGenum SG_EXPORT sgmCoreMouseGetWheel(void* mouse, SGint* w)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *w = glfwGetMouseWheel();

    return SG_OK;
}

SGenum SG_EXPORT sgmCoreMouseSetCallbacks(void* mouse, SGCoreMouseCallbacks* callbacks)
{
    if(mouse == NULL)
        return SG_OK; // SG_INVALID_VALUE

    if(callbacks == NULL)
        main_window->cbMouse = NULL; // TODO: check if memcpy handles NULL gracefully (if it does, remove this if/else)
    else
        main_window->cbMouse = memcpy(main_window->cbMouse, callbacks, sizeof(SGCoreMouseCallbacks));

    return SG_OK;
}
//SGenum SG_EXPORT sgmCoreMouseGetCallbacks(void* mouse, SGCoreMouseCallbacks** callbacks);
