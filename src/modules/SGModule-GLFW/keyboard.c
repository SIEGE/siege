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
#include "keyboard.h"
#include "window.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

int keysGLFW[] = {
     GLFW_KEY_SPACE    , GLFW_KEY_ESC
    ,GLFW_KEY_F1       , GLFW_KEY_F2         , GLFW_KEY_F3         , GLFW_KEY_F4      , GLFW_KEY_F5        , GLFW_KEY_F6
    ,GLFW_KEY_F7       , GLFW_KEY_F8         , GLFW_KEY_F9         , GLFW_KEY_F10     , GLFW_KEY_F11       , GLFW_KEY_F12
    ,GLFW_KEY_F13      , GLFW_KEY_F14        , GLFW_KEY_F15        , GLFW_KEY_F16     , GLFW_KEY_F17       , GLFW_KEY_F18     , GLFW_KEY_F19
    ,GLFW_KEY_F20      , GLFW_KEY_F21        , GLFW_KEY_F22        , GLFW_KEY_F23     , GLFW_KEY_F24       , GLFW_KEY_F25
    ,GLFW_KEY_UP       , GLFW_KEY_DOWN       , GLFW_KEY_LEFT       , GLFW_KEY_RIGHT
    ,GLFW_KEY_LSHIFT   , GLFW_KEY_RSHIFT     , GLFW_KEY_LCTRL      , GLFW_KEY_RCTRL   , GLFW_KEY_LALT      , GLFW_KEY_RALT
    ,GLFW_KEY_TAB      , GLFW_KEY_ENTER      , GLFW_KEY_BACKSPACE
    ,GLFW_KEY_INSERT   , GLFW_KEY_DEL        , GLFW_KEY_PAGEUP     , GLFW_KEY_PAGEDOWN, GLFW_KEY_HOME      , GLFW_KEY_END
    ,GLFW_KEY_KP_0     , GLFW_KEY_KP_1       , GLFW_KEY_KP_2       , GLFW_KEY_KP_3    , GLFW_KEY_KP_4      , GLFW_KEY_KP_5    , GLFW_KEY_KP_6    , GLFW_KEY_KP_7 , GLFW_KEY_KP_8, GLFW_KEY_KP_9
    ,GLFW_KEY_KP_DIVIDE, GLFW_KEY_KP_MULTIPLY, GLFW_KEY_KP_SUBTRACT, GLFW_KEY_KP_ADD  , GLFW_KEY_KP_DECIMAL, GLFW_KEY_KP_EQUAL, GLFW_KEY_KP_ENTER
    ,0
};

SGuint keysSIEGE[] = {
     SG_KEYBOARD_KEY_SPACE, SG_KEYBOARD_KEY_ESC
    ,SG_KEYBOARD_KEY_F1, SG_KEYBOARD_KEY_F2, SG_KEYBOARD_KEY_F3, SG_KEYBOARD_KEY_F4, SG_KEYBOARD_KEY_F5, SG_KEYBOARD_KEY_F6
    ,SG_KEYBOARD_KEY_F7, SG_KEYBOARD_KEY_F8, SG_KEYBOARD_KEY_F9, SG_KEYBOARD_KEY_F10, SG_KEYBOARD_KEY_F11, SG_KEYBOARD_KEY_F12
    ,SG_KEYBOARD_KEY_F13, SG_KEYBOARD_KEY_F14, SG_KEYBOARD_KEY_F15, SG_KEYBOARD_KEY_F16, SG_KEYBOARD_KEY_F17, SG_KEYBOARD_KEY_F18, SG_KEYBOARD_KEY_F19
    ,SG_KEYBOARD_KEY_F20, SG_KEYBOARD_KEY_F21, SG_KEYBOARD_KEY_F22, SG_KEYBOARD_KEY_F23, SG_KEYBOARD_KEY_F24, SG_KEYBOARD_KEY_F25
    ,SG_KEYBOARD_KEY_UP, SG_KEYBOARD_KEY_DOWN, SG_KEYBOARD_KEY_LEFT, SG_KEYBOARD_KEY_RIGHT
    ,SG_KEYBOARD_KEY_LSHIFT, SG_KEYBOARD_KEY_RSHIFT, SG_KEYBOARD_KEY_LCTRL, SG_KEYBOARD_KEY_RCTRL, SG_KEYBOARD_KEY_LALT, SG_KEYBOARD_KEY_RALT
    ,SG_KEYBOARD_KEY_TAB, SG_KEYBOARD_KEY_ENTER, SG_KEYBOARD_KEY_BACKSPACE
    ,SG_KEYBOARD_KEY_INSERT, SG_KEYBOARD_KEY_DELETE, SG_KEYBOARD_KEY_PAGEUP, SG_KEYBOARD_KEY_PAGEDOWN, SG_KEYBOARD_KEY_HOME, SG_KEYBOARD_KEY_END
    ,SG_KEYBOARD_KEY_KP0, SG_KEYBOARD_KEY_KP1, SG_KEYBOARD_KEY_KP2, SG_KEYBOARD_KEY_KP3, SG_KEYBOARD_KEY_KP4, SG_KEYBOARD_KEY_KP5, SG_KEYBOARD_KEY_KP6, SG_KEYBOARD_KEY_KP7, SG_KEYBOARD_KEY_KP8, SG_KEYBOARD_KEY_KP9
    ,SG_KEYBOARD_KEY_KP_DIVIDE, SG_KEYBOARD_KEY_KP_MULTIPLY, SG_KEYBOARD_KEY_KP_SUBTRACT, SG_KEYBOARD_KEY_KP_ADD, SG_KEYBOARD_KEY_KP_DECIMAL, SG_KEYBOARD_KEY_KP_EQUAL, SG_KEYBOARD_KEY_KP_ENTER
    ,0
};

SGuint keyGLFWtoSIEGE(int key)
{
    SGuint sgkey = key;

    int i;
    for(i = 0; keysGLFW[i] != 0; i++)
        if(keysGLFW[i] == key)
        {
            sgkey = keysSIEGE[i];
            break;
        }

    return sgkey;
}
int keySIEGEtoGLFW(SGuint key)
{
    int glfwkey = key;

    int i;
    for(i = 0; keysSIEGE[i] != 0; i++)
        if(keysSIEGE[i] == key)
        {
            glfwkey = keysGLFW[i];
            break;
        }

    return glfwkey;
}

void GLFWCALL keyboardKey(int key, int down)
{
    if(main_window->cbKeyboard->key != NULL)
        main_window->cbKeyboard->key((void*)1, keyGLFWtoSIEGE(key), down);
}
void GLFWCALL keyboardChar(int chr, int down)
{
    if(main_window->cbKeyboard->chr != NULL)
        main_window->cbKeyboard->chr((void*)1, chr, down);
}

SGuint SG_EXPORT sgmCoreKeyboardCreate(void** keyboard, void* window)
{
    *keyboard = malloc(1);
    return SG_OK;
}
SGuint SG_EXPORT sgmCoreKeyboardDestroy(void* keyboard)
{
    if(keyboard == NULL)
        return SG_OK; // SG_INVALID_VALUE

    free(keyboard);
    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreKeyboardSetKey(void* keyboard, SGuint key, SGbool down);
SGuint SG_EXPORT sgmCoreKeyboardGetKey(void* keyboard, SGuint key, SGbool* down)
{
    if(keyboard == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *down = glfwGetKey(keySIEGEtoGLFW(key));
    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreKeyboardSetChr(void* keyboard, SGuint chr, SGbool down);
//SGuint SG_EXPORT sgmCoreKeyboardGetChr(void* keyboard, SGuint chr, SGbool* down);

SGuint SG_EXPORT sgmCoreKeyboardSetCallbacks(void* keyboard, SGCoreKeyboardCallbacks* callbacks)
{
    if(keyboard == NULL)
        return SG_OK; // SG_INVALID_VALUE

    if(callbacks == NULL)
        main_window->cbKeyboard = NULL; // TODO: check if memcpy handles NULL gracefully (if it does, remove this if/else)
    else
        main_window->cbKeyboard = memcpy(main_window->cbKeyboard, callbacks, sizeof(SGCoreKeyboardCallbacks));

    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreKeyboardGetCallbacks(void* keyboard, SGCoreKeyboardCallbacks** callbacks);
