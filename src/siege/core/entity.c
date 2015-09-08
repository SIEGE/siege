/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
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

SGbool SG_CALL _sgEntityInit(void)
{
    _sg_entList = sgListCreate();
    if(!_sg_entList)
        return SG_FALSE;
    _sg_entSMap = sgSMapCreate();
    return SG_TRUE;
}
SGbool SG_CALL _sgEntityDeinit(void)
{
    sgEntityDestroyAll();
    sgListDestroy(_sg_entList);
    sgSMapDestroy(_sg_entSMap);
    return SG_TRUE;
}

static void SG_CALL _sg_evCall(SGEntity* entity, size_t num, va_list args)
{
    if(!entity->active) return;

    SGenum type;

    size_t siz[2];
    SGuint val[2];
    void* ptr[2];

    SGuint i;
    for(i = 0; i < num; i++)
    {
        type = va_arg(args, SGenum);
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

            case SG_EVF_TEXTCHARP:
                val[0] = va_arg(args, SGenum);
                if(entity->evKeyboardCharPress != NULL)
                    entity->evKeyboardCharPress(entity, val[0]);
                break;

            case SG_EVF_INPUTBUTH:
                val[0] = va_arg(args, SGint);
                val[1] = va_arg(args, SGuint);
                if(entity->evInputButton != NULL)
                    entity->evInputButton(entity, val[0], val[1]);
                break;
            case SG_EVF_INPUTBUTP:
                val[0] = va_arg(args, SGint);
                val[1] = va_arg(args, SGuint);
                if(entity->evInputButtonPress != NULL)
                    entity->evInputButtonPress(entity, val[0], val[1]);
                break;
            case SG_EVF_INPUTBUTR:
                val[0] = va_arg(args, SGint);
                val[1] = va_arg(args, SGuint);
                if(entity->evInputButtonRelease != NULL)
                    entity->evInputButtonRelease(entity, val[0], val[1]);
                break;
            case SG_EVF_INPUTAMOVE:
                val[0] = va_arg(args, SGint);
                ptr[0] = va_arg(args, float*);
                siz[0] = va_arg(args, size_t);
                if(entity->evInputAxisMove != NULL)
                    entity->evInputAxisMove(entity, val[0], ptr[0], siz[0]);
                break;
            case SG_EVF_INPUTPMOVE:
                val[0] = va_arg(args, SGint);
                ptr[0] = va_arg(args, float*);
                siz[0] = va_arg(args, size_t);
                if(entity->evInputPosMove != NULL)
                    entity->evInputPosMove(entity, val[0], ptr[0], siz[0]);
                break;

            // networking goes here (SG_EVF_NET)

            case SG_EVF_LVLSTART:
                if(entity->evLevelStart != NULL)
                    entity->evLevelStart(entity);
                break;

            case SG_EVF_LVLEND:
                if(entity->evLevelEnd != NULL)
                    entity->evLevelEnd(entity);
                break;

            default:
                if(type & SG_EVT_USER)
                {
                    if(entity->evUser)
                        entity->evUser(entity, type & SG_EV_USERMASK, args);
                }
        }
    }
}
static void SG_CALL _sg_evDraw(SGEntity* entity)
{
    if(entity->visible)
        sgEntityDraw(entity);
}

SGEntity* SG_CALL sgEntityCreate(void)
{
    static const SGEntity DefaultEntity = { 0 };

    SGEntity* entity = malloc(sizeof(SGEntity));
    *entity = DefaultEntity;
    entity->active = SG_TRUE;
    entity->pausable = SG_TRUE;

    entity->visible = SG_TRUE;
    entity->pos = sgVec2f(0.0, 0.0);
    entity->depth = 0.0;
    entity->angle = 0.0;

    entity->minside = SG_FALSE;

    entity->evDraw = _sg_evDraw;

    //entity->imask = ~0; //< TODO: Figure out the proper mask for this

    entity->node = sgListAppend(_sg_entList, entity);
    entity->mnode = NULL;
    return entity;
}
void SG_CALL sgEntityDestroy(SGEntity* entity)
{
    if(entity == NULL)
        return;

    if(entity->lcDestroy != NULL)
        entity->lcDestroy(entity);

    sgListRemoveNode(_sg_entList, entity->node);
    sgEntitySetName(entity, NULL);

    free(entity);
}
void SG_CALL sgEntityDestroyAll(void)
{
    while(_sg_entList->head)
        sgEntityDestroy(_sg_entList->head->item);
}

void SG_CALL sgEntitySetName(SGEntity* entity, const char* name)
{
    SGList* list;
    if(entity->mnode)
    {
        list = entity->mnode->val;
        sgListRemoveNode(list, entity->mlnode);
        if(!list->head)
        {
            sgSMapRemove(_sg_entSMap, entity->mnode->key);
            sgListDestroy(list);
        }
        entity->mnode = NULL;
        entity->mlnode = NULL;
    }
    if(!name)
        return;

    SGSMapNode* mnode = sgSMapFind(_sg_entSMap, name);
    if(!mnode)
        mnode = sgSMapAssignNode(_sg_entSMap, name, sgListCreate());

    entity->mnode = mnode;
    entity->mlnode = sgListAppend(mnode->val, entity);
}
char* SG_CALL sgEntityGetName(SGEntity* entity)
{
    if(!entity->mnode) return NULL;

    return entity->mnode->key;
}

void SG_CALL sgEntitySetSprite(SGEntity* entity, SGSprite* sprite)
{
    if(entity == NULL)
        return;

    entity->sprite = sprite;
}
SGSprite* SG_CALL sgEntityGetSprite(SGEntity* entity)
{
    if(entity == NULL)
        return NULL;

    return entity->sprite;
}

void SG_CALL sgEntitySetMask(SGEntity* entity, SGMask* mask)
{
    if(entity == NULL)
        return;

    entity->mask = mask;
}
SGMask* SG_CALL sgEntityGetMask(SGEntity* entity)
{
    if(entity == NULL)
        return NULL;

    return entity->mask;
}

void SG_CALL sgEntitySetPhysicsBody(SGEntity* entity, SGPhysicsBody* body)
{
    if(entity == NULL)
        return;
    if(entity->body)
        entity->body->entity = NULL;
    if(body)
        body->entity = entity;
    entity->body = body;
}
SGPhysicsBody* SG_CALL sgEntityGetPhysicsBody(SGEntity* entity)
{
    if(entity == NULL)
        return NULL;

    return entity->body;
}

void SG_CALL sgEntitySetAudioSource(SGEntity* entity, SGAudioSource* source)
{
    if(entity == NULL)
        return;

    entity->source = source;
}
SGAudioSource* SG_CALL sgEntityGetAudioSource(SGEntity* entity)
{
    if(entity == NULL)
        return NULL;

    return entity->source;
}

void SG_CALL sgEntitySetPos2fv(SGEntity* entity, SGVec2 pos)
{
    if(entity == NULL)
        return;

    entity->pos = pos;
    if(entity->body != NULL)
        sgPhysicsBodySetPos(entity->body, pos.x, pos.y);
}
void SG_CALL sgEntitySetPos2f(SGEntity* entity, float x, float y)
{
    sgEntitySetPos2fv(entity, sgVec2f(x, y));
}
SGVec2 SG_CALL sgEntityGetPos2fv(SGEntity* entity)
{
    if(entity->body != NULL)
    {
        SGVec2 ret;
        sgPhysicsBodyGetPos(entity->body, &ret.x, &ret.y);
        return ret;
    }
    return entity->pos;
}

void SG_CALL sgEntitySetPosX(SGEntity* entity, float x)
{
    entity->pos.x = x;
    if(entity->body != NULL)
        sgPhysicsBodySetPosX(entity->body, x);
}
float SG_CALL sgEntityGetPosX(SGEntity* entity)
{
    if(entity->body != NULL)
        return sgPhysicsBodyGetPosX(entity->body);
    return entity->pos.x;
}
void SG_CALL sgEntitySetPosY(SGEntity* entity, float y)
{
    entity->pos.y = y;
    if(entity->body != NULL)
        sgPhysicsBodySetPosY(entity->body, y);
}
float SG_CALL sgEntityGetPosY(SGEntity* entity)
{
    if(entity->body != NULL)
        return sgPhysicsBodyGetPosY(entity->body);
    return entity->pos.y;
}

void SG_CALL sgEntitySetDepth(SGEntity* entity, float depth)
{
    if(entity == NULL)
        return;

    entity->depth = depth;
}
float SG_CALL sgEntityGetDepth(SGEntity* entity)
{
    if(entity == NULL)
        return SG_NAN;

    return entity->depth;
}

void SG_CALL sgEntitySetAngleRads(SGEntity* entity, float rads)
{
    if(entity == NULL)
        return;

    entity->angle = rads;
    if(entity->body != NULL)
        sgPhysicsBodySetAngleRads(entity->body, rads);
}
float SG_CALL sgEntityGetAngleRads(SGEntity* entity)
{
    if(entity == NULL)
        return SG_NAN;

    if(entity->body != NULL)
        return sgPhysicsBodyGetAngleRads(entity->body);
    return entity->angle;
}
void SG_CALL sgEntitySetAngleDegs(SGEntity* entity, float degs)
{
    sgEntitySetAngleRads(entity, degs * SG_PI / 180.0);
}
float SG_CALL sgEntityGetAngleDegs(SGEntity* entity)
{
    return sgEntityGetAngleRads(entity) * 180.0 / SG_PI;
}

void SG_CALL sgEntityDraw(SGEntity* entity)
{
    if(entity == NULL)
        return;
    if(entity->sprite == NULL)
        return;

    if(entity->body != NULL)
    {
        sgPhysicsBodyGetPos(entity->body, &entity->pos.x, &entity->pos.y);
        entity->angle = sgPhysicsBodyGetAngleRads(entity->body);
    }

    sgSpriteDrawRads3f1f(entity->sprite, entity->pos.x, entity->pos.y, entity->depth, entity->angle);
}

SGList* SG_CALL sgEntityFind(const char* name)
{
    return sgSMapFind(_sg_entSMap, name);
}
SGEntity* SG_CALL sgEntityFindIter(SGEntity* prev, const char* name)
{
    if(prev)
        return prev->mlnode ? prev->mlnode->next->item : NULL;
    SGList* list = sgSMapFind(_sg_entSMap, name);
    if(list)
        return list->head->item;
    return NULL;
}

void SG_CALL sgEntityEventSignalv(size_t num, va_list args)
{
    _sg_entStop = SG_FALSE;
    SGEntity* entity;
    SGListNode* node;
    SGListNode* next;
    va_list curarg;
    for(node = _sg_entList->head; node; node = next)
    {
        next = node->next;

        if(_sg_entStop)
            break;
        entity = node->item;

        va_copy(curarg, args);
        _sg_evCall(entity, num, curarg);
        va_end(curarg);
    }
}
void SG_CALL sgEntityEventSignal(size_t num, ...)
{
    va_list args;
    va_start(args, num);
    sgEntityEventSignalv(num, args);
    va_end(args);
}
void SG_CALL sgEntityEventStop(void)
{
    _sg_entStop = SG_TRUE;
}
