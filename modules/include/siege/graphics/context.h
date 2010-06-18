#ifndef __SIEGE_GRAPHICS_CONTEXT_H__
#define __SIEGE_GRAPHICS_CONTEXT_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgGraphicsContextCreate(void** context, SGuint width, SGuint height, SGuint bpp);
    SGuint SG_EXPORT sgGraphicsContextDestroy(void* context);
    SGuint SG_EXPORT sgGraphicsContextResize(void* context, SGuint width, SGuint height);
    SGuint SG_EXPORT sgGraphicsContextClear(void* context, float* color);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_CONTEXT_H__
