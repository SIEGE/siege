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

#ifndef __SIEGE_GRAPHICS_SURFACE_H__
#define __SIEGE_GRAPHICS_SURFACE_H__

#include "../common.h"
#include "texture.h"
#include "../util/stream.h"
#include "../util/ivector.h"
#include "../util/vector.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGSurface
{
    void* fboid;
    void* rbid;
    SGTexture* texture;
    SGbool deltex;
} SGSurface;

SGbool SG_CALL _sgSurfaceInit(void);
SGbool SG_CALL _sgSurfaceDeinit(void);

SGSurface* SG_CALL sgSurfaceCreateBitmap(SGBitmap* bmp, SGbool delbmp);
SGSurface* SG_CALL sgSurfaceCreateStream(SGStream* stream, SGbool delstream);
SGSurface* SG_CALL sgSurfaceCreateFile(const char* fname);
SGSurface* SG_CALL sgSurfaceCreateData(SGuint width, SGuint height, SGenum bpp, void* data);
SGSurface* SG_CALL sgSurfaceCreateTexture(SGTexture* texture, SGbool deltex);
SGSurface* SG_CALL sgSurfaceCreate(SGuint width, SGuint height, SGenum bpp);
void SG_CALL sgSurfaceDestroy(SGSurface* surface);

SGbool SG_CALL sgSurfaceSetTexture(SGSurface* surface, SGTexture* texture, SGbool deltex);
SGTexture* SG_CALL sgSurfaceGetTexture(SGSurface* surface);

void SG_CALL sgSurfaceSetData(SGSurface* surface, size_t width, size_t height, SGenum bpp, void* data);
void SG_CALL sgSurfaceSetSubData(SGSurface* surface, size_t x, size_t y, size_t width, size_t height, SGenum bpp, void* data);
void* SG_CALL sgSurfaceGetData(SGSurface* surface);
void SG_CALL sgSurfaceFreeData(void* data);

void SG_CALL sgSurfaceDrawRads3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_CALL sgSurfaceDrawDegs3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_CALL sgSurfaceDrawRads2f2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_CALL sgSurfaceDrawDegs2f2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset, float angle);
void SG_CALL sgSurfaceDrawRads3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle);
void SG_CALL sgSurfaceDrawDegs3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle);
void SG_CALL sgSurfaceDrawRads2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float angle);
void SG_CALL sgSurfaceDrawDegs2f2f1f(SGSurface* surface, float x, float y, float xscale, float yscale, float angle);
void SG_CALL sgSurfaceDrawRads3f1f(SGSurface* surface, float x, float y, float z, float angle);
void SG_CALL sgSurfaceDrawDegs3f1f(SGSurface* surface, float x, float y, float z, float angle);
void SG_CALL sgSurfaceDrawRads2f1f(SGSurface* surface, float x, float y, float angle);
void SG_CALL sgSurfaceDrawDegs2f1f(SGSurface* surface, float x, float y, float angle);
void SG_CALL sgSurfaceDraw3f2f2f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset);
void SG_CALL sgSurfaceDraw2f2f2f(SGSurface* surface, float x, float y, float xscale, float yscale, float xoffset, float yoffset);
void SG_CALL sgSurfaceDraw3f2f(SGSurface* surface, float x, float y, float z, float xscale, float yscale);
void SG_CALL sgSurfaceDraw2f2f(SGSurface* surface, float x, float y, float xscale, float yscale);
void SG_CALL sgSurfaceDraw3f(SGSurface* surface, float x, float y, float z);
void SG_CALL sgSurfaceDraw2f(SGSurface* surface, float x, float y);
void SG_CALL sgSurfaceDraw(SGSurface* surface);

void SG_CALL sgSurfaceTarget(SGSurface* surface);
void SG_CALL sgSurfaceUntarget(SGSurface* surface);
void SG_CALL sgSurfaceClear4f(SGSurface* surface, float r, float g, float b, float a);
void SG_CALL sgSurfaceClear3f(SGSurface* surface, float r, float g, float b);
void SG_CALL sgSurfaceClear2f(SGSurface* surface, float g, float a);
void SG_CALL sgSurfaceClear1f(SGSurface* surface, float g);
void SG_CALL sgSurfaceClear4ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b, SGubyte a);
void SG_CALL sgSurfaceClear3ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b);
void SG_CALL sgSurfaceClear2ub(SGSurface* surface, SGubyte g, SGubyte a);
void SG_CALL sgSurfaceClear1ub(SGSurface* surface, SGubyte g);
void SG_CALL sgSurfaceClear(SGSurface* surface);

SGIVec2 SG_CALL sgSurfaceGetSize2iv(SGSurface* surface);
SGVec2 SG_CALL sgSurfaceGetSize2fv(SGSurface* surface);
SGuint SG_CALL sgSurfaceGetWidth(SGSurface* surface);
SGuint SG_CALL sgSurfaceGetHeight(SGSurface* surface);
SGenum SG_CALL sgSurfaceGetBPP(SGSurface* surface);

/* DEPRECATED */
void SG_CALL SG_HINT_DEPRECATED sgSurfaceGetSize(SGSurface* surface, SGuint* width, SGuint* height);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_SURFACE_H__
