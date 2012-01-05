/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "COPYING.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/
#ifndef __SIEGE_UTIL_TIME_H__
#define __SIEGE_UTIL_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "../common.h"

#define SG_NANOSECONDS_IN_A_SECOND 1000000000ULL
#define SG_MICROSECONDS_IN_A_SECOND 1000000ULL
#define SG_MILLISECONDS_IN_A_SECOND 1000ULL

/**
 * Function: sgGetTime
 *
 * Returns: nanoseconds from a fixed, unspecified, origin.
 */
SGlong SG_EXPORT sgGetTime(void);

/**
 * Functions: sgNSleep, sgUSleep, sgMSleep
 *
 * Sleep for the given amount of {nano/micro/milli}seconds.
 */
void SG_EXPORT sgNSleep(SGulong nseconds);
void SG_EXPORT sgUSleep(SGulong useconds);
void SG_EXPORT sgMSleep(SGulong mseconds);

/**
 * Function: sgSleep
 *
 * Sleep for the given amount of seconds.
 */
void SG_EXPORT sgSleep(SGulong seconds);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_TIME_H__
