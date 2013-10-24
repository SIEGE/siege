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

#ifndef __SIEGE_PHYSICS_SPACE_H__
#define __SIEGE_PHYSICS_SPACE_H__

#include "../common.h"
#include "../config.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_USE_PHYSICS
struct SGPhysicsBody;
struct SGPhysicsShape;
struct SGPhysicsConstraint;

typedef struct SGPhysicsSpace
{
    void* handle;
    struct SGPhysicsBody* sbody;
    void* data;
} SGPhysicsSpace;

#ifdef SG_BUILD_LIBRARY
SGPhysicsSpace* _sg_physSpaceMain;
#endif // SG_BUILD_LIBRARY

SGbool SG_CALL _sgPhysicsSpaceInit(void);
SGbool SG_CALL _sgPhysicsSpaceDeinit(void);

SGPhysicsSpace* SG_CALL sgPhysicsSpaceCreate(void);
void SG_CALL sgPhysicsSpaceDestroy(SGPhysicsSpace* space);

void SG_CALL sgPhysicsSpaceStep(SGPhysicsSpace* space, float time);

void SG_CALL sgPhysicsSpaceSetIterations(SGPhysicsSpace* space, SGuint iterations);
void SG_CALL sgPhysicsSpaceSetGravity(SGPhysicsSpace* space, float x, float y);
//void SG_CALL sgPhysicsSpaceGetGravity(SGPhysicsSpace* space, float* x, float* y);
void SG_CALL sgPhysicsSpaceSetDamping(SGPhysicsSpace* space, float damping);
//float SG_CALL sgPhysicsSpaceGetDamping(SGPhysicsSpace* space);

void SG_CALL sgPhysicsSpaceSetData(SGPhysicsSpace* space, void* data);
void* SG_CALL sgPhysicsSpaceGetData(SGPhysicsSpace* space);

struct SGPhysicsBody* SG_CALL sgPhysicsSpaceGetStaticBody(SGPhysicsSpace* space);
SGPhysicsSpace* SG_CALL sgPhysicsSpaceGetDefault(void);

void SG_CALL _sgPhysicsSpaceAddShape(SGPhysicsSpace* space, struct SGPhysicsShape* shape);
void SG_CALL _sgPhysicsSpaceRemoveShape(SGPhysicsSpace* space, struct SGPhysicsShape* shape);

void SG_CALL _sgPhysicsSpaceAddBody(SGPhysicsSpace* space, struct SGPhysicsBody* body);
void SG_CALL _sgPhysicsSpaceRemoveBody(SGPhysicsSpace* space, struct SGPhysicsBody* body);

void SG_CALL _sgPhysicsSpaceAddConstraint(SGPhysicsSpace* space, struct SGPhysicsConstraint* constraint);
void SG_CALL _sgPhysicsSpaceRemoveConstraint(SGPhysicsSpace* space, struct SGPhysicsConstraint* constraint);
#endif /* SG_USE_PHYSICS */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_SPACE_H__
