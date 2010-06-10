#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

Uint8* keyStates;
int keyNumStates;

SGuint keySDLtoSIEGE(int key);
int keySIEGEtoSDL(SGuint key);

void cbKeyboardKey(int key, int down);
void cbKeyboardChar(int chr, int down);

#endif // __KEYBOARD_H__
