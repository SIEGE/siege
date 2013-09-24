/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_GRAPHICS_TEXTURE_H__
#define __SIEGE_GRAPHICS_TEXTURE_H__

#include "../common.h"
#include "../util/stream.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGTexture
{
    void* handle;
    SGuint width, height;
    SGenum bpp;
} SGTexture;

SGTexture* SG_CALL sgTextureCreateStream(SGStream* stream, SGbool delstream);
SGTexture* SG_CALL sgTextureCreateFile(const char* fname);
SGTexture* SG_CALL sgTextureCreateData(SGuint width, SGuint height, SGenum bpp, void* data);
SGTexture* SG_CALL sgTextureCreate(SGuint width, SGuint height, SGenum bpp);
void SG_CALL sgTextureDestroy(SGTexture* texture);

void SG_CALL sgTextureSetData(SGTexture* texture, size_t width, size_t height, SGenum bpp, void* data);
void SG_CALL sgTextureSetSubData(SGTexture* texture, size_t x, size_t y, size_t width, size_t height, SGenum bpp, void* data);
void* SG_CALL sgTextureGetData(SGTexture* texture);
void SG_CALL sgTextureFreeData(void* data);

void SG_CALL sgTextureDrawRads3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_CALL sgTextureDrawDegs3f2f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_CALL sgTextureDrawRads2f2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_CALL sgTextureDrawDegs2f2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_CALL sgTextureDrawRads3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle);
void SG_CALL sgTextureDrawDegs3f2f1f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float angle);
void SG_CALL sgTextureDrawRads2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float angle);
void SG_CALL sgTextureDrawDegs2f2f1f(SGTexture* texture, float x, float y, float xscale, float yscale, float angle);
void SG_CALL sgTextureDrawRads3f1f(SGTexture* texture, float x, float y, float z, float angle);
void SG_CALL sgTextureDrawDegs3f1f(SGTexture* texture, float x, float y, float z, float angle);
void SG_CALL sgTextureDrawRads2f1f(SGTexture* texture, float x, float y, float angle);
void SG_CALL sgTextureDrawDegs2f1f(SGTexture* texture, float x, float y, float angle);
void SG_CALL sgTextureDraw3f2f2f(SGTexture* texture, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset);
void SG_CALL sgTextureDraw2f2f2f(SGTexture* texture, float x, float y, float xscale, float yscale, float xoffset, float yoffset);
void SG_CALL sgTextureDraw3f2f(SGTexture* texture, float x, float y, float z, float xscale, float yscale);
void SG_CALL sgTextureDraw2f2f(SGTexture* texture, float x, float y, float xscale, float yscale);
void SG_CALL sgTextureDraw3f(SGTexture* texture, float x, float y, float z);
void SG_CALL sgTextureDraw2f(SGTexture* texture, float x, float y);
void SG_CALL sgTextureDraw(SGTexture* texture);

void SG_CALL sgTextureSetWrap(SGTexture* texture, SGenum swrap, SGenum twrap);
void SG_CALL sgTextureSetInterpolation(SGTexture* texture, SGenum interp);

void SG_CALL sgTextureGetSize(SGTexture* texture, SGuint* width, SGuint* height);
SGuint SG_CALL sgTextureGetWidth(SGTexture* texture);
SGuint SG_CALL sgTextureGetHeight(SGTexture* texture);
SGenum SG_CALL sgTextureGetBPP(SGTexture* texture);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TEXTURE_H__
