#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

typedef struct Joystick
{
    SGuint id;
    SGbool active;

    SGuint numaxis;
    float* axis;
    SGuint numbuttons;
    SGbool* buttons;
} Joystick;

#endif // __JOYSTICK_H__
