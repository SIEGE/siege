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

#ifndef __SIEGE_MODULES_FONTS_H__
#define __SIEGE_MODULES_FONTS_H__
#include "../common.h"
#include "../util/link.h"
#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGModuleFonts
{
    /// Fonts
    SGuint SG_EXPORT (*sgmFontsFaceCreate)(void** face, const char* fname);
    SGuint SG_EXPORT (*sgmFontsFaceDestroy)(void* face);
    SGuint SG_EXPORT (*sgmFontsFaceSetHeight)(void* face, float height);
    //SGuint SG_EXPORT (*sgmFontsFaceGetHeight)(void* face, float* height);
    SGuint SG_EXPORT (*sgmFontsCharsCreate)(void* face,
                SGdchar* chars, SGuint charnum,
                float* width, float* height,
                float* prex, float* prey,
                float* postx, float* posty,
                SGuint* datawidth, SGuint* dataheight, void** data);
    SGuint SG_EXPORT (*sgmFontsCharsFreeData)(void* data);
} SGModuleFonts;

#ifdef SG_BUILD_LIBRARY
SGModuleFonts _sg_modFonts;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sgModuleLoadFonts(SGLibrary* lib);

SGModuleFonts* SG_EXPORT sgModuleGetFonts(void);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // __SIEGE_MODULES_FONTS_H__
