#ifndef __WINDOW_H__
#define __WINDOW_H__

typedef struct Window
{
    SGCoreWindowCallbacks* cbWindow;
    SGCoreJoystickCallbacks* cbJoystick;
    SGCoreKeyboardCallbacks* cbKeyboard;
    SGCoreMouseCallbacks* cbMouse;
} Window;
Window* main_window;

void GLFWCALL windowOpen();
int GLFWCALL windowClose();
void GLFWCALL windowResize(int x, int y);

#endif // __WINDOW_H__
