/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#define SG_BUILD_LIBRARY
#include <siege/core/entity.h>
#include <siege/audio/source.h>
#include <siege/graphics/sprite.h>
#include <siege/graphics/mask.h>
#include <siege/physics/body.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

SGbool SG_EXPORT _sgEntityInit(void)
{
	_sg_cList = sgPListCreate(SG_PLIST_HFO);
	if(_sg_cList != NULL)
		return SG_TRUE;
	return SG_FALSE;
}
SGbool SG_EXPORT _sgEntityDeinit(void)
{
	while(_sg_cList->first)
		sgEntityDestroy(_sg_cList->first->item);
	sgListDestroy(_sg_cList);
	return SG_TRUE;
}

SGbool SG_EXPORT _sg_evCall(SGEntity* entity, va_list args)
{
	if(!entity->active)
		return SG_TRUE;

    SGuint num = va_arg(args, SGuint);
    SGenum type;

    size_t siz[2];
    SGuint val[2];
    void* ptr[2];

	SGuint i;
	for(i = 0; i < num; i++)
	{
        type = va_arg(args, SGenum);
		if(entity->type & (type & SG_EVT_ALL))
			switch(type)
			{
				case SG_EVF_INIT:
					if(entity->evInit != NULL)
						entity->evInit(entity);
					break;
				case SG_EVF_DEINIT:
					if(entity->evDeinit != NULL)
						entity->evDeinit(entity);
					break;

				case SG_EVF_START:
					if(entity->evStart != NULL)
						entity->evStart(entity);
					break;
				case SG_EVF_EXIT:
					if(entity->evExit != NULL)
						entity->evExit(entity);
					break;
				case SG_EVF_TICK:
					if(entity->evTick != NULL)
						entity->evTick(entity);
					break;
				case SG_EVF_TICKB:
					if(entity->evTickBegin != NULL)
						entity->evTickBegin(entity);
					break;
				case SG_EVF_TICKE:
					if(entity->evTickEnd != NULL)
						entity->evTickEnd(entity);
					break;
				case SG_EVF_DRAW:
					if(entity->evDraw != NULL)
						entity->evDraw(entity);
					break;

				case SG_EVF_WINOPEN:
					if(entity->evWindowOpen != NULL)
						entity->evWindowOpen(entity);
					break;
				case SG_EVF_WINCLOSE:
					if(entity->evWindowClose != NULL)
						entity->evWindowClose(entity);
					break;
				case SG_EVF_WINRESIZE:
                    val[0] = va_arg(args, SGuint);
                    val[1] = va_arg(args, SGuint);
					if(entity->evWindowResize != NULL)
						entity->evWindowResize(entity, val[0], val[1]);
					break;

				case SG_EVF_MOUSEBUTH:
                    val[0] = va_arg(args, SGuint);
					if(entity->evMouseButton != NULL)
						entity->evMouseButton(entity, val[0]);
					break;
				case SG_EVF_MOUSEBUTP:
                    val[0] = va_arg(args, SGuint);
					if(entity->evMouseButtonPress != NULL)
						entity->evMouseButtonPress(entity, val[0]);
					break;
				case SG_EVF_MOUSEBUTR:
                    val[0] = va_arg(args, SGuint);
					if(entity->evMouseButtonRelease != NULL)
						entity->evMouseButtonRelease(entity, val[0]);
					break;

				case SG_EVF_MOUSEBUTLH:
					if(entity->evMouseButtonLeft != NULL)
						entity->evMouseButtonLeft(entity);
					break;
				case SG_EVF_MOUSEBUTLP:
					if(entity->evMouseButtonLeftPress != NULL)
						entity->evMouseButtonLeftPress(entity);
					break;
				case SG_EVF_MOUSEBUTLR:
					if(entity->evMouseButtonLeftRelease != NULL)
						entity->evMouseButtonLeftRelease(entity);
					break;

				case SG_EVF_MOUSEBUTRH:
					if(entity->evMouseButtonRight != NULL)
						entity->evMouseButtonRight(entity);
					break;
				case SG_EVF_MOUSEBUTRP:
					if(entity->evMouseButtonRightPress != NULL)
						entity->evMouseButtonRightPress(entity);
					break;
				case SG_EVF_MOUSEBUTRR:
					if(entity->evMouseButtonRightRelease != NULL)
						entity->evMouseButtonRightRelease(entity);
					break;

				case SG_EVF_MOUSEBUTMH:
					if(entity->evMouseButtonMiddle != NULL)
						entity->evMouseButtonMiddle(entity);
					break;
				case SG_EVF_MOUSEBUTMP:
					if(entity->evMouseButtonMiddlePress != NULL)
						entity->evMouseButtonMiddlePress(entity);
					break;
				case SG_EVF_MOUSEBUTMR:
					if(entity->evMouseButtonMiddleRelease != NULL)
						entity->evMouseButtonMiddleRelease(entity);
					break;

				case SG_EVF_MOUSEMOVE:
                    val[0] = va_arg(args, SGuint);
                    val[1] = va_arg(args, SGuint);
					if(entity->evMouseMove != NULL)
						entity->evMouseMove(entity, val[0], val[1]);
					break;
				case SG_EVF_MOUSEWHEEL:
                    val[0] = va_arg(args, SGuint);
					if(entity->evMouseWheel != NULL)
						entity->evMouseWheel(entity, val[0]);
					break;

				case SG_EVF_KEYKEYH:
                    val[0] = va_arg(args, SGuint);
					if(entity->evKeyboardKey != NULL)
						entity->evKeyboardKey(entity, val[0]);
					break;
				case SG_EVF_KEYKEYP:
                    val[0] = va_arg(args, SGuint);
					if(entity->evKeyboardKeyPress != NULL)
						entity->evKeyboardKeyPress(entity, val[0]);
					break;
				case SG_EVF_KEYKEYR:
				    val[0] = va_arg(args, SGuint);
					if(entity->evKeyboardKeyRelease != NULL)
						entity->evKeyboardKeyRelease(entity, val[0]);
					break;
				case SG_EVF_KEYKEYA:
				    val[0] = va_arg(args, SGuint);
					if(entity->evKeyboardKeyRepeat != NULL)
						entity->evKeyboardKeyRepeat(entity, val[0]);
					break;

				/*case SG_EVF_KEYCHARH:
				    val[0] = va_arg(args, SGuint);
					if(entity->evKeyboardChar != NULL)
						entity->evKeyboardChar(entity, val[0]);
					break;*/
				case SG_EVF_KEYCHARP:
					if(entity->evKeyboardCharPress != NULL)
						entity->evKeyboardCharPress(entity, val[0]);
					break;
				/*case SG_EVF_KEYCHARR:
				    val[0] = va_arg(args, SGuint);
					if(entity->evKeyboardCharRelease != NULL)
						entity->evKeyboardCharRelease(entity, val[0]);
					break;*/
				case SG_EVF_KEYCHARA:
				    val[0] = va_arg(args, SGuint);
					if(entity->evKeyboardCharRepeat != NULL)
						entity->evKeyboardCharRepeat(entity, val[0]);
					break;

				case SG_EVF_JOYSTICKBUTH:
				    val[0] = va_arg(args, SGuint);
                    val[1] = va_arg(args, SGuint);
					if(entity->evJoystickButton != NULL)
						entity->evJoystickButton(entity, val[0], val[1]);
					break;
				case SG_EVF_JOYSTICKBUTP:
				    val[0] = va_arg(args, SGuint);
                    val[1] = va_arg(args, SGuint);
					if(entity->evJoystickButtonPress != NULL)
						entity->evJoystickButtonPress(entity, val[0], val[1]);
					break;
				case SG_EVF_JOYSTICKBUTR:
				    val[0] = va_arg(args, SGuint);
                    val[1] = va_arg(args, SGuint);
					if(entity->evJoystickButtonRelease != NULL)
						entity->evJoystickButtonRelease(entity, val[0], val[1]);
					break;
				case SG_EVF_JOYSTICKMOVE:
                    val[0] = va_arg(args, SGuint);
                    ptr[0] = va_arg(args, float*);
                    siz[0] = va_arg(args, size_t);
					if(entity->evJoystickMove != NULL)
						entity->evJoystickMove(entity, val[0], ptr[0], siz[0]);
					break;

				// networking goes here (SG_EVF_NET)

				case SG_EVF_PHYSCOLH:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollision != NULL)
						entity->evCollision(entity, ptr[0], ptr[1]);
					break;
				case SG_EVF_PHYSCOL1:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollisionOne != NULL)
						entity->evCollisionOne(entity, ptr[0], ptr[1]);
					break;
				case SG_EVF_PHYSCOL2:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollisionTwo != NULL)
						entity->evCollisionTwo(entity, ptr[0], ptr[1]);
					break;

				case SG_EVF_PHYSCOLBH:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollisionBegin != NULL)
						entity->evCollisionBegin(entity, ptr[0], ptr[1]);
					break;
				case SG_EVF_PHYSCOLB1:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollisionOneBegin != NULL)
						entity->evCollisionOneBegin(entity, ptr[0], ptr[1]);
					break;
				case SG_EVF_PHYSCOLB2:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollisionTwoBegin != NULL)
						entity->evCollisionTwoBegin(entity, ptr[0], ptr[1]);
					break;

				case SG_EVF_PHYSCOLEH:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollisionEnd != NULL)
						entity->evCollisionEnd(entity, ptr[0], ptr[1]);
					break;
				case SG_EVF_PHYSCOLE1:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollisionOneEnd != NULL)
						entity->evCollisionOneEnd(entity, ptr[0], ptr[1]);
					break;
				case SG_EVF_PHYSCOLE2:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionPoint*);
					if(entity->evCollisionTwoEnd != NULL)
						entity->evCollisionTwoEnd(entity, ptr[0], ptr[1]);
					break;

				case SG_EVF_PHYSCOLRH:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionResult*);
					if(entity->evCollisionResult != NULL)
						entity->evCollisionResult(entity, ptr[0], ptr[1]);
					break;
				case SG_EVF_PHYSCOLR1:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionResult*);
					if(entity->evCollisionOneResult != NULL)
						entity->evCollisionOneResult(entity, ptr[0], ptr[1]);
					break;
				case SG_EVF_PHYSCOLR2:
                    ptr[0] = va_arg(args, SGEntity*);
                    ptr[1] = va_arg(args, SGCollisionResult*);
					if(entity->evCollisionTwoResult != NULL)
						entity->evCollisionTwoResult(entity, ptr[0], ptr[1]);
					break;

				case SG_EVF_LVLSTART:
					if(entity->evLevelStart != NULL)
						entity->evLevelStart(entity);
					break;

				case SG_EVF_LVLEND:
					if(entity->evLevelEnd != NULL)
						entity->evLevelEnd(entity);
			}
	}
	return SG_TRUE;
}

SGvoid SG_EXPORT _sg_evDraw(SGEntity* entity)
{
	if(entity->visible)
		sgEntityDraw(entity);
}

SGEntity* SG_EXPORT sgEntityCreate(float priority, SGenum type)
{
	SGEntity* entity = malloc(sizeof(SGEntity));
	memset(entity, 0, sizeof(SGEntity));
	entity->type = type;
	entity->active = SG_TRUE;
	entity->pausable = SG_TRUE;
	entity->event = sgEventCreate(priority, SG_EV_INTERNAL, entity, (SGEventCall*)_sg_evCall);

	entity->visible = SG_TRUE;
	entity->x = 0.0;
	entity->y = 0.0;
	entity->depth = 0.0;
	entity->angle = 0.0;

	entity->minside = SG_FALSE;

	entity->evDraw = _sg_evDraw;

	sgPListInsertPriority(_sg_cList, priority, entity);
	return entity;
}
void SG_EXPORT sgEntityDestroy(SGEntity* entity)
{
	if(entity == NULL)
		return;

	if(entity->lcDestroy != NULL)
		entity->lcDestroy(entity);

	sgListRemoveItem(_sg_cList, entity);
	sgEventDestroy(entity->event);

	free(entity);
}

void SG_EXPORT sgEntitySetSprite(SGEntity* entity, SGSprite* sprite)
{
	if(entity == NULL)
		return;

	entity->sprite = sprite;
}
SGSprite* SG_EXPORT sgEntityGetSprite(SGEntity* entity)
{
	if(entity == NULL)
		return NULL;

	return entity->sprite;
}

void SG_EXPORT sgEntitySetMask(SGEntity* entity, SGMask* mask)
{
	if(entity == NULL)
		return;

	entity->mask = mask;
}
SGMask* SG_EXPORT sgEntityGetMask(SGEntity* entity)
{
	if(entity == NULL)
		return NULL;

	return entity->mask;
}

void SG_EXPORT sgEntitySetPhysicsBody(SGEntity* entity, SGPhysicsBody* body)
{
	if(entity == NULL)
		return;

	entity->body = body;
}
SGPhysicsBody* SG_EXPORT sgEntityGetPhysicsBody(SGEntity* entity)
{
	if(entity == NULL)
		return NULL;

	return entity->body;
}

void SG_EXPORT sgEntitySetAudioSource(SGEntity* entity, SGAudioSource* source)
{
	if(entity == NULL)
		return;

	entity->source = source;
}
SGAudioSource* SG_EXPORT sgEntityGetAudioSource(SGEntity* entity)
{
	if(entity == NULL)
		return NULL;

	return entity->source;
}

void SG_EXPORT sgEntitySetPos(SGEntity* entity, float x, float y)
{
	if(entity == NULL)
		return;

	entity->x = x;
	entity->y = y;
	if(entity->body != NULL)
		sgPhysicsBodySetPos(entity->body, x, y);
}
void SG_EXPORT sgEntityGetPos(SGEntity* entity, float* x, float* y)
{
	if(entity == NULL)
		return;

	if(x != NULL)
		*x = entity->x;
	if(y != NULL)
		*y = entity->y;
	if(entity->body != NULL)
		sgPhysicsBodyGetPos(entity->body, x, y);
}

void SG_EXPORT sgEntitySetPosX(SGEntity* entity, float x)
{
	if(entity == NULL)
		return;

	entity->x = x;
	if(entity->body != NULL)
		sgPhysicsBodySetPosX(entity->body, x);
}
float SG_EXPORT sgEntityGetPosX(SGEntity* entity)
{
	if(entity == NULL)
		return SG_NAN;

	if(entity->body != NULL)
		return sgPhysicsBodyGetPosX(entity->body);
	return entity->x;
}
void SG_EXPORT sgEntitySetPosY(SGEntity* entity, float y)
{
	if(entity == NULL)
		return;

	entity->y = y;
	if(entity->body != NULL)
		sgPhysicsBodySetPosY(entity->body, y);
}
float SG_EXPORT sgEntityGetPosY(SGEntity* entity)
{
	if(entity == NULL)
		return SG_NAN;

	if(entity->body != NULL)
		return sgPhysicsBodyGetPosY(entity->body);
	return entity->y;
}

void SG_EXPORT sgEntitySetDepth(SGEntity* entity, float depth)
{
	if(entity == NULL)
		return;

	entity->depth = depth;
}
float SG_EXPORT sgEntityGetDepth(SGEntity* entity)
{
	if(entity == NULL)
		return SG_NAN;

	return entity->depth;
}

void SG_EXPORT sgEntitySetAngleRads(SGEntity* entity, float rads)
{
	if(entity == NULL)
		return;

	entity->angle = rads;
	if(entity->body != NULL)
		sgPhysicsBodySetAngleRads(entity->body, rads);
}
float SG_EXPORT sgEntityGetAngleRads(SGEntity* entity)
{
	if(entity == NULL)
		return SG_NAN;

	if(entity->body != NULL)
		return sgPhysicsBodyGetAngleRads(entity->body);
	return entity->angle;
}
void SG_EXPORT sgEntitySetAngleDegs(SGEntity* entity, float degs)
{
	sgEntitySetAngleRads(entity, degs * SG_PI / 180.0);
}
float SG_EXPORT sgEntityGetAngleDegs(SGEntity* entity)
{
	return sgEntityGetAngleRads(entity) * 180.0 / SG_PI;
}

void SG_EXPORT sgEntityDraw(SGEntity* entity)
{
	if(entity == NULL)
		return;
	if(entity->sprite == NULL)
		return;

	if(entity->body != NULL)
	{
		sgPhysicsBodyGetPos(entity->body, &entity->x, &entity->y);
		entity->angle = sgPhysicsBodyGetAngleRads(entity->body);
	}

	sgSpriteDrawRads3f1f(entity->sprite, entity->x, entity->y, entity->depth, entity->angle);
}

