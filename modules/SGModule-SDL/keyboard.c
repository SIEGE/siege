#include "main.h"
#include "keyboard.h"
#include "window.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

int keysSDL[] = {
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
SGuint  keysSIEGE[] = {
         SG_KEYBOARD_KEY_SPACE     , SG_KEYBOARD_KEY_ESC
        ,SG_KEYBOARD_KEY_F1        , SG_KEYBOARD_KEY_F2         , SG_KEYBOARD_KEY_F3         , SG_KEYBOARD_KEY_F4      , SG_KEYBOARD_KEY_F5  , SG_KEYBOARD_KEY_F6
        ,SG_KEYBOARD_KEY_F7        , SG_KEYBOARD_KEY_F8         , SG_KEYBOARD_KEY_F9         , SG_KEYBOARD_KEY_F10     , SG_KEYBOARD_KEY_F11 , SG_KEYBOARD_KEY_F12
        ,SG_KEYBOARD_KEY_F13       , SG_KEYBOARD_KEY_F14        , SG_KEYBOARD_KEY_F15
        ,SG_KEYBOARD_KEY_UP        , SG_KEYBOARD_KEY_DOWN       , SG_KEYBOARD_KEY_LEFT       , SG_KEYBOARD_KEY_RIGHT
        ,SG_KEYBOARD_KEY_LSHIFT    , SG_KEYBOARD_KEY_RSHIFT     , SG_KEYBOARD_KEY_LCTRL      , SG_KEYBOARD_KEY_RCTRL   , SG_KEYBOARD_KEY_LALT, SG_KEYBOARD_KEY_RALT
        ,SG_KEYBOARD_KEY_TAB       , SG_KEYBOARD_KEY_ENTER      , SG_KEYBOARD_KEY_BACKSPACE
        ,SG_KEYBOARD_KEY_INSERT    , SG_KEYBOARD_KEY_DELETE     , SG_KEYBOARD_KEY_PAGEUP     , SG_KEYBOARD_KEY_PAGEDOWN, SG_KEYBOARD_KEY_HOME, SG_KEYBOARD_KEY_END
        ,SG_KEYBOARD_KEY_KP0       , SG_KEYBOARD_KEY_KP1        , SG_KEYBOARD_KEY_KP2        , SG_KEYBOARD_KEY_KP3     , SG_KEYBOARD_KEY_KP4
        ,SG_KEYBOARD_KEY_KP5       , SG_KEYBOARD_KEY_KP6        , SG_KEYBOARD_KEY_KP7        , SG_KEYBOARD_KEY_KP8     , SG_KEYBOARD_KEY_KP9
        ,SG_KEYBOARD_KEY_KP_DIVIDE , SG_KEYBOARD_KEY_KP_MULTIPLY, SG_KEYBOARD_KEY_KP_SUBTRACT, SG_KEYBOARD_KEY_KP_ADD
        ,SG_KEYBOARD_KEY_KP_DECIMAL, SG_KEYBOARD_KEY_KP_EQUAL   , SG_KEYBOARD_KEY_KP_ENTER
        ,SG_KEYBOARD_KEY_UNKNOWN
    };

SGuint keySDLtoSIEGE(int key)
{
    SGuint sgkey = key;
    int i;
    for(i = 0; keysSDL[i] != 0; i++)
        if(keysSDL[i] == key)
        {
            sgkey = keysSIEGE[i];
            break;
        }
    return sgkey;
}
int keySIEGEtoSDL(SGuint key)
{
    int sdlkey = key;
    int i;
    for(i = 0; keysSIEGE[i] != 0; i++)
        if(keysSIEGE[i] == key)
        {
            sdlkey = keysSDL[i];
            break;
        }
    return sdlkey;
}

void keyboardKey(int key, int down)
{
    if(main_window->cbKeyboard->key != NULL)
        main_window->cbKeyboard->key((void*)1, keySDLtoSIEGE(key), down);
}
void keyboardChar(int chr, int down)
{
    if(main_window->cbKeyboard->chr != NULL)
        main_window->cbKeyboard->chr((void*)1, chr, down);
}

SGuint SG_EXPORT sgCoreKeyboardCreate(void** keyboard, void* window)
{
    *keyboard = malloc(1);
    return SG_OK;
}
SGuint SG_EXPORT sgCoreKeyboardDestroy(void* keyboard)
{
    if(keyboard == NULL)
        return SG_OK; // SG_INVALID_VALUE

    free(keyboard);
    return SG_OK;
}
//SGuint SG_EXPORT sgCoreKeyboardSetKey(void* keyboard, SGuint key, SGbool down);
SGuint SG_EXPORT sgCoreKeyboardGetKey(void* keyboard, SGuint key, SGbool* down)
{
    if(keyboard == NULL)
        return SG_OK; // SG_INVALID_VALUE

    int sdlk = keySIEGEtoSDL(key);
    if(sdlk >= keyNumStates)
        return SG_UNKNOWN_ERROR; // SG_INVALID_VALUE
    *down = keyStates[sdlk];

    return SG_OK;
}
//SGuint SG_EXPORT sgCoreKeyboardSetChr(void* keyboard, SGuint chr, SGbool down);
//SGuint SG_EXPORT sgCoreKeyboardGetChr(void* keyboard, SGuint chr, SGbool* down);

SGuint SG_EXPORT sgCoreKeyboardSetCallbacks(void* keyboard, SGCoreKeyboardCallbacks* callbacks)
{
    if(keyboard == NULL)
        return SG_OK; // SG_INVALID_VALUE

    if(callbacks == NULL)
        main_window->cbKeyboard = NULL; // TODO: check if memcpy handles NULL gracefully (if it does, remove this if/else)
    else
        main_window->cbKeyboard = memcpy(main_window->cbKeyboard, callbacks, sizeof(SGCoreKeyboardCallbacks));

    return SG_OK;
}
//SGuint SG_EXPORT sgCoreKeyboardGetCallbacks(void* keyboard, SGCoreKeyboardCallbacks** callbacks);
