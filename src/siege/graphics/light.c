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
#include <siege/core/window.h>
#include <siege/graphics/light.h>
#include <siege/graphics/draw.h>

#include <stdlib.h>
#include <math.h>

#define OP <=

static SGLightSpace* _sgLightGetSpace(void)
{
    if(!_sg_lightSpaceMain) _sg_lightSpaceMain = sgLightSpaceCreate(0, 0);
    return _sg_lightSpaceMain;
}

SGbool SG_CALL _sgLightInit(void)
{
    _sg_lightSpaceMain = NULL;
    return SG_TRUE;
}
SGbool SG_CALL _sgLightDeinit(void)
{
    sgLightSpaceForceDestroy(_sg_lightSpaceMain);
    _sg_lightSpaceMain = NULL;
    return SG_TRUE;
}

void SG_CALL _sgLightSpaceAddLight(SGLightSpace* space, SGLight* light)
{
    if(space == NULL) space = _sgLightGetSpace();
    light->space = space;
    light->node = sgListAppend(&space->lights, light);
    sgLightLock(light);
}
void SG_CALL _sgLightSpaceAddShadowShape(SGLightSpace* space, SGShadowShape* shape)
{
    if(space == NULL) space = _sgLightGetSpace();
    shape->space = space;
    shape->node = sgListAppend(&space->shapes, shape);
    sgShadowShapeLock(shape);
}
void SG_CALL _sgLightSpaceRemoveLight(SGLightSpace* space, SGLight* light)
{
    sgListRemoveNode(&space->lights, light->node);
}
void SG_CALL _sgLightSpaceRemoveShadowShape(SGLightSpace* space, SGShadowShape* shape)
{
    sgListRemoveNode(&space->shapes, shape->node);
}

SGLightSpace* SG_CALL sgLightSpaceCreate(SGuint width, SGuint height)
{
    SGLightSpace* space = malloc(sizeof(SGLightSpace));
    if(!space) return NULL;
    sgRCountInit(&space->cnt);

    if(!width)
        width = sgWindowGetWidth();
    if(!height)
        height = sgWindowGetHeight();

    space->buffer = sgSurfaceCreate(width, height, 32);
    space->lbuffer = sgSurfaceCreate(width, height, 32);

    sgListInit(&space->lights);
    sgListInit(&space->shapes);

    space->ambience.r = 0.0;
    space->ambience.g = 0.0;
    space->ambience.b = 0.0;
    space->ambience.a = 1.0;

    return space;
}
void SG_CALL sgLightSpaceForceDestroy(SGLightSpace* space)
{
    if(!space)
        return;

    SGListNode* node;
    SGListNode* next;

    for(node = space->lights.head; node; node = next)
    {
        next = node->next;
        sgLightUnlock(node->item);
    }
    sgListDeinit(&space->lights);

    for(node = space->shapes.head; node; node = next)
    {
        next = node->next;
        sgShadowShapeUnlock(node->item);
    }
    sgListDeinit(&space->shapes);

    sgSurfaceRelease(space->buffer);
    sgSurfaceRelease(space->lbuffer);
    sgRCountDeinit(&space->cnt);
    free(space);
}

void SG_CALL sgLightSpaceRelease(SGLightSpace* space)
{
    sgLightSpaceUnlock(space);
}
void SG_CALL sgLightSpaceLock(SGLightSpace* space)
{
    if(!space) return;
    sgRCountInc(&space->cnt);
}
void SG_CALL sgLightSpaceUnlock(SGLightSpace* space)
{
    if(!space) return;
    if(!sgRCountDec(&space->cnt))
        sgLightSpaceForceDestroy(space);
}

void SG_CALL sgLightSpaceSetAmbience4f(SGLightSpace* space, float r, float g, float b, float a)
{
    space->ambience.r = r;
    space->ambience.g = g;
    space->ambience.b = b;
    space->ambience.a = a;
}

SGSurface* SG_CALL sgLightSpaceGetBuffer(SGLightSpace* space)
{
    return space->buffer;
}

void SG_CALL sgLightSpaceResize(SGLightSpace* space, SGuint width, SGuint height)
{
    sgSurfaceRelease(space->buffer);
    sgSurfaceRelease(space->lbuffer);
    space->buffer = sgSurfaceCreate(width, height, 32);
    space->lbuffer = sgSurfaceCreate(width, height, 32);
}
void SG_CALL sgLightSpaceUpdate(SGLightSpace* space)
{
    SGListNode* lnode;
    SGListNode* snode;

    sgSurfaceClear4f(space->buffer, space->ambience.r, space->ambience.g, space->ambience.b, space->ambience.a);
    for(lnode = space->lights.head; lnode != NULL; lnode = lnode->next)
    {
        if(!sgLightGetActive(lnode->item))
            continue;
        sgDrawSetBlendFunc(SG_FUNC_ONE, SG_FUNC_ZERO);
        sgSurfaceClear4f(space->lbuffer, 0.0, 0.0, 0.0, 1.0);
        sgSurfaceTarget(space->lbuffer);
        sgLightDraw(lnode->item);
        if(sgLightGetShadow(lnode->item))
        {
            for(snode = space->shapes.head; snode != NULL; snode = snode->next)
            {
                if(!sgShadowShapeGetActive(snode->item))
                    continue;
                sgShadowShapeCast(snode->item, lnode->item);
            }
        }
        sgSurfaceUntarget(space->lbuffer);

        sgDrawSetBlendFunc(SG_FUNC_SRC_ALPHA, SG_FUNC_ONE);
        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgSurfaceTarget(space->buffer);
        sgSurfaceDraw(space->lbuffer);
        sgSurfaceUntarget(space->buffer);
    }
    sgDrawSetBlendFunc(SG_FUNC_SRC_ALPHA, SG_FUNC_ONE_MINUS_SRC_ALPHA);
}
void SG_CALL sgLightSpaceDraw(SGLightSpace* space, SGenum flags)
{
    if(flags & SG_SHADOW_DRAW_MUL)
    {
        if(flags & SG_SHADOW_DRAW_SQR)
            sgDrawSetBlendFunc(SG_FUNC_DST_COLOR, SG_FUNC_SRC_COLOR);
        else
            sgDrawSetBlendFunc(SG_FUNC_DST_COLOR, SG_FUNC_ZERO);
    }
    else /* note to self: sgDrawSetBlendFunc(SG_FUNC_SRC_COLOR, SG_FUNC_ONE); makes for an interesting effect; I should prooly add an API for that */
        sgDrawSetBlendFunc(SG_FUNC_SRC_ALPHA, SG_FUNC_ONE);
    sgSurfaceDraw(space->buffer);
    sgDrawSetBlendFunc(SG_FUNC_SRC_ALPHA, SG_FUNC_ONE_MINUS_SRC_ALPHA);
}
void SG_CALL sgLightSpaceDrawDBG(SGLightSpace* space, SGenum flags)
{
    SGListNode* lnode;
    SGListNode* snode;
    for(snode = space->shapes.head; snode != NULL; snode = snode->next)
    {
        if(!sgShadowShapeGetActive(snode->item))
            continue;
        sgShadowShapeDrawDBG(snode->item, SG_TRUE);
    }
    for(snode = space->shapes.head; snode != NULL; snode = snode->next)
    {
        if(!sgShadowShapeGetActive(snode->item))
            continue;
        sgShadowShapeDrawDBG(snode->item, SG_FALSE);
    }
    for(lnode = space->lights.head; lnode != NULL; lnode = lnode->next)
    {
        if(!sgLightGetActive(lnode->item))
            continue;
        sgLightDrawDBG(lnode->item);
        if(sgLightGetShadow(lnode->item))
        {
            for(snode = space->shapes.head; snode != NULL; snode = snode->next)
            {
                if(!sgShadowShapeGetActive(snode->item))
                    continue;
                sgShadowShapeCastDBG(snode->item, lnode->item);
            }
        }
    }
}

SGLight* SG_CALL sgLightCreate(SGLightSpace* space, float x, float y, float radius)
{
    SGLight* light = malloc(sizeof(SGLight));
    if(light == NULL)
        return NULL;
    sgRCountInit(&light->cnt);

    _sgLightSpaceAddLight(space, light);

    light->pos = sgVec2f(x, y);
    light->radius = radius;
    light->color = sgColor4ub(1.0, 1.0, 1.0, 1.0);

    light->depth = 0.0;
    light->height = 0.0;

    light->active = SG_TRUE;
    light->stat = SG_FALSE;
    light->shadow = SG_TRUE;

    light->angle = 0.0;
    light->cone = 2 * SG_PI;
    light->sprite = NULL;

    return light;
}
void SG_CALL sgLightForceDestroy(SGLight* light)
{
    if(light == NULL)
        return;

    _sgLightSpaceRemoveLight(light->space, light);

    //if(light->sprite)
    //    sgSpriteDestroy(light->sprite);
    sgRCountDeinit(&light->cnt);
    free(light);
}

void SG_CALL sgLightRelease(SGLight* light)
{
    sgLightUnlock(light);
}
void SG_CALL sgLightLock(SGLight* light)
{
    if(!light) return;
    sgRCountInc(&light->cnt);
}
void SG_CALL sgLightUnlock(SGLight* light)
{
    if(!light) return;
    if(!sgRCountDec(&light->cnt))
        sgLightForceDestroy(light);
}

void SG_CALL sgLightSetPos(SGLight* light, float x, float y)
{
    light->pos = sgVec2f(x, y);
}
void SG_CALL sgLightSetPosX(SGLight* light, float x)
{
    light->pos.x = x;
}
void SG_CALL sgLightSetPosY(SGLight* light, float y)
{
    light->pos.y = y;
}

void SG_CALL sgLightGetPos(SGLight* light, float* x, float* y)
{
    if(x != NULL)
        *x = light->pos.x;
    if(y != NULL)
        *y = light->pos.y;
}
float SG_CALL sgLightGetPosX(SGLight* light)
{
    return light->pos.x;
}
float SG_CALL sgLightGetPosY(SGLight* light)
{
    return light->pos.y;
}

void SG_CALL sgLightSetRadius(SGLight* light, float radius)
{
    light->radius = radius;
}
float SG_CALL sgLightGetRadius(SGLight* light)
{
    return light->radius;
}

void SG_CALL sgLightSetColor4f(SGLight* light, float r, float g, float b, float a)
{
    light->color = sgColor4f(r, g, b, a);
}
void SG_CALL sgLightSetColor3f(SGLight* light, float r, float g, float b)
{
    sgLightSetColor4f(light, r, g, b, 1.0);
}
void SG_CALL sgLightSetColor2f(SGLight* light, float g, float a)
{
    sgLightSetColor4f(light, g, g, g, a);
}
void SG_CALL sgLightSetColor1f(SGLight* light, float g)
{
    sgLightSetColor4f(light, g, g, g, 1.0);
}

void SG_CALL sgLightSetColor4ub(SGLight* light, SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    light->color = sgColor4ub(r, g, b, a);
}
void SG_CALL sgLightSetColor3ub(SGLight* light, SGubyte r, SGubyte g, SGubyte b)
{
    sgLightSetColor4ub(light, r, g, b, 255);
}
void SG_CALL sgLightSetColor2ub(SGLight* light, SGubyte g, SGubyte a)
{
    sgLightSetColor4ub(light, g, g, g, a);
}
void SG_CALL sgLightSetColor1ub(SGLight* light, SGubyte g)
{
    sgLightSetColor4ub(light, g, g, g, 255);
}

void SG_CALL sgLightSetDepth(SGLight* light, float depth)
{
    light->depth = depth;
}
float SG_CALL sgLightGetDepth(SGLight* light)
{
    return light->depth;
}

void SG_CALL sgLightSetHeight(SGLight* light, float height)
{
    light->height = height;
}
float SG_CALL sgLightGetHeight(SGLight* light)
{
    return light->height;
}

void SG_CALL sgLightSetActive(SGLight* light, SGbool active)
{
    light->active = active;
}
SGbool SG_CALL sgLightGetActive(SGLight* light)
{
    return light->active;
}

void SG_CALL sgLightSetStatic(SGLight* light, SGbool stat)
{
    light->stat = stat;
}
SGbool SG_CALL sgLightGetStatic(SGLight* light)
{
    return light->stat;
}

void SG_CALL sgLightSetShadow(SGLight* light, SGbool shadow)
{
    light->shadow = shadow;
}
SGbool SG_CALL sgLightGetShadow(SGLight* light)
{
    return light->shadow;
}

void SG_CALL sgLightSetAngleRads(SGLight* light, float rads)
{
    light->angle = rads;
}
float SG_CALL sgLightGetAngleRads(SGLight* light)
{
    return light->angle;
}

void SG_CALL sgLightSetAngleDegs(SGLight* light, float degs)
{
    light->angle = degs * SG_PI / 180.0;
}
float SG_CALL sgLightGetAngleDegs(SGLight* light)
{
    return light->angle * 180.0 / SG_PI;
}

void SG_CALL sgLightSetConeRads(SGLight* light, float rads)
{
    light->cone = rads;
}
float SG_CALL sgLightGetConeRads(SGLight* light)
{
    return light->cone;
}

void SG_CALL sgLightSetConeDegs(SGLight* light, float degs)
{
    light->cone = degs * SG_PI / 180.0;
}
float SG_CALL sgLightGetConeDegs(SGLight* light)
{
    return light->cone * 180.0 / SG_PI;
}

void SG_CALL sgLightDraw(SGLight* light)
{
    sgDrawColor4f(light->color.r, light->color.g, light->color.b, light->color.a);
    if(light->sprite)
    {
        sgSpriteDrawRads2f1f(light->sprite, light->pos.x, light->pos.y, light->angle);
    }
    else
    {
        size_t i;
        int sides = SG_MAX(3, (int)(light->radius * 0.5));
        float f = 2 * SG_PI / sides;
        sgDrawBegin(SG_TRIANGLE_FAN);
            sgDrawVertex2f(light->pos.x, light->pos.y);
            sgDrawColor4f(light->color.r, light->color.g, light->color.b, 0.0);
            for(i = 0; i <= sides; i++)
            {
                sgDrawVertex2f(light->pos.x + cos(f * i) * light->radius,
                            light->pos.y + sin(f * i) * light->radius);
            }
        sgDrawEnd();
    }
}

void SG_CALL sgLightDrawDBG(SGLight* light)
{
    sgDrawColor4f(1.0, 1.0, 0.0, 1.0);
    sgDrawCircle2fv(light->pos, light->radius, SG_FALSE);
}

SGShadowShape* SG_CALL sgShadowShapeCreate(SGLightSpace* space, SGenum type)
{
    SGShadowShape* shape = malloc(sizeof(SGShadowShape));
    if(shape == NULL)
        return NULL;
    sgRCountInit(&shape->cnt);

    _sgLightSpaceAddShadowShape(space, shape);

    shape->type = type;
    shape->pos = sgVec2f(SG_NAN, SG_NAN);

    shape->depth = 0.0;

    shape->active = SG_TRUE;
    shape->stat = SG_FALSE;

    shape->angle = 0.0;

    shape->numverts = 0;
    shape->verts = NULL;

    return shape;
}
SGShadowShape* SG_CALL sgShadowShapeCreateSegment(SGLightSpace* space, float x1, float y1, float x2, float y2)
{
    SGShadowShape* shape = sgShadowShapeCreate(space, SG_SHAPE_SEGMENT);
    if(shape == NULL)
        return NULL;

    shape->pos = sgVec2f((x1 + x2) / 2, (y1 + y2) / 2);

    float dx = ((x2 > x1) ? x2 : x1) - shape->pos.x;
    float dy = ((y2 > y1) ? y2 : y1) - shape->pos.y;

    shape->numverts = 2;
    shape->verts = malloc(2 * sizeof(SGVec2));
    shape->verts[0] = sgVec2f(-dx, -dy);
    shape->verts[1] = sgVec2f(dx, dy);

    return shape;
}
SGShadowShape* SG_CALL sgShadowShapeCreatePoly(SGLightSpace* space, float x, float y, float* verts, size_t numverts)
{
    SGShadowShape* shape = sgShadowShapeCreate(space, SG_SHAPE_POLYGON);
    if(shape == NULL)
        return NULL;

    shape->pos = sgVec2f(x, y);

    shape->numverts = numverts;
    shape->verts = malloc(numverts * sizeof(SGVec2));
    size_t i;
    for(i = 0; i < numverts; i++)
    {
        shape->verts[i] = sgVec2f(verts[2*i], verts[2*i+1]);
    }

    return shape;
}
SGShadowShape* SG_CALL sgShadowShapeCreateCircle(SGLightSpace* space, float x, float y, float radius)
{
    SGShadowShape* shape = sgShadowShapeCreate(space, SG_SHAPE_SEGMENT);
    if(shape == NULL)
        return NULL;

    shape->pos = sgVec2f(x, y);

    shape->numverts = 1;
    shape->verts = malloc(1 * sizeof(SGVec2));
    shape->verts[0] = sgVec2f(radius, radius);

    return shape;
}
void SG_CALL sgShadowShapeForceDestroy(SGShadowShape* shape)
{
    if(shape == NULL)
        return;

    _sgLightSpaceRemoveShadowShape(shape->space, shape);

    free(shape->verts);
    sgRCountDeinit(&shape->cnt);
    free(shape);
}

void SG_CALL sgShadowShapeRelease(SGShadowShape* shape)
{
    sgShadowShapeUnlock(shape);
}
void SG_CALL sgShadowShapeLock(SGShadowShape* shape)
{
    if(!shape) return;
    sgRCountInc(&shape->cnt);
}
void SG_CALL sgShadowShapeUnlock(SGShadowShape* shape)
{
    if(!shape) return;
    if(!sgRCountDec(&shape->cnt))
        sgShadowShapeForceDestroy(shape);
}

void SG_CALL sgShadowShapeSetDepth(SGShadowShape* shape, float depth)
{
    shape->depth = depth;
}
float SG_CALL sgShadowShapeGetDepth(SGShadowShape* shape)
{
    return shape->depth;
}

void SG_CALL sgShadowShapeSetActive(SGShadowShape* shape, SGbool active)
{
    shape->active = active;
}
SGbool SG_CALL sgShadowShapeGetActive(SGShadowShape* shape)
{
    return shape->active;
}

void SG_CALL sgShadowShapeSetStatic(SGShadowShape* shape, SGbool stat)
{
    shape->stat = stat;
}
SGbool SG_CALL sgShadowShapeGetStatic(SGShadowShape* shape)
{
    return shape->stat;
}

void SG_CALL sgShadowShapeDrawDBG(SGShadowShape* shape, SGbool fill)
{
    if(shape == NULL)
        return;

    if(fill)
        sgDrawColor4f(0.0, 0.5, 0.75, 1.0);
    else
        sgDrawColor4f(0.0, 1.0, 0.75, 1.0);

    SGVec2 vec;

    size_t i;
    switch(shape->type)
    {
        case SG_SHAPE_SEGMENT:
            vec = sgVec2RotateRads(shape->verts[0],
                                     sgVec2AngleRads(shape->verts[0]) + shape->angle);
            sgDrawLine2fv(sgVec2Add(shape->pos, vec), sgVec2Sub(shape->pos, vec));
            break;
        case SG_SHAPE_POLYGON:
            if(fill)
                sgDrawBegin(SG_CONVEX_POLYGON);
            else
                sgDrawBegin(SG_LINE_LOOP);
            for(i = 0; i < shape->numverts; i++)
            {
                vec = sgVec2RotateRads(shape->verts[i],
                                         sgVec2AngleRads(shape->verts[i]) + shape->angle);
                sgDrawVertex2fv(sgVec2Add(shape->pos, vec));
            }
            sgDrawEnd();
            break;
        case SG_SHAPE_CIRCLE:
            sgDrawCircle2fv(shape->pos, shape->verts[0].x, fill);
            break;
    }
}

void SG_CALL sgShadowShapeCast(SGShadowShape* shape, SGLight* light)
{
    sgDrawColor4f(0.0, 0.0, 0.0, 1.0);
    sgDrawBegin(SG_TRIANGLES);

    /*SGVec2* curr;*/
    SGVec2* next;
    SGVec2 tcurr, tnext;
    SGVec2 tmpc, tmpn;
    size_t i;

    if(shape->numverts > 0)
    {
        tcurr = sgVec2RotateRads(shape->verts[0], sgVec2AngleRads(shape->verts[0]) + shape->angle);
        tcurr = sgVec2Add(tcurr, shape->pos);
    }
    for(i = 0; i < shape->numverts; i++)
    {
        /*curr = &shape->verts[i];*/
        next = &shape->verts[(i + 1) % shape->numverts];

        tnext = sgVec2RotateRads(*next, sgVec2AngleRads(*next) + shape->angle);
        tnext = sgVec2Add(tnext, shape->pos);

        if(sgVec2PDot(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) OP 0)
        {
            tmpc = sgVec2Add(tcurr, sgVec2Resize(sgVec2Sub(tcurr, light->pos), light->radius));
            tmpn = sgVec2Add(tnext, sgVec2Resize(sgVec2Sub(tnext, light->pos), light->radius));

            sgDrawVertex2f(tcurr.x, tcurr.y);
            sgDrawVertex2f(tnext.x, tnext.y);
            sgDrawVertex2f(tmpc.x, tmpc.y);

            sgDrawVertex2f(tmpc.x, tmpc.y);
            sgDrawVertex2f(tmpn.x, tmpn.y);
            sgDrawVertex2f(tnext.x, tnext.y);
        }
        tcurr = tnext;
    }
    sgDrawEnd();
}

void SG_CALL sgShadowShapeCastDBG(SGShadowShape* shape, SGLight* light)
{
    /*SGVec2* curr;*/
    SGVec2* next;
    SGVec2 tcurr, tnext;
    SGVec2 tmpc, tmpn;
    size_t i;

    sgDrawBegin(SG_LINES);

    if(shape->numverts > 0)
    {
        tcurr = sgVec2RotateRads(shape->verts[0], sgVec2AngleRads(shape->verts[0]) + shape->angle);
        tcurr = sgVec2Add(tcurr, shape->pos);
    }
    for(i = 0; i < shape->numverts; i++)
    {
        /*curr = &shape->verts[i];*/
        next = &shape->verts[(i + 1) % shape->numverts];

        tnext = sgVec2RotateRads(*next, sgVec2AngleRads(*next) + shape->angle);
        tnext = sgVec2Add(tnext, shape->pos);

        if(sgVec2PDot(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) OP 0)
        {
            sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
            sgDrawVertex2f(tcurr.x, tcurr.y);
            sgDrawVertex2f(tnext.x, tnext.y);

            tmpc = sgVec2Add(tcurr, sgVec2Resize(sgVec2Sub(tcurr, light->pos), light->radius));
            tmpn = sgVec2Add(tnext, sgVec2Resize(sgVec2Sub(tnext, light->pos), light->radius));

            sgDrawVertex2f(tcurr.x, tcurr.y);
            sgDrawVertex2f(tmpc.x, tmpc.y);
            //sgDrawVertex2f(next->x, next->y);

            //sgDrawVertex2f(tmpc.x, tmpc.y);
            sgDrawVertex2f(tmpn.x, tmpn.y);
            sgDrawVertex2f(tnext.x, tnext.y);

            sgDrawColor4f(1.0, 0.5, 0.0, 0.5);
            sgDrawVertex2f(tmpc.x, tmpc.y);
            sgDrawVertex2f(tmpn.x, tmpn.y);
        }
        tcurr = tnext;
    }

    sgDrawEnd();
}

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgLightSpaceDestroy(SGLightSpace* space)
{
    sgLightSpaceRelease(space);
}
void SG_CALL SG_HINT_DEPRECATED sgLightDestroy(SGLight* light)
{
    sgLightRelease(light);
}
void SG_CALL SG_HINT_DEPRECATED sgShadowShapeDestroy(SGShadowShape* shape)
{
    sgShadowShapeRelease(shape);
}
