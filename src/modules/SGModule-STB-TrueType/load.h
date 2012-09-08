/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __LOAD_H__
#define __LOAD_H__

#include "stb_truetype.h"

typedef struct FontFace
{
    stbtt_fontinfo info;
    void* buf;
    float height;
} FontFace;

#endif // __LOAD_H__
