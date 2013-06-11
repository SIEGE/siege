/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "common.h"

#include <stdlib.h>

SGenum SG_CALL sgmPhysicsConstraintCreate(void** constr, void* body1, void* body2, SGenum type, float* vdata)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE

    switch(type)
    {
        case SG_CONSTRAINT_PIN:       *constr = cpPinJointNew(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3])); break;
        case SG_CONSTRAINT_SLIDE:     *constr = cpSlideJointNew(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3]), vdata[4], vdata[5]); break;
        case SG_CONSTRAINT_PIVOT:     *constr = cpPivotJointNew2(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3])); break;
        case SG_CONSTRAINT_GROOVE:    *constr = cpGrooveJointNew(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3]), cpv(vdata[4], vdata[5])); break;
        case SG_CONSTRAINT_LINSPRING: *constr = cpDampedSpringNew(body1, body2, cpv(vdata[0], vdata[1]), cpv(vdata[2], vdata[3]), vdata[4], vdata[5], vdata[6]); break;
        case SG_CONSTRAINT_ROTSPRING: *constr = cpDampedRotarySpringNew(body1, body2, vdata[0], vdata[1], vdata[2]); break;
        case SG_CONSTRAINT_ROTLIMIT:  *constr = cpRotaryLimitJointNew(body1, body2, vdata[0], vdata[1]); break;
        case SG_CONSTRAINT_RATCHET:   *constr = cpRatchetJointNew(body1, body2, vdata[0], vdata[1]); break;
        case SG_CONSTRAINT_GEAR:      *constr = cpGearJointNew(body1, body2, vdata[0], vdata[1]); break;
        case SG_CONSTRAINT_MOTOR:     *constr = cpSimpleMotorNew(body1, body2, vdata[0]); break;
        default:
            *constr = NULL;
            return SG_OK; // SG_INVALID_ENUM
    }

    return SG_OK;
}
SGenum SG_CALL sgmPhysicsConstraintDestroy(void* constr)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
    cpConstraintFree(constr);
    return SG_OK;
}

//SGenum SG_CALL sgmPhysicsConstraintSetAnchorOne(void* constr, float x, float y)
//SGenum SG_CALL sgmPhysicsConstraintSetAnchorTwo(void* constr, float x, float y)
//SGenum SG_CALL sgmPhysicsConstraintSetMin(void* constr, float min)
//SGenum SG_CALL sgmPhysicsConstraintSetMax(void* constr, float max)
//SGenum SG_CALL sgmPhysicsConstraintSetLength(void* constr, float length)
//SGenum SG_CALL sgmPhysicsConstraintSetAngle(void* constr, float angle)
//SGenum SG_CALL sgmPhysicsConstraintSetStiffness(void* constr, float stiffness)
//SGenum SG_CALL sgmPhysicsConstraintSetDamping(void* constr, float damping)
//SGenum SG_CALL sgmPhysicsConstraintSetPhase(void* constr, float phase)
//SGenum SG_CALL sgmPhysicsConstraintSetRatchet(void* constr, float ratchet)
//SGenum SG_CALL sgmPhysicsConstraintSetRatio(void* constr, float ratio)
//SGenum SG_CALL sgmPhysicsConstraintSetRate(void* constr, float rate)

SGenum SG_CALL sgmPhysicsConstraintSetMaxForce(void* constr, float max)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
    cpConstraintSetMaxForce(constr, max);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsConstraintSetErrorBias(void* constr, float bias)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
    cpConstraintSetErrorBias(constr, bias);
    return SG_OK;
}
SGenum SG_CALL sgmPhysicsConstraintSetMaxBias(void* constr, float max)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
    cpConstraintSetMaxBias(constr, max);
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsConstraintSetData(void* constr, void* data)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
    cpConstraintSetUserData(constr, data);
    return SG_OK;
}

SGenum SG_CALL sgmPhysicsConstraintGetData(void* constr, void** data)
{
    if(!constr)
        return SG_OK; // SG_INVALID_VALUE
    *data = cpConstraintGetUserData(constr);
    return SG_OK;
}
