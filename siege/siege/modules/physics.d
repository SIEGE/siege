module siege.modules.physics;

private
{
    import derelict.util.loader;

    import siege.modules.modules;
}

enum: uint
{
    SG_PHYSICS_BODY_PASSIVE    = 0x01, // add both
    SG_PHYSICS_BODY_NORMAL     = 0x02, // add both
    SG_PHYSICS_BODY_SEMISTATIC = 0x03, // add shape
    SG_PHYSICS_BODY_STATIC     = 0x04, // add sshape
}

enum: uint
{
    SG_PHYSICS_SHAPE_SEGMENT = 0x01,
    SG_PHYSICS_SHAPE_POLYGON = 0x02,
    SG_PHYSICS_SHAPE_CIRCLE  = 0x03,
}

void loadModulePhysics(SharedLib lib)
{
    /// Physics
    checkBindFunc(sgPhysicsBodyCreate)("sgmPhysicsBodyCreate", lib);
    checkBindFunc(sgPhysicsBodyDestroy)("sgmPhysicsBodyDestroy", lib);

    checkBindFunc(sgPhysicsBodySetMass)("sgmPhysicsBodySetMass", lib);
    checkBindFunc(sgPhysicsBodyGetMass)("sgmPhysicsBodyGetMass", lib);
    checkBindFunc(sgPhysicsBodySetMoment)("sgmPhysicsBodySetMoment", lib);
    checkBindFunc(sgPhysicsBodyGetMoment)("sgmPhysicsBodyGetMoment", lib);
    checkBindFunc(sgPhysicsBodySetPosition)("sgmPhysicsBodySetPosition", lib);
    checkBindFunc(sgPhysicsBodyGetPosition)("sgmPhysicsBodyGetPosition", lib);
    checkBindFunc(sgPhysicsBodySetVelocity)("sgmPhysicsBodySetVelocity", lib);
    checkBindFunc(sgPhysicsBodyGetVelocity)("sgmPhysicsBodyGetVelocity", lib);
    checkBindFunc(sgPhysicsBodySetForce)("sgmPhysicsBodySetForce", lib);
    checkBindFunc(sgPhysicsBodyGetForce)("sgmPhysicsBodyGetForce", lib);
    checkBindFunc(sgPhysicsBodySetAngle)("sgmPhysicsBodySetAngle", lib);
    checkBindFunc(sgPhysicsBodyGetAngle)("sgmPhysicsBodyGetAngle", lib);
    checkBindFunc(sgPhysicsBodySetAngularVelocity)("sgmPhysicsBodySetAngularVelocity", lib);
    checkBindFunc(sgPhysicsBodyGetAngularVelocity)("sgmPhysicsBodyGetAngularVelocity", lib);
    checkBindFunc(sgPhysicsBodySetTorque)("sgmPhysicsBodySetTorque", lib);
    checkBindFunc(sgPhysicsBodyGetTorque)("sgmPhysicsBodyGetTorque", lib);
    checkBindFunc(sgPhysicsBodySetData)("sgmPhysicsBodySetData", lib);
    checkBindFunc(sgPhysicsBodyGetData)("sgmPhysicsBodyGetData", lib);

    // constraint

    checkBindFunc(sgPhysicsShapeCreate)("sgmPhysicsShapeCreate", lib);
    checkBindFunc(sgPhysicsShapeDestroy)("sgmPhysicsShapeDestroy", lib);

    checkBindFunc(sgPhysicsSpaceCreate)("sgmPhysicsSpaceCreate", lib);
    checkBindFunc(sgPhysicsSpaceDestroy)("sgmPhysicsSpaceDestroy", lib);
    checkBindFunc(sgPhysicsSpaceStep)("sgmPhysicsSpaceStep", lib);
    checkBindFunc(sgPhysicsSpaceSetGravity)("sgmPhysicsSpaceSetGravity", lib);

    checkBindFunc(sgPhysicsSpaceAddShape)("sgmPhysicsSpaceAddShape", lib);
    checkBindFunc(sgPhysicsSpaceRemoveShape)("sgmPhysicsSpaceRemoveShape", lib);
    //checkBindFunc(sgPhysicsSpaceAddStaticShape)("sgmPhysicsSpaceAddStaticShape", lib);
    //checkBindFunc(sgPhysicsSpaceRemoveStaticShape)("sgmPhysicsSpaceRemoveStaticShape", lib);
    checkBindFunc(sgPhysicsSpaceAddBody)("sgmPhysicsSpaceAddBody", lib);
    checkBindFunc(sgPhysicsSpaceRemoveBody)("sgmPhysicsSpaceRemoveBody", lib);
    checkBindFunc(sgPhysicsSpaceAddConstraint)("sgmPhysicsSpaceAddConstraint", lib);
    checkBindFunc(sgPhysicsSpaceRemoveConstraint)("sgmPhysicsSpaceRemoveConstraint", lib);

    checkBindFunc(sgPhysicsBodyWorldToLocal_TEST)("sgmPhysicsBodyWorldToLocal_TEST", lib);
    checkBindFunc(sgPhysicsBodyLocalToWorld_TEST)("sgmPhysicsBodyLocalToWorld_TEST", lib);
    checkBindFunc(sgPhysicsShapeGetBB_TEST)("sgmPhysicsShapeGetBB_TEST", lib);
    checkBindFunc(sgPhysicsShapeGetPoints_TEST)("sgmPhysicsShapeGetPoints_TEST", lib);
    checkBindFunc(sgPhysicsShapeFreePoints_TEST)("sgmPhysicsShapeFreePoints_TEST", lib);
}

extern(C)
{
    /// Physics
    uint function(void** cbody, uint type) sgPhysicsBodyCreate;
    uint function(void* cbody) sgPhysicsBodyDestroy;

    uint function(void* cbody, float mass) sgPhysicsBodySetMass;
    uint function(void* cbody, float* mass) sgPhysicsBodyGetMass;
    uint function(void* cbody, float moment) sgPhysicsBodySetMoment;
    uint function(void* cbody, float* moment) sgPhysicsBodyGetMoment;
    uint function(void* cbody, float x, float y) sgPhysicsBodySetPosition;
    uint function(void* cbody, float* x, float* y) sgPhysicsBodyGetPosition;
    uint function(void* cbody, float x, float y) sgPhysicsBodySetVelocity;
    uint function(void* cbody, float* x, float* y) sgPhysicsBodyGetVelocity;
    uint function(void* cbody, float x, float y) sgPhysicsBodySetForce;
    uint function(void* cbody, float* x, float* y) sgPhysicsBodyGetForce;
    uint function(void* cbody, float angle) sgPhysicsBodySetAngle;
    uint function(void* cbody, float* angle) sgPhysicsBodyGetAngle;
    uint function(void* cbody, float angvel) sgPhysicsBodySetAngularVelocity;
    uint function(void* cbody, float* angvel) sgPhysicsBodyGetAngularVelocity;
    uint function(void* cbody, float torque) sgPhysicsBodySetTorque;
    uint function(void* cbody, float* torque) sgPhysicsBodyGetTorque;
    uint function(void* cbody, void* data) sgPhysicsBodySetData;
    uint function(void* cbody, void** data) sgPhysicsBodyGetData;

    // constraint

    uint function(void** shape, void* cbody, float xoffset, float yoffset, uint type, uint numverts, float* vertices) sgPhysicsShapeCreate;
    uint function(void* shape) sgPhysicsShapeDestroy;

    uint function(void** space) sgPhysicsSpaceCreate;
    uint function(void* space) sgPhysicsSpaceDestroy;
    uint function(void* space, float time) sgPhysicsSpaceStep;
    uint function(void* space, float x, float y) sgPhysicsSpaceSetGravity;

    uint function(void* space, void* shape) sgPhysicsSpaceAddShape;
    uint function(void* space, void* shape) sgPhysicsSpaceRemoveShape;
    //uint function(void* space, void* shape) sgPhysicsSpaceAddStaticShape;
    //uint function(void* space, void* shape) sgPhysicsSpaceRemoveStaticShape;
    uint function(void* space, void* cbody) sgPhysicsSpaceAddBody;
    uint function(void* space, void* cbody) sgPhysicsSpaceRemoveBody;
    uint function(void* space, void* constraint) sgPhysicsSpaceAddConstraint;
    uint function(void* space, void* constraint) sgPhysicsSpaceRemoveConstraint;


    uint function(void* cbody, float* x, float* y) sgPhysicsBodyWorldToLocal_TEST;
    uint function(void* cbody, float* x, float* y) sgPhysicsBodyLocalToWorld_TEST;
    uint function(void* shape, float* t, float* l, float* b, float* r) sgPhysicsShapeGetBB_TEST;
    uint function(void* shape, uint* pnum, float** points) sgPhysicsShapeGetPoints_TEST;
    uint function(float* points) sgPhysicsShapeFreePoints_TEST;
}
