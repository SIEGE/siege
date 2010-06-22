#ifndef __SIEGE_GRAPHICS_TEXTURE_H__
#define __SIEGE_GRAPHICS_TEXTURE_H__

#include "../../common.h"

#ifdef SG_LEGACY_API
#    define sgGraphicsTextureCreate sgmGraphicsTextureCreate
//#    define sgGraphicsTextureCreateData sgmGraphicsTextureCreateData
#    define sgGraphicsTextureDestroy sgmGraphicsTextureDestroy
#    define sgGraphicsTextureSetData sgmGraphicsTextureSetData
//#    define sgGraphicsTextureGetData sgmGraphicsTextureGetData
//#    define sgGraphicsTextureFreeData sgmGraphicsTextureFreeData
#    define sgGraphicsTextureGetSize sgmGraphicsTextureGetSize
#    define sgGraphicsTextureDraw sgmGraphicsTextureDraw
#endif // SG_LEGACY_API

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmGraphicsTextureCreate(void** texture, void* context);
    //SGuint SG_EXPORT sgmGraphicsTextureCreateData(void** texture, void* context, SGuint width, SGuint height, SGuint bpp, void* data);
    SGuint SG_EXPORT sgmGraphicsTextureDestroy(void* texture);
    SGuint SG_EXPORT sgmGraphicsTextureSetData(void* texture, SGuint width, SGuint height, SGuint bpp, void* data);
    //SGuint SG_EXPORT sgmGraphicsTextureGetData(void* texture, SGuint* width, SGuint* height, SGuint* bpp, void** data);
    //SGuint SG_EXPORT sgmGraphicsTextureFreeData(void* data);
    SGuint SG_EXPORT sgmGraphicsTextureGetSize(void* texture, SGuint* width, SGuint* height);
    SGuint SG_EXPORT sgmGraphicsTextureDraw(void* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_TEXTURE_H__
