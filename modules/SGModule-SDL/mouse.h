#ifndef __MOUSE_H__
#define __MOUSE_H__

Uint8 mouseState;
int mouseX;
int mouseY;
int mouseW;

void cbMouseButton(int button, int action);
void cbMouseMove(int x, int y);
void cbMouseWheel(int w);

#endif // __MOUSE_H__
