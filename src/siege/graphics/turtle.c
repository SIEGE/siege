/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#define SG_BUILD_LIBRARY
#include <siege/graphics/turtle.h>
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

SGTurtle* SG_CALL sgTurtleCreateRads(float x, float y, float rads, SGbool draw)
{
    SGTurtle* turtle = malloc(sizeof(SGTurtle));
    if(!turtle) return NULL;
    sgRCountInit(&turtle->cnt);
    turtle->stack = NULL;
    turtle->stacklen = 0;

    turtle->start.x = x;
    turtle->start.y = y;
    turtle->start.angle = rads;
    turtle->start.draw = draw;
    sgTurtleReset(turtle);
    return turtle;
}
SGTurtle* SG_CALL sgTurtleCreateDegs(float x, float y, float degs, SGbool draw)
{
    return sgTurtleCreateRads(x, y, degs * SG_PI / 180.0, draw);
}
void SG_CALL sgTurtleForceDestroy(SGTurtle* turtle)
{
    if(turtle == NULL)
        return;

    free(turtle->stack);
    sgRCountDeinit(&turtle->cnt);
    free(turtle);
}

void SG_CALL sgTurtleRelease(SGTurtle* turtle)
{
    sgTurtleUnlock(turtle);
}
void SG_CALL sgTurtleLock(SGTurtle* turtle)
{
    if(!turtle) return;
    sgRCountInc(&turtle->cnt);
}
void SG_CALL sgTurtleUnlock(SGTurtle* turtle)
{
    if(!turtle) return;
    if(!sgRCountDec(&turtle->cnt))
        sgTurtleForceDestroy(turtle);
}

void SG_CALL sgTurtleReset(SGTurtle* turtle)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->start, sizeof(SGTurtleState));
    memcpy(&turtle->curr, &turtle->start, sizeof(SGTurtleState));
}
void SG_CALL sgTurtlePush(SGTurtle* turtle)
{
    if(turtle == NULL)
        return;

    turtle->stack = realloc(turtle->stack, (turtle->stacklen + 1) * sizeof(SGTurtleState));
    memcpy(&turtle->stack[turtle->stacklen], &turtle->curr, sizeof(SGTurtleState));
    turtle->stacklen++;
}
void SG_CALL sgTurtlePop(SGTurtle* turtle)
{
    if(turtle == NULL)
        return;

    turtle->stacklen--;
    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    memcpy(&turtle->curr, &turtle->stack[turtle->stacklen], sizeof(SGTurtleState));
    turtle->stack = realloc(turtle->stack, turtle->stacklen * sizeof(SGTurtleState));
}

void SG_CALL sgTurtleStep(SGTurtle* turtle, float dist)
{
    if(turtle == NULL)
        return;

    float newx = turtle->curr.x + cos(turtle->curr.angle) * dist;
    float newy = turtle->curr.y - sin(turtle->curr.angle) * dist; // we use -sin() because the y axis is reverse
    sgTurtleMove(turtle, newx, newy);
}
void SG_CALL sgTurtleMove(SGTurtle* turtle, float x, float y)
{
    if(turtle == NULL)
        return;

    sgTurtleJump(turtle, x, y);
    if(turtle->curr.draw)
    {
        sgDrawBegin(SG_LINES);
            sgDrawVertex2f(turtle->prev.x, turtle->prev.y);
            sgDrawVertex2f(x, y);
        sgDrawEnd();
    }
}
void SG_CALL sgTurtleJump(SGTurtle* turtle, float x, float y)
{
    sgTurtleSetPos(turtle, x, y);
}

void SG_CALL sgTurtlePenUp(SGTurtle* turtle)
{
    sgTurtleSetPen(turtle, SG_FALSE);
}
void SG_CALL sgTurtlePenDown(SGTurtle* turtle)
{
    sgTurtleSetPen(turtle, SG_TRUE);
}

void SG_CALL sgTurtleSetPen(SGTurtle* turtle, SGbool pen)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.draw = pen;
}
SGbool SG_CALL sgTurtleGetPen(SGTurtle* turtle)
{
    if(turtle == NULL)
        return SG_FALSE;

    return turtle->curr.draw;
}
void SG_CALL sgTurtleSetPos(SGTurtle* turtle, float x, float y)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.x = x;
    turtle->curr.y = y;
}
void SG_CALL sgTurtleSetPosX(SGTurtle* turtle, float x)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.x = x;
}
void SG_CALL sgTurtleSetPosY(SGTurtle* turtle, float y)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.y = y;
}
void SG_CALL sgTurtleGetPos(SGTurtle* turtle, float* x, float* y)
{
    if(turtle == NULL)
        return;

    if(x != NULL)
        *x = turtle->curr.x;
    if(y != NULL)
        *y = turtle->curr.y;
}
float SG_CALL sgTurtleGetPosX(SGTurtle* turtle)
{
    if(turtle == NULL)
        return SG_NAN;

    return turtle->curr.x;
}
float SG_CALL sgTurtleGetPosY(SGTurtle* turtle)
{
    if(turtle == NULL)
        return SG_NAN;

    return turtle->curr.y;
}

void SG_CALL sgTurtleTurnLeftRads(SGTurtle* turtle, float rads)
{
    if(turtle == NULL)
        return;

    sgTurtleSetAngleRads(turtle, turtle->curr.angle + rads);
}
void SG_CALL sgTurtleTurnLeftDegs(SGTurtle* turtle, float degs)
{
    sgTurtleTurnLeftRads(turtle, degs * SG_PI / 180.0);
}
void SG_CALL sgTurtleTurnRightRads(SGTurtle* turtle, float rads)
{
    if(turtle == NULL)
        return;

    sgTurtleSetAngleRads(turtle, turtle->curr.angle - rads);
}
void SG_CALL sgTurtleTurnRightDegs(SGTurtle* turtle, float degs)
{
    sgTurtleTurnRightRads(turtle, degs * SG_PI / 180.0);
}

void SG_CALL sgTurtleSetAngleRads(SGTurtle* turtle, float rads)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.angle = rads;
}
float SG_CALL sgTurtleGetAngleRads(SGTurtle* turtle)
{
    if(turtle == NULL)
        return SG_NAN;

    return turtle->curr.angle;
}

void SG_CALL sgTurtleSetAngleDegs(SGTurtle* turtle, float degs)
{
    sgTurtleSetAngleRads(turtle, degs * SG_PI / 180.0);
}
float SG_CALL sgTurtleGetAngleDegs(SGTurtle* turtle)
{
    return sgTurtleGetAngleRads(turtle) * 180.0 / SG_PI;
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgTurtleDestroy(SGTurtle* turtle)
{
    sgTurtleRelease(turtle);
}
