#ifndef __SIEGE_INPUT_VINPUT_H__
#define __SIEGE_INPUT_VINPUT_H__
#include "../common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SG_INPUT_ID_KEYBOARD    -1
#define SG_INPUT_ID_MOUSE       -2

#ifdef SG_BUILD_LIBRARY
typedef struct SGIInput
{
    SGbool available;

    // TODO: SGuint or size_t?
    SGuint nbuttons;
    SGuint naxis;
    SGuint npos;

    // TODO: Merge to reduce heap impact
    SGulong* pbuttons;
    SGulong* buttons;
    float* paxis;
    float* axis;
    float* daxis;
    float* ppos;
    float* pos;
    float* dpos;
    SGint* pposi;
    SGint* posi;
    SGint* dposi;
} SGIInput;

SGIInput* _sg_inputs;

void SG_CALL _sgVInputUpdateKeyboard(void);
void SG_CALL _sgVInputUpdateMouse(void);
#endif /* SG_BUILD_LIBRARY */

SGbool SG_CALL _sgVInputInit(void);
SGbool SG_CALL _sgVInputDeinit(void);

// TODO: IsActive/IsAttached/IsValid?
SGbool SG_CALL sgInputIsAvailable(SGint id);

size_t SG_CALL sgInputGetNumButtons(SGint id);
size_t SG_CALL sgInputGetNumAxis(SGint id);
size_t SG_CALL sgInputGetNumPos(SGint id);

SGbool SG_CALL sgInputGetButtonPrev(SGint id, SGuint button);
SGbool SG_CALL sgInputGetButton(SGint id, SGuint button);
SGbool SG_CALL sgInputGetButtonPress(SGint id, SGuint button);
SGbool SG_CALL sgInputGetButtonRelease(SGint id, SGuint button);

float* SG_CALL sgInputGetAxisPrev(SGint id);
float* SG_CALL sgInputGetAxis(SGint id);
float* SG_CALL sgInputGetAxisDelta(SGint id);

float* SG_CALL sgInputGetPosPrev(SGint id);
float* SG_CALL sgInputGetPos(SGint id);
float* SG_CALL sgInputGetPosDelta(SGint id);

SGint* SG_CALL sgInputGetIPosPrev(SGint id);
SGint* SG_CALL sgInputGetIPos(SGint id);
SGint* SG_CALL sgInputGetIPosDelta(SGint id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SIEGE_INPUT_VINPUT_H__ */
