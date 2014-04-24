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
#include "../module.h"
#include "body.h"

#define SG_CONSTRAINT_PIN       0x01
#define SG_CONSTRAINT_SLIDE     0x02
#define SG_CONSTRAINT_PIVOT     0x03
#define SG_CONSTRAINT_GROOVE    0x04
#define SG_CONSTRAINT_LINSPRING 0x05
#define SG_CONSTRAINT_ROTSPRING 0x06
#define SG_CONSTRAINT_ROTLIMIT  0x07
#define SG_CONSTRAINT_RATCHET   0x08
#define SG_CONSTRAINT_GEAR      0x09
#define SG_CONSTRAINT_MOTOR     0x0A

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

SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreate)(SGPhysicsBody* body1, SGPhysicsBody* body2, SGenum type);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreatePin)(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateSlide)(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float min, float max);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreatePivot)(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateGroove)(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float xa, float ya);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateLinSpring)(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float rest, float st, float damp);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateRotSpringRads)(SGPhysicsBody* body1, SGPhysicsBody* body2, float rads, float st, float damp);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateRotSpringDegs)(SGPhysicsBody* body1, SGPhysicsBody* body2, float degs, float st, float damp);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateRotLimitRads)(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateRotLimitDegs)(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateRatchet)(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratchet);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateGear)(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratio);
SGPhysicsConstraint* SG_CALL SG_FPTR(sgPhysicsConstraintCreateMotor)(SGPhysicsBody* body1, SGPhysicsBody* body2, float rate);
void SG_CALL SG_FPTR(sgPhysicsConstraintDestroy)(SGPhysicsConstraint* constr);

void SG_CALL SG_FPTR(sgPhysicsConstraintSetAnchorOne)(SGPhysicsConstraint* constr, float x, float y);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetAnchorTwo)(SGPhysicsConstraint* constr, float x, float y);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetMin)(SGPhysicsConstraint* constr, float min);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetMax)(SGPhysicsConstraint* constr, float max);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetLength)(SGPhysicsConstraint* constr, float length);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetAngleRads)(SGPhysicsConstraint* constr, float rads);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetAngleDegs)(SGPhysicsConstraint* constr, float degs);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetStiffness)(SGPhysicsConstraint* constr, float stiffness);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetDamping)(SGPhysicsConstraint* constr, float damping);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetPhase)(SGPhysicsConstraint* constr, float phase);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetRatchet)(SGPhysicsConstraint* constr, float ratchet);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetRatio)(SGPhysicsConstraint* constr, float ratio);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetRate)(SGPhysicsConstraint* constr, float rate);

void SG_CALL SG_FPTR(sgPhysicsConstraintSetMaxForce)(SGPhysicsConstraint* constr, float max);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetErrorBias)(SGPhysicsConstraint* constr, float bias);
void SG_CALL SG_FPTR(sgPhysicsConstraintSetMaxBias)(SGPhysicsConstraint* constr, float max);

void SG_CALL SG_FPTR(sgPhysicsConstraintSetData)(SGPhysicsConstraint* constr, void* data);
void* SG_CALL SG_FPTR(sgPhysicsConstraintGetData)(SGPhysicsConstraint* constr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_PHYSICS_CONSTRAINT_H__
