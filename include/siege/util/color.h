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

void SG_CALL _sgColorPreprocess(char* buf, size_t buflen, const char* name);
SGColor SG_CALL _sgColorValue(const char* name, SGubyte flag);

SGColor SG_CALL sgColor4f(float r, float g, float b, float a);
SGColor SG_CALL sgColor3f(float r, float g, float b);
SGColor SG_CALL sgColor2f(float g, float a);
SGColor SG_CALL sgColor1f(float g);
SG_EXPORT SGColor SG_CALL sgColor4fp(const float* rgba);
SG_EXPORT SGColor SG_CALL sgColor3fp(const float* rgb);
SG_EXPORT SGColor SG_CALL sgColor2fp(const float* ga);
SG_EXPORT SGColor SG_CALL sgColor1fp(const float* g);
SGColor SG_CALL sgColor4ub(SGubyte r, SGubyte g, SGubyte b, SGubyte a);
SGColor SG_CALL sgColor3ub(SGubyte r, SGubyte g, SGubyte b);
SGColor SG_CALL sgColor2ub(SGubyte g, SGubyte a);
SGColor SG_CALL sgColor1ub(SGubyte g);
SG_EXPORT SGColor SG_CALL sgColor4ubp(const SGubyte* rgba);
SG_EXPORT SGColor SG_CALL sgColor3ubp(const SGubyte* rgb);
SG_EXPORT SGColor SG_CALL sgColor2ubp(const SGubyte* ga);
SG_EXPORT SGColor SG_CALL sgColor1ubp(const SGubyte* g);
SGColor SG_CALL sgColorRGBA(SGuint color);
SGColor SG_CALL sgColorBGRA(SGuint color);
SGColor SG_CALL sgColorARGB(SGuint color);
SGColor SG_CALL sgColorABGR(SGuint color);
SGColor SG_CALL sgColorRGB(SGuint color);
SGColor SG_CALL sgColorBGR(SGuint color);
SGColor SG_CALL sgColorX11(const char* name);
SGColor SG_CALL sgColorWeb(const char* name);
SGColor SG_CALL sgColorNan(void);

SGbool SG_CALL sgColorIsNan(SGColor c);

SGColor SG_CALL sgColorMix(SGColor a, SGColor b, float t);
SGColor SG_CALL sgColorAdd(SGColor a, SGColor b);
SGColor SG_CALL sgColorSub(SGColor a, SGColor b);
SGColor SG_CALL sgColorMul(SGColor a, SGColor b);
SGColor SG_CALL sgColorDiv(SGColor a, SGColor b);

void SG_CALL sgColorTo4ub(SGColor c, SGubyte* r, SGubyte* g, SGubyte* b, SGubyte* a);
void SG_CALL sgColorTo4ubv(SGColor c, SGubyte* rgba);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_COLOR_H__
