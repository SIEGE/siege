#define SG_BUILD_LIBRARY
#include <siege/input/joystick.h>
#include <siege/core/window.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

void SG_EXPORT _sg_cbJoystickButton(void* joystick, SGuint button, SGbool down)
{
    SGuint joy = 0;
    if(_sg_modInput.sgmCoreJoystickGetID != NULL)
        _sg_modInput.sgmCoreJoystickGetID(joystick, &joy);

    SGbool pressed = _sg_joyJoys[joy]->bcurr[button] && !_sg_joyJoys[joy]->bprev[button];

    _sg_joyJoys[joy]->bprev[button] = _sg_joyJoys[joy]->bcurr[button];
    _sg_joyJoys[joy]->bcurr[button] = down;

    SGenum events[2];
    memset(events, 0, sizeof(events));
    events[0] = SG_EVF_JOYSTICKBUTH;
    if(pressed)
        events[1] = SG_EVF_JOYSTICKBUTP;
    else if(!down)
        events[1] = SG_EVF_JOYSTICKBUTR;

    char* buf = malloc(sizeof(SGuint) + sizeof(SGbool));
    memcpy(buf, &joy, sizeof(SGuint));
    memcpy(buf + sizeof(SGuint), &button, sizeof(SGbool));

    _SGEntityCall call;
    call = (_SGEntityCall){2, events, (void*[]){buf, buf}};
    sgEventCall(SG_EV_INTERNAL, &call);

    free(buf);
}
void SG_EXPORT _sg_cbJoystickMove(void* joystick, float* axis)
{
    SGuint joy = 0;
    if(_sg_modInput.sgmCoreJoystickGetID != NULL)
        _sg_modInput.sgmCoreJoystickGetID(joystick, &joy);

    SGuint numaxis = 0;
    if(_sg_modInput.sgmCoreJoystickGetNumAxis != NULL)
        _sg_modInput.sgmCoreJoystickGetNumAxis(joystick, &numaxis);

    char* buf = malloc(sizeof(SGuint) + sizeof(float*) + sizeof(SGuint));
    memcpy(buf, &joy, sizeof(SGuint));
    memcpy(buf + sizeof(SGuint), &axis, sizeof(float*));
    memcpy(buf + sizeof(SGuint) + sizeof(float*), &numaxis, sizeof(SGuint));

    _SGEntityCall call;
    call = (_SGEntityCall){2, (SGenum[]){SG_EVF_JOYSTICKMOVE}, (void*[]){buf, buf}};
    sgEventCall(SG_EV_INTERNAL, &call);

    free(buf);
}

SGbool SG_EXPORT _sgJoystickInit(void)
{
    SGuint i;
    _sg_joyNum = 0;

    if(_sg_modInput.sgmCoreJoystickGetNumJoysticks != NULL)
        _sg_modInput.sgmCoreJoystickGetNumJoysticks(_sg_winHandle, &_sg_joyNum);

    _sg_joyJoys = malloc(_sg_joyNum * sizeof(_SGJoystick*));
    for(i = 0; i < _sg_joyNum; i++)
        _sg_joyJoys[i] = _sgJoystickCreate(i);

    _sg_joyCallbacks.button = _sg_cbJoystickButton;
    _sg_joyCallbacks.move = _sg_cbJoystickMove;
    memset(&_sg_joyCallbacks, 0, sizeof(SGCoreJoystickCallbacks));

    return SG_TRUE;
}
SGbool SG_EXPORT _sgJoystickDeinit(void)
{
    SGuint i;
    for(i = 0; i < _sg_joyNum; i++)
        _sgJoystickDestroy(_sg_joyJoys[i]);
    free(_sg_joyJoys);

    return SG_TRUE;
}

_SGJoystick* SG_EXPORT _sgJoystickCreate(SGuint id)
{
    _SGJoystick* joy = malloc(sizeof(_SGJoystick));
    if(joy == NULL)
        return NULL;

    joy->id = id;
    joy->numbuttons = 0;
    joy->numaxis = 0;

    if(_sg_modInput.sgmCoreJoystickCreate != NULL)
        _sg_modInput.sgmCoreJoystickCreate(&joy->handle, _sg_winHandle, id);
    if(_sg_modInput.sgmCoreJoystickSetCallbacks != NULL)
        _sg_modInput.sgmCoreJoystickSetCallbacks(joy->handle, &_sg_joyCallbacks);

    if(_sg_modInput.sgmCoreJoystickGetNumButtons != NULL)
        _sg_modInput.sgmCoreJoystickGetNumButtons(joy->handle, &joy->numbuttons);
    joy->bprev = malloc(joy->numbuttons * sizeof(SGbool));
    joy->bcurr = malloc(joy->numbuttons * sizeof(SGbool));

    if(_sg_modInput.sgmCoreJoystickGetNumAxis != NULL)
        _sg_modInput.sgmCoreJoystickGetNumAxis(joy->handle, &joy->numaxis);
    joy->aprev = malloc(joy->numaxis * sizeof(SGbool));
    joy->acurr = malloc(joy->numaxis * sizeof(SGbool));
    joy->adelt = malloc(joy->numaxis * sizeof(SGbool));

    return joy;
}
void SG_EXPORT _sgJoystickDestroy(_SGJoystick* joy)
{
    if(joy == NULL)
        return;

    free(joy->aprev);
    free(joy->acurr);
    free(joy->adelt);
    free(joy->bprev);
    free(joy->bcurr);

    if(_sg_modInput.sgmCoreJoystickDestroy != NULL)
        _sg_modInput.sgmCoreJoystickDestroy(joy->handle);

    free(joy);
}

SGbool SG_EXPORT sgJoystickGetButtonPrev(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bprev[button];
}
SGbool SG_EXPORT sgJoystickGetButton(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bcurr[button];
}
SGbool SG_EXPORT sgJoystickGetButtonPress(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bcurr[button] && !_sg_joyJoys[joy]->bprev[button];
}
SGbool SG_EXPORT sgJoystickGetButtonRelease(SGuint joy, SGuint button)
{
    if(joy >= _sg_joyNum)
        return SG_FALSE;
    if(button >= _sg_joyJoys[joy]->numbuttons)
        return SG_FALSE;

    return _sg_joyJoys[joy]->bprev[button] && !_sg_joyJoys[joy]->bcurr[button];
}

float* SG_EXPORT sgJoystickGetAxisPrev(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->aprev;
}
float SG_EXPORT sgJoystickGetAxisIndexPrev(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->aprev[axis];
}

float* SG_EXPORT sgJoystickGetAxis(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->acurr;
}
float SG_EXPORT sgJoystickGetAxisIndex(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->acurr[axis];
}

float* SG_EXPORT sgJoystickGetAxisDelta(SGuint joy)
{
    if(joy >= _sg_joyNum)
        return NULL;

    return _sg_joyJoys[joy]->adelt;
}
float SG_EXPORT sgJoystickGetAxisIndexDelta(SGuint joy, SGuint axis)
{
    if(joy >= _sg_joyNum)
        return SG_NAN;
    if(axis >= _sg_joyJoys[joy]->numaxis)
        return SG_NAN;

    return _sg_joyJoys[joy]->adelt[axis];
}
