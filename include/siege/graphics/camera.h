#ifndef __SIEGE_GRAPHICS_CAMERA_H__
#define __SIEGE_GRAPHICS_CAMERA_H__
#include "../common.h"
#include "../util/rect.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct SGCamera
{
    SGRect rect;
    float angle;
} SGCamera;

#ifdef SG_BUILD_LIBRARY
SGCamera* _sg_cameraMain;
SGCamera* _sg_cameraCurr;
#endif // SG_BUILD_LIBRARY

SGbool SG_CALL _sgCameraInit(void);
SGbool SG_CALL _sgCameraDeinit(void);

SGCamera* SG_CALL sgCameraCreateR(SGRect rect, float angle);
void SG_CALL sgCameraDestroy(SGCamera* camera);

void SG_CALL sgCameraSetAngle(SGCamera* camera, float angle);
float SG_CALL sgCameraGetAngle(SGCamera* camera);

void SG_CALL sgCameraSetRect(SGCamera* camera, SGRect rect);
SGRect SG_CALL sgCameraGetRect(SGCamera* camera);

void SG_CALL sgCameraSetPos2fv(SGCamera* camera, SGVec2 pos);
void SG_CALL sgCameraSetPosCenter2fv(SGCamera* camera, SGVec2 pos);
void SG_CALL sgCameraSetSize2fv(SGCamera* camera, SGVec2 size);
void SG_CALL sgCameraSetSizeCenter2fv(SGCamera* camera, SGVec2 size);

void SG_CALL sgCameraUse(SGCamera* camera);

SGbool SG_CALL sgCameraPointInside2fv(SGCamera* camera, SGVec2 point);

// TODO: Rename to Project/Unproject?
SGVec2 SG_CALL sgCameraLocalToNormal2fv(SGCamera* camera, SGVec2 lpoint);
SGVec2 SG_CALL sgCameraNormalToLocal2fv(SGCamera* camera, SGVec2 npoint);

/*
 * semi-DEPRECATED: use sgCameraSetSizeCenter2fv, instead
 * (function will likely be renamed)
 */
void SG_CALL sgCameraZoomCentered(SGCamera* camera, float factor);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_CAMERA_H__
