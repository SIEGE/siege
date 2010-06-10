#include "main.h"
#include "space.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgPhysicsSpaceCreate(void** space)
{
    *space = cpSpaceNew();
    cpSpace** cspace = (cpSpace**)space;
    (*cspace)->iterations = 10; // TEST
    (*cspace)->elasticIterations = 10;
    (*cspace)->damping = 0.75;
    return SG_OK;
}

SGuint SG_EXPORT sgPhysicsSpaceDestroy(void* space)
{
    if(space == NULL)
        return SG_OK; // SG_INVALID_VALUE

    //cpSpaceFreeChildren(space);
    cpSpaceFree(space);
    return SG_OK;
}

SGuint SG_EXPORT sgPhysicsSpaceStep(void* space, float time)
{
    if(space == NULL)
        return SG_OK; // SG_INVALID_VALUE

    cpSpaceStep(space, time);
    return SG_OK;
}

SGuint SG_EXPORT sgPhysicsSpaceSetGravity(void* space, float x, float y)
{
    if(space == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpSpace* cspace = (cpSpace*)space;
    cspace->gravity.x = x;
    cspace->gravity.y = y;
    return SG_OK;
}
//SGuint SG_EXPORT sgPhysicsSpaceGetGravity(void* space, float* x, float* y);

SGuint SG_EXPORT sgPhysicsSpaceAddShape(void* space, void* shape)
{
    if(space == NULL || shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShape* cshape = (cpShape*)shape;
    cpBody* cbody = cshape->body;
    if(((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_STATIC)
        cpSpaceAddShape(space, shape);
    else
        cpSpaceAddStaticShape(space, shape);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsSpaceRemoveShape(void* space, void* shape)
{
    if(space == NULL || shape == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpShape* cshape = (cpShape*)shape;
    cpBody* cbody = cshape->body;
    if(((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_STATIC)
        cpSpaceRemoveShape(space, shape);
    else
        cpSpaceRemoveStaticShape(space, shape);
    return SG_OK;
}
//SGuint SG_EXPORT sgPhysicsSpaceAddStaticShape(void* space, void* shape);
//SGuint SG_EXPORT sgPhysicsSpaceRemoveStaticShape(void* space, void* shape);
SGuint SG_EXPORT sgPhysicsSpaceAddBody(void* space, void* body)
{
    if(space == NULL || body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBody* cbody = (cpBody*)body;
    if((((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_STATIC) && (((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_SEMISTATIC)) // we shouldn't put the body in, if it's static
        cpSpaceAddBody(space, body);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsSpaceRemoveBody(void* space, void* body)
{
    if(space == NULL || body == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpBody* cbody = (cpBody*)body;
    if((((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_STATIC) && (((DataExt*)cbody->data)->type != SG_PHYSICS_BODY_SEMISTATIC)) // we shouldn't put the body in, if it's static
        cpSpaceRemoveBody(space, body);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsSpaceAddConstraint(void* space, void* constraint)
{
    if(space == NULL || constraint == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceAddConstraint(space, constraint);
    return SG_OK;
}
SGuint SG_EXPORT sgPhysicsSpaceRemoveConstraint(void* space, void* constraint)
{
    if(space == NULL || constraint == NULL)
        return SG_OK; // SG_INVALID_VALUE
    cpSpaceRemoveConstraint(space, constraint);
    return SG_OK;
}
