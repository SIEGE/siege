/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

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

SGTexture* SG_EXPORT sgTextureCreateFile(const char* fname);
SGTexture* SG_EXPORT sgTextureCreateData(SGuint width, SGuint height, SGenum bpp, void* data);
SGTexture* SG_EXPORT sgTextureCreate(SGuint width, SGuint height, SGenum bpp);
void SG_EXPORT sgTextureDestroy(SGTexture* texture);

void SG_EXPORT sgTextureDrawRads3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_EXPORT sgTextureDrawDegs3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_EXPORT sgTextureDrawRads2f2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_EXPORT sgTextureDrawDegs2f2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_EXPORT sgTextureDrawRads3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle);
void SG_EXPORT sgTextureDrawDegs3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle);
void SG_EXPORT sgTextureDrawRads2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float angle);
void SG_EXPORT sgTextureDrawDegs2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float angle);
void SG_EXPORT sgTextureDrawRads3f1f(SGTexture* texture, float x, float y, float z, float angle);
void SG_EXPORT sgTextureDrawDegs3f1f(SGTexture* texture, float x, float y, float z, float angle);
void SG_EXPORT sgTextureDrawRads2f1f(SGTexture* texture, float x, float y, float angle);
void SG_EXPORT sgTextureDrawDegs2f1f(SGTexture* texture, float x, float y, float angle);
void SG_EXPORT sgTextureDraw3f2f2f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset);
void SG_EXPORT sgTextureDraw2f2f2f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset);
void SG_EXPORT sgTextureDraw3f2f(SGTexture* texture, float x, float y, float z, float xscale, float yscale);
void SG_EXPORT sgTextureDraw2f2f(SGTexture* texture, float x, float y, float xscale, float yscale);
void SG_EXPORT sgTextureDraw3f(SGTexture* texture, float x, float y, float z);
void SG_EXPORT sgTextureDraw2f(SGTexture* texture, float x, float y);
void SG_EXPORT sgTextureDraw(SGTexture* texture);

void SG_EXPORT sgTextureGetSize(SGTexture* texture, SGuint* width, SGuint* height);
SGuint SG_EXPORT sgTextureGetWidth(SGTexture* texture);
SGuint SG_EXPORT sgTextureGetHeight(SGTexture* texture);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TEXTURE_H__
