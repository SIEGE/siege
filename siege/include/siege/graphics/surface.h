#ifndef __SIEGE_GRAPHICS_SURFACE_H__
#define __SIEGE_GRAPHICS_SURFACE_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGSurface
{
    void* handle;
} SGSurface;

#ifdef SG_BUILD_LIBRARY
void* _sg_surfTarget;
#endif // SGC_BUILD_LIBRARY

SGbool _sgSurfaceInit();
SGbool _sgSurfaceDeinit();

SGSurface* sgSurfaceCreateFile(char* fname);
SGSurface* sgSurfaceCreateData(SGuint width, SGuint height, SGenum bpp, void* data);
SGSurface* sgSurfaceCreate(SGuint width, SGuint height, SGenum bpp);
void sgSurfaceDestroy(SGSurface* surface);

void sgSurfaceDrawRads3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void sgSurfaceDrawDegs3f2f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float xoffset, float yoffset, float angle);
void sgSurfaceDrawRads3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle);
void sgSurfaceDrawDegs3f2f1f(SGSurface* surface, float x, float y, float z, float xscale, float yscale, float angle);
/*void sgSurfaceDraw(SGSurface* surface, float x, float y, float xscale, float yscale, float angle);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float z, float xscale, float yscale);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float xscale, float yscale);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float z, float angle);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float angle);
void sgSurfaceDraw(SGSurface* surface, float x, float y, float z);
void sgSurfaceDraw(SGSurface* surface, float x, float y);*/
void sgSurfaceDraw(SGSurface* surface);

void sgSurfaceTarget(SGSurface* surface);
void sgSurfaceUntarget(SGSurface* surface);
void sgSurfaceClear4f(SGSurface* surface, float r, float g, float b, float a);
void sgSurfaceClear3f(SGSurface* surface, float r, float g, float b);
void sgSurfaceClear2f(SGSurface* surface, float g, float a);
void sgSurfaceClear1f(SGSurface* surface, float g);
void sgSurfaceClear4ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b, SGubyte a);
void sgSurfaceClear3ub(SGSurface* surface, SGubyte r, SGubyte g, SGubyte b);
void sgSurfaceClear2ub(SGSurface* surface, SGubyte g, SGubyte a);
void sgSurfaceClear1ub(SGSurface* surface, SGubyte g);
void sgSurfaceClear(SGSurface* surface);

void sgSurfaceGetSize(SGSurface* surface, SGuint* width, SGuint* height);
SGuint sgSurfaceGetWidth(SGSurface* surface);
SGuint sgSurfaceGetHeight(SGSurface* surface);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_SURFACE_H__
