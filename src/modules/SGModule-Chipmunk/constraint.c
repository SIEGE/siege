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

#include "main.h"
#include "constraint.h"

#include <stdio.h>
#include <stdlib.h>

SGenum SG_EXPORT sgmPhysicsConstraintCreate(void** constr, void* body1, void* body2, SGenum type, float* vdata)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE

    switch(type)
    {
        case SG_PHYSICS_CONSTRAINT_PIN:       *constr = cpPinJointNew(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3])); break;
        case SG_PHYSICS_CONSTRAINT_SLIDE:     *constr = cpSlideJointNew(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3]), vdata[4], vdata[5]); break;
        case SG_PHYSICS_CONSTRAINT_PIVOT:     *constr = cpPivotJointNew2(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3])); break;
        case SG_PHYSICS_CONSTRAINT_GROOVE:    *constr = cpGrooveJointNew(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3]), cpv(vdata[4], vdata[5])); break;
        case SG_PHYSICS_CONSTRAINT_LINSPRING: *constr = cpDampedSpringNew(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3]), vdata[4], vdata[5], vdata[6]); break;
        case SG_PHYSICS_CONSTRAINT_ROTSPRING: *constr = cpDampedRotarySpringNew(body1, body2, vdata[0], vdata[1], vdata[2]); break;
        case SG_PHYSICS_CONSTRAINT_ROTLIMIT:  *constr = cpRotaryLimitJointNew(body1, body2, vdata[0], vdata[1]); break;
        case SG_PHYSICS_CONSTRAINT_RATCHET:   *constr = cpRatchetJointNew(body1, body2, vdata[0], vdata[1]); break;
        case SG_PHYSICS_CONSTRAINT_GEAR:      *constr = cpGearJointNew(body1, body2, vdata[0], vdata[1]); break;
        case SG_PHYSICS_CONSTRAINT_MOTOR:     *constr = cpSimpleMotorNew(body1, body2, vdata[0]); break;
        default:
            *constr = NULL;
            return SG_OK; // SG_INVALID_ENUM
    }

    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsConstraintDestroy(void* constr)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
    cpConstraintFree(constr);
    return SG_OK;
}

//SGenum SG_EXPORT sgmPhysicsConstraintSetAnchorOne(void* constr, float x, float y)
//SGenum SG_EXPORT sgmPhysicsConstraintSetAnchorTwo(void* constr, float x, float y)
//SGenum SG_EXPORT sgmPhysicsConstraintSetMin(void* constr, float min)
//SGenum SG_EXPORT sgmPhysicsConstraintSetMax(void* constr, float max)
//SGenum SG_EXPORT sgmPhysicsConstraintSetLength(void* constr, float length)
//SGenum SG_EXPORT sgmPhysicsConstraintSetAngle(void* constr, float angle)
//SGenum SG_EXPORT sgmPhysicsConstraintSetStiffness(void* constr, float stiffness)
//SGenum SG_EXPORT sgmPhysicsConstraintSetDamping(void* constr, float damping)
//SGenum SG_EXPORT sgmPhysicsConstraintSetPhase(void* constr, float phase)
//SGenum SG_EXPORT sgmPhysicsConstraintSetRatchet(void* constr, float ratchet)
//SGenum SG_EXPORT sgmPhysicsConstraintSetRatio(void* constr, float ratio)
//SGenum SG_EXPORT sgmPhysicsConstraintSetRate(void* constr, float rate)

SGenum SG_EXPORT sgmPhysicsConstraintSetMaxForce(void* constr, float max)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
	cpConstraintSetMaxForce(constr, max);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsConstraintSetErrorBias(void* constr, float bias)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
	cpConstraintSetErrorBias(constr, bias);
    return SG_OK;
}
SGenum SG_EXPORT sgmPhysicsConstraintSetMaxBias(void* constr, float max)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
    cpConstraintSetMaxBias(constr, max);
    return SG_OK;
}

SGenum SG_EXPORT sgmPhysicsConstraintSetData(void* constr, void* data)
{
    if(!constr)
		return SG_OK; // SG_INVALID_VALUE
    cpConstraintSetUserData(constr, data);
    return SG_OK;
}

SGenum SG_EXPORT sgmPhysicsConstraintGetData(void* constr, void** data)
{
    if(!constr)
		return SG_OK; // SG_INVALID_VALUE
    *data = cpConstraintGetUserData(constr);
    return SG_OK;
}
