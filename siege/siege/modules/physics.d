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
    checkBindFunc(sgmPhysicsBodyCreate)("sgmPhysicsBodyCreate", lib);
    checkBindFunc(sgmPhysicsBodyDestroy)("sgmPhysicsBodyDestroy", lib);

    checkBindFunc(sgmPhysicsBodySetMass)("sgmPhysicsBodySetMass", lib);
    checkBindFunc(sgmPhysicsBodyGetMass)("sgmPhysicsBodyGetMass", lib);
    checkBindFunc(sgmPhysicsBodySetMoment)("sgmPhysicsBodySetMoment", lib);
    checkBindFunc(sgmPhysicsBodyGetMoment)("sgmPhysicsBodyGetMoment", lib);
    checkBindFunc(sgmPhysicsBodySetPosition)("sgmPhysicsBodySetPosition", lib);
    checkBindFunc(sgmPhysicsBodyGetPosition)("sgmPhysicsBodyGetPosition", lib);
    checkBindFunc(sgmPhysicsBodySetVelocity)("sgmPhysicsBodySetVelocity", lib);
    checkBindFunc(sgmPhysicsBodyGetVelocity)("sgmPhysicsBodyGetVelocity", lib);
    checkBindFunc(sgmPhysicsBodySetForce)("sgmPhysicsBodySetForce", lib);
    checkBindFunc(sgmPhysicsBodyGetForce)("sgmPhysicsBodyGetForce", lib);
    checkBindFunc(sgmPhysicsBodySetAngle)("sgmPhysicsBodySetAngle", lib);
    checkBindFunc(sgmPhysicsBodyGetAngle)("sgmPhysicsBodyGetAngle", lib);
    checkBindFunc(sgmPhysicsBodySetAngularVelocity)("sgmPhysicsBodySetAngularVelocity", lib);
    checkBindFunc(sgmPhysicsBodyGetAngularVelocity)("sgmPhysicsBodyGetAngularVelocity", lib);
    checkBindFunc(sgmPhysicsBodySetTorque)("sgmPhysicsBodySetTorque", lib);
    checkBindFunc(sgmPhysicsBodyGetTorque)("sgmPhysicsBodyGetTorque", lib);
    checkBindFunc(sgmPhysicsBodySetData)("sgmPhysicsBodySetData", lib);
    checkBindFunc(sgmPhysicsBodyGetData)("sgmPhysicsBodyGetData", lib);

    // constraint

    checkBindFunc(sgmPhysicsShapeCreate)("sgmPhysicsShapeCreate", lib);
    checkBindFunc(sgmPhysicsShapeDestroy)("sgmPhysicsShapeDestroy", lib);

    checkBindFunc(sgmPhysicsSpaceCreate)("sgmPhysicsSpaceCreate", lib);
    checkBindFunc(sgmPhysicsSpaceDestroy)("sgmPhysicsSpaceDestroy", lib);
    checkBindFunc(sgmPhysicsSpaceStep)("sgmPhysicsSpaceStep", lib);
    checkBindFunc(sgmPhysicsSpaceSetGravity)("sgmPhysicsSpaceSetGravity", lib);

    checkBindFunc(sgmPhysicsSpaceAddShape)("sgmPhysicsSpaceAddShape", lib);
    checkBindFunc(sgmPhysicsSpaceRemoveShape)("sgmPhysicsSpaceRemoveShape", lib);
    //checkBindFunc(sgmPhysicsSpaceAddStaticShape)("sgmPhysicsSpaceAddStaticShape", lib);
    //checkBindFunc(sgmPhysicsSpaceRemoveStaticShape)("sgmPhysicsSpaceRemoveStaticShape", lib);
    checkBindFunc(sgmPhysicsSpaceAddBody)("sgmPhysicsSpaceAddBody", lib);
    checkBindFunc(sgmPhysicsSpaceRemoveBody)("sgmPhysicsSpaceRemoveBody", lib);
    checkBindFunc(sgmPhysicsSpaceAddConstraint)("sgmPhysicsSpaceAddConstraint", lib);
    checkBindFunc(sgmPhysicsSpaceRemoveConstraint)("sgmPhysicsSpaceRemoveConstraint", lib);

    checkBindFunc(sgmPhysicsBodyWorldToLocal_TEST)("sgmPhysicsBodyWorldToLocal_TEST", lib);
    checkBindFunc(sgmPhysicsBodyLocalToWorld_TEST)("sgmPhysicsBodyLocalToWorld_TEST", lib);
    checkBindFunc(sgmPhysicsShapeGetBB_TEST)("sgmPhysicsShapeGetBB_TEST", lib);
    checkBindFunc(sgmPhysicsShapeGetPoints_TEST)("sgmPhysicsShapeGetPoints_TEST", lib);
    checkBindFunc(sgmPhysicsShapeFreePoints_TEST)("sgmPhysicsShapeFreePoints_TEST", lib);
}

extern(C)
{
    /// Physics
    uint function(void** cbody, uint type) sgmPhysicsBodyCreate;
    uint function(void* cbody) sgmPhysicsBodyDestroy;

    uint function(void* cbody, float mass) sgmPhysicsBodySetMass;
    uint function(void* cbody, float* mass) sgmPhysicsBodyGetMass;
    uint function(void* cbody, float moment) sgmPhysicsBodySetMoment;
    uint function(void* cbody, float* moment) sgmPhysicsBodyGetMoment;
    uint function(void* cbody, float x, float y) sgmPhysicsBodySetPosition;
    uint function(void* cbody, float* x, float* y) sgmPhysicsBodyGetPosition;
    uint function(void* cbody, float x, float y) sgmPhysicsBodySetVelocity;
    uint function(void* cbody, float* x, float* y) sgmPhysicsBodyGetVelocity;
    uint function(void* cbody, float x, float y) sgmPhysicsBodySetForce;
    uint function(void* cbody, float* x, float* y) sgmPhysicsBodyGetForce;
    uint function(void* cbody, float angle) sgmPhysicsBodySetAngle;
    uint function(void* cbody, float* angle) sgmPhysicsBodyGetAngle;
    uint function(void* cbody, float angvel) sgmPhysicsBodySetAngularVelocity;
    uint function(void* cbody, float* angvel) sgmPhysicsBodyGetAngularVelocity;
    uint function(void* cbody, float torque) sgmPhysicsBodySetTorque;
    uint function(void* cbody, float* torque) sgmPhysicsBodyGetTorque;
    uint function(void* cbody, void* data) sgmPhysicsBodySetData;
    uint function(void* cbody, void** data) sgmPhysicsBodyGetData;

    // constraint

    uint function(void** shape, void* cbody, float xoffset, float yoffset, uint type, uint numverts, float* vertices) sgmPhysicsShapeCreate;
    uint function(void* shape) sgmPhysicsShapeDestroy;

    uint function(void** space) sgmPhysicsSpaceCreate;
    uint function(void* space) sgmPhysicsSpaceDestroy;
    uint function(void* space, float time) sgmPhysicsSpaceStep;
    uint function(void* space, float x, float y) sgmPhysicsSpaceSetGravity;

    uint function(void* space, void* shape) sgmPhysicsSpaceAddShape;
    uint function(void* space, void* shape) sgmPhysicsSpaceRemoveShape;
    //uint function(void* space, void* shape) sgmPhysicsSpaceAddStaticShape;
    //uint function(void* space, void* shape) sgmPhysicsSpaceRemoveStaticShape;
    uint function(void* space, void* cbody) sgmPhysicsSpaceAddBody;
    uint function(void* space, void* cbody) sgmPhysicsSpaceRemoveBody;
    uint function(void* space, void* constraint) sgmPhysicsSpaceAddConstraint;
    uint function(void* space, void* constraint) sgmPhysicsSpaceRemoveConstraint;


    uint function(void* cbody, float* x, float* y) sgmPhysicsBodyWorldToLocal_TEST;
    uint function(void* cbody, float* x, float* y) sgmPhysicsBodyLocalToWorld_TEST;
    uint function(void* shape, float* t, float* l, float* b, float* r) sgmPhysicsShapeGetBB_TEST;
    uint function(void* shape, uint* pnum, float** points) sgmPhysicsShapeGetPoints_TEST;
    uint function(float* points) sgmPhysicsShapeFreePoints_TEST;
}
