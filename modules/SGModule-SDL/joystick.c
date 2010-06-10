#include "main.h"
#include "joystick.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgCoreJoystickGetFlags(SGenum** flags)
{
    *flags = (SGenum[]) {SG_JOYSTICK_BUTTON_NOCB, SG_JOYSTICK_AXIS_NOCB, 0};
    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickFreeFlags(SGenum* flags)
{
    if(flags == NULL)
        return SG_OK; // SG_INVALID_VALUE

    // we don't do it because we assign a static array to flags in the first place...
    //free(flags);

    return SG_OK;
}

SGuint SG_EXPORT sgCoreJoystickGetNumJoysticks(void* window, SGuint* numjoys)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numjoys = SDL_NumJoysticks();

    return SG_OK;
}

SGuint SG_EXPORT sgCoreJoystickCreate(void** joystick, void* window, SGuint id)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *joystick = SDL_JoystickOpen(id);

    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickDestroy(void* joystick)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    SDL_JoystickClose(joystick);

    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickGetID(void* joystick, SGuint* id)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *id = SDL_JoystickIndex(joystick);

    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickGetNumButtons(void* joystick, SGuint* numbuttons)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numbuttons = SDL_JoystickNumButtons(joystick);

    return SG_OK;
}
//SGuint SG_EXPORT sgCoreJoystickButtonSetState(void* joystick, SGbool* state)
SGuint SG_EXPORT sgCoreJoystickButtonGetState(void* joystick, SGbool* state)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    int numb = SDL_JoystickNumButtons(joystick);
    int i;
    for(i = 0; i < numb; i++)
        state[i] = SDL_JoystickGetButton(joystick, i);

    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickGetNumAxis(void* joystick, SGuint* numaxis)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numaxis = SDL_JoystickNumAxes(joystick);

    return SG_OK;
}
//SGuint SG_EXPORT sgCoreJoystickAxisSetPosition(void* joystick, float* position);
SGuint SG_EXPORT sgCoreJoystickAxisGetPosition(void* joystick, float* position)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    int numa = SDL_JoystickNumAxes(joystick);
    int i;
    for(i = 0; i < numa; i++)
        position[i] = SDL_JoystickGetAxis(joystick, i) / 32768.0;

    return SG_OK;
}

SGuint SG_EXPORT sgCoreJoystickSetCallbacks(void* joystick, SGCoreJoystickCallbacks* callbacks)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    // TODO

    return SG_OK; // SG_INVALID_VALUE
}
//SGuint SG_EXPORT sgCoreJoystickGetCallbacks(void* joystick, SGCoreJoystickCallbacks** callbacks);
