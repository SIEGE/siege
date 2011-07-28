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

#ifndef __SIEGE_UTIL_ANGLE_H__
#define __SIEGE_UTIL_ANGLE_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*#ifdef SG_BUILD_LIBRARY
#endif // SG_BUILD_LIBRARY*/

float sgAngleDifferenceRads(float angle1, float angle2);
float sgAngleDifferenceDegs(float angle1, float angle2);

float sgAngleRadToDeg(float rads);
float sgAngleDegToRad(float degs);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_ANGLE_H__
