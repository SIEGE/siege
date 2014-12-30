/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_GRAPHICS_TRAIL_H__
#define __SIEGE_GRAPHICS_TRAIL_H__

#include "../common.h"
#include "../util/rcount.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \brief A siege trail, useful for missile trails and similar
 */
typedef struct SGTrail
{
    SGRCount cnt;

    SGuint numpoints;    /// < The number of points in the trail

    float* xpoints;        /// < X point positions
    float* ypoints;        /// < Y point positions

    SGuint maxpoints;    /// < The maximum number of points in the trail
} SGTrail;

void SG_CALL sgTrailPopPoint(SGTrail* trail);

/// @{
/**
 * \brief Create a trail
 * \memberof SGTrail
 *
 * \param maxpoints The maximum number of points in the trail
 *
 * \return The newly created trail if successful, NULL otherwise.
 */
SGTrail* SG_CALL sgTrailCreate(SGuint maxpoints);
/**
 * \brief Destroy a trail
 * \memberof SGTrail
 *
 * \param trail The trail to destroy. It should not be used anymore after this call.
 */
void SG_CALL sgTrailForceDestroy(SGTrail* trail);
/// @}

void SG_CALL sgTrailRelease(SGTrail* trail);
void SG_CALL sgTrailLock(SGTrail* trail);
void SG_CALL sgTrailUnlock(SGTrail* trail);

//void SG_CALL sgTrailSetGradient(SGGradient* grad);

/// @{
/**
 * \brief Add a new point to the trail
 * \memberof SGTrail
 *
 * \param trail The trail to which we want to add the point
 * \param x X position
 * \param y Y position
 *
 * \sa
 *    sgTrailAddBreak
 */
void SG_CALL sgTrailAddPoint2f(SGTrail* trail, float x, float y);
/**
 * \brief Add a break (jump) to the trail
 * \memberof SGTrail
 *
 * \param trail The trail to which we want to add the break
 *
 * Breaks are used when the trail "jumps" from one point to
 * the next, without drawing a line in between.
 *
 * \sa
 *    sgTrailAddPoint2f
 */
void SG_CALL sgTrailAddBreak(SGTrail* trail);
/// @}

/// @{
/**
 * \brief Draw the trail
 * \memberof SGTrail
 *
 * \param trail The trail to draw
 */
void SG_CALL sgTrailDraw(SGTrail* trail);
/// @}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgTrailDestroy(SGTrail* trail);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TRAIL_H__
