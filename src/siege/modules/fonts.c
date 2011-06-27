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
    _SG_BIND(sgmFontsFaceCreate);
    _SG_BIND(sgmFontsFaceDestroy);
    _SG_BIND(sgmFontsFaceSetHeight);
    //_SG_BIND(sgmFontsFaceGetHeight);

	_SG_BIND(sgmFontsCharsCreate);
    _SG_BIND(sgmFontsCharsFreeData);

	_SG_BIND(sgmFontsConvCreate);
	_SG_BIND(sgmFontsConvDestroy);
	_SG_BIND(sgmFontsConv);
	_SG_BIND(sgmFontsConvFreeData);
}

