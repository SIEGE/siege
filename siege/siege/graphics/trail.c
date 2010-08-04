#define SG_BUILD_LIBRARY
#include <siege/graphics/trail.h>
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

void SG_EXPORT _sgTrailPopPoint(SGTrail* trail)
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

SGTrail* SG_EXPORT sgTrailCreate(SGuint maxpoints)
{
    SGTrail* trail = malloc(sizeof(SGTrail));
    if(trail == NULL)
        return NULL;
    trail->numpoints = 0;
    trail->xpoints = NULL;
    trail->ypoints = NULL;

    trail->maxpoints = maxpoints;
    return trail;
}
void SG_EXPORT sgTrailDestroy(SGTrail* trail)
{
    if(trail == NULL)
        return;

    free(trail->xpoints);
    free(trail->ypoints);
    free(trail);
}

//void SG_EXPORT sgTrailSetGradient(SGGradient* grad);

void SG_EXPORT sgTrailAddPoint2f(SGTrail* trail, float x, float y)
{
    if(trail == NULL)
        return;

    trail->numpoints++;
    trail->xpoints = realloc(trail->xpoints, trail->numpoints * sizeof(float));
    trail->ypoints = realloc(trail->ypoints, trail->numpoints * sizeof(float));
    trail->xpoints[trail->numpoints - 1] = x;
    trail->ypoints[trail->numpoints - 1] = y;
    if(trail->numpoints > trail->maxpoints)
        _sgTrailPopPoint(trail);
}
void SG_EXPORT sgTrailAddBreak(SGTrail* trail)
{
    sgTrailAddPoint2f(trail, SG_NAN, SG_NAN);
}
void SG_EXPORT sgTrailDraw(SGTrail* trail)
{
    if(trail == NULL)
        return;

    if((trail->numpoints != 0) && ((trail->xpoints[0] != trail->xpoints[0]) || (trail->ypoints[0] != trail->ypoints[0])))
        _sgTrailPopPoint(trail);
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
        if((x != x) || (y != y))
            continue;
        sumlen += sqrt((px - x) * (px - x) + (py - y) * (py - y));
        px = x;
        py = y;
    }

    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_STRIP);
        px = trail->xpoints[0];
        py = trail->ypoints[0];
        for(i = 0; i < trail->numpoints; i++)
        {
            x = trail->xpoints[i];
            y = trail->ypoints[i];
            if((x != x) || (y != y))
            {
                sgDrawEnd();
                sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_STRIP);
                continue;
            }
            sgDrawVertex2f(x, y);

            curlen += sqrt((px - x) * (px - x) + (py - y) * (py - y));
            px = x;
            py = y;
        }
    sgDrawEnd();
}
