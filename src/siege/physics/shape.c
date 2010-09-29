#define SG_BUILD_LIBRARY
#include <siege/physics/shape.h>
#include <siege/modules/physics.h>

#include <siege/util/vector.h>

//
#include <siege/graphics/draw.h>
//

#include <stdlib.h>
#include <string.h>
#include <math.h>

SGPhysicsShape* SG_EXPORT sgPhysicsShapeCreate(SGPhysicsBody* body, SGenum type)
{
    SGPhysicsShape* shape = malloc(sizeof(SGPhysicsShape));
    if(shape == NULL)
        return NULL;

    shape->body = body;
    shape->type = type;

    shape->x = SG_NAN;
    shape->y = SG_NAN;
    shape->numverts = 0;
    shape->verts = NULL;

    return shape;
}
SGPhysicsShape* SG_EXPORT sgPhysicsShapeCreateSegment(SGPhysicsBody* body, float x1, float y1, float x2, float y2, float width)
{
    SGPhysicsShape* shape = sgPhysicsShapeCreate(body, SG_PHYSICS_SHAPE_SEGMENT);
    if(shape == NULL)
        return NULL;

    shape->x = 0;
    shape->y = 0;

    shape->numverts = 2;
    shape->verts = malloc(5 * sizeof(float));
    shape->verts[0] = x1;
    shape->verts[1] = y1;
    shape->verts[2] = x2;
    shape->verts[3] = y2;
    shape->verts[4] = width;

    if(_sg_modPhysics.sgmPhysicsShapeCreate != NULL)
        _sg_modPhysics.sgmPhysicsShapeCreate(&shape->handle, body->handle, 0, 0, shape->type, shape->numverts, shape->verts);
    if(_sg_modPhysics.sgmPhysicsSpaceAddShape != NULL)
        _sg_modPhysics.sgmPhysicsSpaceAddShape(body->space->handle, shape->handle);

    return shape;
}
SGPhysicsShape* SG_EXPORT sgPhysicsShapeCreatePoly(SGPhysicsBody* body, float x, float y, float* verts, size_t numverts)
{
    SGPhysicsShape* shape = sgPhysicsShapeCreate(body, SG_PHYSICS_SHAPE_POLYGON);
    if(shape == NULL)
        return NULL;

    shape->x = x;
    shape->y = y;

    shape->numverts = numverts;
    shape->verts = malloc(2 * numverts * sizeof(float));
    memcpy(shape->verts, verts, 2 * numverts * sizeof(float));

    if(_sg_modPhysics.sgmPhysicsShapeCreate != NULL)
        _sg_modPhysics.sgmPhysicsShapeCreate(&shape->handle, body->handle, x, y, shape->type, shape->numverts, shape->verts);
    if(_sg_modPhysics.sgmPhysicsSpaceAddShape != NULL)
        _sg_modPhysics.sgmPhysicsSpaceAddShape(body->space->handle, shape->handle);

    return shape;
}
SGPhysicsShape* SG_EXPORT sgPhysicsShapeCreateCircle(SGPhysicsBody* body, float x, float y, float r1, float r2)
{
    SGPhysicsShape* shape = sgPhysicsShapeCreate(body, SG_PHYSICS_SHAPE_CIRCLE);
    if(shape == NULL)
        return NULL;

    if(r2 < r1)
    {
        float tmp = r1;
        r1 = r2;
        r2 = tmp;
    }

    shape->x = x;
    shape->y = y;

    shape->numverts = 1;
    shape->verts = malloc(2 * sizeof(float));
    shape->verts[0] = r1;
    shape->verts[1] = r2;

    if(_sg_modPhysics.sgmPhysicsShapeCreate != NULL)
        _sg_modPhysics.sgmPhysicsShapeCreate(&shape->handle, body->handle, x, y, shape->type, shape->numverts, &shape->verts[1]);
    if(_sg_modPhysics.sgmPhysicsSpaceAddShape != NULL)
        _sg_modPhysics.sgmPhysicsSpaceAddShape(body->space->handle, shape->handle);

    return shape;
}
void SG_EXPORT sgPhysicsShapeDestroy(SGPhysicsShape* shape)
{
    if(shape == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsSpaceRemoveShape != NULL)
        _sg_modPhysics.sgmPhysicsSpaceRemoveShape(shape->body->space->handle, shape->handle);
    if(_sg_modPhysics.sgmPhysicsShapeDestroy != NULL)
        _sg_modPhysics.sgmPhysicsShapeDestroy(shape->handle);

    free(shape->verts);

    free(shape);
}

float SG_EXPORT sgPhysicsShapeGetAreaS(SGPhysicsShape* shape)
{
    if(shape == NULL)
        return SG_NAN;

    SGVec2 curr;
    SGVec2 next;
    float area;
    size_t i;

    switch(shape->type)
    {
        case SG_PHYSICS_SHAPE_SEGMENT:
            return hypot(shape->verts[0] - shape->verts[2], shape->verts[1] - shape->verts[3]) * shape->verts[4];

        case SG_PHYSICS_SHAPE_POLYGON:
            area = 0;
            for(i = 0; i < shape->numverts; i++)
            {
                curr.x = shape->verts[2*i];
                curr.y = shape->verts[2*i+1];
                next.x = shape->verts[2*((i+1) % shape->numverts)];
                next.y = shape->verts[2*((i+1) % shape->numverts)+1];

                area += sgVec2Cross(curr, next);
            }
            return area / 2.0;

        case SG_PHYSICS_SHAPE_CIRCLE:
            return M_PI * (shape->verts[1] * shape->verts[1] - shape->verts[0] * shape->verts[0]);
    }
    return SG_NAN;
}
float SG_EXPORT sgPhysicsShapeGetAreaU(SGPhysicsShape* shape)
{
    return fabs(sgPhysicsShapeGetAreaS(shape));
}
float SG_EXPORT sgPhysicsShapeGetMass(SGPhysicsShape* shape, float density)
{
    return sgPhysicsShapeGetAreaU(shape) * density;
}
float SG_EXPORT sgPhysicsShapeGetMomentMass(SGPhysicsShape* shape, float mass)
{
    if(shape == NULL)
        return SG_NAN;

    SGVec2 curr;
    SGVec2 next;
    float nom;
    float den;
    size_t i;

    switch(shape->type)
    {
        case SG_PHYSICS_SHAPE_SEGMENT:
            return mass * (((shape->verts[0] - shape->verts[2]) * (shape->verts[0] - shape->verts[2]) -
                            (shape->verts[1] - shape->verts[3]) * (shape->verts[1] - shape->verts[3])) / 12.0 +
                           ((shape->verts[0] - shape->verts[2]) * (shape->verts[0] - shape->verts[2]) +
                            (shape->verts[1] - shape->verts[3]) * (shape->verts[1] - shape->verts[3])) / 2.0);

        case SG_PHYSICS_SHAPE_POLYGON:
            nom = 0;
            den = 0;
            for(i = 0; i < shape->numverts; i++)
            {
                curr.x = shape->verts[2*i] - shape->x;
                curr.y = shape->verts[2*i+1] - shape->y;
                next.x = shape->verts[2*((i+1) % shape->numverts)] - shape->x;
                next.y = shape->verts[2*((i+1) % shape->numverts)+1] - shape->y;

                nom += fabs(sgVec2Cross(curr, next)) * (sgVec2GetLength2(next) + sgVec2Dot(next, curr) + sgVec2GetLength2(curr));
                den += fabs(sgVec2Cross(curr, next));
            }
            return nom / den * mass / 6.0;

        case SG_PHYSICS_SHAPE_CIRCLE:
            return mass * (shape->verts[0] * shape->verts[0] + shape->verts[1] * shape->verts[1]) / 2.0;
    }
    return SG_NAN;
}
float SG_EXPORT sgPhysicsShapeGetMomentDensity(SGPhysicsShape* shape, float density)
{
    if(shape == NULL)
        return SG_NAN;

    SGVec2 curr;
    SGVec2 next;
    float moment;
    size_t i;

    switch(shape->type)
    {
        case SG_PHYSICS_SHAPE_SEGMENT:
            return sgPhysicsShapeGetMomentMass(shape, sgPhysicsShapeGetMass(shape, density));

        case SG_PHYSICS_SHAPE_POLYGON:
            moment = 0;
            for(i = 0; i < shape->numverts; i++)
            {
                curr.x = shape->verts[2*i] - shape->x;
                curr.y = shape->verts[2*i+1] - shape->y;
                next.x = shape->verts[2*((i+1) % shape->numverts)] - shape->x;
                next.y = shape->verts[2*((i+1) % shape->numverts)+1] - shape->y;

                moment += density / 12.0 * fabs(sgVec2Cross(curr, next)) * (sgVec2GetLength2(next) + sgVec2Dot(next, curr) + sgVec2GetLength2(curr));
            }
            return moment;

        case SG_PHYSICS_SHAPE_CIRCLE:
            return sgPhysicsShapeGetMomentMass(shape, sgPhysicsShapeGetMass(shape, density));
    }
    return SG_NAN;
}

void SG_EXPORT sgPhysicsShapeDrawDBG(SGPhysicsShape* shape)
{
    if(shape == NULL)
        return;

    // draw BB
    float t, l, b, r;
    if(_sg_modPhysics.sgmPhysicsShapeGetBB_TEST != NULL)
        _sg_modPhysics.sgmPhysicsShapeGetBB_TEST(shape->handle, &t, &l, &b, &r);

    sgDrawColor4f(0.5, 0.5, 0.5, 0.5);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);
        sgDrawVertex2f(l, t);
        sgDrawVertex2f(r, t);
        sgDrawVertex2f(r, b);
        sgDrawVertex2f(l, b);
    sgDrawEnd();

    // draw shape
    SGuint pnum;
    float* points;
    if(_sg_modPhysics.sgmPhysicsBodyLocalToWorld_TEST == NULL)
        return;
    if(_sg_modPhysics.sgmPhysicsShapeGetPoints_TEST != NULL)
        _sg_modPhysics.sgmPhysicsShapeGetPoints_TEST(shape->handle, &pnum, &points);

    SGuint i;
    for(i = 0; i < pnum; i++)
        _sg_modPhysics.sgmPhysicsBodyLocalToWorld_TEST(shape->body->handle, &points[2*i], &points[2*i+1]);

    sgDrawColor4f(0.0, 0.5, 0.75, 0.75);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);
        for(i = 0; i < pnum; i++)
            sgDrawVertex2f(points[2*i], points[2*i+1]);
    sgDrawEnd();
    sgDrawColor4f(1.0, 1.0, 1.0, 1.0);

    if(_sg_modPhysics.sgmPhysicsShapeFreePoints_TEST != NULL)
        _sg_modPhysics.sgmPhysicsShapeFreePoints_TEST(points);
}
