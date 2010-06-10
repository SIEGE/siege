#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

SGuint keyGLFWtoSIEGE(int key);
int keySIEGEtoGLFW(SGuint key);

void GLFWCALL cbKeyboardKey(int key, int down);
void GLFWCALL cbKeyboardChar(int chr, int down);

#endif // __KEYBOARD_H__
