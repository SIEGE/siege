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

#define SG_BUILD_MODULE
#include <siege/physics/constraint.h>

#include <stdlib.h>

#include "compat.h"

static void _postCreate(SGPhysicsConstraint* constr)
{
    //SG_ASSERT(constr->body1->space == constr->body2->space);

    cpConstraintSetUserData(constr->handle, constr);
    _sgPhysicsSpaceAddConstraint(constr->body1->space, constr);
}

SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreate(SGPhysicsBody* body1, SGPhysicsBody* body2, SGenum type)
{
    SGPhysicsConstraint* constr = malloc(sizeof(SGPhysicsConstraint));
    if(!constr) return NULL;

    constr->handle = NULL;
    constr->body1 = body1;
    constr->body2 = body2;
    constr->data = NULL;
    constr->type = type;

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreatePin(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_PIN);
    if(!constr) return NULL;

    constr->handle = cpPinJointNew(body1->handle, body2->handle, cpv(x1, y1), cpv(x2, y2));
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateSlide(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float min, float max)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_SLIDE);
    if(!constr) return NULL;

    constr->handle = cpSlideJointNew(body1->handle, body2->handle, cpv(x1, y1), cpv(x2, y2), min, max);
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreatePivot(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_PIVOT);
    if(!constr) return NULL;

    constr->handle = cpPivotJointNew2(body1->handle, body2->handle, cpv(x1, y1), cpv(x2, y2));
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateGroove(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float xa, float ya)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_GROOVE);
    if(!constr) return NULL;

    constr->handle = cpGrooveJointNew(body1->handle, body2->handle, cpv(x1, y1), cpv(x2, y2), cpv(xa, ya));
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateLinSpring(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float rest, float st, float damp)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_LINSPRING);
    if(!constr) return NULL;

    constr->handle = cpDampedSpringNew(body1->handle, body2->handle, cpv(x1, y1), cpv(x2, y2), rest, st, damp);
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRotSpringRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float rads, float st, float damp)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_ROTSPRING);
    if(!constr) return NULL;

    constr->handle = cpDampedRotarySpringNew(body1->handle, body2->handle, rads, st, damp);
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRotSpringDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float degs, float st, float damp)
{
    return sgPhysicsConstraintCreateRotSpringRads(body1, body2, degs * SG_PI / 180.0, st, damp);
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRotLimitRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_ROTLIMIT);
    if(!constr) return NULL;

    constr->handle = cpRotaryLimitJointNew(body1->handle, body2->handle, min, max);
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRotLimitDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max)
{
    return sgPhysicsConstraintCreateRotLimitRads(body1, body2, min * SG_PI / 180.0, max * SG_PI / 180.0);
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateRatchet(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratchet)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_RATCHET);
    if(!constr) return NULL;

    constr->handle = cpRatchetJointNew(body1->handle, body2->handle, phase, ratchet);
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateGear(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratio)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_GEAR);
    if(!constr) return NULL;

    constr->handle = cpGearJointNew(body1->handle, body2->handle, phase, ratio);
    _postCreate(constr);

    return constr;
}
SGPhysicsConstraint* SG_CALL sgPhysicsConstraintCreateMotor(SGPhysicsBody* body1, SGPhysicsBody* body2, float rate)
{
    SGPhysicsConstraint* constr = sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_MOTOR);
    if(!constr) return NULL;

    constr->handle = cpSimpleMotorNew(body1->handle, body2->handle, rate);
    _postCreate(constr);

    return constr;
}
void SG_CALL sgPhysicsConstraintDestroy(SGPhysicsConstraint* constr)
{
    if(!constr) return;

    _sgPhysicsSpaceRemoveConstraint(constr->body1->space, constr);
    cpConstraintFree(constr->handle);
    free(constr);
}

// $$$$$ TODO $$$$$
void SG_CALL sgPhysicsConstraintSetAnchorOne(SGPhysicsConstraint* constr, float x, float y)
{
}
void SG_CALL sgPhysicsConstraintSetAnchorTwo(SGPhysicsConstraint* constr, float x, float y)
{
}
void SG_CALL sgPhysicsConstraintSetMin(SGPhysicsConstraint* constr, float min)
{
}
void SG_CALL sgPhysicsConstraintSetMax(SGPhysicsConstraint* constr, float max)
{
}
void SG_CALL sgPhysicsConstraintSetLength(SGPhysicsConstraint* constr, float length)
{
}
void SG_CALL sgPhysicsConstraintSetAngleRads(SGPhysicsConstraint* constr, float rads)
{
}
void SG_CALL sgPhysicsConstraintSetAngleDegs(SGPhysicsConstraint* constr, float degs)
{
    sgPhysicsConstraintSetAngleRads(constr, degs * SG_PI / 180.0);
}
void SG_CALL sgPhysicsConstraintSetStiffness(SGPhysicsConstraint* constr, float stiffness)
{
}
void SG_CALL sgPhysicsConstraintSetDamping(SGPhysicsConstraint* constr, float damping)
{
}
void SG_CALL sgPhysicsConstraintSetPhase(SGPhysicsConstraint* constr, float phase)
{
}
void SG_CALL sgPhysicsConstraintSetRatchet(SGPhysicsConstraint* constr, float ratchet)
{
}
void SG_CALL sgPhysicsConstraintSetRatio(SGPhysicsConstraint* constr, float ratio)
{
}
void SG_CALL sgPhysicsConstraintSetRate(SGPhysicsConstraint* constr, float rate)
{
}

void SG_CALL sgPhysicsConstraintSetMaxForce(SGPhysicsConstraint* constr, float max)
{
    cpConstraintSetMaxForce(constr->handle, max);
}
// float SG_CALL sgPhysicsConstraintGetMaxForce(SGPhysicsConstraint* constr);
void SG_CALL sgPhysicsConstraintSetErrorBias(SGPhysicsConstraint* constr, float bias)
{
    cpConstraintSetErrorBias(constr->handle, bias);
}
// float SG_CALL sgPhysicsConstraintGetErrorBias(SGPhysicsConstraint* constr);
void SG_CALL sgPhysicsConstraintSetMaxBias(SGPhysicsConstraint* constr, float max)
{
    cpConstraintSetMaxBias(constr->handle, max);
}
// float SG_CALL sgPhysicsConstraintGetMaxBias(SGPhysicsConstraint* constr);

void SG_CALL sgPhysicsConstraintSetData(SGPhysicsConstraint* constr, void* data)
{
    constr->data = data;
}
void* SG_CALL sgPhysicsConstraintGetData(SGPhysicsConstraint* constr)
{
    return constr->data;
}
