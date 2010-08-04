#ifndef __SIEGE_GRAPHICS_TURTLE_H__
#define __SIEGE_GRAPHICS_TURTLE_H__

#include "../common.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGTurtleState
{
    float x;
    float y;
    float angle;
    SGbool draw;
} SGTurtleState;

typedef struct SGTurtle
{
    SGTurtleState* stack;
    size_t stacklen;

    SGTurtleState start;
    SGTurtleState prev;
    SGTurtleState curr;
} SGTurtle;

SGbool SG_EXPORT _sgTurtleInit(void);
SGbool SG_EXPORT _sgTurtleDeinit(void);

SGTurtle* SG_EXPORT sgTurtleCreate(float x, float y, float angle, SGbool draw);
void SG_EXPORT sgTurtleDestroy(SGTurtle* turtle);
void SG_EXPORT sgTurtleReset(SGTurtle* turtle);
void SG_EXPORT sgTurtlePush(SGTurtle* turtle);
void SG_EXPORT sgTurtlePop(SGTurtle* turtle);
void SG_EXPORT sgTurtleStep(SGTurtle* turtle, float dist);
void SG_EXPORT sgTurtleMove(SGTurtle* turtle, float x, float y);
void SG_EXPORT sgTurtleJump(SGTurtle* turtle, float x, float y);
void SG_EXPORT sgTurtlePenUp(SGTurtle* turtle);
void SG_EXPORT sgTurtlePenDown(SGTurtle* turtle);

void SG_EXPORT sgTurtleSetPen(SGTurtle* turtle, SGbool pen);
SGbool SG_EXPORT sgTurtleGetPen(SGTurtle* turtle);
// alias of jump
void SG_EXPORT sgTurtleSetPos(SGTurtle* turtle, float x, float y);
void SG_EXPORT sgTurtleSetPosX(SGTurtle* turtle, float x);
void SG_EXPORT sgTurtleSetPosY(SGTurtle* turtle, float y);
void SG_EXPORT sgTurtleGetPos(SGTurtle* turtle, float* x, float* y);
float SG_EXPORT sgTurtleGetPosX(SGTurtle* turtle);
float SG_EXPORT sgTurtleGetPosY(SGTurtle* turtle);

// positive CCW
void SG_EXPORT sgTurtleTurnLeftRads(SGTurtle* turtle, float rads);
void SG_EXPORT sgTurtleTurnLeftDegs(SGTurtle* turtle, float degs);
void SG_EXPORT sgTurtleTurnRightRads(SGTurtle* turtle, float rads);
void SG_EXPORT sgTurtleTurnRightDegs(SGTurtle* turtle, float degs);

void SG_EXPORT sgTurtleSetAngleRads(SGTurtle* turtle, float rads);
float SG_EXPORT sgTurtleGetAngleRads(SGTurtle* turtle);

void SG_EXPORT sgTurtleSetAngleDegs(SGTurtle* turtle, float degs);
float SG_EXPORT sgTurtleGetAngleDegs(SGTurtle* turtle);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TURTLE_H__
