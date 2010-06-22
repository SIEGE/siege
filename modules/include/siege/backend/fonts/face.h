#ifndef __SIEGE_BACKEND_FONTS_FACE_H__
#define __SIEGE_BACKEND_FONTS_FACE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmFontsFaceCreate(void** face, char* fname);
    SGuint SG_EXPORT sgmFontsFaceDestroy(void* face);
    SGuint SG_EXPORT sgmFontsFaceSetHeight(void* face, float height);
    //SGuint SG_EXPORT sgmFontsFaceGetHeight(void* face, float* height);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_FONTS_FACE_H__
