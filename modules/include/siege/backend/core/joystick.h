#ifndef __SIEGE_CORE_JOYSTICK_H__
#define __SIEGE_CORE_JOYSTICK_H__

#include "../../common.h"

#ifdef SG_LEGACY_API
#    define sgCoreJoystickGetFlags sgmCoreJoystickGetFlags
#    define sgCoreJoystickFreeFlags sgmCoreJoystickFreeFlags

#    define sgCoreJoystickGetNumJoysticks sgmCoreJoystickGetNumJoysticks
#    define sgCoreJoystickCreate sgmCoreJoystickCreate
#    define sgCoreJoystickDestroy sgmCoreJoystickDestroy
#    define sgCoreJoystickGetID sgmCoreJoystickGetID
#    define sgCoreJoystickGetNumButtons sgmCoreJoystickGetNumButtons
//#    define sgCoreJoystickSetButtons sgmCoreJoystickSetButtons
#    define sgCoreJoystickGetButtons sgmCoreJoystickGetButtons
#    define sgCoreJoystickGetNumAxis sgmCoreJoystickGetNumAxis
//#    define sgCoreJoystickSetAxis sgmCoreJoystickSetAxis
#    define sgCoreJoystickGetAxis sgmCoreJoystickGetAxis

#    define sgCoreJoystickSetCallbacks sgmCoreJoystickSetCallbacks
//#    define sgCoreJoystickGetCallbacks sgmCoreJoystickGetCallbacks
#endif // SG_LEGACY_API

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGCoreJoystickCallbacks
    {
        void SG_EXPORT (*button)(void* joystick, SGuint button, SGbool down);
        //void SG_EXPORT (*button)(void* joystick, SGbool* buttons);
        //void SG_EXPORT (*move)(void* joystick, SGuint axis, float position);
        void SG_EXPORT (*move)(void* joystick, float* axis);
    } SGCoreJoystickCallbacks;

    /**
        WARNING: Subject to change
    */
    SGuint SG_EXPORT sgmCoreJoystickGetFlags(SGenum** flags);
    SGuint SG_EXPORT sgmCoreJoystickFreeFlags(SGenum* flags);

    SGuint SG_EXPORT sgmCoreJoystickGetNumJoysticks(void* window, SGuint* numjoys);
    SGuint SG_EXPORT sgmCoreJoystickCreate(void** joystick, void* window, SGuint id);
    SGuint SG_EXPORT sgmCoreJoystickDestroy(void* joystick);
    SGuint SG_EXPORT sgmCoreJoystickGetID(void* joystick, SGuint* id);
    SGuint SG_EXPORT sgmCoreJoystickGetNumButtons(void* joystick, SGuint* numbuttons);
    //SGuint SG_EXPORT sgmCoreJoystickSetButtons(void* joystick, SGbool* state);
    SGuint SG_EXPORT sgmCoreJoystickGetButtons(void* joystick, SGbool* state);
    SGuint SG_EXPORT sgmCoreJoystickGetNumAxis(void* joystick, SGuint* numaxis);
    //SGuint SG_EXPORT sgmCoreJoystickSetAxis(void* joystick, float* position);
    SGuint SG_EXPORT sgmCoreJoystickGetAxis(void* joystick, float* position);

    SGuint SG_EXPORT sgmCoreJoystickSetCallbacks(void* joystick, SGCoreJoystickCallbacks* callbacks);
    //SGuint SG_EXPORT sgmCoreJoystickGetCallbacks(void* joystick, SGCoreJoystickCallbacks** callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_CORE_JOYSTICK_H__