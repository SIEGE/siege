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

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

Uint8* keyStates;
int keyNumStates;

SGuint keySDLtoSIEGE(int key);
int keySIEGEtoSDL(SGuint key);

void keyboardKey(int key, int down);
void keyboardChar(int chr);

#endif // __KEYBOARD_H__
