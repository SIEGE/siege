#ifndef __SIEGE_UTIL_COLOR_H__
#define __SIEGE_UTIL_COLOR_H__

#include "../common.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGColor
{
 float r, g, b, a;
} SGColor;

#ifdef SG_BUILD_LIBRARY
size_t _sg_colNum;
SGubyte* _sg_colFlags;
char** _sg_colNames;
SGColor* _sg_colValues;
#endif // SG_BUILD_LIBRARY

SGbool _sgColorInit(void);
SGbool _sgColorDeinit(void);

void _sgColorPreprocess(char* buf, size_t buflen, char* name);
SGColor _sgColorValue(char* name, SGubyte flag);

SGColor sgColor4f(float r, float g, float b, float a);
SGColor sgColor3f(float r, float g, float b);
SGColor sgColor2f(float g, float a);
SGColor sgColor1f(float g);
SGColor sgColor4fv(float* f);
SGColor sgColor3fv(float* f);
SGColor sgColor2fv(float* f);
SGColor sgColor1fv(float* f);
SGColor sgColor4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a);
SGColor sgColor3ub(SGubyte r, SGubyte g, SGubyte b);
SGColor sgColor2ub(SGubyte g, SGubyte a);
SGColor sgColor1ub(SGubyte g);
SGColor sgColor4ubv(SGubyte* ub);
SGColor sgColor3ubv(SGubyte* ub);
SGColor sgColor2ubv(SGubyte* ub);
SGColor sgColor1ubv(SGubyte* ub);
SGColor sgColorRGBA(SGuint color);
SGColor sgColorBGRA(SGuint color);
SGColor sgColorARGB(SGuint color);
SGColor sgColorABGR(SGuint color);
SGColor sgColorRGB(SGuint color);
SGColor sgColorBGR(SGuint color);
SGColor sgColorX11(char* name);
SGColor sgColorWeb(char* name);
SGColor sgColorNan(void);

SGbool sgColorIsNan(SGColor c);

SGColor sgColorMix(SGColor a, SGColor b, float t);
SGColor sgColorAdd1c(SGColor a, SGColor b);
SGColor sgColorSub1c(SGColor a, SGColor b);
SGColor sgColorMul1c(SGColor a, SGColor b);
SGColor sgColorDiv1c(SGColor a, SGColor b);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_COLOR_H__
