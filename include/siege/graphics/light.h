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
#include "../util/rcount.h"
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
    SGRCount cnt;

    SGSurface* buffer;
    SGSurface* lbuffer;
    SGList lights;
    SGList shapes;
    SGColor ambience;
} SGLightSpace;

typedef struct SGLight
{
    SGRCount cnt;

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
    SGRCount cnt;

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

SGbool SG_CALL _sgLightInit(void);
SGbool SG_CALL _sgLightDeinit(void);

void SG_CALL _sgLightSpaceAddLight(SGLightSpace* space, SGLight* light);
void SG_CALL _sgLightSpaceAddShadowShape(SGLightSpace* space, SGShadowShape* shape);
void SG_CALL _sgLightSpaceRemoveLight(SGLightSpace* space, SGLight* light);
void SG_CALL _sgLightSpaceRemoveShadowShape(SGLightSpace* space, SGShadowShape* shape);


SGLightSpace* SG_CALL sgLightSpaceCreate(SGuint width, SGuint height);
void SG_CALL sgLightSpaceForceDestroy(SGLightSpace* space);

void SG_CALL sgLightSpaceRelease(SGLightSpace* space);
void SG_CALL sgLightSpaceLock(SGLightSpace* space);
void SG_CALL sgLightSpaceUnlock(SGLightSpace* space);

/*
 * TODO: Should this set the ambience to 1.0f and premultiply the rest?
 * The problem is that any other (= non-1.0f) setting makes the lights blow up.
 */
void SG_CALL sgLightSpaceSetAmbience4f(SGLightSpace* space, float r, float g, float b, float a);

SGSurface* SG_CALL sgLightSpaceGetBuffer(SGLightSpace* space);

void SG_CALL sgLightSpaceResize(SGLightSpace* space, SGuint width, SGuint height);
/* TODO: Have an offset in the Update function, to track the camera */
void SG_CALL sgLightSpaceUpdate(SGLightSpace* space);
void SG_CALL sgLightSpaceDraw(SGLightSpace* space, SGenum flags);
void SG_CALL sgLightSpaceDrawDBG(SGLightSpace* space, SGenum flags);

SGLight* SG_CALL sgLightCreate(SGLightSpace* space, float x, float y, float radius);
void SG_CALL sgLightForceDestroy(SGLight* light);

void SG_CALL sgLightRelease(SGLight* light);
void SG_CALL sgLightLock(SGLight* light);
void SG_CALL sgLightUnlock(SGLight* light);

void SG_CALL sgLightSetPos(SGLight* light, float x, float y);
void SG_CALL sgLightSetPosX(SGLight* light, float x);
void SG_CALL sgLightSetPosY(SGLight* light, float y);

void SG_CALL sgLightGetPos(SGLight* light, float* x, float* y);
float SG_CALL sgLightGetPosX(SGLight* light);
float SG_CALL sgLightGetPosY(SGLight* light);

void SG_CALL sgLightSetRadius(SGLight* light, float radius);
float SG_CALL sgLightGetRadius(SGLight* light);

void SG_CALL sgLightSetColor4f(SGLight* light, float r, float g, float b, float a);
void SG_CALL sgLightSetColor3f(SGLight* light, float r, float g, float b);
void SG_CALL sgLightSetColor2f(SGLight* light, float g, float a);
void SG_CALL sgLightSetColor1f(SGLight* light, float g);

void SG_CALL sgLightSetColor4ub(SGLight* light, SGubyte r, SGubyte g, SGubyte b, SGubyte a);
void SG_CALL sgLightSetColor3ub(SGLight* light, SGubyte r, SGubyte g, SGubyte b);
void SG_CALL sgLightSetColor2ub(SGLight* light, SGubyte g, SGubyte a);
void SG_CALL sgLightSetColor1ub(SGLight* light, SGubyte g);

void SG_CALL sgLightSetDepth(SGLight* light, float depth);
float SG_CALL sgLightGetDepth(SGLight* light);

void SG_CALL sgLightSetHeight(SGLight* light, float height);
float SG_CALL sgLightGetHeight(SGLight* light);

void SG_CALL sgLightSetActive(SGLight* light, SGbool active);
SGbool SG_CALL sgLightGetActive(SGLight* light);

void SG_CALL sgLightSetStatic(SGLight* light, SGbool stat);
SGbool SG_CALL sgLightGetStatic(SGLight* light);

void SG_CALL sgLightSetShadow(SGLight* light, SGbool shadow);
SGbool SG_CALL sgLightGetShadow(SGLight* light);

void SG_CALL sgLightSetAngleRads(SGLight* light, float rads);
float SG_CALL sgLightGetAngleRads(SGLight* light);

void SG_CALL sgLightSetAngleDegs(SGLight* light, float degs);
float SG_CALL sgLightGetAngleDegs(SGLight* light);

void SG_CALL sgLightSetConeRads(SGLight* light, float rads);
float SG_CALL sgLightGetConeRads(SGLight* light);

void SG_CALL sgLightSetConeDegs(SGLight* light, float degs);
float SG_CALL sgLightGetConeDegs(SGLight* light);

void SG_CALL sgLightDraw(SGLight* light);

void SG_CALL sgLightDrawDBG(SGLight* light);

SGShadowShape* SG_CALL sgShadowShapeCreate(SGLightSpace* space, SGenum type);
SGShadowShape* SG_CALL sgShadowShapeCreateSegment(SGLightSpace* space, float x1, float y1, float x2, float y2);
SGShadowShape* SG_CALL sgShadowShapeCreatePoly(SGLightSpace* space, float x, float y, float* verts, size_t numverts);
SGShadowShape* SG_CALL sgShadowShapeCreateCircle(SGLightSpace* space, float x, float y, float radius);
void SG_CALL sgShadowShapeForceDestroy(SGShadowShape* shape);

void SG_CALL sgShadowShapeRelease(SGShadowShape* shape);
void SG_CALL sgShadowShapeLock(SGShadowShape* shape);
void SG_CALL sgShadowShapeUnlock(SGShadowShape* shape);

void SG_CALL sgShadowShapeSetDepth(SGShadowShape* shape, float depth);
float SG_CALL sgShadowShapeGetDepth(SGShadowShape* shape);

void SG_CALL sgShadowShapeSetActive(SGShadowShape* shape, SGbool active);
SGbool SG_CALL sgShadowShapeGetActive(SGShadowShape* shape);

void SG_CALL sgShadowShapeSetStatic(SGShadowShape* shape, SGbool stat);
SGbool SG_CALL sgShadowShapeGetStatic(SGShadowShape* shape);

void SG_CALL sgShadowShapeDrawDBG(SGShadowShape* shape, SGbool fill);

void SG_CALL sgShadowShapeCast(SGShadowShape* shape, SGLight* light);
void SG_CALL sgShadowShapeCastDBG(SGShadowShape* shape, SGLight* light);

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgLightSpaceDestroy(SGLightSpace* space);
void SG_CALL SG_HINT_DEPRECATED sgLightDestroy(SGLight* light);
void SG_CALL SG_HINT_DEPRECATED sgShadowShapeDestroy(SGShadowShape* shape);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_LIGHT_H__
