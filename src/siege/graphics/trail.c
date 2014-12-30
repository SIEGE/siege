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
#include <siege/graphics/trail.h>
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

void SG_CALL sgTrailPopPoint(SGTrail* trail)
{
    if(trail == NULL)
        return;
    if(trail->numpoints == 0)
        return;

    trail->numpoints--;
    memmove(&trail->xpoints[0], &trail->xpoints[1], trail->numpoints * sizeof(float));
    memmove(&trail->ypoints[0], &trail->ypoints[1], trail->numpoints * sizeof(float));
    trail->xpoints = realloc(trail->xpoints, trail->numpoints * sizeof(float));
    trail->ypoints = realloc(trail->ypoints, trail->numpoints * sizeof(float));
}

SGTrail* SG_CALL sgTrailCreate(SGuint maxpoints)
{
    SGTrail* trail = malloc(sizeof(SGTrail));
    if(trail == NULL)
        return NULL;
    sgRCountInit(&trail->cnt);
    trail->numpoints = 0;
    trail->xpoints = NULL;
    trail->ypoints = NULL;

    trail->maxpoints = maxpoints;
    return trail;
}
void SG_CALL sgTrailForceDestroy(SGTrail* trail)
{
    if(trail == NULL)
        return;

    free(trail->xpoints);
    free(trail->ypoints);
    sgRCountDeinit(&trail->cnt);
    free(trail);
}

void SG_CALL sgTrailRelease(SGTrail* trail)
{
    sgTrailUnlock(trail);
}
void SG_CALL sgTrailLock(SGTrail* trail)
{
    if(!trail) return;
    sgRCountInc(&trail->cnt);
}
void SG_CALL sgTrailUnlock(SGTrail* trail)
{
    if(!trail) return;
    if(!sgRCountDec(&trail->cnt))
        sgTrailForceDestroy(trail);
}

//void SG_CALL sgTrailSetGradient(SGGradient* grad);

void SG_CALL sgTrailAddPoint2f(SGTrail* trail, float x, float y)
{
    if(trail == NULL)
        return;

    trail->numpoints++;
    trail->xpoints = realloc(trail->xpoints, trail->numpoints * sizeof(float));
    trail->ypoints = realloc(trail->ypoints, trail->numpoints * sizeof(float));
    trail->xpoints[trail->numpoints - 1] = x;
    trail->ypoints[trail->numpoints - 1] = y;
    if(trail->numpoints > trail->maxpoints && trail->maxpoints)
        sgTrailPopPoint(trail);
}
void SG_CALL sgTrailAddBreak(SGTrail* trail)
{
    sgTrailAddPoint2f(trail, SG_NAN, SG_NAN);
}
void SG_CALL sgTrailDraw(SGTrail* trail)
{
    if(trail == NULL)
        return;

    if((trail->numpoints != 0) && ((trail->xpoints[0] != trail->xpoints[0]) || (trail->ypoints[0] != trail->ypoints[0])))
        sgTrailPopPoint(trail);
    if(trail->numpoints == 0)
        return;

    SGuint i;

    float sumlen = 0.0;
    float curlen = 0.0;
    float px = trail->xpoints[0];
    float py = trail->ypoints[0];
    float x;
    float y;

    for(i = 0; i < trail->numpoints; i++)
    {
        x = trail->xpoints[i];
        y = trail->ypoints[i];
        if(SG_IS_NAN(x) || SG_IS_NAN(y))
            continue;
        sumlen += sqrt((px - x) * (px - x) + (py - y) * (py - y));
        px = x;
        py = y;
    }

    sgDrawBegin(SG_LINE_STRIP);
        px = trail->xpoints[0];
        py = trail->ypoints[0];
        for(i = 0; i < trail->numpoints; i++)
        {
            x = trail->xpoints[i];
            y = trail->ypoints[i];
            if(SG_IS_NAN(x) || SG_IS_NAN(y))
            {
                sgDrawEnd();
                sgDrawBegin(SG_LINE_STRIP);
                continue;
            }
            sgDrawColor2f(1.0, i / (float)(trail->numpoints - 1));

            sgDrawVertex2f(x, y);

            curlen += sqrt((px - x) * (px - x) + (py - y) * (py - y));
            px = x;
            py = y;
        }
    sgDrawEnd();
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgTrailDestroy(SGTrail* trail)
{
    sgTrailRelease(trail);
}
