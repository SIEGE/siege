#define SG_BUILD_LIBRARY
#include <siege/graphics/turtle.h>
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

SGbool SG_EXPORT _sgTurtleInit(void)
{
    return SG_TRUE;
}
SGbool SG_EXPORT _sgTurtleDeinit(void)
{
    return SG_TRUE;
}

SGTurtle* SG_EXPORT sgTurtleCreateRads(float x, float y, float rads, SGbool draw)
{
    SGTurtle* turtle = malloc(sizeof(SGTurtle));
    turtle->stack = NULL;
    turtle->stacklen = 0;

    turtle->start.x = x;
    turtle->start.y = y;
    turtle->start.angle = rads;
    turtle->start.draw = draw;
    sgTurtleReset(turtle);
    return turtle;
}
SGTurtle* SG_EXPORT sgTurtleCreateDegs(float x, float y, float degs, SGbool draw)
{
    return sgTurtleCreateRads(x, y, degs * M_PI / 180.0, draw);
}
void SG_EXPORT sgTurtleDestroy(SGTurtle* turtle)
{
    if(turtle == NULL)
        return;

    free(turtle->stack);
    free(turtle);
}

void SG_EXPORT sgTurtleReset(SGTurtle* turtle)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->start, sizeof(SGTurtleState));
    memcpy(&turtle->curr, &turtle->start, sizeof(SGTurtleState));
}
void SG_EXPORT sgTurtlePush(SGTurtle* turtle)
{
    if(turtle == NULL)
        return;

    turtle->stack = realloc(turtle->stack, (turtle->stacklen + 1) * sizeof(SGTurtleState));
    memcpy(&turtle->stack[turtle->stacklen], &turtle->curr, sizeof(SGTurtleState));
    turtle->stacklen++;
}
void SG_EXPORT sgTurtlePop(SGTurtle* turtle)
{
    if(turtle == NULL)
        return;

    turtle->stacklen--;
    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    memcpy(&turtle->curr, &turtle->stack[turtle->stacklen], sizeof(SGTurtleState));
    turtle->stack = realloc(turtle->stack, turtle->stacklen * sizeof(SGTurtleState));
}

void SG_EXPORT sgTurtleStep(SGTurtle* turtle, float dist)
{
    if(turtle == NULL)
        return;

    float newx = turtle->curr.x + cos(turtle->curr.angle) * dist;
    float newy = turtle->curr.y - sin(turtle->curr.angle) * dist; // we use -sin() because the y axis is reverse
    sgTurtleMove(turtle, newx, newy);
}
void SG_EXPORT sgTurtleMove(SGTurtle* turtle, float x, float y)
{
    if(turtle == NULL)
        return;

    sgTurtleJump(turtle, x, y);
    if(turtle->curr.draw)
    {
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINES);
            sgDrawVertex2f(turtle->prev.x, turtle->prev.y);
            sgDrawVertex2f(x, y);
        sgDrawEnd();
    }
}
void SG_EXPORT sgTurtleJump(SGTurtle* turtle, float x, float y)
{
    sgTurtleSetPos(turtle, x, y);
}

void SG_EXPORT sgTurtlePenUp(SGTurtle* turtle)
{
    sgTurtleSetPen(turtle, SG_FALSE);
}
void SG_EXPORT sgTurtlePenDown(SGTurtle* turtle)
{
    sgTurtleSetPen(turtle, SG_TRUE);
}

void SG_EXPORT sgTurtleSetPen(SGTurtle* turtle, SGbool pen)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.draw = pen;
}
SGbool SG_EXPORT sgTurtleGetPen(SGTurtle* turtle)
{
    if(turtle == NULL)
        return SG_FALSE;

    return turtle->curr.draw;
}
void SG_EXPORT sgTurtleSetPos(SGTurtle* turtle, float x, float y)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.x = x;
    turtle->curr.y = y;
}
void SG_EXPORT sgTurtleSetPosX(SGTurtle* turtle, float x)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.x = x;
}
void SG_EXPORT sgTurtleSetPosY(SGTurtle* turtle, float y)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.y = y;
}
void SG_EXPORT sgTurtleGetPos(SGTurtle* turtle, float* x, float* y)
{
    if(turtle == NULL)
        return;

    if(x != NULL)
        *x = turtle->curr.x;
    if(y != NULL)
        *y = turtle->curr.y;
}
float SG_EXPORT sgTurtleGetPosX(SGTurtle* turtle)
{
    if(turtle == NULL)
        return SG_NAN;

    return turtle->curr.x;
}
float SG_EXPORT sgTurtleGetPosY(SGTurtle* turtle)
{
    if(turtle == NULL)
        return SG_NAN;

    return turtle->curr.y;
}

void SG_EXPORT sgTurtleTurnLeftRads(SGTurtle* turtle, float rads)
{
    if(turtle == NULL)
        return;

    sgTurtleSetAngleRads(turtle, turtle->curr.angle + rads);
}
void SG_EXPORT sgTurtleTurnLeftDegs(SGTurtle* turtle, float degs)
{
    sgTurtleTurnLeftRads(turtle, degs * M_PI / 180.0);
}
void SG_EXPORT sgTurtleTurnRightRads(SGTurtle* turtle, float rads)
{
    if(turtle == NULL)
        return;

    sgTurtleSetAngleRads(turtle, turtle->curr.angle - rads);
}
void SG_EXPORT sgTurtleTurnRightDegs(SGTurtle* turtle, float degs)
{
    sgTurtleTurnRightRads(turtle, degs * M_PI / 180.0);
}

void SG_EXPORT sgTurtleSetAngleRads(SGTurtle* turtle, float rads)
{
    if(turtle == NULL)
        return;

    memcpy(&turtle->prev, &turtle->curr, sizeof(SGTurtleState));
    turtle->curr.angle = rads;
}
float SG_EXPORT sgTurtleGetAngleRads(SGTurtle* turtle)
{
    if(turtle == NULL)
        return SG_NAN;

    return turtle->curr.angle;
}

void SG_EXPORT sgTurtleSetAngleDegs(SGTurtle* turtle, float degs)
{
    sgTurtleSetAngleRads(turtle, degs * M_PI / 180.0);
}
float SG_EXPORT sgTurtleGetAngleDegs(SGTurtle* turtle)
{
    return sgTurtleGetAngleRads(turtle) * 180.0 / M_PI;
}
