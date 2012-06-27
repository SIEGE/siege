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

#define SG_BUILD_LIBRARY
#include <siege/physics/constraint.h>
#include <siege/modules/physics.h>

#include <stdlib.h>

SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreate(SGPhysicsBody* body1, SGPhysicsBody* body2, SGenum type, float* vdata)
{
    SGPhysicsConstraint* constr = malloc(sizeof(SGPhysicsConstraint));
    if(!constr)
        return NULL;
    constr->handle = NULL;
    constr->body1 = body1;
    constr->body2 = body2;
    constr->data = NULL;
    constr->type = type;
    if(psgmPhysicsConstraintCreate)
        psgmPhysicsConstraintCreate(&constr->handle, body1->handle, body2->handle, type, vdata);
    if(psgmPhysicsConstraintSetData)
        psgmPhysicsConstraintSetData(constr->handle, constr);
    if(psgmPhysicsSpaceAddConstraint)
        psgmPhysicsSpaceAddConstraint(body1->space->handle, constr->handle);
    return constr;
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreatePin(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2)
{
    float vdata[4];
    vdata[0] = x1; vdata[1] = y1; vdata[2] = x2; vdata[3] = y2;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_PIN, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateSlide(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float min, float max)
{
    float vdata[6];
    vdata[0] = x1; vdata[1] = y1; vdata[2] = x2; vdata[3] = y2;
    vdata[4] = min; vdata[5] = max;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_SLIDE, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreatePivot(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2)
{
    float vdata[4];
    vdata[0] = x1; vdata[1] = y1; vdata[2] = x2; vdata[3] = y2;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_PIVOT, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateGroove(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float xa, float ya)
{
    float vdata[6];
    vdata[0] = x1; vdata[1] = y1; vdata[2] = x2; vdata[3] = y2;
    vdata[4] = xa; vdata[5] = ya;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_GROOVE, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateLinSpring(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float rest, float st, float damp)
{
    float vdata[7];
    vdata[0] = x1; vdata[1] = y1; vdata[2] = x2; vdata[3] = y2;
    vdata[4] = rest; vdata[5] = st; vdata[6] = damp;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_LINSPRING, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotSpringRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float rads, float st, float damp)
{
    float vdata[3];
    vdata[0] = rads; vdata[1] = st; vdata[2] = damp;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_ROTSPRING, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotSpringDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float degs, float st, float damp)
{
    return sgPhysicsConstraintCreateRotSpringRads(body1, body2, degs * SG_PI / 180.0, st, damp);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotLimitRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max)
{
    float vdata[2];
    vdata[0] = min; vdata[1] = max;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_ROTLIMIT, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotLimitDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max)
{
    return sgPhysicsConstraintCreateRotLimitRads(body1, body2, min * SG_PI / 180.0, max * SG_PI / 180.0);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRatchet(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratchet)
{
    float vdata[2];
    vdata[0] = phase; vdata[1] = ratchet;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_RATCHET, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateGear(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratio)
{
    float vdata[2];
    vdata[0] = phase; vdata[1] = ratio;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_GEAR, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateMotor(SGPhysicsBody* body1, SGPhysicsBody* body2, float rate)
{
    float vdata[1];
    // we do this anyways since that float might become double in SIEGE's future
    vdata[0] = rate;
    return sgPhysicsConstraintCreate(body1, body2, SG_CONSTRAINT_MOTOR, vdata);
}
void SG_EXPORT sgPhysicsConstraintDestroy(SGPhysicsConstraint* constr)
{
    if(!constr)
        return;

    if(psgmPhysicsSpaceRemoveConstraint)
        psgmPhysicsSpaceRemoveConstraint(constr->body1->space->handle, constr->handle);
    if(psgmPhysicsConstraintDestroy)
        psgmPhysicsConstraintDestroy(constr->handle);

    free(constr);
}

void SG_EXPORT sgPhysicsConstraintSetAnchorOne(SGPhysicsConstraint* constr, float x, float y)
{
    if(psgmPhysicsConstraintSetAnchorOne)
        psgmPhysicsConstraintSetAnchorOne(constr->handle, x, y);
}
void SG_EXPORT sgPhysicsConstraintSetAnchorTwo(SGPhysicsConstraint* constr, float x, float y)
{
    if(psgmPhysicsConstraintSetAnchorTwo)
        psgmPhysicsConstraintSetAnchorTwo(constr->handle, x, y);
}
void SG_EXPORT sgPhysicsConstraintSetMin(SGPhysicsConstraint* constr, float min)
{
    if(psgmPhysicsConstraintSetMin)
        psgmPhysicsConstraintSetMin(constr->handle, min);
}
void SG_EXPORT sgPhysicsConstraintSetMax(SGPhysicsConstraint* constr, float max)
{
    if(psgmPhysicsConstraintSetMax)
        psgmPhysicsConstraintSetMax(constr->handle, max);
}
void SG_EXPORT sgPhysicsConstraintSetLength(SGPhysicsConstraint* constr, float length)
{
    if(psgmPhysicsConstraintSetLength)
        psgmPhysicsConstraintSetLength(constr->handle, length);
}
void SG_EXPORT sgPhysicsConstraintSetAngleRads(SGPhysicsConstraint* constr, float rads)
{
    if(psgmPhysicsConstraintSetAngle)
        psgmPhysicsConstraintSetAngle(constr->handle, rads);
}
void SG_EXPORT sgPhysicsConstraintSetAngleDegs(SGPhysicsConstraint* constr, float degs)
{
    if(psgmPhysicsConstraintSetAngle)
        psgmPhysicsConstraintSetAngle(constr->handle, degs * SG_PI / 180.0);
}
void SG_EXPORT sgPhysicsConstraintSetStiffness(SGPhysicsConstraint* constr, float stiffness)
{
    if(psgmPhysicsConstraintSetStiffness)
        psgmPhysicsConstraintSetStiffness(constr->handle, stiffness);
}
void SG_EXPORT sgPhysicsConstraintSetDamping(SGPhysicsConstraint* constr, float damping)
{
    if(psgmPhysicsConstraintSetDamping)
        psgmPhysicsConstraintSetDamping(constr->handle, damping);
}
void SG_EXPORT sgPhysicsConstraintSetPhase(SGPhysicsConstraint* constr, float phase)
{
    if(psgmPhysicsConstraintSetPhase)
        psgmPhysicsConstraintSetPhase(constr->handle, phase);
}
void SG_EXPORT sgPhysicsConstraintSetRatchet(SGPhysicsConstraint* constr, float ratchet)
{
    if(psgmPhysicsConstraintSetRatchet)
        psgmPhysicsConstraintSetRatchet(constr->handle, ratchet);
}
void SG_EXPORT sgPhysicsConstraintSetRatio(SGPhysicsConstraint* constr, float ratio)
{
    if(psgmPhysicsConstraintSetRatio)
        psgmPhysicsConstraintSetRatio(constr->handle, ratio);
}
void SG_EXPORT sgPhysicsConstraintSetRate(SGPhysicsConstraint* constr, float rate)
{
    if(psgmPhysicsConstraintSetRate)
        psgmPhysicsConstraintSetRate(constr->handle, rate);
}

void SG_EXPORT sgPhysicsConstraintSetMaxForce(SGPhysicsConstraint* constr, float max)
{
	if(psgmPhysicsConstraintSetMaxForce)
		psgmPhysicsConstraintSetMaxForce(constr->handle, max);
}
void SG_EXPORT sgPhysicsConstraintSetErrorBias(SGPhysicsConstraint* constr, float bias)
{
	if(psgmPhysicsConstraintSetErrorBias)
		psgmPhysicsConstraintSetErrorBias(constr->handle, bias);
}
void SG_EXPORT sgPhysicsConstraintSetMaxBias(SGPhysicsConstraint* constr, float max)
{
	if(psgmPhysicsConstraintSetMaxBias)
		psgmPhysicsConstraintSetMaxBias(constr->handle, max);
}

void SG_EXPORT sgPhysicsConstraintSetData(SGPhysicsConstraint* constr, void* data)
{
    constr->data = data;
}
void* SG_EXPORT sgPhysicsConstraintGetData(SGPhysicsConstraint* constr)
{
    return constr->data;
}
