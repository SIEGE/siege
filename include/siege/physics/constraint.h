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
#include "../config.h"
#include "body.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_USE_PHYSICS
typedef struct SGPhysicsConstraint
{
    void* handle;
    SGPhysicsBody* body1;
    SGPhysicsBody* body2;
    void* data;

    SGenum type;
} SGPhysicsConstraint;

SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreate(SGPhysicsBody* body1, SGPhysicsBody* body2, SGenum type);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreatePin(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateSlide(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float min, float max);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreatePivot(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateGroove(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float xa, float ya);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateLinSpring(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float rest, float st, float damp);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRotSpringRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float rads, float st, float damp);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRotSpringDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float degs, float st, float damp);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRotLimitRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRotLimitDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRatchet(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratchet);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateGear(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratio);
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateMotor(SGPhysicsBody* body1, SGPhysicsBody* body2, float rate);
void SG_CALL sgPhysicsConstraintDestroy(SGPhysicsConstraint* constr);

void SG_CALL sgPhysicsConstraintSetAnchorOne(SGPhysicsConstraint* constr, float x, float y);
void SG_CALL sgPhysicsConstraintSetAnchorTwo(SGPhysicsConstraint* constr, float x, float y);
void SG_CALL sgPhysicsConstraintSetMin(SGPhysicsConstraint* constr, float min);
void SG_CALL sgPhysicsConstraintSetMax(SGPhysicsConstraint* constr, float max);
void SG_CALL sgPhysicsConstraintSetLength(SGPhysicsConstraint* constr, float length);
void SG_CALL sgPhysicsConstraintSetAngleRads(SGPhysicsConstraint* constr, float rads);
void SG_CALL sgPhysicsConstraintSetAngleDegs(SGPhysicsConstraint* constr, float degs);
void SG_CALL sgPhysicsConstraintSetStiffness(SGPhysicsConstraint* constr, float stiffness);
void SG_CALL sgPhysicsConstraintSetDamping(SGPhysicsConstraint* constr, float damping);
void SG_CALL sgPhysicsConstraintSetPhase(SGPhysicsConstraint* constr, float phase);
void SG_CALL sgPhysicsConstraintSetRatchet(SGPhysicsConstraint* constr, float ratchet);
void SG_CALL sgPhysicsConstraintSetRatio(SGPhysicsConstraint* constr, float ratio);
void SG_CALL sgPhysicsConstraintSetRate(SGPhysicsConstraint* constr, float rate);

void SG_CALL sgPhysicsConstraintSetMaxForce(SGPhysicsConstraint* constr, float max);
void SG_CALL sgPhysicsConstraintSetErrorBias(SGPhysicsConstraint* constr, float bias);
void SG_CALL sgPhysicsConstraintSetMaxBias(SGPhysicsConstraint* constr, float max);

void SG_CALL sgPhysicsConstraintSetData(SGPhysicsConstraint* constr, void* data);
void* SG_CALL sgPhysicsConstraintGetData(SGPhysicsConstraint* constr);
#endif /* SG_USE_PHYSICS */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_CONSTRAINT_H__
