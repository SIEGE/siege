/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#define SG_BUILD_LIBRARY
#include <siege/physics/space.h>
#include <siege/physics/body.h>
#include <siege/modules/physics.h>

#include <stdlib.h>

SGbool SG_CALL _sgPhysicsSpaceInit(void)
{
    _sg_physSpaceMain = sgPhysicsSpaceCreate();
    sgPhysicsSpaceSetGravity(_sg_physSpaceMain, 0, 10);
    return SG_TRUE;
}
SGbool SG_CALL _sgPhysicsSpaceDeinit(void)
{
    sgPhysicsSpaceDestroy(_sg_physSpaceMain);
    return SG_TRUE;
}

SGPhysicsSpace* SG_CALL sgPhysicsSpaceCreate(void)
{
    SGPhysicsSpace* space = malloc(sizeof(SGPhysicsSpace));
    if(!space)
		return NULL;
	space->handle = NULL;

    if(psgmPhysicsSpaceCreate != NULL)
        psgmPhysicsSpaceCreate(&space->handle);

	space->sbody = malloc(sizeof(SGPhysicsBody));
	space->sbody->handle = NULL;
	space->sbody->space = space;
	space->sbody->data = NULL;
	space->sbody->type = SG_BODY_STATIC;
	space->sbody->entity = NULL;
	if(psgmPhysicsSpaceGetStaticBody)
		psgmPhysicsSpaceGetStaticBody(space->handle, &space->sbody->handle);
	if(psgmPhysicsBodySetData)
		psgmPhysicsBodySetData(space->sbody->handle, space->sbody);

    sgPhysicsSpaceSetGravity(space, 0.0, 0.0);

    return space;
}
void SG_CALL sgPhysicsSpaceDestroy(SGPhysicsSpace* space)
{
    if(!space)
        return;

	free(space->sbody);

    if(psgmPhysicsSpaceDestroy != NULL)
        psgmPhysicsSpaceDestroy(space->handle);

    free(space);
}

void SG_CALL sgPhysicsSpaceStep(SGPhysicsSpace* space, float time)
{
    if(psgmPhysicsSpaceStep != NULL)
        psgmPhysicsSpaceStep(space->handle, time);
}

void SG_CALL sgPhysicsSpaceSetIterations(SGPhysicsSpace* space, SGuint iterations)
{
	if(psgmPhysicsSpaceSetIterations)
		psgmPhysicsSpaceSetIterations(space->handle, iterations);
}
void SG_CALL sgPhysicsSpaceSetGravity(SGPhysicsSpace* space, float x, float y)
{
    if(psgmPhysicsSpaceSetGravity != NULL)
        psgmPhysicsSpaceSetGravity(space->handle, x, y);
}
//void SG_CALL sgPhysicsSpaceGetGravity(SGPhysicsSpace* space, float* x, float* y);
void SG_CALL sgPhysicsSpaceSetDamping(SGPhysicsSpace* space, float damping)
{
	if(psgmPhysicsSpaceSetDamping)
		psgmPhysicsSpaceSetDamping(space->handle, damping);
}
//float SG_CALL sgPhysicsSpaceGetDamping(SGPhysicsSpace* space);

void SG_CALL sgPhysicsSpaceSetData(SGPhysicsSpace* space, void* data)
{
	space->data = data;
}
void* SG_CALL sgPhysicsSpaceGetData(SGPhysicsSpace* space)
{
	return space->data;
}

SGPhysicsBody* SG_CALL sgPhysicsSpaceGetStaticBody(SGPhysicsSpace* space)
{
	return space->sbody;
}
SGPhysicsSpace* SG_CALL sgPhysicsSpaceGetDefault(void)
{
	return _sg_physSpaceMain;
}
