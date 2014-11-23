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

#ifndef __SIEGE_INPUT_KEYBOARD_H__
#define __SIEGE_INPUT_KEYBOARD_H__
#include "../common.h"

/**
 * \name Keyboard keys
 */
/// @{
#define SG_KEY_UNKNOWN      0x000
#define SG_KEY_SPACE        0x020
#define SG_KEY_ESC          0x100
#define SG_KEY_F1           0x101
#define SG_KEY_F2           0x102
#define SG_KEY_F3           0x103
#define SG_KEY_F4           0x104
#define SG_KEY_F5           0x105
#define SG_KEY_F6           0x106
#define SG_KEY_F7           0x107
#define SG_KEY_F8           0x108
#define SG_KEY_F9           0x109
#define SG_KEY_F10          0x10A
#define SG_KEY_F11          0x10B
#define SG_KEY_F12          0x10C
#define SG_KEY_F13          0x10D
#define SG_KEY_F14          0x10E
#define SG_KEY_F15          0x10F
#define SG_KEY_F16          0x110
#define SG_KEY_F17          0x111
#define SG_KEY_F18          0x112
#define SG_KEY_F19          0x113
#define SG_KEY_F20          0x114
#define SG_KEY_F21          0x115
#define SG_KEY_F22          0x116
#define SG_KEY_F23          0x117
#define SG_KEY_F24          0x118
#define SG_KEY_F25          0x119
#define SG_KEY_UP           0x200
#define SG_KEY_DOWN         0x201
#define SG_KEY_LEFT         0x202
#define SG_KEY_RIGHT        0x203
#define SG_KEY_LSHIFT       0x210
#define SG_KEY_RSHIFT       0x211
#define SG_KEY_LCTRL        0x220
#define SG_KEY_RCTRL        0x221
#define SG_KEY_LALT         0x230
#define SG_KEY_RALT         0x231
#define SG_KEY_TAB          0x240
#define SG_KEY_ENTER        0x241
#define SG_KEY_BACKSPACE    0x242
#define SG_KEY_INSERT       0x250
#define SG_KEY_DELETE       0x251
#define SG_KEY_HOME         0x252
#define SG_KEY_END          0x253
#define SG_KEY_PAGEUP       0x254
#define SG_KEY_PAGEDOWN     0x255
#define SG_KEY_KP0          0x300
#define SG_KEY_KP1          0x301
#define SG_KEY_KP2          0x302
#define SG_KEY_KP3          0x303
#define SG_KEY_KP4          0x304
#define SG_KEY_KP5          0x305
#define SG_KEY_KP6          0x306
#define SG_KEY_KP7          0x307
#define SG_KEY_KP8          0x308
#define SG_KEY_KP9          0x309
#define SG_KEY_KP_ADD       0x310
#define SG_KEY_KP_SUBTRACT  0x311
#define SG_KEY_KP_MULTIPLY  0x312
#define SG_KEY_KP_DIVIDE    0x313
#define SG_KEY_KP_DECIMAL   0x314
#define SG_KEY_KP_EQUAL     0x315
#define SG_KEY_KP_ENTER     0x316
/// @}

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

void SG_CALL _sg_cbKeyboardKey(SGuint key, SGbool down);
void SG_CALL _sg_cbKeyboardChar(SGdchar chr);

void SG_CALL _sgKeyboardUpdatePre(void);
void SG_CALL _sgKeyboardUpdatePost(void);

SGbool SG_CALL _sgKeyboardInit(void);
SGbool SG_CALL _sgKeyboardDeinit(void);

void SG_CALL _sgKeyboardKeyUpdate(SGenum key, SGbool down);

SGbool SG_CALL sgKeyboardKey(SGenum key);
SGbool SG_CALL sgKeyboardKeyPress(SGenum key);
SGbool SG_CALL sgKeyboardKeyRelease(SGenum key);
SGbool SG_CALL sgKeyboardKeyRepeat(SGenum key);

// might re-add this in the future; probably not
// SGbool SG_CALL sgKeyboardCharPress(SGdchar chr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_INPUT_KEYBOARD_H__
