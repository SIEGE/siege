/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

typedef struct TextureData
{
    void* context;

    GLuint texid;

    SGuint width, height;
    SGuint awidth, aheight;
    float wratio, hratio;
    SGubyte bpp;
    GLuint glbpp;
	SGenum glformat;
} TextureData;

#endif // __TEXTURE_H__
