#ifndef __SIEGE_GRAPHICS_LOAD_H__
#define __SIEGE_GRAPHICS_LOAD_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmGraphicsLoadFile(char* fname, SGuint* width, SGuint* height, SGuint* bpp, void** data);
    //SGuint SG_EXPORT sgmGraphicsLoadStream(void* stream, SGuint* width, SGuint* height, SGuint* bpp, void** data);
    SGuint SG_EXPORT sgmGraphicsLoadFreeData(void* data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_GRAPHICS_LOAD_H__
