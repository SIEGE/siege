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

#define SG_BUILD_LIBRARY
#include <siege/util/angle.h>

float sgAngleDifferenceRads(float angle1, float angle2)
{
    float angle = angle2 - angle1;
    while(angle < -SG_PI)
        angle += 2 * SG_PI;
    while(angle > SG_PI)
        angle -= 2 * SG_PI;
    return angle;
}
float sgAngleDifferenceDegs(float angle1, float angle2)
{
    float angle = angle2 - angle1;
    while(angle < -180.0)
        angle += 360.0;
    while(angle > 180.0)
        angle -= 360.0;
    return angle;
}

float sgAngleRadToDeg(float rads)
{
    return rads * 180.0 / SG_PI;
}
float sgAngleDegToRad(float degs)
{
    return degs * SG_PI / 180.0;
}
