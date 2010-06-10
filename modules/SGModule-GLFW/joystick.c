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

    *numjoys = 0;
    while(glfwGetJoystickParam(GLFW_JOYSTICK_1 + *numjoys, GLFW_PRESENT))
        (*numjoys)++;

    return SG_OK;
}

SGuint SG_EXPORT sgCoreJoystickCreate(void** joystick, void* window, SGuint id)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick** cjoystick = (Joystick**)joystick;

    *cjoystick = malloc(sizeof(Joystick));
    (*cjoystick)->id = GLFW_JOYSTICK_1 + id - 1;
    (*cjoystick)->active = glfwGetJoystickParam((*cjoystick)->id, GLFW_PRESENT);

    (*cjoystick)->numaxis = glfwGetJoystickParam((*cjoystick)->id, GLFW_AXES);
    (*cjoystick)->axis = calloc((*cjoystick)->numaxis, sizeof(float));
    (*cjoystick)->numbuttons = glfwGetJoystickParam((*cjoystick)->id, GLFW_BUTTONS);
    (*cjoystick)->buttons = calloc((*cjoystick)->numbuttons, sizeof(SGbool));

    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickDestroy(void* joystick)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    free(cjoystick->axis);
    free(cjoystick->buttons);
    free(cjoystick);

    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickGetID(void* joystick, SGuint* id)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *id = cjoystick->id - GLFW_JOYSTICK_1 + 1;

    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickGetNumButtons(void* joystick, SGuint* numbuttons)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *numbuttons = cjoystick->numbuttons;

    return SG_OK;
}
//SGuint SG_EXPORT sgCoreJoystickButtonSetState(void* joystick, SGbool* state)
SGuint SG_EXPORT sgCoreJoystickButtonGetState(void* joystick, SGbool* state)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    glfwGetJoystickButtons(cjoystick->id, cjoystick->buttons, cjoystick->numbuttons);
    state = memcpy(state, cjoystick->buttons, cjoystick->numbuttons * sizeof(SGbool));

    return SG_OK;
}
SGuint SG_EXPORT sgCoreJoystickGetNumAxis(void* joystick, SGuint* numaxis)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *numaxis = cjoystick->numaxis;

    return SG_OK;
}
//SGuint SG_EXPORT sgCoreJoystickAxisSetPosition(void* joystick, float* position);
SGuint SG_EXPORT sgCoreJoystickAxisGetPosition(void* joystick, float* position)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    glfwGetJoystickPos(cjoystick->id, cjoystick->axis, cjoystick->numaxis);
    position = memcpy(position, cjoystick->axis, cjoystick->numaxis * sizeof(float));

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
