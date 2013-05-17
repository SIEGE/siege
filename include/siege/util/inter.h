/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_UTIL_INTER_H__
#define __SIEGE_UTIL_INTER_H__

#include "../common.h"
#include "vector.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define SG_ITYPE_LINE       0
#define SG_ITYPE_SEGMENT    1
#define SG_ITYPE_RAY        2

float SG_CALL sgIntersectU(SGVec2* inter, SGVec2* u, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersect(SGVec2* inter, SGenum type12, SGVec2 p1, SGVec2 p2, SGenum type34, SGVec2 p3, SGVec2 p4);

/**
 * Conveniency wrappers.
 * L - Line
 * S - Segment
 * R - Ray
 */

SGbool SG_CALL sgIntersectLL(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersectLS(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersectLR(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersectSL(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersectSS(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersectSR(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersectRL(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersectRS(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);
SGbool SG_CALL sgIntersectRR(SGVec2* inter, SGVec2 p1, SGVec2 p2, SGVec2 p3, SGVec2 p4);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* __SIEGE_UTIL_INTER_H__ */
