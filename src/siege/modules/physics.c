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
#include <siege/util/link.h>
#include <siege/modules/modules.h>
#include <siege/modules/physics.h>

void SG_EXPORT _sgModuleLoadPhysics(SGLibrary* lib)
{
    void* fptr;

    /// Physics
    _SG_BIND(sgmPhysicsBodyCreate);
    _SG_BIND(sgmPhysicsBodyDestroy);

    _SG_BIND(sgmPhysicsBodySetMass);
    _SG_BIND(sgmPhysicsBodyGetMass);
    _SG_BIND(sgmPhysicsBodySetMoment);
    _SG_BIND(sgmPhysicsBodyGetMoment);
    _SG_BIND(sgmPhysicsBodySetPosition);
    _SG_BIND(sgmPhysicsBodyGetPosition);
    _SG_BIND(sgmPhysicsBodySetVelocity);
    _SG_BIND(sgmPhysicsBodyGetVelocity);
    _SG_BIND(sgmPhysicsBodySetForce);
    _SG_BIND(sgmPhysicsBodyGetForce);
    _SG_BIND(sgmPhysicsBodySetAngle);
    _SG_BIND(sgmPhysicsBodyGetAngle);
    _SG_BIND(sgmPhysicsBodySetAngularVelocity);
    _SG_BIND(sgmPhysicsBodyGetAngularVelocity);
    _SG_BIND(sgmPhysicsBodySetTorque);
    _SG_BIND(sgmPhysicsBodyGetTorque);
    _SG_BIND(sgmPhysicsBodySetData);
    _SG_BIND(sgmPhysicsBodyGetData);

    _SG_BIND(sgmPhysicsBodyApplyImpulse);
    _SG_BIND(sgmPhysicsBodyApplyForce);

    _SG_BIND(sgmPhysicsCollisionIgnore);
    _SG_BIND(sgmPhysicsCollisionGetNumContacts);
    _SG_BIND(sgmPhysicsCollisionGetPoint);
    _SG_BIND(sgmPhysicsCollisionGetNormal);
    _SG_BIND(sgmPhysicsCollisionGetDistance);
    _SG_BIND(sgmPhysicsCollisionGetImpulse);
    _SG_BIND(sgmPhysicsCollisionSetCallbacks);

    _SG_BIND(sgmPhysicsConstraintCreate);
    _SG_BIND(sgmPhysicsConstraintDestroy);

    _SG_BIND(sgmPhysicsConstraintSetAnchorOne);
    _SG_BIND(sgmPhysicsConstraintSetAnchorTwo);
    _SG_BIND(sgmPhysicsConstraintSetMin);
    _SG_BIND(sgmPhysicsConstraintSetMax);
    _SG_BIND(sgmPhysicsConstraintSetLength);
    _SG_BIND(sgmPhysicsConstraintSetAngle);
    _SG_BIND(sgmPhysicsConstraintSetStiffness);
    _SG_BIND(sgmPhysicsConstraintSetDamping);
    _SG_BIND(sgmPhysicsConstraintSetPhase);
    _SG_BIND(sgmPhysicsConstraintSetRatchet);
    _SG_BIND(sgmPhysicsConstraintSetRatio);
    _SG_BIND(sgmPhysicsConstraintSetRate);

    _SG_BIND(sgmPhysicsConstraintSetMaxForce);
	_SG_BIND(sgmPhysicsConstraintSetBiasCoeficient);
	_SG_BIND(sgmPhysicsConstraintSetMaxBias);

    _SG_BIND(sgmPhysicsConstraintSetData);
    _SG_BIND(sgmPhysicsConstraintGetData);

    _SG_BIND(sgmPhysicsShapeCreate);
    _SG_BIND(sgmPhysicsShapeDestroy);

    _SG_BIND(sgmPhysicsShapeSetGroup);
    _SG_BIND(sgmPhysicsShapeGetGroup);
    _SG_BIND(sgmPhysicsShapeSetFriction);
    _SG_BIND(sgmPhysicsShapeGetFriction);
    _SG_BIND(sgmPhysicsShapeSetRestitution);
    _SG_BIND(sgmPhysicsShapeGetRestitution);
    _SG_BIND(sgmPhysicsShapeSetData);
    _SG_BIND(sgmPhysicsShapeGetData);

    _SG_BIND(sgmPhysicsSpaceCreate);
    _SG_BIND(sgmPhysicsSpaceDestroy);
    _SG_BIND(sgmPhysicsSpaceStep);
    _SG_BIND(sgmPhysicsSpaceSetIterations);
    _SG_BIND(sgmPhysicsSpaceSetGravity);
    //_SG_BIND(sgmPhysicsSpaceGetGravity);
    _SG_BIND(sgmPhysicsSpaceSetDamping);
    //_SG_BIND(sgmPhysicsSpaceGetDamping);

    _SG_BIND(sgmPhysicsSpaceAddShape);
    _SG_BIND(sgmPhysicsSpaceRemoveShape);
    //_SG_BIND(sgmPhysicsSpaceAddStaticShape);
    //_SG_BIND(sgmPhysicsSpaceRemoveStaticShape);
    _SG_BIND(sgmPhysicsSpaceAddBody);
    _SG_BIND(sgmPhysicsSpaceRemoveBody);
    _SG_BIND(sgmPhysicsSpaceAddConstraint);
    _SG_BIND(sgmPhysicsSpaceRemoveConstraint);

    _SG_BIND(sgmPhysicsSpaceRehash);
    _SG_BIND(sgmPhysicsSpaceGetStaticBody);

    _SG_BIND(sgmPhysicsBodyWorldToLocal_TEST);
    _SG_BIND(sgmPhysicsBodyLocalToWorld_TEST);
    _SG_BIND(sgmPhysicsShapeGetBB_TEST);
    _SG_BIND(sgmPhysicsShapeGetPoints_TEST);
    _SG_BIND(sgmPhysicsShapeFreePoints_TEST);
}
