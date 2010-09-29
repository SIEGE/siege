#ifndef __SIEGE_GRAPHICS_TRAIL_H__
#define __SIEGE_GRAPHICS_TRAIL_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
    \brief A siege trail, useful for missile trails and similar
*/
typedef struct SGTrail
{
    /**
        \brief The number of points in the trail
    */
    SGuint numpoints;
    /**
        \brief X point positions
    */
    float* xpoints;
    /**
        \brief Y point positions
    */
    float* ypoints;

    /**
        \brief The maximum number of points in the trail
    */
    SGuint maxpoints;
} SGTrail;

void SG_EXPORT _sgTrailPopPoint(SGTrail* trail);

// @{
/**
    \memberof SGTrail
    \brief Create a trail
    \param maxpoints The maximum number of points in the trail
    \return The newly created trail if successful, NULL otherwise.
*/
SGTrail* SG_EXPORT sgTrailCreate(SGuint maxpoints);
/**
    \memberof SGTrail
    \brief Destroy a trail
    \param trail The trail to destroy. It should not be used anymore after this call.
*/
void SG_EXPORT sgTrailDestroy(SGTrail* trail);
// @}

//void SG_EXPORT sgTrailSetGradient(SGGradient* grad);

// @{
/**
    \memberof SGTrail
    \brief Add a new point to the trail
    \param trail The trail to which we want to add the point
    \param x X position
    \param y Y position

    \sa
        sgTrailAddBreak
*/
void SG_EXPORT sgTrailAddPoint2f(SGTrail* trail, float x, float y);
/**
    \memberof SGTrail
    \brief Add a break (jump) to the trail
    \param trail The trail to which we want to add the break

    Breaks are used when the trail "jumps" from one point to the next, without drawing a line in between.
    \sa
        sgTrailAddPoint2f
*/
void SG_EXPORT sgTrailAddBreak(SGTrail* trail);
// @}

// @{
/**
    \memberof SGTrail
    \brief Draw the trail
    \param trail The trail to draw
*/
void SG_EXPORT sgTrailDraw(SGTrail* trail);
// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TRAIL_H__
