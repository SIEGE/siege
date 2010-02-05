module siege.physics.space;

private
{
    import siege.modules.modules;
    import siege.modules.physics;

    import siege.physics.constraint;
    import siege.physics.pbody;
    import siege.physics.shape;
    import siege.physics.space;

    import siege.util.vector;
}

class Space
{
    private
    {
        void* shandle;
        Shape[] sshapes;
        Body[] sbodies;
        Constraint[] sconstraints;
    }

    this(Vector gravity = Vector(0, 10))
    {
        if(sgPhysicsSpaceCreate !is null)
            sgPhysicsSpaceCreate(&shandle);
        if(sgPhysicsSpaceSetGravity !is null)
            sgPhysicsSpaceSetGravity(shandle, gravity.x, gravity.y);
    }

    ~this()
    {
        if(sgPhysicsSpaceDestroy !is null)
            sgPhysicsSpaceDestroy(shandle);
    }

    void step(float time)
    {
        if(sgPhysicsSpaceStep !is null)
            sgPhysicsSpaceStep(shandle, time);
    }

    void gravity(Vector g)
    {
        if(sgPhysicsSpaceSetGravity !is null)
            sgPhysicsSpaceSetGravity(shandle, g.x, g.y);
    }
    /*Vector gravity()
    {
        Vector g;
        if(sgPhysicsSpaceGetGravity !is null)
            sgPhysicsSpaceGetGravity(shandle, &g.x, &g.y);
        return g;
    }*/

    Space opCatAssign(Shape shape)
    {
        sshapes ~= shape;
        if(sgPhysicsSpaceAddShape !is null)
            sgPhysicsSpaceAddShape(shandle, shape.handle());
        return this;
    }
    Space opCatAssign(Body pbody)
    {
        sbodies ~= pbody;
        if(sgPhysicsSpaceAddBody !is null)
            sgPhysicsSpaceAddBody(shandle, pbody.handle());
        return this;
    }
    Space opCatAssign(Constraint constraint)
    {
        sconstraints ~= constraint;
        if(sgPhysicsSpaceAddConstraint !is null)
            sgPhysicsSpaceAddConstraint(shandle, constraint.handle());
        return this;
    }

    void* handle()
    {
        return shandle;
    }

    static Space main;
}
