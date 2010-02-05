module siege.physics.pbody;

private
{
    import siege.core.core;
    import siege.core.entity;
    import siege.modules.physics;
    import siege.modules.modules;

    import siege.physics.constraint;
    import siege.physics.shape;

    import siege.core.event;

    import siege.util.vector;
    import siege.util.vmath;

    // for testing purposes
    import siege.graphics.draw;
    import std.math;

    void cbCollisionBegin(Entity one, Entity two, CollisionPoint point)
    {
        one.evCollisionBegin(two, point);
        two.evCollisionBegin(one, point);
        one.evCollisionOneBegin(two, point);
        two.evCollisionTwoBegin(one, point);
    }
    void cbCollisionEnd(Entity one, Entity two, CollisionPoint point)
    {
        one.evCollisionEnd(two, point);
        two.evCollisionEnd(one, point);
        one.evCollisionOneEnd(two, point);
        two.evCollisionTwoEnd(one, point);
    }
    void cbCollision(Entity one, Entity two, CollisionPoint point)
    {
        one.evCollision(two, point);
        two.evCollision(one, point);
        one.evCollisionOne(two, point);
        two.evCollisionTwo(one, point);
    }
    void cbCollisionResult(Entity one, Entity two, CollisionResult result)
    {
        one.evCollisionResult(two, result);
        two.evCollisionResult(one, result);
        one.evCollisionOneResult(two, result);
        two.evCollisionTwoResult(one, result);
    }
}

struct CollisionPoint
{
    Vector position;
    Vector velocity;
    Vector normal;
    float separation;
    float friction;
    float restitution;
}
struct CollisionResult
{
    Vector position;
    Vector normal;
    Vector impulse;
}

struct BodyShape
{
    bool circle;
    Vector[] vertices;
    float radius; // or width of segment for vertices == 2
}

struct BodyData
{
    Vector position;
    float angle;

    BodyShape[] shapes;
    float density = 1.0;
    float rotscale = 1.0;

    float friction = 0.75; // TODO
    float restitution = 0.25; // TODO

    bool stat;
    bool passive; // TODO!
    bool usePhysics = true;
}

class BodyVelocity
{
    private
    {
        void* bhandle;
    }

    this(void* bhandle)
    {
        this.bhandle = bhandle;
    }

    void linear(Vector l)
    {
        if(sgPhysicsBodySetVelocity !is null)
            sgPhysicsBodySetVelocity(bhandle, l.x, l.y);
    }
    Vector linear()
    {
        Vector l;
        if(sgPhysicsBodyGetVelocity !is null)
            sgPhysicsBodyGetVelocity(bhandle, &l.x, &l.y);
        return l;
    }
    void angular(float a)
    {
        if(sgPhysicsBodySetAngularVelocity !is null)
            sgPhysicsBodySetAngularVelocity(bhandle, a);
    }
    float angular()
    {
        float a;
        if(sgPhysicsBodyGetAngularVelocity !is null)
            sgPhysicsBodyGetAngularVelocity(bhandle, &a);
        return a;
    }
}
/*class BodyDamping
{
    private
    {
        void* bhandle;
    }

    this(void* bhandle)
    {
        this.bhandle = bhandle;
    }

    void linear(float l)
    {
        pbody.setLinearDamping(bhandle, l);
    }
    float linear()
    {
        return pbody.getLinearDamping(bhandle);
    }
    void angular(float a)
    {
        pbody.setAngularDamping(bhandle, a);
    }
    float angular()
    {
        return pbody.getAngularDamping(bhandle);
    }
}*/

class Body: EventClient
{
    package
    {
        void* bhandle;
        Shape[] bshapes;
        Constraint[] bconstraints;
    }

    BodyData data;
    BodyVelocity velocity;
    //BodyDamping damping;

    this(BodyData data)
    {
        this.data = data;

        uint type = SG_PHYSICS_BODY_NORMAL;
        if(data.density == float.infinity)
        {
            if(data.stat)
                type = SG_PHYSICS_BODY_STATIC;
            else
                type = SG_PHYSICS_BODY_SEMISTATIC;
        }

        if(sgPhysicsBodyCreate !is null)
            sgPhysicsBodyCreate(&bhandle, type);
        if(sgPhysicsBodySetPosition !is null)
            sgPhysicsBodySetPosition(bhandle, data.position.x, data.position.y);
        if(sgPhysicsBodySetAngle !is null)
            sgPhysicsBodySetAngle(bhandle, data.angle * 180 / PI);
        if(sgPhysicsBodySetData !is null)
            sgPhysicsBodySetData(bhandle, cast(void*)this);

        velocity = new BodyVelocity(bhandle);
        //damping = new BodyDamping(bhandle);
    }

    ~this()
    {
        if(sgPhysicsBodyDestroy !is null)
            sgPhysicsBodyDestroy(bhandle);
    }

    void position(Vector p)
    {
        if(sgPhysicsBodySetPosition !is null)
            sgPhysicsBodySetPosition(bhandle, p.x, p.y);
    }
    Vector position()
    {
        Vector p;
        if(sgPhysicsBodyGetPosition !is null)
            sgPhysicsBodyGetPosition(bhandle, &p.x, &p.y);
        return p;
    }
    void angle(float a)
    {
        if(sgPhysicsBodySetAngle !is null)
            sgPhysicsBodySetAngle(bhandle, angle * 180 / PI);
    }
    float angle()
    {
        float a;
        if(sgPhysicsBodyGetAngle !is null)
            sgPhysicsBodyGetAngle(bhandle, &a);
        return a * 180 / PI;
    }

    void mass(float m)
    {
        if(sgPhysicsBodySetMass !is null)
            sgPhysicsBodySetMass(bhandle, m);
    }
    float mass()
    {
        float m;
        if(sgPhysicsBodyGetMass !is null)
            sgPhysicsBodyGetMass(bhandle, &m);
        return m;
    }

    void moment(float m)
    {
        if(sgPhysicsBodySetMoment !is null)
            sgPhysicsBodySetMoment(bhandle, m);
    }
    float moment()
    {
        float m;
        if(sgPhysicsBodyGetMoment !is null)
            sgPhysicsBodyGetMoment(bhandle, &m);
        return m;
    }

    void* handle()
    {
        return bhandle;
    }

    void drawDBG()
    {
        foreach(shape; bshapes)
            shape.drawDBG();
    }

    /*Vector[][] worldPolysDBG()
    {
        Vector[][] t;
        t = new Vector[][](data.shapes.length);

        foreach(i, shape; data.shapes)
        {
            if(shape.circle)
                return null;

            t[i] = new Vector[](shape.vertices.length);
            foreach(j, v; shape.vertices)
            {
                t[i][j] = worldPointDBG(v);
            }

        }
        return t;
    }

    Vector worldPointDBG(Vector p)
    {
        float[] wp = pbody.worldPointDBG(bhandle, p.x, p.y);
        return Vector(wp[0], wp[1]);
    }
    Vector worldPointDBG(float[] p)
    {
        float[] wp = pbody.worldPointDBG(bhandle, p[0], p[1]);
        return Vector(wp[0], wp[1]);
    }

    // for debugging purposes
    void drawDBG(bool vel = false)
    {
        Vector pos = position();
        if(vel)
        {
            siege.graphics.draw.draw.begin(Primitive.Lines);
                siege.graphics.draw.draw.vertex(pos);
                siege.graphics.draw.draw.vertex(pos + velocity.linear);
            siege.graphics.draw.draw.end();
            return;
        }

        uint sides = 16;
        cfloat[] circleData;
        uint circle;
        {
            float r = 2 * PI / sides;

            circleData = new cfloat[sides];
            for(circle = 0; circle < sides; circle++)
            {
                circleData[circle] = expi(circle * r);
            }
        }


        Vector wp;
        siege.graphics.draw.draw.begin(Primitive.LineLoop);
        foreach(shape; data.shapes)
        {
            if(shape.circle)
            {
                for(circle = 0; circle < sides; circle++)
                {
                    siege.graphics.draw.draw.vertex(pos.x + circleData[circle].re * shape.radius, pos.y + circleData[circle].im * shape.radius);
                }
            }
            else
            {
                foreach(v; shape.vertices)
                {
                    wp = worldPointDBG(v);
                    siege.graphics.draw.draw.vertex(wp);
                }
                /+foreach(v; shape.vertices)
                {
                    siege.graphics.draw.draw.vertex(pos.x + v[0], pos.y + v[1]);
                }+/
            }
        }
        siege.graphics.draw.draw.end();
    }*/
}
