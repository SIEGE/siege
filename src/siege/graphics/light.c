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

/*
    TODO: change the way shadows are extended;
    currently, we use winw/winh, we should try getting some viewport info...
*/

SGbool SG_EXPORT _sgLightInit(void)
{
    _sg_lightSpaceMain = sgLightSpaceCreate();

    return SG_TRUE;
}
SGbool SG_EXPORT _sgLightDeinit(void)
{
    sgLightSpaceDestroy(_sg_lightSpaceMain);

    return SG_TRUE;
}

void SG_EXPORT _sgLightSpaceAddLight(SGLightSpace* space, SGLight* light)
{
    if(space == NULL)
        space = _sg_lightSpaceMain;
    light->space = space;
    light->node = sgListAppend(space->lights, light);
}
void SG_EXPORT _sgLightSpaceAddShadowShape(SGLightSpace* space, SGShadowShape* shape)
{
    if(space == NULL)
        space = _sg_lightSpaceMain;
    shape->space = space;
    shape->node = sgListAppend(space->shapes, shape);
}
void SG_EXPORT _sgLightSpaceRemoveLight(SGLightSpace* space, SGLight* light)
{
    sgListRemoveNode(space->lights, light->node);
}
void SG_EXPORT _sgLightSpaceRemoveShadowShape(SGLightSpace* space, SGShadowShape* shape)
{
    sgListRemoveNode(space->shapes, shape->node);
}

SGLightSpace* SG_EXPORT sgLightSpaceCreate(void)
{
    SGLightSpace* space = malloc(sizeof(SGLightSpace));

    SGuint width, height;
    sgWindowGetSize(&width, &height);

    space->buffer = sgSurfaceCreate(width, height, 32);
    space->lbuffer = sgSurfaceCreate(width, height, 32);
    space->lights = sgListCreate();
    space->shapes = sgListCreate();

    space->ambience = (SGColor){0.0, 0.0, 0.0, 0.0};

    return space;
}
void SG_EXPORT sgLightSpaceDestroy(SGLightSpace* space)
{
    if(!space)
        return;

    SGListNode* node;

    for(node = space->lights->first; node != NULL; node = node->next)
        sgLightDestroy(node->item);
    sgListDestroy(space->lights);

    for(node = space->shapes->first; node != NULL; node = node->next)
        sgShadowShapeDestroy(node->item);
    sgListDestroy(space->shapes);

    sgSurfaceDestroy(space->buffer);
    sgSurfaceDestroy(space->lbuffer);

    free(space);
}

void SG_EXPORT sgLightSpaceSetAmbience4f(SGLightSpace* space, float r, float g, float b, float a)
{
    space->ambience.r = r;
    space->ambience.g = g;
    space->ambience.b = b;
    space->ambience.a = a;
}

SGSurface* SG_EXPORT sgLightSpaceGetBuffer(SGLightSpace* space)
{
    return space->buffer;
}

void SG_EXPORT sgLightSpaceUpdate(SGLightSpace* space)
{
    SGListNode* lnode;
    SGListNode* snode;

    sgSurfaceClear4f(space->buffer, space->ambience.r, space->ambience.g, space->ambience.b, space->ambience.a);
    for(lnode = space->lights->first; lnode != NULL; lnode = lnode->next)
    {
        if(!sgLightGetActive(lnode->item))
            continue;
        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_ONE, SG_GRAPHICS_FUNC_ZERO);
        sgSurfaceClear4f(space->lbuffer, 0.0, 0.0, 0.0, 1.0);
        sgSurfaceTarget(space->lbuffer);
        sgLightDraw(lnode->item);
        if(sgLightGetShadow(lnode->item))
        {
            for(snode = space->shapes->first; snode != NULL; snode = snode->next)
            {
                if(!sgShadowShapeGetActive(snode->item))
                    continue;
                sgShadowShapeCast(snode->item, lnode->item);
            }
        }
        sgSurfaceUntarget(space->lbuffer);

        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE);
        sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
        sgSurfaceTarget(space->buffer);
        sgSurfaceDraw(space->lbuffer);
        sgSurfaceUntarget(space->buffer);
    }
    sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);
}
void SG_EXPORT sgLightSpaceDraw(SGLightSpace* space, SGenum flags)
{
    if(flags & SG_SHADOW_DRAW_MUL)
    {
        if(flags & SG_SHADOW_DRAW_SQR)
            sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_DST_COLOR, SG_GRAPHICS_FUNC_SRC_COLOR);
        else
            sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_DST_COLOR, SG_GRAPHICS_FUNC_ZERO);
    }
    else
        sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE);
    sgSurfaceDraw(space->buffer);
    sgDrawSetBlendFunc(SG_GRAPHICS_FUNC_SRC_ALPHA, SG_GRAPHICS_FUNC_ONE_MINUS_SRC_ALPHA);
}
void SG_EXPORT sgLightSpaceDrawDBG(SGLightSpace* space, SGenum flags)
{
    SGListNode* lnode;
    SGListNode* snode;
    for(snode = space->shapes->first; snode != NULL; snode = snode->next)
    {
        if(!sgShadowShapeGetActive(snode->item))
            continue;
        sgShadowShapeDrawDBG(snode->item, SG_TRUE);
    }
    for(snode = space->shapes->first; snode != NULL; snode = snode->next)
    {
        if(!sgShadowShapeGetActive(snode->item))
            continue;
        sgShadowShapeDrawDBG(snode->item, SG_FALSE);
    }
    for(lnode = space->lights->first; lnode != NULL; lnode = lnode->next)
    {
        if(!sgLightGetActive(lnode->item))
            continue;
        sgLightDrawDBG(lnode->item);
        if(sgLightGetShadow(lnode->item))
        {
            for(snode = space->shapes->first; snode != NULL; snode = snode->next)
            {
                if(!sgShadowShapeGetActive(snode->item))
                    continue;
                sgShadowShapeCastDBG(snode->item, lnode->item);
            }
        }
    }
}

SGLight* SG_EXPORT sgLightCreate(SGLightSpace* space, float x, float y, float radius)
{
    SGLight* light = malloc(sizeof(SGLight));
    if(light == NULL)
        return NULL;

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
    light->cone = 2 * M_PI;
    light->sprite = NULL;

    return light;
}
void SG_EXPORT sgLightDestroy(SGLight* light)
{
    if(light == NULL)
        return;

    _sgLightSpaceRemoveLight(light->space, light);

    //if(light->sprite)
    //    sgSpriteDestroy(light->sprite);
    free(light);
}

void SG_EXPORT sgLightSetPos(SGLight* light, float x, float y)
{
    light->pos = sgVec2f(x, y);
}
void SG_EXPORT sgLightSetPosX(SGLight* light, float x)
{
    light->pos.x = x;
}
void SG_EXPORT sgLightSetPosY(SGLight* light, float y)
{
    light->pos.y = y;
}

void SG_EXPORT sgLightGetPos(SGLight* light, float* x, float* y)
{
    if(x != NULL)
        *x = light->pos.x;
    if(y != NULL)
        *y = light->pos.y;
}
float SG_EXPORT sgLightGetPosX(SGLight* light)
{
    return light->pos.x;
}
float SG_EXPORT sgLightGetPosY(SGLight* light)
{
    return light->pos.y;
}

void SG_EXPORT sgLightSetRadius(SGLight* light, float radius)
{
    light->radius = radius;
}
float SG_EXPORT sgLightGetRadius(SGLight* light)
{
    return light->radius;
}

void SG_EXPORT sgLightSetColor4f(SGLight* light, float r, float g, float b, float a)
{
    light->color = sgColor4f(r, g, b, a);
}
void SG_EXPORT sgLightSetColor3f(SGLight* light, float r, float g, float b)
{
    sgLightSetColor4f(light, r, g, b, 1.0);
}
void SG_EXPORT sgLightSetColor2f(SGLight* light, float g, float a)
{
    sgLightSetColor4f(light, g, g, g, a);
}
void SG_EXPORT sgLightSetColor1f(SGLight* light, float g)
{
    sgLightSetColor4f(light, g, g, g, 1.0);
}

void SG_EXPORT sgLightSetColor4ub(SGLight* light, SGubyte r, SGubyte g, SGubyte b, SGubyte a)
{
    light->color = sgColor4ub(r, g, b, a);
}
void SG_EXPORT sgLightSetColor3ub(SGLight* light, SGubyte r, SGubyte g, SGubyte b)
{
    sgLightSetColor4ub(light, r, g, b, 255);
}
void SG_EXPORT sgLightSetColor2ub(SGLight* light, SGubyte g, SGubyte a)
{
    sgLightSetColor4ub(light, g, g, g, a);
}
void SG_EXPORT sgLightSetColor1ub(SGLight* light, SGubyte g)
{
    sgLightSetColor4ub(light, g, g, g, 255);
}

void SG_EXPORT sgLightSetDepth(SGLight* light, float depth)
{
    light->depth = depth;
}
float SG_EXPORT sgLightGetDepth(SGLight* light)
{
    return light->depth;
}

void SG_EXPORT sgLightSetHeight(SGLight* light, float height)
{
    light->height = height;
}
float SG_EXPORT sgLightGetHeight(SGLight* light)
{
    return light->height;
}

void SG_EXPORT sgLightSetActive(SGLight* light, SGbool active)
{
    light->active = active;
}
SGbool SG_EXPORT sgLightGetActive(SGLight* light)
{
    return light->active;
}

void SG_EXPORT sgLightSetStatic(SGLight* light, SGbool stat)
{
    light->stat = stat;
}
SGbool SG_EXPORT sgLightGetStatic(SGLight* light)
{
    return light->stat;
}

void SG_EXPORT sgLightSetShadow(SGLight* light, SGbool shadow)
{
    light->shadow = shadow;
}
SGbool SG_EXPORT sgLightGetShadow(SGLight* light)
{
    return light->shadow;
}

void SG_EXPORT sgLightSetAngleRads(SGLight* light, float rads)
{
    light->angle = rads;
}
float SG_EXPORT sgLightGetAngleRads(SGLight* light)
{
    return light->angle;
}

void SG_EXPORT sgLightSetAngleDegs(SGLight* light, float degs)
{
    light->angle = degs * M_PI / 180.0;
}
float SG_EXPORT sgLightGetAngleDegs(SGLight* light)
{
    return light->angle * 180.0 / M_PI;
}

void SG_EXPORT sgLightSetConeRads(SGLight* light, float rads)
{
    light->cone = rads;
}
float SG_EXPORT sgLightGetConeRads(SGLight* light)
{
    return light->cone;
}

void SG_EXPORT sgLightSetConeDegs(SGLight* light, float degs)
{
    light->cone = degs * M_PI / 180.0;
}
float SG_EXPORT sgLightGetConeDegs(SGLight* light)
{
    return light->cone * 180.0 / M_PI;
}

void SG_EXPORT sgLightDraw(SGLight* light)
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
        float f = 2 * M_PI / sides;
        sgDrawBegin(SG_GRAPHICS_PRIMITIVE_TRIANGLE_FAN);
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

void SG_EXPORT sgLightDrawDBG(SGLight* light)
{
    sgDrawColor4f(1.0, 1.0, 0.0, 1.0);
    sgDrawCircle(light->pos.x, light->pos.y, light->radius, SG_FALSE);
}

SGShadowShape* SG_EXPORT sgShadowShapeCreate(SGLightSpace* space, SGenum type)
{
    SGShadowShape* shape = malloc(sizeof(SGShadowShape));
    if(shape == NULL)
        return NULL;

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
SGShadowShape* SG_EXPORT sgShadowShapeCreateSegment(SGLightSpace* space, float x1, float y1, float x2, float y2)
{
    SGShadowShape* shape = sgShadowShapeCreate(space, SG_SHADOW_SHAPE_SEGMENT);
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
SGShadowShape* SG_EXPORT sgShadowShapeCreatePoly(SGLightSpace* space, float x, float y, float* verts, size_t numverts)
{
    SGShadowShape* shape = sgShadowShapeCreate(space, SG_SHADOW_SHAPE_POLYGON);
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
SGShadowShape* SG_EXPORT sgShadowShapeCreateCircle(SGLightSpace* space, float x, float y, float radius)
{
    SGShadowShape* shape = sgShadowShapeCreate(space, SG_SHADOW_SHAPE_SEGMENT);
    if(shape == NULL)
        return NULL;

    shape->pos = sgVec2f(x, y);

    shape->numverts = 1;
    shape->verts = malloc(1 * sizeof(SGVec2));
    shape->verts[0] = sgVec2f(radius, radius);

    return shape;
}
void SG_EXPORT sgShadowShapeDestroy(SGShadowShape* shape)
{
    if(shape == NULL)
        return;

    _sgLightSpaceRemoveShadowShape(shape->space, shape);

    free(shape->verts);
    free(shape);
}

void SG_EXPORT sgShadowShapeSetDepth(SGShadowShape* shape, float depth)
{
    shape->depth = depth;
}
float SG_EXPORT sgShadowShapeGetDepth(SGShadowShape* shape)
{
    return shape->depth;
}

void SG_EXPORT sgShadowShapeSetActive(SGShadowShape* shape, SGbool active)
{
    shape->active = active;
}
SGbool SG_EXPORT sgShadowShapeGetActive(SGShadowShape* shape)
{
    return shape->active;
}

void SG_EXPORT sgShadowShapeSetStatic(SGShadowShape* shape, SGbool stat)
{
    shape->stat = stat;
}
SGbool SG_EXPORT sgShadowShapeGetStatic(SGShadowShape* shape)
{
    return shape->stat;
}

void SG_EXPORT sgShadowShapeDrawDBG(SGShadowShape* shape, SGbool fill)
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
        case SG_SHADOW_SHAPE_SEGMENT:
            vec = sgVec2SetAngleRads(shape->verts[0],
                                     sgVec2GetAngleRads(shape->verts[0]) + shape->angle);
            sgDrawLine(shape->pos.x + vec.x, shape->pos.y + vec.y,
                       shape->pos.x - vec.x, shape->pos.y - vec.y);
            break;
        case SG_SHADOW_SHAPE_POLYGON:
            if(fill)
                sgDrawBegin(SG_GRAPHICS_PRIMITIVE_CONVEX_POLYGON);
            else
                sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINE_LOOP);
            for(i = 0; i < shape->numverts; i++)
            {
                vec = sgVec2SetAngleRads(shape->verts[i],
                                         sgVec2GetAngleRads(shape->verts[i]) + shape->angle);
                sgDrawVertex2f(shape->pos.x + vec.x, shape->pos.y + vec.y);
            }
            sgDrawEnd();
            break;
        case SG_SHADOW_SHAPE_CIRCLE:
            sgDrawCircle(shape->pos.x, shape->pos.y, shape->verts[0].x, fill);
            break;
    }
}

void SG_EXPORT sgShadowShapeCast(SGShadowShape* shape, SGLight* light)
{
    sgDrawColor4f(0.0, 0.0, 0.0, 1.0);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_TRIANGLES);

    SGVec2* curr;
    SGVec2* next;
    SGVec2 tcurr, tnext;
    SGVec2 tmpc, tmpn;
    size_t i;

    SGuint winw, winh;
    sgWindowGetSize(&winw, &winh);

    if(shape->numverts > 0)
    {
        tcurr = sgVec2SetAngleRads(shape->verts[0], sgVec2GetAngleRads(shape->verts[0]) + shape->angle);
        tcurr = sgVec2Add(tcurr, shape->pos);
    }
    for(i = 0; i < shape->numverts; i++)
    {
        curr = &shape->verts[i];
        next = &shape->verts[(i + 1) % shape->numverts];

        tnext = sgVec2SetAngleRads(*next, sgVec2GetAngleRads(*next) + shape->angle);
        tnext = sgVec2Add(tnext, shape->pos);

        if(sgVec2Cross(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) OP 0)
        {
            tmpc = sgVec2Add(tcurr, sgVec2SetLength(sgVec2Sub(tcurr, light->pos), winw + winh));
            tmpn = sgVec2Add(tnext, sgVec2SetLength(sgVec2Sub(tnext, light->pos), winw + winh));

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

void SG_EXPORT sgShadowShapeCastDBG(SGShadowShape* shape, SGLight* light)
{
    SGVec2* curr;
    SGVec2* next;
    SGVec2 tcurr, tnext;
    SGVec2 tmpc, tmpn;
    size_t i;

    sgDrawColor4f(1.0, 0.0, 0.0, 1.0);
    sgDrawBegin(SG_GRAPHICS_PRIMITIVE_LINES);

    SGuint winw, winh;
    sgWindowGetSize(&winw, &winh);

    if(shape->numverts > 0)
    {
        tcurr = sgVec2SetAngleRads(shape->verts[0], sgVec2GetAngleRads(shape->verts[0]) + shape->angle);
        tcurr = sgVec2Add(tcurr, shape->pos);
    }
    for(i = 0; i < shape->numverts; i++)
    {
        curr = &shape->verts[i];
        next = &shape->verts[(i + 1) % shape->numverts];

        tnext = sgVec2SetAngleRads(*next, sgVec2GetAngleRads(*next) + shape->angle);
        tnext = sgVec2Add(tnext, shape->pos);

        if(sgVec2Cross(sgVec2Sub(tnext, tcurr), sgVec2Sub(tnext, light->pos)) OP 0)
        {
            sgDrawVertex2f(tcurr.x, tcurr.y);
            sgDrawVertex2f(tnext.x, tnext.y);

            tmpc = sgVec2Add(tcurr, sgVec2SetLength(sgVec2Sub(tcurr, light->pos), winw + winh));
            tmpn = sgVec2Add(tnext, sgVec2SetLength(sgVec2Sub(tnext, light->pos), winw + winh));

            sgDrawVertex2f(tcurr.x, tcurr.y);
            sgDrawVertex2f(tmpc.x, tmpc.y);
            //sgDrawVertex2f(next->x, next->y);

            //sgDrawVertex2f(tmpc.x, tmpc.y);
            sgDrawVertex2f(tmpn.x, tmpn.y);
            sgDrawVertex2f(tnext.x, tnext.y);
        }
        tcurr = tnext;
    }

    sgDrawEnd();
}
