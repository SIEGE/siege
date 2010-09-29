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

#define SG_BUILD_LIBRARY
#include <siege/util/link.h>
#include <siege/modules/modules.h>
#include <siege/modules/fonts.h>

void SG_EXPORT _sgModuleLoadFonts(SGLibrary* lib)
{
    void* fptr;

    /// Fonts
    _SG_BINDS(_sg_modFonts, sgmFontsFaceCreate);
    _SG_BINDS(_sg_modFonts, sgmFontsFaceDestroy);
    _SG_BINDS(_sg_modFonts, sgmFontsFaceSetHeight);
    //_SG_BINDS(_sg_modFonts, sgmFontsFaceGetHeight);
    _SG_BINDS(_sg_modFonts, sgmFontsCharsCreate);
    _SG_BINDS(_sg_modFonts, sgmFontsCharsFreeData);
}

SGModuleFonts* SG_EXPORT sgModuleGetFonts(void)
{
    return &_sg_modFonts;
}
