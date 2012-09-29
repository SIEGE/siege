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
#include "keyboard.h"
#include "window.h"

#include <string.h>
#include <ctype.h>

static const int keysSDL[] = {
         SDLK_SPACE    , SDLK_ESCAPE
        ,SDLK_F1       , SDLK_F2         , SDLK_F3       , SDLK_F4      , SDLK_F5  , SDLK_F6
        ,SDLK_F7       , SDLK_F8         , SDLK_F9       , SDLK_F10     , SDLK_F11 , SDLK_F12
        ,SDLK_F13      , SDLK_F14        , SDLK_F15
        ,SDLK_UP       , SDLK_DOWN       , SDLK_LEFT     , SDLK_RIGHT
        ,SDLK_LSHIFT   , SDLK_RSHIFT     , SDLK_LCTRL    , SDLK_RCTRL   , SDLK_LALT, SDLK_RALT
        ,SDLK_TAB      , SDLK_RETURN     , SDLK_BACKSPACE
        ,SDLK_INSERT   , SDLK_DELETE     , SDLK_PAGEUP   , SDLK_PAGEDOWN, SDLK_HOME, SDLK_END
        ,SDLK_KP0      , SDLK_KP1        , SDLK_KP2      , SDLK_KP3     , SDLK_KP4
        ,SDLK_KP5      , SDLK_KP6        , SDLK_KP7      , SDLK_KP8     , SDLK_KP9
        ,SDLK_KP_DIVIDE, SDLK_KP_MULTIPLY, SDLK_KP_MINUS , SDLK_KP_PLUS
        ,SDLK_KP_PERIOD, SDLK_KP_EQUALS  , SDLK_KP_ENTER
        ,SDLK_UNKNOWN
    };
static const SGenum keysSIEGE[] = {
         SG_KEY_SPACE     , SG_KEY_ESC
        ,SG_KEY_F1        , SG_KEY_F2         , SG_KEY_F3         , SG_KEY_F4      , SG_KEY_F5  , SG_KEY_F6
        ,SG_KEY_F7        , SG_KEY_F8         , SG_KEY_F9         , SG_KEY_F10     , SG_KEY_F11 , SG_KEY_F12
        ,SG_KEY_F13       , SG_KEY_F14        , SG_KEY_F15
        ,SG_KEY_UP        , SG_KEY_DOWN       , SG_KEY_LEFT       , SG_KEY_RIGHT
        ,SG_KEY_LSHIFT    , SG_KEY_RSHIFT     , SG_KEY_LCTRL      , SG_KEY_RCTRL   , SG_KEY_LALT, SG_KEY_RALT
        ,SG_KEY_TAB       , SG_KEY_ENTER      , SG_KEY_BACKSPACE
        ,SG_KEY_INSERT    , SG_KEY_DELETE     , SG_KEY_PAGEUP     , SG_KEY_PAGEDOWN, SG_KEY_HOME, SG_KEY_END
        ,SG_KEY_KP0       , SG_KEY_KP1        , SG_KEY_KP2        , SG_KEY_KP3     , SG_KEY_KP4
        ,SG_KEY_KP5       , SG_KEY_KP6        , SG_KEY_KP7        , SG_KEY_KP8     , SG_KEY_KP9
        ,SG_KEY_KP_DIVIDE , SG_KEY_KP_MULTIPLY, SG_KEY_KP_SUBTRACT, SG_KEY_KP_ADD
        ,SG_KEY_KP_DECIMAL, SG_KEY_KP_EQUAL   , SG_KEY_KP_ENTER
        ,SG_KEY_UNKNOWN
    };

/* TODO: change into O(1) conversion by using direct table access */
static SGenum keySDLtoSIEGE(int key)
{
    SGuint sgkey = key;
    int i;
    for(i = 0; keysSDL[i] != 0; i++)
        if(keysSDL[i] == key)
        {
            sgkey = keysSIEGE[i];
            break;
        }
    if(keysSDL[i] == 0) // if we didn't find a key
        sgkey = toupper(sgkey);
    return sgkey;
}

static int dummyKeyboard = 1;

void keyboardKey(int key, int down)
{
    if(main_window->cbKeyboard->key != NULL)
        main_window->cbKeyboard->key(&dummyKeyboard, keySDLtoSIEGE(key), down);
}
void keyboardChar(int chr)
{
    if(main_window->cbKeyboard->chr != NULL)
        main_window->cbKeyboard->chr(&dummyKeyboard, chr);
}

SGenum SG_EXPORT sgmCoreKeyboardCreate(void** keyboard, void* window)
{
    *keyboard = &dummyKeyboard;
    return SG_OK;
}
SGenum SG_EXPORT sgmCoreKeyboardDestroy(void* keyboard)
{
    if(keyboard == NULL)
        return SG_INVALID_VALUE;
    return SG_OK;
}

SGenum SG_EXPORT sgmCoreKeyboardSetCallbacks(void* keyboard, SGCoreKeyboardCallbacks* callbacks)
{
    if(keyboard == NULL)
        return SG_INVALID_VALUE;

    if(callbacks == NULL)
        main_window->cbKeyboard = NULL;
    else
        memcpy(main_window->cbKeyboard, callbacks, sizeof(SGCoreKeyboardCallbacks));

    return SG_OK;
}
//SGenum SG_EXPORT sgmCoreKeyboardGetCallbacks(void* keyboard, SGCoreKeyboardCallbacks** callbacks);
