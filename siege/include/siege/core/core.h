#ifndef __SIEGE_CORE_H__
#define __SIEGE_CORE_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

SGuint SG_EXPORT sgLoadModules(char** modules);
SGbool SG_EXPORT sgLoadModule(char* name);
SGbool SG_EXPORT sgInit(SGuint width, SGuint height, SGuint bpp, SGenum flags);
SGbool SG_EXPORT sgDeinit(void);

SGint SG_EXPORT sgRun(void);
SGbool SG_EXPORT sgLoop(SGint* code);
void SG_EXPORT sgStop(SGint ret);
SGulong SG_EXPORT sgGetTick(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_H__
