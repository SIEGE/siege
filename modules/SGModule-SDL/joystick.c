#include "main.h"
#include "joystick.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgmCoreJoystickGetFlags(SGenum** flags)
{
    *flags = (SGenum[]) {SG_JOYSTICK_BUTTON_NOCB, SG_JOYSTICK_AXIS_NOCB, 0};
    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickFreeFlags(SGenum* flags)
{
    if(flags == NULL)
        return SG_OK; // SG_INVALID_VALUE

    // we don't do it because we assign a static array to flags in the first place...
    //free(flags);

    return SG_OK;
}

SGuint SG_EXPORT sgmCoreJoystickGetNumJoysticks(void* window, SGuint* numjoys)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numjoys = SDL_NumJoysticks();

    return SG_OK;
}

SGuint SG_EXPORT sgmCoreJoystickCreate(void** joystick, void* window, SGuint id)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *joystick = SDL_JoystickOpen(id);

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickDestroy(void* joystick)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    SDL_JoystickClose(joystick);

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetID(void* joystick, SGuint* id)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *id = SDL_JoystickIndex(joystick);

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetNumButtons(void* joystick, SGuint* numbuttons)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numbuttons = SDL_JoystickNumButtons(joystick);

    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreJoystickButtonSetState(void* joystick, SGbool* state)
SGuint SG_EXPORT sgmCoreJoystickButtonGetState(void* joystick, SGbool* state)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    int numb = SDL_JoystickNumButtons(joystick);
    int i;
    for(i = 0; i < numb; i++)
        state[i] = SDL_JoystickGetButton(joystick, i);

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetNumAxis(void* joystick, SGuint* numaxis)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numaxis = SDL_JoystickNumAxes(joystick);

    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreJoystickAxisSetPosition(void* joystick, float* position);
SGuint SG_EXPORT sgmCoreJoystickAxisGetPosition(void* joystick, float* position)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    int numa = SDL_JoystickNumAxes(joystick);
    int i;
    for(i = 0; i < numa; i++)
        position[i] = SDL_JoystickGetAxis(joystick, i) / 32768.0;

    return SG_OK;
}

SGuint SG_EXPORT sgmCoreJoystickSetCallbacks(void* joystick, SGCoreJoystickCallbacks* callbacks)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE

    // TODO

    return SG_OK; // SG_INVALID_VALUE
}
//SGuint SG_EXPORT sgmCoreJoystickGetCallbacks(void* joystick, SGCoreJoystickCallbacks** callbacks);
