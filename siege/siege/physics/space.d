module siege.physics.space;

private
{
    import siege.modules.physics;

    import siege.physics.constraint;
    import siege.physics.pbody;
    import siege.physics.shape;

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
        if(sgmPhysicsSpaceCreate !is null)
            sgmPhysicsSpaceCreate(&shandle);
        if(sgmPhysicsSpaceSetGravity !is null)
            sgmPhysicsSpaceSetGravity(shandle, gravity.x, gravity.y);
    }

    ~this()
    {
        if(sgmPhysicsSpaceDestroy !is null)
            sgmPhysicsSpaceDestroy(shandle);
    }

    void step(float time)
    {
        if(sgmPhysicsSpaceStep !is null)
            sgmPhysicsSpaceStep(shandle, time);
    }

    void gravity(Vector g)
    {
        if(sgmPhysicsSpaceSetGravity !is null)
            sgmPhysicsSpaceSetGravity(shandle, g.x, g.y);
    }
    /*Vector gravity()
    {
        Vector g;
        if(sgmPhysicsSpaceGetGravity !is null)
            sgmPhysicsSpaceGetGravity(shandle, &g.x, &g.y);
        return g;
    }*/

    Space opCatAssign(Shape shape)
    {
        sshapes ~= shape;
        if(sgmPhysicsSpaceAddShape !is null)
            sgmPhysicsSpaceAddShape(shandle, shape.handle());
        return this;
    }
    Space opCatAssign(Body pbody)
    {
        sbodies ~= pbody;
        if(sgmPhysicsSpaceAddBody !is null)
            sgmPhysicsSpaceAddBody(shandle, pbody.handle());
        return this;
    }
    Space opCatAssign(Constraint constraint)
    {
        sconstraints ~= constraint;
        if(sgmPhysicsSpaceAddConstraint !is null)
            sgmPhysicsSpaceAddConstraint(shandle, constraint.handle());
        return this;
    }

    void* handle()
    {
        return shandle;
    }

    static Space main;
}
