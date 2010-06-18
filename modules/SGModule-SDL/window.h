#ifndef __WINDOW_H__
#define __WINDOW_H__

typedef struct Window
{
    SDL_Surface* surface;
    SGbool opened;

    SGCoreWindowCallbacks* cbWindow;
    SGCoreJoystickCallbacks* cbJoystick;
    SGCoreKeyboardCallbacks* cbKeyboard;
    SGCoreMouseCallbacks* cbMouse;
} Window;
Window* main_window;

void windowOpen();
int windowClose();
void windowResize(int x, int y);

#endif // __WINDOW_H__
