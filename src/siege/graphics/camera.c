#define SG_BUILD_LIBRARY
#include <siege/graphics/camera.h>
#include <siege/util/angle.h>

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
    sgCameraSetRect(camera, sgRect2fvWH(pos, sgRectSize(camera->rect)));
}
void SG_CALL sgCameraSetPosCenter2fv(SGCamera* camera, SGVec2 pos)
{
    SGVec2 size = sgRectSize(camera->rect);
    sgCameraSetRect(camera, sgRect2fvWH(sgVec2Sub(pos, sgVec2Divf(size, 2)), size));
}
void SG_CALL sgCameraSetSize2fv(SGCamera* camera, SGVec2 size)
{
    sgCameraSetRect(camera, sgRect2fvWH(camera->rect.a, size));
}
void SG_CALL sgCameraSetSizeCenter2fv(SGCamera* camera, SGVec2 size)
{
    SGVec2 opos = camera->rect.a;
    SGVec2 osize = sgRectSize(camera->rect);

    SGVec2 pos = sgVec2Add(opos, sgVec2Sub(osize, sgVec2Divf(size, 2)));
    sgCameraSetRect(camera, sgRect2fvWH(pos, size));
}

void SG_CALL sgCameraUse(SGCamera* camera)
{
    _sg_cameraCurr = camera;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    SGVec2 hsize = sgVec2Divf(sgRectSize(camera->rect), 2);

    /* TODO: Reverse a,b for 2nd pair? */
    glOrtho(camera->rect.a.x, camera->rect.b.x, camera->rect.b.y, camera->rect.a.y, 127, -128);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(+hsize.x,+hsize.y, 0);
    glRotatef(sgAngleRadToDeg(camera->angle), 0, 0, 1);
    glTranslatef(-hsize.x,-hsize.y, 0);
}

SGbool SG_CALL sgCameraPointInside2fv(SGCamera* camera, SGVec2 point)
{
    point = sgCameraLocalToNormal2fv(camera, point);
    return camera->rect.a.x <= point.x && point.x <= camera->rect.b.x
        && camera->rect.a.y <= point.y && point.y <= camera->rect.b.y;
}

SGVec2 SG_CALL sgCameraLocalToNormal2fv(SGCamera* camera, SGVec2 lpoint)
{
    // FIXME VERIFY: CHECK IF IT IS `-angle` OR `+angle`
    lpoint = sgVec2RotateRads(lpoint, -camera->angle);

    SGVec2 pos = camera->rect.a;
    SGVec2 size = sgRectSize(camera->rect);
    return sgVec2Div(sgVec2Sub(lpoint, pos), size);
}
SGVec2 SG_CALL sgCameraNormalToLocal2fv(SGCamera* camera, SGVec2 npoint)
{
    SGVec2 pos = camera->rect.a;
    SGVec2 size = sgRectSize(camera->rect);
    npoint = sgVec2Add(pos, sgVec2Mul(npoint, size));

    // FIXME VERIFY: CHECK IF IT IS `-angle` OR `+angle`
    return sgVec2RotateRads(npoint, +camera->angle);
}

/* semi-DEPRECATED */
void SG_CALL sgCameraZoomCentered(SGCamera* camera, float factor)
{
    sgCameraSetSizeCenter2fv(camera, sgVec2Divf(sgRectSize(camera->rect), factor));
}
