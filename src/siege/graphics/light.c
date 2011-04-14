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
    _sg_shadowShapes = sgListCreate();

    return SG_TRUE;
}
SGbool SG_EXPORT _sgLightDeinit(void)
{
    SGListNode* node;
    for(node = _sg_shadowShapes->first; node != NULL; node = node->next)
        sgShadowShapeDestroy(node->item);

    sgListDestroy(_sg_shadowShapes);

    return SG_TRUE;
}

SGLight* SG_EXPORT sgLightCreate(float x, float y, float radius)
{
    SGLight* light = malloc(sizeof(SGLight));
    if(light == NULL)
        return NULL;

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
void SG_EXPORT sgLightDrawShadows(SGLight* light)
{
    SGListNode* node;
    for(node = _sg_shadowShapes->first; node != NULL; node = node->next)
        sgShadowShapeCast(node->item, light);
}

void SG_EXPORT sgLightDrawDBG(SGLight* light)
{
    sgDrawColor4f(1.0, 1.0, 0.0, 1.0);
    sgDrawCircle(light->pos.x, light->pos.y, light->radius, SG_FALSE);
}
void SG_EXPORT sgLightDrawShadowsDBG(SGLight* light)
{
    SGListNode* node;
    for(node = _sg_shadowShapes->first; node != NULL; node = node->next)
        sgShadowShapeCastDBG(node->item, light);
}

SGShadowShape* SG_EXPORT sgShadowShapeCreate(SGenum type)
{
    SGShadowShape* shape = malloc(sizeof(SGShadowShape));
    if(shape == NULL)
        return NULL;

    shape->node = sgListAppend(_sg_shadowShapes, shape);

    shape->type = type;
    shape->pos = sgVec2f(SG_NAN, SG_NAN);

    shape->depth = 0.0;

    shape->angle = 0.0;

    shape->numverts = 0;
    shape->verts = NULL;

    return shape;
}
SGShadowShape* SG_EXPORT sgShadowShapeCreateSegment(float x1, float y1, float x2, float y2)
{
    SGShadowShape* shape = sgShadowShapeCreate(SG_SHADOW_SHAPE_SEGMENT);
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
SGShadowShape* SG_EXPORT sgShadowShapeCreatePoly(float x, float y, float* verts, size_t numverts)
{
    SGShadowShape* shape = sgShadowShapeCreate(SG_SHADOW_SHAPE_POLYGON);
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
SGShadowShape* SG_EXPORT sgShadowShapeCreateCircle(float x, float y, float radius)
{
    SGShadowShape* shape = sgShadowShapeCreate(SG_SHADOW_SHAPE_SEGMENT);
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

    sgListRemoveNode(_sg_shadowShapes, shape->node);

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

void SG_EXPORT sgShadowShapeDrawDBG(SGShadowShape* shape)
{
    if(shape == NULL)
        return;

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
            sgDrawCircle(shape->pos.x, shape->pos.y, shape->verts[0].x, SG_FALSE);
            break;
    }
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
