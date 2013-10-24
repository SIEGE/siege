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
#include "../module.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

struct SGPhysicsBody;
struct SGPhysicsShape;
struct SGPhysicsConstraint;

typedef struct SGPhysicsSpace
{
    void* handle;
    struct SGPhysicsBody* sbody;
    void* data;
} SGPhysicsSpace;

#ifdef SG_BUILD_MODULE
SGPhysicsSpace* _sg_physSpaceMain;

SGbool SG_CALL SG_FPTR(_sgPhysicsSpaceInit)(void);
SGbool SG_CALL SG_FPTR(_sgPhysicsSpaceDeinit)(void);
#endif // SG_BUILD_MODULE

SGPhysicsSpace* SG_CALL SG_FPTR(sgPhysicsSpaceCreate)(void);
void SG_CALL SG_FPTR(sgPhysicsSpaceDestroy)(SGPhysicsSpace* space);

void SG_CALL SG_FPTR(sgPhysicsSpaceStep)(SGPhysicsSpace* space, float time);

void SG_CALL SG_FPTR(sgPhysicsSpaceSetIterations)(SGPhysicsSpace* space, SGuint iterations);
void SG_CALL SG_FPTR(sgPhysicsSpaceSetGravity)(SGPhysicsSpace* space, float x, float y);
//void SG_CALL SG_FPTR(sgPhysicsSpaceGetGravity)(SGPhysicsSpace* space, float* x, float* y);
void SG_CALL SG_FPTR(sgPhysicsSpaceSetDamping)(SGPhysicsSpace* space, float damping);
//float SG_CALL SG_FPTR(sgPhysicsSpaceGetDamping)(SGPhysicsSpace* space);

void SG_CALL SG_FPTR(sgPhysicsSpaceSetData)(SGPhysicsSpace* space, void* data);
void* SG_CALL SG_FPTR(sgPhysicsSpaceGetData)(SGPhysicsSpace* space);

struct SGPhysicsBody* SG_CALL SG_FPTR(sgPhysicsSpaceGetStaticBody)(SGPhysicsSpace* space);
SGPhysicsSpace* SG_CALL SG_FPTR(sgPhysicsSpaceGetDefault)(void);

void SG_CALL SG_FPTR(_sgPhysicsSpaceAddShape)(SGPhysicsSpace* space, struct SGPhysicsShape* shape);
void SG_CALL SG_FPTR(_sgPhysicsSpaceRemoveShape)(SGPhysicsSpace* space, struct SGPhysicsShape* shape);

void SG_CALL SG_FPTR(_sgPhysicsSpaceAddBody)(SGPhysicsSpace* space, struct SGPhysicsBody* body);
void SG_CALL SG_FPTR(_sgPhysicsSpaceRemoveBody)(SGPhysicsSpace* space, struct SGPhysicsBody* body);

void SG_CALL SG_FPTR(_sgPhysicsSpaceAddConstraint)(SGPhysicsSpace* space, struct SGPhysicsConstraint* constraint);
void SG_CALL SG_FPTR(_sgPhysicsSpaceRemoveConstraint)(SGPhysicsSpace* space, struct SGPhysicsConstraint* constraint);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_SPACE_H__
