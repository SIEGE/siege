#ifndef __SIEGE_CORE_WINDOW_H__
#define __SIEGE_CORE_WINDOW_H__

#include "../modules/window.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifdef SG_BUILD_LIBRARY
char* _sg_winTitle;
void* _sg_winHandle;
void* _sg_gfxHandle;
SGCoreWindowCallbacks _sg_winCallbacks;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sg_cbWindowOpen(void* window);
void SG_EXPORT _sg_cbWindowClose(void* window);
void SG_EXPORT _sg_cbWindowResize(void* window, SGuint width, SGuint height);

SGbool SG_EXPORT _sgWindowInit(void);
SGbool SG_EXPORT _sgWindowDeinit(void);
SGbool SG_EXPORT sgWindowOpen(SGuint width, SGuint height, SGuint bpp, SGenum flags);
SGbool SG_EXPORT sgWindowIsOpened(void);
void SG_EXPORT sgWindowClose(void);

void SG_EXPORT sgWindowSetTitleF(char* format, ...);
void SG_EXPORT sgWindowSetTitleFV(char* format, va_list args);
void SG_EXPORT sgWindowSetTitle(char* title);
char* SG_EXPORT sgWindowGetTitle(void);

void SG_EXPORT sgWindowSetSize(SGuint width, SGuint height);
void SG_EXPORT sgWindowGetSize(SGuint* width, SGuint* height);

void SG_EXPORT sgWindowSetWidth(SGuint width);
SGuint SG_EXPORT sgWindowGetWidth(void);
void SG_EXPORT sgWindowSetHeight(SGuint height);
SGuint SG_EXPORT sgWindowGetHeight(void);

void SG_EXPORT sgWindowSwapBuffers(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_WINDOW_H__
