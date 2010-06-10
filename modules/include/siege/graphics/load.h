#ifndef __SIEGE_GRAPHICS_LOAD_H__
#define __SIEGE_GRAPHICS_LOAD_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgGraphicsLoadFile(char* fname, SGuint* width, SGuint* height, SGubyte* bpp, void** data);
    //SGuint SG_EXPORT sgGraphicsLoadStream(void* stream, SGuint* width, SGuint* height, SGubyte* bpp, void** data);
    SGuint SG_EXPORT sgGraphicsLoadFreeData(void* data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_LOAD_H__
