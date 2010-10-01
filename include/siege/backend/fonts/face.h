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
