module siege.physics.shape;

private
{
    import siege.modules.physics;

    import siege.graphics.draw;

    import siege.physics.pbody;
    import siege.util.vector;
    import siege.util.vmath;
    import siege.util.color;
}

private float area(Vector[] points ...)
{
    assert(points.length >= 3);

    //Vector pprev;
    Vector pcurr;
    Vector pnext;
    float area = 0;
    foreach(i, point; points)
    {
        //pprev = points[(i == 0) ? $-1 : i-1];
        pcurr = point;
        pnext = points[(i == $-1) ? 0 : i+1];

        area += cross(pcurr, pnext);
    }

    return area / 2;
}

// http://www.physicsforums.com/showpost.php?p=210518&postcount=13
// http://www.physicsforums.com/showpost.php?p=210675&postcount=21
private float moment(float density, Vector center, Vector[] points ...)
{
    float m = 0;
    Vector next;
    foreach(i, curr; points)
    {
        curr = curr - center;
        next = points[(i + 1) % points.length] - center;
        m += density / 12 * abs(cross(curr, next)) * (next.length2 + dot(next, curr) + curr.length2);
    }
    return m;
}

class Shape
{
    private
    {
        void* shandle;
        Body pbody;
        uint type;
    }

    this(Body pbody, uint type)
    {
        this.pbody = pbody;
        pbody.bshapes ~= this;
        this.type = type;
    }

    ~this()
    {
        if(sgmPhysicsShapeDestroy !is null)
            sgmPhysicsShapeDestroy(shandle);
    }

    void* handle()
    {
        return shandle;
    }

    void drawDBG(Color bbox = Color(0.5, 0.5, 0.5, 0.5), Color poly = Color(0.0, 0.5, 0.75, 0.75))
    {
        float t, l, b, r;

        if(sgmPhysicsShapeGetBB_TEST !is null)
            sgmPhysicsShapeGetBB_TEST(shandle, &t, &l, &b, &r);

        draw.color(bbox);
        draw.begin(Primitive.LineLoop);
            draw.vertex(l, t);
            draw.vertex(r, t);
            draw.vertex(r, b);
            draw.vertex(l, b);
        draw.end();
    }
}

class SegmentShape: Shape
{
    this(Body pbody, Vector a, Vector b, float width = 1)
    {
        super(pbody, SG_PHYSICS_SHAPE_SEGMENT);

        Vector diff = (a - b);

        float newmass = pbody.data.density * diff.length * width;
        pbody.mass = pbody.mass + newmass;
        pbody.moment = pbody.moment + pbody.data.rotscale * newmass * (diff.length2 + width*width) / 12; // WARNING: NEEDS TO BE SET PROPERLY

        if(sgmPhysicsShapeCreate !is null)
            sgmPhysicsShapeCreate(&shandle, pbody.handle(), 0, 0, type, 2, [a.x, a.y, b.x, b.y, width].ptr);
    }

    void drawDBG(Color bbox = Color(0.5, 0.5, 0.5, 0.5), Color poly = Color(0.0, 0.5, 0.75, 0.75))
    {
        super.drawDBG(bbox, poly);
        uint pnum;
        float* points;
        if(sgmPhysicsBodyLocalToWorld_TEST is null)
            return;
        if(sgmPhysicsShapeGetPoints_TEST !is null)
            sgmPhysicsShapeGetPoints_TEST(shandle, &pnum, &points);

        sgmPhysicsBodyLocalToWorld_TEST(pbody.handle(), &points[0], &points[1]);
        sgmPhysicsBodyLocalToWorld_TEST(pbody.handle(), &points[2], &points[3]);

        draw.color(poly);
        draw.line.width(points[4]);
        draw.begin(Primitive.LineLoop);
            draw.vertex(points[0], points[1]);
            draw.vertex(points[2], points[3]);
        draw.end();
        draw.line.width(1.0);

        if(sgmPhysicsShapeFreePoints_TEST !is null)
            sgmPhysicsShapeFreePoints_TEST(points);
    }
}

class PolyShape: Shape
{
    this(Body pbody, Vector offset, Vector[] vertices ...)
    {
        super(pbody, SG_PHYSICS_SHAPE_POLYGON);

        Vector center = Vector(0, 0);
        foreach(vert; vertices)
            center = center + vert;
        center = center / vertices.length;

        float a = area(vertices);
        if(a > 0) // WARNING: CLOCKWISE HACK (todo: unhack it)
            vertices = vertices.reverse;
        else
            a = -a;
        float newmass = pbody.data.density * a;
        pbody.mass = pbody.mass + newmass;
        pbody.moment = pbody.moment + pbody.data.rotscale * moment(pbody.data.density, center, vertices);

        float[] fverts = new float[](vertices.length * 2);
        foreach(i, v; vertices)
            fverts[2*i..2*i+2] = [v.x, v.y].dup;

        if(sgmPhysicsShapeCreate !is null)
            sgmPhysicsShapeCreate(&shandle, pbody.handle(), offset.x, offset.y, type, vertices.length, fverts.ptr);
    }

    void drawDBG(Color bbox = Color(0.5, 0.5, 0.5, 0.5), Color poly = Color(0.0, 0.5, 0.75, 0.75))
    {
        super.drawDBG(bbox, poly);
        uint pnum;
        float* points;
        if(sgmPhysicsBodyLocalToWorld_TEST is null)
            return;
        if(sgmPhysicsShapeGetPoints_TEST !is null)
            sgmPhysicsShapeGetPoints_TEST(shandle, &pnum, &points);

        for(uint i = 0; i < pnum; i++)
            sgmPhysicsBodyLocalToWorld_TEST(pbody.handle(), &points[2*i], &points[2*i+1]);

        draw.color(poly);
        draw.begin(Primitive.LineLoop);
            for(uint i = 0; i < pnum; i++)
                draw.vertex(points[2*i], points[2*i+1]);
        draw.end();

        if(sgmPhysicsShapeFreePoints_TEST !is null)
            sgmPhysicsShapeFreePoints_TEST(points);
    }
}

class CircleShape: Shape
{
    this(Body pbody, Vector offset, float radius)
    {
        super(pbody, SG_PHYSICS_SHAPE_CIRCLE);

        float newmass = pbody.data.density * PI * radius * radius;
        pbody.mass = pbody.mass + newmass;
        pbody.moment = pbody.moment + newmass * radius * radius / 2;

        if(sgmPhysicsShapeCreate !is null)
            sgmPhysicsShapeCreate(&shandle, pbody.handle(), offset.x, offset.y, type, 0, &radius);
    }

    void drawDBG(Color bbox = Color(0.5, 0.5, 0.5, 0.5), Color poly = Color(0.0, 0.5, 0.75, 0.75))
    {
        super.drawDBG(bbox, poly);
        uint pnum;
        float* points;
        if(sgmPhysicsBodyLocalToWorld_TEST is null)
            return;
        if(sgmPhysicsShapeGetPoints_TEST !is null)
            sgmPhysicsShapeGetPoints_TEST(shandle, &pnum, &points);

        sgmPhysicsBodyLocalToWorld_TEST(pbody.handle(), &points[0], &points[1]);

        uint sides = 16;
        cfloat c;
        draw.color(poly);
        draw.begin(Primitive.LineLoop);
            for(uint i = 0; i < sides; i++)
            {
                c = expi(i / cast(float)sides * M_2_PI) * points[2];
                draw.vertex(points[2*i] + c.re, points[2*i+1] + c.im);
            }
        draw.end();

        if(sgmPhysicsShapeFreePoints_TEST !is null)
            sgmPhysicsShapeFreePoints_TEST(points);
    }
}
