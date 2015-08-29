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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_CAMERA_H__
