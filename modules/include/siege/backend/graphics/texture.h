#ifndef __SIEGE_GRAPHICS_TEXTURE_H__
#define __SIEGE_GRAPHICS_TEXTURE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgGraphicsTextureCreate(void** texture, void* context);
    //SGuint SG_EXPORT sgGraphicsTextureCreateData(void** texture, void* context, SGuint width, SGuint height, SGuint bpp, void* data);
    SGuint SG_EXPORT sgGraphicsTextureDestroy(void* texture);
    SGuint SG_EXPORT sgGraphicsTextureSetData(void* texture, SGuint width, SGuint height, SGuint bpp, void* data);
    //SGuint SG_EXPORT sgGraphicsTextureGetData(void* texture, SGuint* width, SGuint* height, SGuint* bpp, void** data);
    //SGuint SG_EXPORT sgGraphicsTextureFreeData(void* data);
    SGuint SG_EXPORT sgGraphicsTextureGetSize(void* texture, SGuint* width, SGuint* height);
    SGuint SG_EXPORT sgGraphicsTextureDraw(void* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_TEXTURE_H__
