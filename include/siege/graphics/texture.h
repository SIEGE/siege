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
#include "bitmap.h"
#include "../util/stream.h"
#include "../util/ivector.h"
#include "../util/vector.h"

#define SG_WRAP_CURRENT             0x00
#define SG_WRAP_CLAMP               0x01
#define SG_WRAP_CLAMP_TO_EDGE       0x02
#define SG_WRAP_MIRRORED_REPEAT     0x03
#define SG_WRAP_REPEAT              0x04

#define SG_INTERP_CURRENT   0x00
#define SG_INTERP_NEAREST   0x01
#define SG_INTERP_LINEAR    0x02

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

SGTexture* SG_CALL sgTextureCreateBitmap(SGBitmap* bmp, SGbool delbmp);
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

SGIVec2 SG_CALL sgTextureGetSize2iv(SGTexture* texture);
SGVec2 SG_CALL sgTextureGetSize2fv(SGTexture* texture);
SGuint SG_CALL sgTextureGetWidth(SGTexture* texture);
SGuint SG_CALL sgTextureGetHeight(SGTexture* texture);
SGenum SG_CALL sgTextureGetBPP(SGTexture* texture);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TEXTURE_H__
