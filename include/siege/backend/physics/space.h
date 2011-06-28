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

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceCreate)(void** space);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceDestroy)(void* space);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceStep)(void* space, float time);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsSpaceSetIterations)(void* space, SGuint iterations, SGuint eiterations);
    //SGenum SG_EXPORT SG_FPTR(sgmPhysicsSpaceGetIterations)(void* space, SGuint* iterations, SGuint* eiterations);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceSetGravity)(void* space, float x, float y);
    //SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceGetGravity)(void* space, float* x, float* y);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsSpaceSetDamping)(void* space, float damping);
    //SGenum SG_EXPORT SG_FPTR(sgmPhysicsSpaceGetDamping)(void* space, float* damping);

    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceAddShape)(void* space, void* shape);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceRemoveShape)(void* space, void* shape);
    //SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceAddStaticShape)(void* space, void* shape);
    //SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceRemoveStaticShape)(void* space, void* shape);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceAddBody)(void* space, void* body);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceRemoveBody)(void* space, void* body);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceAddConstraint)(void* space, void* constraint);
    SGuint SG_EXPORT SG_FPTR(sgmPhysicsSpaceRemoveConstraint)(void* space, void* constraint);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_PHYSICS_SPACE_H__
