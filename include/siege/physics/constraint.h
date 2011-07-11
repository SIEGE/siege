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

#ifndef __SIEGE_PHYSICS_CONSTRAINT_H__
#define __SIEGE_PHYSICS_CONSTRAINT_H__

#include "../common.h"
#include "body.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGPhysicsConstraint
{
    void* handle;
    SGPhysicsBody* body1;
    SGPhysicsBody* body2;
    void* data;

    SGenum type;
} SGPhysicsConstraint;

SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreate(SGPhysicsBody* body1, SGPhysicsBody* body2, SGenum type, float* vdata);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreatePin(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateSlide(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float min, float max);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreatePivot(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateGroove(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float xa, float ya);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateLinSpring(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float rest, float st, float damp);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotSpringRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float rads, float st, float damp);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotSpringDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float degs, float st, float damp);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotLimitRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotLimitDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRatchet(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratchet);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateGear(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratio);
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateMotor(SGPhysicsBody* body1, SGPhysicsBody* body2, float rate);
void SG_EXPORT sgPhysicsConstraintDestroy(SGPhysicsConstraint* constr);

void SG_EXPORT sgPhysicsConstraintSetAnchorOne(SGPhysicsConstraint* constr, float x, float y);
void SG_EXPORT sgPhysicsConstraintSetAnchorTwo(SGPhysicsConstraint* constr, float x, float y);
void SG_EXPORT sgPhysicsConstraintSetMin(SGPhysicsConstraint* constr, float min);
void SG_EXPORT sgPhysicsConstraintSetMax(SGPhysicsConstraint* constr, float max);
void SG_EXPORT sgPhysicsConstraintSetLength(SGPhysicsConstraint* constr, float length);
void SG_EXPORT sgPhysicsConstraintSetAngleRads(SGPhysicsConstraint* constr, float rads);
void SG_EXPORT sgPhysicsConstraintSetAngleDegs(SGPhysicsConstraint* constr, float degs);
void SG_EXPORT sgPhysicsConstraintSetStiffness(SGPhysicsConstraint* constr, float stiffness);
void SG_EXPORT sgPhysicsConstraintSetDamping(SGPhysicsConstraint* constr, float damping);
void SG_EXPORT sgPhysicsConstraintSetPhase(SGPhysicsConstraint* constr, float phase);
void SG_EXPORT sgPhysicsConstraintSetRatchet(SGPhysicsConstraint* constr, float ratchet);
void SG_EXPORT sgPhysicsConstraintSetRatio(SGPhysicsConstraint* constr, float ratio);
void SG_EXPORT sgPhysicsConstraintSetRate(SGPhysicsConstraint* constr, float rate);

void SG_EXPORT sgPhysicsConstraintSetData(SGPhysicsConstraint* constr, void* data);
void* SG_EXPORT sgPhysicsConstraintGetData(SGPhysicsConstraint* constr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_CONSTRAINT_H__
