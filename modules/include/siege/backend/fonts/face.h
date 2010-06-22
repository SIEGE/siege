#ifndef __SIEGE_FONTS_FACE_H__
#define __SIEGE_FONTS_FACE_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgFontsFaceCreate(void** face, char* fname);
    SGuint SG_EXPORT sgFontsFaceDestroy(void* face);
    SGuint SG_EXPORT sgFontsFaceSetHeight(void* face, float height);
    //SGuint SG_EXPORT sgFontsFaceGetHeight(void* face, float* height);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_FONTS_FACE_H__
