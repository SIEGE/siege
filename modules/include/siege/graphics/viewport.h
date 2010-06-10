#ifndef __SIEGE_GRAPHICS_VIEWPORT_H__
#define __SIEGE_GRAPHICS_VIEWPORT_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgGraphicsViewportCreate(void** viewport, void* context);
    //SGuint SG_EXPORT sgGraphicsViewportCreateView(void** viewport, void* context, SGuint wx, SGuint wy, SGuint wwidth, SGuint wheight, float x, float y, float width, float height);
    SGuint SG_EXPORT sgGraphicsViewportDestroy(void* viewport);
    SGuint SG_EXPORT sgGraphicsViewportSetView(void* viewport, SGuint wx, SGuint wy, SGuint wwidth, SGuint wheight, float x, float y, float width, float height);
    //SGuint SG_EXPORT sgGraphicsViewportGetView(void* viewport, SGuint* wx, SGuint* wy, SGuint* wwidth, SGuint* wheight, float* x, float* y, float* width, float* height);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_VIEWPORT_H__
