#ifndef __SIEGE_GRAPHICS_TRAIL_H__
#define __SIEGE_GRAPHICS_TRAIL_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGTrail
{
    SGuint numpoints;
    float* xpoints;
    float* ypoints;

    SGuint maxpoints;
} SGTrail;

void SG_EXPORT _sgTrailPopPoint(SGTrail* trail);

SGTrail* SG_EXPORT sgTrailCreate(SGuint maxpoints);
void SG_EXPORT sgTrailDestroy(SGTrail* trail);

//void SG_EXPORT sgTrailSetGradient(SGGradient* grad);

void SG_EXPORT sgTrailAddPoint2f(SGTrail* trail, float x, float y);
void SG_EXPORT sgTrailAddBreak(SGTrail* trail);
void SG_EXPORT sgTrailDraw(SGTrail* trail);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TRAIL_H__
