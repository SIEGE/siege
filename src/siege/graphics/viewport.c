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

SGViewport* SG_CALL sgViewportCreate4i4f(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey)
{
    SGViewport* viewport = sgViewportCreate();
    if(viewport == NULL)
        return NULL;

    sgViewportSet4i4f(viewport, wposx, wposy, wsizex, wsizey, posx, posy, sizex, sizey);
    return viewport;
}
SGViewport* SG_CALL sgViewportCreate4i(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey)
{
    return sgViewportCreate4i4f(wposx, wposy, wsizex, wsizey, wposx, wposy, wsizex, wsizey);
}
SGViewport* SG_CALL sgViewportCreate(void)
{
    SGViewport* viewport = malloc(sizeof(SGViewport));
    if(viewport == NULL)
        return NULL;

    sgListAppend(_sg_viewList, viewport);
    return viewport;
}
void SG_CALL sgViewportDestroy(SGViewport* viewport)
{
    if(viewport == NULL)
        return;

    sgListRemoveItem(_sg_viewList, viewport);
    free(viewport);
}
void SG_CALL sgViewportSet4i4f(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey)
{
    if(viewport == NULL)
        return;

    viewport->wposx = wposx;
    viewport->wposy = wposy;
    viewport->wsizex = wsizex;
    viewport->wsizey = wsizey;
    viewport->posx = posx;
    viewport->posy = posy;
    viewport->sizex = sizex;
    viewport->sizey = sizey;
    sgViewportReset(viewport);
}
void SG_CALL sgViewportSet4i(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey)
{
    sgViewportSet4i4f(viewport, wposx, wposy, wsizex, wsizey, wposx, wposy, wsizex, wsizey);
}
void SG_CALL sgViewportReset(SGViewport* viewport)
{
    if(viewport == NULL)
        return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(viewport->wposx, viewport->wposy, viewport->wsizex, viewport->wsizey);
    glOrtho(viewport->posx, viewport->posx + viewport->sizex, viewport->posy + viewport->sizey, viewport->posy, 127, -128);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SG_CALL sgViewportSetWPos(SGViewport* viewport, SGuint wposx, SGuint wposy)
{
    viewport->wposx = wposx;
    viewport->wposy = wposy;
    sgViewportReset(viewport);
}
void SG_CALL sgViewportSetWSize(SGViewport* viewport, SGuint wsizex, SGuint wsizey)
{
    viewport->wsizex = wsizex;
    viewport->wsizey = wsizey;
    sgViewportReset(viewport);
}
void SG_CALL sgViewportSetPos(SGViewport* viewport, float posx, float posy)
{
    viewport->posx = posx;
    viewport->posy = posy;
    sgViewportReset(viewport);
}
void SG_CALL sgViewportSetSize(SGViewport* viewport, float sizex, float sizey)
{
    viewport->sizex = sizex;
    viewport->sizey = sizey;
    sgViewportReset(viewport);
}
void SG_CALL sgViewportZoomCentered(SGViewport* viewport, float factor)
{
    float ox = viewport->sizex;
    float oy = viewport->sizey;
    viewport->sizex /= factor;
    viewport->sizey /= factor;
    viewport->posx += ox - viewport->sizex / 2;
    viewport->posy += oy - viewport->sizey / 2;
    sgViewportReset(viewport);
}

SGbool SG_CALL sgViewportInsideWindow(SGViewport* viewport, float x, float y)
{
    return viewport->wposx <= x && viewport->wposx + viewport->wsizex <= x
        && viewport->wposy <= y && viewport->wposy + viewport->wsizey <= y;
}
SGbool SG_CALL sgViewportInsideLocal(SGViewport* viewport, float x, float y)
{
    return viewport->posx <= x && viewport->posx + viewport->sizex <= x
        && viewport->posy <= y && viewport->posy + viewport->sizey <= y;
}

void SG_CALL sgViewportLocalToWindow(SGViewport* viewport, float* wx, float* wy, float lx, float ly)
{
    float tmp;
    if(!wx) wx = &tmp;
    if(!wy) wy = &tmp;

    *wx = (lx + viewport->posx) * viewport->wsizex / viewport->sizex;
    *wy = (ly + viewport->posy) * viewport->wsizey / viewport->sizey;
}
void SG_CALL sgViewportWindowToLocal(SGViewport* viewport, float* lx, float* ly, float wx, float wy)
{
    float tmp;
    if(!lx) lx = &tmp;
    if(!ly) ly = &tmp;

    *lx = viewport->posx + wx * viewport->sizex / viewport->wsizex;
    *ly = viewport->posy + wy * viewport->sizey / viewport->wsizey;
}
