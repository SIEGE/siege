#ifndef __SIEGE_CORE_JOYSTICK_H__
#define __SIEGE_CORE_JOYSTICK_H__

#include "../../common.h"

typedef struct SGCoreJoystickCallbacks
{
    void SG_EXPORT (*button)(void* joystick, SGuint button, SGbool down);
    //void SG_EXPORT (*button)(void* joystick, SGbool* buttons);
    //void SG_EXPORT (*move)(void* joystick, SGuint axis, float position);
    void SG_EXPORT (*move)(void* joystick, float* axis);
} SGCoreJoystickCallbacks;

#ifdef __cplusplus
extern "C"
{
#endif
    /**
        WARNING: Subject to change
    */
    SGuint SG_EXPORT sgCoreJoystickGetFlags(SGenum** flags);
    SGuint SG_EXPORT sgCoreJoystickFreeFlags(SGenum* flags);

    SGuint SG_EXPORT sgCoreJoystickGetNumJoysticks(void* window, SGuint* numjoys);
    SGuint SG_EXPORT sgCoreJoystickCreate(void** joystick, void* window, SGuint id);
    SGuint SG_EXPORT sgCoreJoystickDestroy(void* joystick);
    SGuint SG_EXPORT sgCoreJoystickGetID(void* joystick, SGuint* id);
    SGuint SG_EXPORT sgCoreJoystickGetNumButtons(void* joystick, SGuint* numbuttons);
    //SGuint SG_EXPORT sgCoreJoystickSetButtons(void* joystick, SGbool* state);
    SGuint SG_EXPORT sgCoreJoystickGetButtons(void* joystick, SGbool* state);
    SGuint SG_EXPORT sgCoreJoystickGetNumAxis(void* joystick, SGuint* numaxis);
    //SGuint SG_EXPORT sgCoreJoystickSetAxis(void* joystick, float* position);
    SGuint SG_EXPORT sgCoreJoystickGetAxis(void* joystick, float* position);

    SGuint SG_EXPORT sgCoreJoystickSetCallbacks(void* joystick, SGCoreJoystickCallbacks* callbacks);
    //SGuint SG_EXPORT sgCoreJoystickGetCallbacks(void* joystick, SGCoreJoystickCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_CORE_JOYSTICK_H__
