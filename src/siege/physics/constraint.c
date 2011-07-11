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
    float vdata[] = {x1, y1, x2, y2};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_PIN, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateSlide(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float min, float max)
{
    float vdata[] = {x1, y1, x2, y2, min, max};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_SLIDE, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreatePivot(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2)
{
    float vdata[] = {x1, y1, x2, y2};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_PIVOT, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateGroove(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float xa, float ya)
{
    float vdata[] = {x1, y1, x2, y2, xa, ya};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_GROOVE, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateLinSpring(SGPhysicsBody* body1, SGPhysicsBody* body2, float x1, float y1, float x2, float y2, float rest, float st, float damp)
{
    float vdata[] = {x1, y1, x2, y2, rest, st, damp};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_LINSPRING, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotSpringRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float rads, float st, float damp)
{
    float vdata[] = {rads, st, damp};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_ROTSPRING, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotSpringDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float degs, float st, float damp)
{
    float vdata[] = {degs * SG_PI / 180.0, st, damp};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_ROTSPRING, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotLimitRads(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max)
{
    float vdata[] = {min, max};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_ROTLIMIT, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRotLimitDegs(SGPhysicsBody* body1, SGPhysicsBody* body2, float min, float max)
{
    float vdata[] = {min * SG_PI / 180.0, max * SG_PI / 180.0};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_ROTLIMIT, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateRatchet(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratchet)
{
    float vdata[] = {phase, ratchet};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_RATCHET, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateGear(SGPhysicsBody* body1, SGPhysicsBody* body2, float phase, float ratio)
{
    float vdata[] = {phase, ratio};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_GEAR, vdata);
}
SGPhysicsConstraint* SG_EXPORT sgPhysicsConstraintCreateMotor(SGPhysicsBody* body1, SGPhysicsBody* body2, float rate)
{
    float vdata[] = {rate};
    return sgPhysicsConstraintCreate(body1, body2, SG_PHYSICS_CONSTRAINT_MOTOR, vdata);
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

void SG_EXPORT sgPhysicsConstraintSetData(SGPhysicsConstraint* constr, void* data)
{
    constr->data = data;
}
void* SG_EXPORT sgPhysicsConstraintGetData(SGPhysicsConstraint* constr)
{
    return constr->data;
}
