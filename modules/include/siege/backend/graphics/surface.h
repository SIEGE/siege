#ifndef __SIEGE_GRAPHICS_SURFACE_H__
#define __SIEGE_GRAPHICS_SURFACE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgGraphicsSurfaceCreate(void** surface, void* context);
    //SGuint SG_EXPORT sgGraphicsSurfaceCreateTexture(void** surface, void* context, void* texture);
    //SGuint SG_EXPORT sgGraphicsSurfaceCreateData(void** surface, void* context, SGuint width, SGuint height, SGuint bpp, void* data);
    SGuint SG_EXPORT sgGraphicsSurfaceDestroy(void* surface);
    SGuint SG_EXPORT sgGraphicsSurfaceSetTexture(void* surface, void* texture);
    SGuint SG_EXPORT sgGraphicsSurfaceGetTexture(void* surface, void** texture);
    SGuint SG_EXPORT sgGraphicsSurfaceSetData(void* surface, SGuint width, SGuint height, SGuint bpp, void* data);
    //SGuint SG_EXPORT sgGraphicsSurfaceGetData(void* surface, SGuint* width, SGuint* height, SGuint* bpp, void** data);
    //SGuint SG_EXPORT sgGraphicsSurfaceFreeData(void* data);
    SGuint SG_EXPORT sgGraphicsSurfaceGetSize(void* surface, SGuint* width, SGuint* height);
    SGuint SG_EXPORT sgGraphicsSurfaceDraw(void* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
    SGuint SG_EXPORT sgGraphicsSurfaceSetTarget(void* surface);
    //SGuint SG_EXPORT sgGraphicsSurfaceGetTarget(void** surface);
    SGuint SG_EXPORT sgGraphicsSurfaceResetTarget(void* surface);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_SURFACE_H__
