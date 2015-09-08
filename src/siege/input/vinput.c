#define SG_BUILD_LIBRARY
#include <siege/input/vinput.h>
#include <siege/input/keyboard.h>
#include <siege/input/mouse.h>
#include <siege/input/joystick.h>
#include <siege/core/entity.h>

#include "../internal/bitop.h"

static SGIInput inputsA[33] = {};

void SG_CALL _sgVInputUpdateKeyboard(void)
{
    /* nothing to do [yet?] */
}
void SG_CALL _sgVInputUpdateMouse(void)
{
    SGIInput* mouse = &_sg_inputs[SG_INPUT_ID_MOUSE];

    mouse->paxis[0] = _sg_mouseWheelPrev;
    mouse->axis[0] = _sg_mouseWheel;
    mouse->daxis[0] = _sg_mouseWheel - _sg_mouseWheelPrev;

    size_t i;
    for(i = 0; i < 2; i++)
    {
        mouse->dposi[i] = mouse->posi[i] - mouse->pposi[i];
        mouse->ppos[i] = mouse->pposi[i];
        mouse->pos[i] = mouse->posi[i];
        mouse->dpos[i] = mouse->dposi[i];
    }
}
void SG_CALL _sgVInputUpdateJoystick(SGuint joy)
{
    //SG_INPUT_ID_JOYSTICK(joy);
    /* nothing to do [yet?] */
}

SGbool SG_CALL _sgVInputInit(void)
{
    _sg_inputs = inputsA + 16;

    SGIInput* keyboard = &_sg_inputs[SG_INPUT_ID_KEYBOARD];
    keyboard->available = SG_TRUE;
    keyboard->nbuttons = SGI_NUM_KEYS;
    keyboard->naxis = 0;
    keyboard->npos = 0;

    keyboard->pbuttons = _sg_keyPrev;
    keyboard->buttons = _sg_keyCurr;

    keyboard->paxis = keyboard->axis = keyboard->daxis = NULL;
    keyboard->ppos = keyboard->pos = keyboard->dpos = NULL;
    keyboard->pposi = keyboard->posi = keyboard->dposi = NULL;
    _sgVInputUpdateKeyboard();

    static float m_axis[3][1];
    static float m_pos[3][2];
    static SGint m_posi[1][2];

    SGIInput* mouse = &_sg_inputs[SG_INPUT_ID_MOUSE];
    mouse->available = SG_TRUE;
    mouse->nbuttons = 64;
    mouse->naxis = 1;
    mouse->npos = 2;

    mouse->pbuttons = &_sg_mouseButtonPrev;
    mouse->buttons = &_sg_mouseButtonCurr;

    mouse->paxis = m_axis[0];
    mouse->axis = m_axis[1];
    mouse->daxis = m_axis[2];

    mouse->ppos = m_pos[0];
    mouse->pos = m_pos[1];
    mouse->dpos = m_pos[2];

    mouse->pposi = &_sg_mousePosPrev.x;
    mouse->posi = &_sg_mousePos.x;
    mouse->dposi = m_posi[0];
    _sgVInputUpdateMouse();

    SGIInput* joystick;
    size_t numjoys = SG_MIN(_sg_joyNum, 14);
    size_t i;
    for(i = 0; i < numjoys; i++)
    {
        joystick = &_sg_inputs[SG_INPUT_ID_JOYSTICK(i)];
        joystick->available = SG_TRUE;
        joystick->nbuttons = _sg_joyJoys[i]->numbuttons;
        joystick->naxis = _sg_joyJoys[i]->numaxis;
        joystick->npos = 0;

        joystick->pbuttons = _sg_joyJoys[i]->bprev;
        joystick->buttons = _sg_joyJoys[i]->bcurr;

        joystick->paxis = _sg_joyJoys[i]->aprev;
        joystick->axis = _sg_joyJoys[i]->acurr;
        joystick->daxis = _sg_joyJoys[i]->adelt;

        joystick->ppos = joystick->pos = joystick->dpos = NULL;
        joystick->pposi = joystick->posi = joystick->dposi = NULL;
        _sgVInputUpdateJoystick(i);
    }

    return SG_TRUE;
}
SGbool SG_CALL _sgVInputDeinit(void)
{
    return SG_TRUE;
}

SGbool SG_CALL sgInputIsAvailable(SGint id)
{
    return _sg_inputs[id].available;
}

// TODO: SGuint or size_t?
size_t SG_CALL sgInputGetNumButtons(SGint id)
{
    if(!_sg_inputs[id].available) return 0;
    return _sg_inputs[id].nbuttons;
}
size_t SG_CALL sgInputGetNumAxis(SGint id)
{
    if(!_sg_inputs[id].available) return 0;
    return _sg_inputs[id].naxis;
}
size_t SG_CALL sgInputGetNumPos(SGint id)
{
    if(!_sg_inputs[id].available) return 0;
    return _sg_inputs[id].npos;
}

SGbool SG_CALL sgInputGetButtonPrev(SGint id, SGuint button)
{
    if(button >= _sg_inputs[id].nbuttons) return SG_FALSE;
    return GET_BITARR(_sg_inputs[id].pbuttons, button);
}
SGbool SG_CALL sgInputGetButton(SGint id, SGuint button)
{
    if(button >= _sg_inputs[id].nbuttons) return SG_FALSE;
    return GET_BITARR(_sg_inputs[id].buttons, button);
}
SGbool SG_CALL sgInputGetButtonPress(SGint id, SGuint button)
{
    if(button >= _sg_inputs[id].nbuttons) return SG_FALSE;
    return !GET_BITARR(_sg_inputs[id].pbuttons, button) && GET_BITARR(_sg_inputs[id].buttons, button);
}
SGbool SG_CALL sgInputGetButtonRelease(SGint id, SGuint button)
{
    if(button >= _sg_inputs[id].nbuttons) return SG_FALSE;
    return GET_BITARR(_sg_inputs[id].pbuttons, button) && !GET_BITARR(_sg_inputs[id].buttons, button);
}

float* SG_CALL sgInputGetAxisPrev(SGint id)
{
    if(!_sg_inputs[id].available) return NULL;
    return _sg_inputs[id].paxis;
}
float* SG_CALL sgInputGetAxis(SGint id)
{
    if(!_sg_inputs[id].available) return NULL;
    return _sg_inputs[id].axis;
}
float* SG_CALL sgInputGetAxisDelta(SGint id)
{
    if(!_sg_inputs[id].available) return NULL;
    return _sg_inputs[id].daxis;
}

float* SG_CALL sgInputGetPosPrev(SGint id)
{
    if(!_sg_inputs[id].available) return NULL;
    return _sg_inputs[id].ppos;
}
float* SG_CALL sgInputGetPos(SGint id)
{
    if(!_sg_inputs[id].available) return NULL;
    return _sg_inputs[id].pos;
}
float* SG_CALL sgInputGetPosDelta(SGint id)
{
    if(!_sg_inputs[id].available) return NULL;
    return _sg_inputs[id].dpos;
}
