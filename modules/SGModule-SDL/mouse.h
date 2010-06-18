#ifndef __MOUSE_H__
#define __MOUSE_H__

Uint8 mouseState;
int mouseX;
int mouseY;
int mouseW;

void mouseButton(int button, int action);
void mouseMove(int x, int y);
void mouseWheel(int w);

#endif // __MOUSE_H__
