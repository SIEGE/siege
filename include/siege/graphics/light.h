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

#ifndef __SIEGE_GRAPHICS_LIGHT_H__
#define __SIEGE_GRAPHICS_LIGHT_H__

#include "../common.h"
#include "../util/list.h"
#include "../util/color.h"
#include "../util/vector.h"
#include "surface.h"
#include "sprite.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define SG_SHADOW_DRAW_ADD 0x00
#define SG_SHADOW_DRAW_MUL 0x01
#define SG_SHADOW_DRAW_SQR 0x02

typedef struct SGLightSpace
{
    SGSurface* buffer;
    SGSurface* lbuffer;
    SGList* lights;
    SGList* shapes;
    SGColor ambience;
} SGLightSpace;

typedef struct SGLight
{
    SGLightSpace* space;
    SGListNode* node;

    SGVec2 pos;
    float radius;
    SGColor color;

    float depth;
    float height;

    SGbool active;
    SGbool stat;
    SGbool shadow;
    SGbool _r1; // reserved

    float angle;
    float cone;
    SGSprite* sprite;
} SGLight;

typedef struct SGShadowShape
{
    SGLightSpace* space;
    SGListNode* node;

    SGenum type;
    SGVec2 pos;

    float depth;

    SGbool active;
    SGbool stat;
    SGbool _r1;
    SGbool _r2;

    float angle;

    size_t numverts;
    SGVec2* verts;
} SGShadowShape;

#ifdef SG_BUILD_LIBRARY
SGLightSpace* _sg_lightSpaceMain;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgLightInit(void);
SGbool SG_EXPORT _sgLightDeinit(void);

void SG_EXPORT _sgLightSpaceAddLight(SGLightSpace* space, SGLight* light);
void SG_EXPORT _sgLightSpaceAddShadowShape(SGLightSpace* space, SGShadowShape* shape);
void SG_EXPORT _sgLightSpaceRemoveLight(SGLightSpace* space, SGLight* light);
void SG_EXPORT _sgLightSpaceRemoveShadowShape(SGLightSpace* space, SGShadowShape* shape);


SGLightSpace* SG_CALL sgLightSpaceCreate(SGuint width, SGuint height);
void SG_EXPORT sgLightSpaceDestroy(SGLightSpace* space);

/*
 * TODO: Should this set the ambience to 1.0f and premultiply the rest?
 * The problem is that any other (= non-1.0f) setting makes the lights blow up.
 */
void SG_EXPORT sgLightSpaceSetAmbience4f(SGLightSpace* space, float r, float g, float b, float a);

SGSurface* SG_EXPORT sgLightSpaceGetBuffer(SGLightSpace* space);

void SG_CALL sgLightSpaceResize(SGLightSpace* space, SGuint width, SGuint height);
/* TODO: Have an offset in the Update function, to track the camera */
void SG_EXPORT sgLightSpaceUpdate(SGLightSpace* space);
void SG_EXPORT sgLightSpaceDraw(SGLightSpace* space, SGenum flags);
void SG_EXPORT sgLightSpaceDrawDBG(SGLightSpace* space, SGenum flags);

SGLight* SG_EXPORT sgLightCreate(SGLightSpace* space, float x, float y, float radius);
void SG_EXPORT sgLightDestroy(SGLight* light);

void SG_EXPORT sgLightSetPos(SGLight* light, float x, float y);
void SG_EXPORT sgLightSetPosX(SGLight* light, float x);
void SG_EXPORT sgLightSetPosY(SGLight* light, float y);

void SG_EXPORT sgLightGetPos(SGLight* light, float* x, float* y);
float SG_EXPORT sgLightGetPosX(SGLight* light);
float SG_EXPORT sgLightGetPosY(SGLight* light);

void SG_EXPORT sgLightSetRadius(SGLight* light, float radius);
float SG_EXPORT sgLightGetRadius(SGLight* light);

void SG_EXPORT sgLightSetColor4f(SGLight* light, float r, float g, float b, float a);
void SG_EXPORT sgLightSetColor3f(SGLight* light, float r, float g, float b);
void SG_EXPORT sgLightSetColor2f(SGLight* light, float g, float a);
void SG_EXPORT sgLightSetColor1f(SGLight* light, float g);

void SG_EXPORT sgLightSetColor4ub(SGLight* light, SGubyte r, SGubyte g, SGubyte b, SGubyte a);
void SG_EXPORT sgLightSetColor3ub(SGLight* light, SGubyte r, SGubyte g, SGubyte b);
void SG_EXPORT sgLightSetColor2ub(SGLight* light, SGubyte g, SGubyte a);
void SG_EXPORT sgLightSetColor1ub(SGLight* light, SGubyte g);

void SG_EXPORT sgLightSetDepth(SGLight* light, float depth);
float SG_EXPORT sgLightGetDepth(SGLight* light);

void SG_EXPORT sgLightSetHeight(SGLight* light, float height);
float SG_EXPORT sgLightGetHeight(SGLight* light);

void SG_EXPORT sgLightSetActive(SGLight* light, SGbool active);
SGbool SG_EXPORT sgLightGetActive(SGLight* light);

void SG_EXPORT sgLightSetStatic(SGLight* light, SGbool stat);
SGbool SG_EXPORT sgLightGetStatic(SGLight* light);

void SG_EXPORT sgLightSetShadow(SGLight* light, SGbool shadow);
SGbool SG_EXPORT sgLightGetShadow(SGLight* light);

void SG_EXPORT sgLightSetAngleRads(SGLight* light, float rads);
float SG_EXPORT sgLightGetAngleRads(SGLight* light);

void SG_EXPORT sgLightSetAngleDegs(SGLight* light, float degs);
float SG_EXPORT sgLightGetAngleDegs(SGLight* light);

void SG_EXPORT sgLightSetConeRads(SGLight* light, float rads);
float SG_EXPORT sgLightGetConeRads(SGLight* light);

void SG_EXPORT sgLightSetConeDegs(SGLight* light, float degs);
float SG_EXPORT sgLightGetConeDegs(SGLight* light);

void SG_EXPORT sgLightDraw(SGLight* light);

void SG_EXPORT sgLightDrawDBG(SGLight* light);

SGShadowShape* SG_EXPORT sgShadowShapeCreate(SGLightSpace* space, SGenum type);
SGShadowShape* SG_EXPORT sgShadowShapeCreateSegment(SGLightSpace* space, float x1, float y1, float x2, float y2);
SGShadowShape* SG_EXPORT sgShadowShapeCreatePoly(SGLightSpace* space, float x, float y, float* verts, size_t numverts);
SGShadowShape* SG_EXPORT sgShadowShapeCreateCircle(SGLightSpace* space, float x, float y, float radius);
void SG_EXPORT sgShadowShapeDestroy(SGShadowShape* shape);

void SG_EXPORT sgShadowShapeSetDepth(SGShadowShape* shape, float depth);
float SG_EXPORT sgShadowShapeGetDepth(SGShadowShape* shape);

void SG_EXPORT sgShadowShapeSetActive(SGShadowShape* shape, SGbool active);
SGbool SG_EXPORT sgShadowShapeGetActive(SGShadowShape* shape);

void SG_EXPORT sgShadowShapeSetStatic(SGShadowShape* shape, SGbool stat);
SGbool SG_EXPORT sgShadowShapeGetStatic(SGShadowShape* shape);

void SG_EXPORT sgShadowShapeDrawDBG(SGShadowShape* shape, SGbool fill);

void SG_EXPORT sgShadowShapeCast(SGShadowShape* shape, SGLight* light);
void SG_EXPORT sgShadowShapeCastDBG(SGShadowShape* shape, SGLight* light);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_LIGHT_H__
