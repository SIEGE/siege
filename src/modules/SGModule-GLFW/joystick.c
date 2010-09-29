#include "main.h"
#include "joystick.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgmCoreJoystickGetNumJoysticks(void* window, SGuint* numjoys)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    *numjoys = 0;
    while(glfwGetJoystickParam(GLFW_JOYSTICK_1 + *numjoys, GLFW_PRESENT))
        (*numjoys)++;

    return SG_OK;
}

SGuint SG_EXPORT sgmCoreJoystickCreate(void** joystick, void* window, SGuint id)
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
SGuint SG_EXPORT sgmCoreJoystickDestroy(void* joystick)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    free(cjoystick->axis);
    free(cjoystick->buttons);
    free(cjoystick);

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetID(void* joystick, SGuint* id)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *id = cjoystick->id - GLFW_JOYSTICK_1 + 1;

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetNumButtons(void* joystick, SGuint* numbuttons)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *numbuttons = cjoystick->numbuttons;

    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreJoystickButtonSetState(void* joystick, SGbool* state)
SGuint SG_EXPORT sgmCoreJoystickButtonGetState(void* joystick, SGbool* state)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    glfwGetJoystickButtons(cjoystick->id, cjoystick->buttons, cjoystick->numbuttons);
    state = memcpy(state, cjoystick->buttons, cjoystick->numbuttons * sizeof(SGbool));

    return SG_OK;
}
SGuint SG_EXPORT sgmCoreJoystickGetNumAxis(void* joystick, SGuint* numaxis)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;
    *numaxis = cjoystick->numaxis;

    return SG_OK;
}
//SGuint SG_EXPORT sgmCoreJoystickAxisSetPosition(void* joystick, float* position);
SGuint SG_EXPORT sgmCoreJoystickAxisGetPosition(void* joystick, float* position)
{
    if(joystick == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Joystick* cjoystick = (Joystick*)joystick;

    glfwGetJoystickPos(cjoystick->id, cjoystick->axis, cjoystick->numaxis);
    position = memcpy(position, cjoystick->axis, cjoystick->numaxis * sizeof(float));

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
