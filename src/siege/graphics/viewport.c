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
#include <siege/graphics/viewport.h>
#include <siege/core/window.h>

#include <stdlib.h>

#include "../internal/gl.h"

SGbool SG_CALL _sgViewportInit(void)
{
    _sg_viewList = sgListCreate();
    if(_sg_viewList == NULL)
        return SG_FALSE;
    return SG_TRUE;
}
SGbool SG_CALL _sgViewportDeinit(void)
{
    //sgViewportDestroy(_sg_viewMain);
    SGListNode* node;
    SGListNode* next;
    for(node = _sg_viewList->head; node != NULL; node = next)
    {
        next = node->next;
        sgViewportDestroy(node->item);
    }
    sgListDestroy(_sg_viewList);
    return SG_TRUE;
}

SGViewport* SG_CALL sgViewportCreateR(SGCamera* camera, SGIRect rect)
{
    SGViewport* viewport = malloc(sizeof(SGViewport));
    if(!viewport) return NULL;
    viewport->camera = camera;
    viewport->rect = rect;
    return viewport;
}
void SG_CALL sgViewportDestroy(SGViewport* viewport)
{
    if(!viewport) return;
    sgListRemoveItem(_sg_viewList, viewport);
    free(viewport);
}

void SG_CALL sgViewportSetRect(SGViewport* viewport, SGIRect rect)
{
    viewport->rect = rect;
    if(_sg_viewCurr == viewport)
        sgViewportUse(viewport);
}
SGIRect SG_CALL sgViewportGetRect(SGViewport* viewport)
{
    return viewport->rect;
}

void SG_CALL sgViewportSetPos2fv(SGViewport* viewport, SGIVec2 pos)
{
    sgViewportSetRect(viewport, sgIRect2ivWH(pos, sgIRectSize(viewport->rect)));
}
/*void SG_CALL sgViewportSetPosCenter2fv(SGViewport* viewport, SGIVec2 pos)
{
    SGUVec2 size = sgRectSize(viewport->rect);
    sgViewportSetRect(viewport, sgRect2ivWH(sgIVec2Sub(pos, sgIVec2Divf(size, 2)), size));
    //TODO
}*/
void SG_CALL sgViewportSetSize2fv(SGViewport* viewport, SGIVec2 size)
{
    sgViewportSetRect(viewport, sgIRect2ivWH(viewport->rect.a, size));
}
/*void SG_CALL sgViewportSetSizeCenter2fv(SGViewport* viewport, SGVec2 size)
{
    SGUVec2 pos = viewport->rect.a;
    // TODO
}*/

void SG_CALL sgViewportUse(SGViewport* viewport)
{
    if(!viewport) return;
    _sg_viewCurr = viewport;

    glViewport(viewport->rect.a.x, viewport->rect.a.y, viewport->rect.b.x - viewport->rect.a.x, viewport->rect.b.y - viewport->rect.b.x);

    if(viewport->camera)
        sgCameraUse(viewport->camera);
}

SGbool SG_CALL sgViewportPointInside2fv(SGViewport* viewport, SGVec2 point)
{
    return viewport->rect.a.x <= point.x && point.x <= viewport->rect.b.x
        && viewport->rect.a.y <= point.y && point.y <= viewport->rect.b.y;
}

SGVec2 SG_CALL sgViewportNormalToWindow2fv(SGViewport* viewport, SGVec2 npoint)
{
    SGVec2 pos = sgVec2iv(viewport->rect.a);
    SGVec2 size = sgVec2iv(sgIRectSize(viewport->rect));
    // basically Normal->Local without rotation
    return sgVec2Add(pos, sgVec2Mul(npoint, size));
}
SGVec2 SG_CALL sgViewportWindowToNormal2fv(SGViewport* viewport, SGVec2 wpoint)
{
    SGVec2 pos = sgVec2iv(viewport->rect.a);
    SGVec2 size = sgVec2iv(sgIRectSize(viewport->rect));
    // basically Local->Normal without rotation
    return sgVec2Div(sgVec2Sub(wpoint, pos), size);
}

SGVec2 SG_CALL sgViewportLocalToWindow2fv(SGViewport* viewport, SGVec2 lpoint)
{
    SGVec2 npoint = sgCameraLocalToNormal2fv(viewport->camera, lpoint);
    return sgViewportNormalToWindow2fv(viewport, npoint);
}
SGVec2 SG_CALL sgViewportWindowToLocal2fv(SGViewport* viewport, SGVec2 wpoint)
{
    SGVec2 npoint = sgViewportWindowToNormal2fv(viewport, wpoint);
    return sgCameraNormalToLocal2fv(viewport->camera, npoint);
}
