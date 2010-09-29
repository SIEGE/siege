#define SG_BUILD_LIBRARY
#include <siege/graphics/viewport.h>
#include <siege/core/window.h>
#include <siege/modules/graphics.h>

#include <stdlib.h>

SGbool SG_EXPORT _sgViewportInit(void)
{
    _sg_viewList = sgLinkedListCreate();
    if(_sg_viewList == NULL)
        return SG_FALSE;
    return SG_TRUE;
}

SGbool SG_EXPORT _sgViewportDeinit(void)
{
    SGLinkedNode* node;
    for(node = _sg_viewList->first; node != NULL; node = node->next)
        sgViewportDestroy(node->item);
    sgLinkedListDestroy(_sg_viewList);
    return SG_TRUE;
}

SGViewport* SG_EXPORT sgViewportCreate4i4f(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey)
{
    SGViewport* viewport = sgViewportCreate();
    if(viewport == NULL)
        return NULL;

    sgViewportSet4i4f(viewport, wposx, wposy, wsizex, wsizey, posx, posy, sizex, sizey);
    return viewport;
}
SGViewport* SG_EXPORT sgViewportCreate4i(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey)
{
    return sgViewportCreate4i4f(wposx, wposy, wsizex, wsizey, wposx, wposy, wsizex, wsizey);
}
SGViewport* SG_EXPORT sgViewportCreate(void)
{
    SGViewport* viewport = malloc(sizeof(SGViewport));
    if(viewport == NULL)
        return NULL;

    if(_sg_modGraphics.sgmGraphicsViewportCreate != NULL)
        _sg_modGraphics.sgmGraphicsViewportCreate(viewport->handle, _sg_gfxHandle);
    sgLinkedListAppend(_sg_viewList, viewport);
    return viewport;
}
void SG_EXPORT sgViewportDestroy(SGViewport* viewport)
{
    if(viewport == NULL)
        return;

    if(_sg_modGraphics.sgmGraphicsViewportDestroy != NULL)
        _sg_modGraphics.sgmGraphicsViewportDestroy(viewport->handle);
    sgLinkedListRemoveItem(_sg_viewList, viewport);
    free(viewport);
}
void SG_EXPORT sgViewportSet4i4f(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey)
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
void SG_EXPORT sgViewportSet4i(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey)
{
    sgViewportSet4i4f(viewport, wposx, wposy, wsizex, wsizey, wposx, wposy, wsizex, wsizey);
}
void SG_EXPORT sgViewportReset(SGViewport* viewport)
{
    if(viewport == NULL)
        return;
    if(_sg_modGraphics.sgmGraphicsViewportSetView != NULL)
        _sg_modGraphics.sgmGraphicsViewportSetView(viewport->handle, viewport->wposx, viewport->wposy, viewport->wsizex, viewport->wsizey, viewport->posx, viewport->posy, viewport->sizex, viewport->sizey);
}
