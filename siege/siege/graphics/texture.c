#define SG_BUILD_LIBRARY
#include <siege/graphics/texture.h>
#include <siege/core/window.h>
#include <siege/modules/graphics.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

SGTexture* sgTextureCreateFile(char* fname)
{
    SGuint width;
    SGuint height;
    SGuint bpp;
    void* data;

    SGuint ret;
    if(_sg_modGraphics.sgmGraphicsLoadFile != NULL)
        ret = _sg_modGraphics.sgmGraphicsLoadFile(fname, &width, &height, &bpp, &data);
    if((_sg_modGraphics.sgmGraphicsLoadFile == NULL) || (ret != SG_OK))
        fprintf(stderr, "Could not load image %s\n", fname);

    SGTexture* texture = sgTextureCreateData(width, height, bpp, data);
    if(_sg_modGraphics.sgmGraphicsLoadFreeData != NULL)
        _sg_modGraphics.sgmGraphicsLoadFreeData(data);
    return texture;
}
SGTexture* sgTextureCreateData(SGuint width, SGuint height, SGenum bpp, void* data)
{
    SGTexture* texture = malloc(sizeof(SGTexture));
    if(texture == NULL)
        return NULL;

    if(data != NULL)
        data = _sgGraphicsToCanvasSize(width, height, bpp, data);

    if(_sg_modGraphics.sgmGraphicsTextureCreate != NULL)
        _sg_modGraphics.sgmGraphicsTextureCreate(&texture->handle, _sg_gfxHandle);
    if(_sg_modGraphics.sgmGraphicsTextureSetData != NULL)
        _sg_modGraphics.sgmGraphicsTextureSetData(texture->handle, width, height, bpp, data);

    // as allocated by _sgGraphicsToCanvasSize (or else it's null, and we don't care)
    free(data);
    return texture;
}
SGTexture* sgTextureCreate(SGuint width, SGuint height, SGenum bpp)
{
    return sgTextureCreateData(width, height, bpp, NULL);
}
void sgTextureDestroy(SGTexture* texture)
{
    if(_sg_modGraphics.sgmGraphicsTextureDestroy != NULL)
        _sg_modGraphics.sgmGraphicsTextureDestroy(texture->handle);
    free(texture);
}

void sgTextureDrawRads3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    if(_sg_modGraphics.sgmGraphicsTextureDraw != NULL)
        _sg_modGraphics.sgmGraphicsTextureDraw(texture->handle, x, y, z, xscale, yscale, xoffset, yoffset, angle);
}
void sgTextureDrawDegs3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, z, xscale, yscale, xoffset, yoffset, angle * M_PI / 180.0);
}
void sgTextureDrawRads3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgTextureDrawRads3f2f2f1f(texture, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
void sgTextureDrawDegs3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle)
{
    sgTextureDrawDegs3f2f2f1f(texture, x, y, z, xscale, yscale, 0.0, 0.0, angle);
}
/*void sgTextureDraw(SGTexture* texture, float x, float y, float xscale, float yscale, float angle);
void sgTextureDraw(SGTexture* texture, float x, float y, float z, float xscale, float yscale);
void sgTextureDraw(SGTexture* texture, float x, float y, float xscale, float yscale);
void sgTextureDraw(SGTexture* texture, float x, float y, float z, float angle);
void sgTextureDraw(SGTexture* texture, float x, float y, float angle);
void sgTextureDraw(SGTexture* texture, float x, float y, float z);
void sgTextureDraw(SGTexture* texture, float x, float y);*/
void sgTextureDraw(SGTexture* texture)
{
    sgTextureDrawRads3f2f2f1f(texture, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void sgTextureGetSize(SGTexture* texture, SGuint* width, SGuint* height)
{
    if((width == NULL) && (height == NULL))
        return;
    SGuint buf;

    // make sure we don't pass any nulls
    if(width == NULL)
        width = &buf;
    if(height == NULL)
        height = &buf;

    if(_sg_modGraphics.sgmGraphicsTextureGetSize != NULL)
        _sg_modGraphics.sgmGraphicsTextureGetSize(texture->handle, width, height);
}
SGuint sgTextureGetWidth(SGTexture* texture)
{
    SGuint width;
    SGuint height;
    if(_sg_modGraphics.sgmGraphicsTextureGetSize != NULL)
        _sg_modGraphics.sgmGraphicsTextureGetSize(texture->handle, &width, &height);
    return width;
}
SGuint sgTextureGetHeight(SGTexture* texture)
{
    SGuint width;
    SGuint height;
    if(_sg_modGraphics.sgmGraphicsTextureGetSize != NULL)
        _sg_modGraphics.sgmGraphicsTextureGetSize(texture->handle, &width, &height);
    return height;
}
