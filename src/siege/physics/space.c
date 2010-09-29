#define SG_BUILD_LIBRARY
#include <siege/physics/space.h>
#include <siege/modules/physics.h>

#include <stdlib.h>

SGbool SG_EXPORT _sgPhysicsSpaceInit(void)
{
    _sg_physSpaceMain = sgPhysicsSpaceCreate();
    sgPhysicsSpaceSetGravity(_sg_physSpaceMain, 0, 10);
    return SG_TRUE;
}
SGbool SG_EXPORT _sgPhysicsSpaceDeinit(void)
{
    sgPhysicsSpaceDestroy(_sg_physSpaceMain);
    return SG_TRUE;
}

SGPhysicsSpace* SG_EXPORT sgPhysicsSpaceCreate(void)
{
    SGPhysicsSpace* space = malloc(sizeof(SGPhysicsSpace));
    if(_sg_modPhysics.sgmPhysicsSpaceCreate != NULL)
        _sg_modPhysics.sgmPhysicsSpaceCreate(&space->handle);

    sgPhysicsSpaceSetGravity(space, 0.0, 0.0);

    return space;
}
void SG_EXPORT sgPhysicsSpaceDestroy(SGPhysicsSpace* space)
{
    if(space == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsSpaceDestroy != NULL)
        _sg_modPhysics.sgmPhysicsSpaceDestroy(space->handle);

    free(space);
}

void SG_EXPORT sgPhysicsSpaceStep(SGPhysicsSpace* space, float time)
{
    if(space == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsSpaceStep != NULL)
        _sg_modPhysics.sgmPhysicsSpaceStep(space->handle, time);
}
void SG_EXPORT sgPhysicsSpaceSetGravity(SGPhysicsSpace* space, float x, float y)
{
    if(space == NULL)
        return;

    if(_sg_modPhysics.sgmPhysicsSpaceSetGravity != NULL)
        _sg_modPhysics.sgmPhysicsSpaceSetGravity(space->handle, x, y);
}
//void SG_EXPORT sgPhysicsSpaceGetGravity(SGPhysicsSpace* space, float* x, float* y);
