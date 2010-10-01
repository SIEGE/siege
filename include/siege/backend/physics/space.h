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

#ifndef __SIEGE_BACKEND_PHYSICS_SPACE_H__
#define __SIEGE_BACKEND_PHYSICS_SPACE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmPhysicsSpaceCreate(void** space);
    SGuint SG_EXPORT sgmPhysicsSpaceDestroy(void* space);
    SGuint SG_EXPORT sgmPhysicsSpaceStep(void* space, float time);
    SGuint SG_EXPORT sgmPhysicsSpaceSetGravity(void* space, float x, float y);
    //SGuint SG_EXPORT sgmPhysicsSpaceGetGravity(void* space, float* x, float* y);

    SGuint SG_EXPORT sgmPhysicsSpaceAddShape(void* space, void* shape);
    SGuint SG_EXPORT sgmPhysicsSpaceRemoveShape(void* space, void* shape);
    //SGuint SG_EXPORT sgmPhysicsSpaceAddStaticShape(void* space, void* shape);
    //SGuint SG_EXPORT sgmPhysicsSpaceRemoveStaticShape(void* space, void* shape);
    SGuint SG_EXPORT sgmPhysicsSpaceAddBody(void* space, void* body);
    SGuint SG_EXPORT sgmPhysicsSpaceRemoveBody(void* space, void* body);
    SGuint SG_EXPORT sgmPhysicsSpaceAddConstraint(void* space, void* constraint);
    SGuint SG_EXPORT sgmPhysicsSpaceRemoveConstraint(void* space, void* constraint);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_PHYSICS_SPACE_H__
