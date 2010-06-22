#ifndef __SIEGE_FONTS_CHARS_H__
#define __SIEGE_FONTS_CHARS_H__

#include "../../common.h"

#ifdef SG_LEGACY_API
#    define sgFontsCharsCreate sgmFontsCharsCreate
#    define sgFontsCharsFreeData sgmFontsCharsFreeData
#endif // SG_LEGACY_API

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmFontsCharsCreate(void* face, SGuint* chars, SGuint charnum, float* width, float* height, float* prex, float* prey, float* postx, float* posty, SGuint* datawidth, SGuint* dataheight, void** data);
    SGuint SG_EXPORT sgmFontsCharsFreeData(void* data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_FONTS_CHARS_H__
