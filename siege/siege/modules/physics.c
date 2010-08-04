#define SG_BUILD_LIBRARY
#include <siege/util/link.h>
#include <siege/modules/modules.h>
#include <siege/modules/physics.h>

void SG_EXPORT _sgModuleLoadPhysics(SGLibrary* lib)
{
    void* fptr;

    /// Physics
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyCreate);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyDestroy);

    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetMass);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetMass);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetMoment);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetMoment);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetPosition);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetPosition);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetVelocity);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetVelocity);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetForce);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetForce);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetAngle);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetAngle);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetAngularVelocity);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetAngularVelocity);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetTorque);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetTorque);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodySetData);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyGetData);

    // constraint

    _SG_BINDS(_sg_modPhysics, sgmPhysicsShapeCreate);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsShapeDestroy);

    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceCreate);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceDestroy);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceStep);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceSetGravity);

    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceAddShape);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceRemoveShape);
    //_SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceAddStaticShape);
    //_SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceRemoveStaticShape);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceAddBody);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceRemoveBody);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceAddConstraint);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsSpaceRemoveConstraint);

    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyWorldToLocal_TEST);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsBodyLocalToWorld_TEST);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsShapeGetBB_TEST);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsShapeGetPoints_TEST);
    _SG_BINDS(_sg_modPhysics, sgmPhysicsShapeFreePoints_TEST);
}

SGModulePhysics* SG_EXPORT sgModuleGetPhysics(void)
{
    return &_sg_modPhysics;
}
