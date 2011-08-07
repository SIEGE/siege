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

#ifndef __SIEGE_BACKEND_PHYSICS_TEST_H__
#define __SIEGE_BACKEND_PHYSICS_TEST_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef SIEGE_TEST
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyWorldToLocal_TEST)(void* body, float* x, float* y);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsBodyLocalToWorld_TEST)(void* body, float* x, float* y);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsShapeGetPoints_TEST)(void* shape, SGuint* pnum, float** points);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsShapeFreePoints_TEST)(float* points);
#endif // SIEGE_TEST

#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_PHYSICS_TEST_H__
