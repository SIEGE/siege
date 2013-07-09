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

#include "common.h"

#include <stdlib.h>

#ifndef GL_FRAMEBUFFER_EXT
#define GL_FRAMEBUFFER_EXT          0
#define GL_COLOR_ATTACHMENT0_EXT    0
#define GL_FRAMEBUFFER_COMPLETE_EXT 0
#endif

PROC_HANDLE;

#define CHECK(FBO, NAME)                    \
    FBO->NAME = GET_PROC_ADDRESS(#NAME);    \
    if(FBO->NAME == NULL)                   \
        FBO->hasFBO = 0;

void checkFBO(FBOFunctions* fbo)
{
    //GLboolean (*glIsRenderbufferEXT) (GLuint);
    CHECK(fbo, glBindRenderbufferEXT);
    CHECK(fbo, glDeleteRenderbuffersEXT);
    CHECK(fbo, glGenRenderbuffersEXT);
    CHECK(fbo, glRenderbufferStorageEXT);
    //void (*glGetRenderbufferParameterivEXT) (GLenum, GLenum, GLint *);
    //GLboolean (*glIsFramebufferEXT) (GLuint);
    CHECK(fbo, glIsFramebufferEXT);
    CHECK(fbo, glBindFramebufferEXT);
    CHECK(fbo, glDeleteFramebuffersEXT);
    CHECK(fbo, glGenFramebuffersEXT);
    CHECK(fbo, glCheckFramebufferStatusEXT);
    //void (*glFramebufferTexture1DEXT) (GLenum, GLenum, GLenum, GLuint, GLint);
    CHECK(fbo, glFramebufferTexture2DEXT);
    //void (*glFramebufferTexture3DEXT) (GLenum, GLenum, GLenum, GLuint, GLint, GLint);
    CHECK(fbo, glFramebufferRenderbufferEXT);
    //void (*glGetFramebufferAttachmentParameterivEXT) (GLenum, GLenum, GLenum, GLint *);
    //void (*glGenerateMipmapEXT) (GLenum);
}

SGuint higherPower(SGuint num)
{
    SGuint ret = 2;
    while(ret < num)
        ret <<= 1;
    return ret;
}

SGenum SG_CALL sgmGraphicsInit(void)
{
    INIT_HANDLE();
    return SG_OK;
}
SGenum SG_CALL sgmGraphicsDeinit(void)
{
    DEINIT_HANDLE();
    return SG_OK;
}
