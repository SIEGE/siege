#ifndef __SIEGE_GRAPHICS_DRAW_H__
#define __SIEGE_GRAPHICS_DRAW_H__

#include "../common.h"
#include "../util/plist.h"
#include "texture.h"

#define _SG_COLOR_OVERLOADS_FUNC(func)                                      \
    void SG_EXPORT func##3f(float r, float g, float b)                      \
    {                                                                       \
        func##4f(r, g, b, 1.0f);                                            \
    }                                                                       \
    void SG_EXPORT func##2f(float g, float a)                               \
    {                                                                       \
        func##4f(g, g, g, a);                                               \
    }                                                                       \
    void SG_EXPORT func##1f(float g)                                        \
    {                                                                       \
        func##4f(g, g, g, 1.0f);                                            \
    }                                                                       \
    void SG_EXPORT func##4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a)    \
    {                                                                       \
        func##4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);           \
    }                                                                       \
    void SG_EXPORT func##3ub(SGubyte r, SGubyte g, SGubyte b)               \
    {                                                                       \
        func##4f(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);                 \
    }                                                                       \
    void SG_EXPORT func##2ub(SGubyte g, SGubyte a)                          \
    {                                                                       \
        func##4f(g / 255.0f, g / 255.0f, g / 255.0f, a / 255.0f);           \
    }                                                                       \
    void SG_EXPORT func##1ub(SGubyte g)                                     \
    {                                                                       \
        func##4f(g / 255.0f, g / 255.0f, g / 255.0f, 1.0f);                 \
    }
#define _SG_COLOR_OVERLOADS_DECL(func)                                    \
    void SG_EXPORT func##3f(float r, float g, float b);                   \
    void SG_EXPORT func##2f(float g, float a);                            \
    void SG_EXPORT func##1f(float g);                                     \
    void SG_EXPORT func##4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a); \
    void SG_EXPORT func##3ub(SGubyte r, SGubyte g, SGubyte b);            \
    void SG_EXPORT func##2ub(SGubyte g, SGubyte a);                       \
    void SG_EXPORT func##1ub(SGubyte g);

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_BUILD_LIBRARY
SGPList* _sg_evList;
SGPList* _sg_cList;
SGenum _sg_drawType;
SGTexture* _sg_drawTexture;
float _sg_drawCurPoint[3];
float _sg_drawCurTexCoord[2];
float _sg_drawCurColor[4];

float* _sg_drawPoints;
float* _sg_drawTexCoords;
float* _sg_drawColors;
SGuint _sg_drawNumPoints;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgDrawInit(void);
SGbool SG_EXPORT _sgDrawDeinit(void);

void SG_EXPORT sgDrawBeginT(SGenum type, SGTexture* texture);
void SG_EXPORT sgDrawBegin(SGenum type);
void SG_EXPORT sgDrawEnd(void);
void SG_EXPORT sgDrawColor4f(float r, float g, float b, float a);
_SG_COLOR_OVERLOADS_DECL(sgDrawColor);
void SG_EXPORT sgDrawTexCoord2f(float x, float y);
void SG_EXPORT sgDrawVertex3f(float x, float y, float z);
void SG_EXPORT sgDrawVertex2f(float x, float y);
void SG_EXPORT sgDrawClear4f(float r, float g, float b, float a);
_SG_COLOR_OVERLOADS_DECL(sgDrawClear);
void SG_EXPORT sgDrawClear(void);

void SG_EXPORT sgDrawPoint(float x, float y);
void SG_EXPORT sgDrawPointSetSize(float size);
//float SG_EXPORT sgDrawPointGetSize(void);

void SG_EXPORT sgDrawLine(float x1, float y1, float x2, float y2);
void SG_EXPORT sgDrawLineSetWidth(float width);
//float SG_EXPORT sgDrawLineGetWidth(void);

void SG_EXPORT sgDrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, SGbool fill);

void SG_EXPORT sgDrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, SGbool fill);

void SG_EXPORT sgDrawRectangle(float x1, float y1, float x2, float y2, SGbool fill);

void SG_EXPORT sgDrawEllipse2R(float x, float y, float rx, float ry, SGbool fill);

void SG_EXPORT sgDrawCircle(float x, float y, float radius, SGbool fill);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_DRAW_H__
