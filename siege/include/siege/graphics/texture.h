#ifndef __SIEGE_GRAPHICS_TEXTURE_H__
#define __SIEGE_GRAPHICS_TEXTURE_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGTexture
{
    void* handle;
} SGTexture;

SGTexture* sgTextureCreateFile(char* fname);
SGTexture* sgTextureCreateData(SGuint width, SGuint height, SGenum bpp, void* data);
SGTexture* sgTextureCreate(SGuint width, SGuint height, SGenum bpp);
void sgTextureDestroy(SGTexture* texture);

void sgTextureDrawRads3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void sgTextureDrawDegs3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void sgTextureDrawRads3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle);
void sgTextureDrawDegs3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle);
/*void sgTextureDraw(SGTexture* texture, float x, float y, float xscale, float yscale, float angle);
void sgTextureDraw(SGTexture* texture, float x, float y, float z, float xscale, float yscale);
void sgTextureDraw(SGTexture* texture, float x, float y, float xscale, float yscale);
void sgTextureDraw(SGTexture* texture, float x, float y, float z, float angle);
void sgTextureDraw(SGTexture* texture, float x, float y, float angle);
void sgTextureDraw(SGTexture* texture, float x, float y, float z);
void sgTextureDraw(SGTexture* texture, float x, float y);*/
void sgTextureDraw(SGTexture* texture);

void sgTextureGetSize(SGTexture* texture, SGuint* width, SGuint* height);
SGuint sgTextureGetWidth(SGTexture* texture);
SGuint sgTextureGetHeight(SGTexture* texture);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TEXTURE_H__
