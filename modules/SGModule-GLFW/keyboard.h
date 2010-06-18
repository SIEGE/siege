#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

SGuint keyGLFWtoSIEGE(int key);
int keySIEGEtoGLFW(SGuint key);

void GLFWCALL keyboardKey(int key, int down);
void GLFWCALL keyboardChar(int chr, int down);

#endif // __KEYBOARD_H__
