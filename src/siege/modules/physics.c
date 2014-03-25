#include <siege/common.h>
#include <siege/physics/module.h>
#include <siege/physics/body.h>
#include <siege/physics/collision.h>
#include <siege/physics/constraint.h>
#include <siege/physics/shape.h>
#include <siege/physics/space.h>
#include <siege/util/link.h>

static SGbool loaded;
static SGLibrary* lib;

#define BIND(NAME)  \
    do { fptr = sgGetProcAddress(lib, #NAME);   \
    (NAME) = fptr;  \
    if(!NAME) return SG_FALSE; } while(0)

static SGbool loadAll(void)
{
    lib = sgLibraryLoad("SGM-Physics");
    if(!lib) lib = sgLibraryLoad("libSGM-Physics");
    if(!lib) return SG_FALSE;

    void* fptr;

    /* INIT/DEINIT */
    BIND(_sgPhysicsInit);
    BIND(_sgPhysicsDeinit);

    /* BODY */
    BIND(sgPhysicsBodyCreate);
    BIND(sgPhysicsBodyDestroy);

    BIND(sgPhysicsBodySetData);
    BIND(sgPhysicsBodyGetData);

    BIND(sgPhysicsBodySetSleeping);
    BIND(sgPhysicsBodyGetSleeping);

    BIND(sgPhysicsBodySetPos);
    BIND(sgPhysicsBodyGetPos);

    BIND(sgPhysicsBodySetPosX);
    BIND(sgPhysicsBodyGetPosX);
    BIND(sgPhysicsBodySetPosY);
    BIND(sgPhysicsBodyGetPosY);

    BIND(sgPhysicsBodySetAngleRads);
    BIND(sgPhysicsBodyGetAngleRads);
    BIND(sgPhysicsBodySetAngleDegs);
    BIND(sgPhysicsBodyGetAngleDegs);

    BIND(sgPhysicsBodySetVel);
    BIND(sgPhysicsBodyGetVel);

    BIND(sgPhysicsBodySetVelX);
    BIND(sgPhysicsBodyGetVelX);
    BIND(sgPhysicsBodySetVelY);
    BIND(sgPhysicsBodyGetVelY);

    BIND(sgPhysicsBodySetAngVelRads);
    BIND(sgPhysicsBodyGetAngVelRads);
    BIND(sgPhysicsBodySetAngVelDegs);
    BIND(sgPhysicsBodyGetAngVelDegs);

    BIND(sgPhysicsBodySetMass);
    BIND(sgPhysicsBodyGetMass);

    BIND(sgPhysicsBodySetMoment);
    BIND(sgPhysicsBodyGetMoment);

    BIND(sgPhysicsBodySetForce);
    BIND(sgPhysicsBodyGetForce);

    BIND(sgPhysicsBodySetForceX);
    BIND(sgPhysicsBodyGetForceX);
    BIND(sgPhysicsBodySetForceY);
    BIND(sgPhysicsBodyGetForceY);

    BIND(sgPhysicsBodySetTorque);
    BIND(sgPhysicsBodyGetTorque);

    BIND(sgPhysicsBodyApplyImpulse);
    BIND(sgPhysicsBodyApplyForce);

    BIND(sgPhysicsBodyWorldToLocal);
    BIND(sgPhysicsBodyLocalToWorld);

    /* COLLISION */
    BIND(sgPhysicsCollisionIgnore);
    BIND(sgPhysicsCollisionGetNumContacts);
    BIND(sgPhysicsCollisionGetPoint);
    BIND(sgPhysicsCollisionGetNormal);
    BIND(sgPhysicsCollisionGetDepth);
    BIND(sgPhysicsCollisionGetImpulse);
    BIND(sgPhysicsCollisionGetShapeOne);
    BIND(sgPhysicsCollisionGetShapeTwo);

    /* CONSTRAINT */
    BIND(sgPhysicsConstraintCreate);
    BIND(sgPhysicsConstraintCreatePin);
    BIND(sgPhysicsConstraintCreateSlide);
    BIND(sgPhysicsConstraintCreatePivot);
    BIND(sgPhysicsConstraintCreateGroove);
    BIND(sgPhysicsConstraintCreateLinSpring);
    BIND(sgPhysicsConstraintCreateRotSpringRads);
    BIND(sgPhysicsConstraintCreateRotSpringDegs);
    BIND(sgPhysicsConstraintCreateRotLimitRads);
    BIND(sgPhysicsConstraintCreateRotLimitDegs);
    BIND(sgPhysicsConstraintCreateRatchet);
    BIND(sgPhysicsConstraintCreateGear);
    BIND(sgPhysicsConstraintCreateMotor);
    BIND(sgPhysicsConstraintDestroy);

    BIND(sgPhysicsConstraintSetAnchorOne);
    BIND(sgPhysicsConstraintSetAnchorTwo);
    BIND(sgPhysicsConstraintSetMin);
    BIND(sgPhysicsConstraintSetMax);
    BIND(sgPhysicsConstraintSetLength);
    BIND(sgPhysicsConstraintSetAngleRads);
    BIND(sgPhysicsConstraintSetAngleDegs);
    BIND(sgPhysicsConstraintSetStiffness);
    BIND(sgPhysicsConstraintSetDamping);
    BIND(sgPhysicsConstraintSetPhase);
    BIND(sgPhysicsConstraintSetRatchet);
    BIND(sgPhysicsConstraintSetRatio);
    BIND(sgPhysicsConstraintSetRate);

    BIND(sgPhysicsConstraintSetMaxForce);
    BIND(sgPhysicsConstraintSetErrorBias);
    BIND(sgPhysicsConstraintSetMaxBias);

    BIND(sgPhysicsConstraintSetData);
    BIND(sgPhysicsConstraintGetData);

    /* SHAPE */
    BIND(sgPhysicsShapeCreate);
    BIND(sgPhysicsShapeCreateSegment);
    BIND(sgPhysicsShapeCreatePoly);
    BIND(sgPhysicsShapeCreateCircle);
    BIND(sgPhysicsShapeDestroy);

    BIND(sgPhysicsShapeSetGroup);
    BIND(sgPhysicsShapeGetGroup);
    BIND(sgPhysicsShapeSetFriction);
    BIND(sgPhysicsShapeGetFriction);

    BIND(sgPhysicsShapeSetRestitution);
    BIND(sgPhysicsShapeGetRestitution);
    BIND(sgPhysicsShapeSetData);
    BIND(sgPhysicsShapeGetData);

    BIND(sgPhysicsShapeGetAreaS);
    BIND(sgPhysicsShapeGetAreaU);
    BIND(sgPhysicsShapeGetMass);
    BIND(sgPhysicsShapeGetMomentMass);
    BIND(sgPhysicsShapeGetMomentDensity);

    BIND(sgPhysicsShapeGetBBox);
    BIND(sgPhysicsShapeDrawDBG);

    /* SPACE */
    BIND(sgPhysicsSpaceCreate);
    BIND(sgPhysicsSpaceDestroy);

    BIND(sgPhysicsSpaceStep);

    BIND(sgPhysicsSpaceSetIterations);
    BIND(sgPhysicsSpaceSetGravity);
//    BIND(sgPhysicsSpaceGetGravity);
    BIND(sgPhysicsSpaceSetDamping);
//    BIND(sgPhysicsSpaceGetDamping);

    BIND(sgPhysicsSpaceSetData);
    BIND(sgPhysicsSpaceGetData);

    BIND(sgPhysicsSpaceGetStaticBody);
    BIND(sgPhysicsSpaceGetDefault);

    BIND(_sgPhysicsSpaceAddShape);
    BIND(_sgPhysicsSpaceRemoveShape);

    BIND(_sgPhysicsSpaceAddBody);
    BIND(_sgPhysicsSpaceRemoveBody);

    BIND(_sgPhysicsSpaceAddConstraint);
    BIND(_sgPhysicsSpaceRemoveConstraint);

    return SG_TRUE;
}

SGbool SG_CALL _sgPhysicsLoad(void)
{
    loaded = loadAll();
    return loaded;
}
SGbool SG_CALL _sgPhysicsUnload(void)
{
    sgLibraryUnload(lib);
    loaded = SG_FALSE;
    return SG_TRUE;
}

SGbool SG_CALL sgPhysicsIsAvailable(void)
{
    return loaded;
}
