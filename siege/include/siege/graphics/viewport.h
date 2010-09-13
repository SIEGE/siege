#ifndef __SIEGE_GRAPHICS_VIEWPORT_H__
#define __SIEGE_GRAPHICS_VIEWPORT_H__
#include "../common.h"
#include "../util/list.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGViewport
{
    void* handle;

    SGuint wposx;
    SGuint wposy;
    SGuint wsizex;
    SGuint wsizey;
    float posx;
    float posy;
    float sizex;
    float sizey;
} SGViewport;

#ifdef SG_BUILD_LIBRARY
SGLinkedList* _sg_viewList;
SGViewport* sgMainViewport;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgViewportInit(void);
SGbool SG_EXPORT _sgViewportDeinit(void);

SGViewport* SG_EXPORT sgViewportCreate4i4f(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey);
SGViewport* SG_EXPORT sgViewportCreate4i(SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey);
SGViewport* SG_EXPORT sgViewportCreate(void);
void SG_EXPORT sgViewportDestroy(SGViewport* viewport);
void SG_EXPORT sgViewportSet4i4f(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey, float posx, float posy, float sizex, float sizey);
void SG_EXPORT sgViewportSet4i(SGViewport* viewport, SGuint wposx, SGuint wposy, SGuint wsizex, SGuint wsizey);
void SG_EXPORT sgViewportReset(SGViewport* viewport);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_VIEWPORT_H__
