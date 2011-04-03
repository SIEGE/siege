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

#ifndef __MAIN_H__
#define __MAIN_H__

#include <siege/backend.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#else
#include <GL/glx.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

typedef struct FBOFunctions
{
    int hasFBO;

    //GLboolean (*glIsRenderbufferEXT) (GLuint);
    void GLAPIENTRY (*glBindRenderbufferEXT) (GLenum, GLuint);
    void GLAPIENTRY (*glDeleteRenderbuffersEXT) (GLsizei, const GLuint *);
    void GLAPIENTRY (*glGenRenderbuffersEXT) (GLsizei, GLuint *);
    void GLAPIENTRY (*glRenderbufferStorageEXT) (GLenum, GLenum, GLsizei, GLsizei);
    //void (*glGetRenderbufferParameterivEXT) (GLenum, GLenum, GLint *);
    //GLboolean (*glIsFramebufferEXT) (GLuint);
    GLboolean GLAPIENTRY (*glIsFramebufferEXT) (GLuint);
    void GLAPIENTRY (*glBindFramebufferEXT) (GLenum, GLuint);
    void GLAPIENTRY (*glDeleteFramebuffersEXT) (GLsizei, const GLuint *);
    void GLAPIENTRY (*glGenFramebuffersEXT) (GLsizei, GLuint *);
    GLenum GLAPIENTRY (*glCheckFramebufferStatusEXT) (GLenum);
    //void (*glFramebufferTexture1DEXT) (GLenum, GLenum, GLenum, GLuint, GLint);
    void GLAPIENTRY (*glFramebufferTexture2DEXT) (GLenum, GLenum, GLenum, GLuint, GLint);
    //void (*glFramebufferTexture3DEXT) (GLenum, GLenum, GLenum, GLuint, GLint, GLint);
    void GLAPIENTRY (*glFramebufferRenderbufferEXT) (GLenum, GLenum, GLenum, GLuint);
    //void (*glGetFramebufferAttachmentParameterivEXT) (GLenum, GLenum, GLenum, GLint *);
    //void (*glGenerateMipmapEXT) (GLenum);
} FBOFunctions;

void checkFBO(FBOFunctions* fbo);
void* getProcAddress(const char* name);
SGuint higherPower(SGuint num);

#endif // __MAIN_H__
