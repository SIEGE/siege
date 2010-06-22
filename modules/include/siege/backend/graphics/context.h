#ifndef __SIEGE_GRAPHICS_CONTEXT_H__
#define __SIEGE_GRAPHICS_CONTEXT_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmGraphicsContextCreate(void** context, SGuint width, SGuint height, SGuint bpp);
    SGuint SG_EXPORT sgmGraphicsContextDestroy(void* context);
    SGuint SG_EXPORT sgmGraphicsContextResize(void* context, SGuint width, SGuint height);
    //SGuint SG_EXPORT sgmGraphicsContextClear(void* context);
    SGuint SG_EXPORT sgmGraphicsContextClearColor(void* context, float* color);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_CONTEXT_H__
