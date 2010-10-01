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

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef SIEGE_TEST
    SGuint SG_EXPORT sgmPhysicsBodyWorldToLocal_TEST(void* body, float* x, float* y);
    SGuint SG_EXPORT sgmPhysicsBodyLocalToWorld_TEST(void* body, float* x, float* y);
    SGuint SG_EXPORT sgmPhysicsShapeGetBB_TEST(void* shape, float* t, float* l, float* b, float* r);
    SGuint SG_EXPORT sgmPhysicsShapeGetPoints_TEST(void* shape, SGuint* pnum, float** points);
    SGuint SG_EXPORT sgmPhysicsShapeFreePoints_TEST(float* points);
#endif // SIEGE_TEST

#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_PHYSICS_TEST_H__
