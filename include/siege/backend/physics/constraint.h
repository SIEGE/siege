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

#ifndef __SIEGE_BACKEND_PHYSICS_CONSTRAINT_H__
#define __SIEGE_BACKEND_PHYSICS_CONSTRAINT_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif

    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintCreate)(void** constr, void* body1, void* body2, SGenum type, float* vdata);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintDestroy)(void* constr);

    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetAnchorOne)(void* constr, float x, float y);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetAnchorTwo)(void* constr, float x, float y);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetMin)(void* constr, float min);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetMax)(void* constr, float max);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetLength)(void* constr, float length);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetAngle)(void* constr, float angle);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetStiffness)(void* constr, float stiffness);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetDamping)(void* constr, float damping);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetPhase)(void* constr, float phase);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetRatchet)(void* constr, float ratchet);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetRatio)(void* constr, float ratio);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetRate)(void* constr, float rate);

    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetMaxForce)(void* constr, float max);
	SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetBiasCoeficient)(void* constr, float bias);
	SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetMaxBias)(void* constr, float max);

    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintSetData)(void* constr, void* data);
    SGenum SG_EXPORT SG_FPTR(sgmPhysicsConstraintGetData)(void* constr, void** data);

#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_PHYSICS_CONSTRAINT_H__
