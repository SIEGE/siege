#define SG_BUILD_LIBRARY
#include <siege/graphics/camera.h>

#include <stdlib.h>

#include "../internal/gl.h"

SGbool SG_CALL _sgCameraInit(void)
{
    return SG_TRUE;
}
SGbool SG_CALL _sgCameraDeinit(void)
{
    return SG_TRUE;
}

SGCamera* SG_CALL sgCameraCreateR(SGRect rect, float angle)
{
    SGCamera* camera = malloc(sizeof(SGCamera));
    if(!camera) return NULL;
    camera->rect = rect;
    camera->angle = angle;
    return camera;
}
void SG_CALL sgCameraDestroy(SGCamera* camera)
{
    if(!camera) return;
    free(camera);
}

void SG_CALL sgCameraSetAngle(SGCamera* camera, float angle)
{
    camera->angle = angle;
}
float SG_CALL sgCameraGetAngle(SGCamera* camera)
{
    return camera->angle;
}

void SG_CALL sgCameraSetRect(SGCamera* camera, SGRect rect)
{
    camera->rect = rect;
}
SGRect SG_CALL sgCameraGetRect(SGCamera* camera)
{
    return camera->rect;
}

void SG_CALL sgCameraSetPos2fv(SGCamera* camera, SGVec2 pos)
{
    camera->rect = sgRect2fvWH(pos, sgRectSize(camera->rect));
}
void SG_CALL sgCameraSetPosCenter2fv(SGCamera* camera, SGVec2 pos)
{
    SGVec2 size = sgRectSize(camera->rect);
    camera->rect = sgRect2fvWH(sgVec2Sub(pos, sgVec2Divf(size, 2)), size);
}
void SG_CALL sgCameraSetSize2fv(SGCamera* camera, SGVec2 size)
{
    camera->rect = sgRect2fvWH(camera->rect.a, size);
}
/*void SG_CALL sgCameraSetSizeCenter2fv(SGCamera* camera, SGVec2 size)
{
    SGVec2 pos = camera->rect.a;
    // TODO
}*/

void SG_CALL sgCameraUse(SGCamera* camera);
