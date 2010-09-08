#include "main.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#ifndef GL_FRAMEBUFFER_EXT
#define GL_FRAMEBUFFER_EXT          0
#define GL_COLOR_ATTACHMENT0_EXT    0
#define GL_FRAMEBUFFER_COMPLETE_EXT 0
#endif

void checkFBO(FBOFunctions* fbo)
{
#define CHECK(FBO, NAME)                \
    FBO->NAME = getProcAddress(#NAME);  \
    if(FBO->NAME == NULL)               \
        FBO->hasFBO = 0;

    //GLboolean (*glIsRenderbufferEXT) (GLuint);
    //void (*glBindRenderbufferEXT) (GLenum, GLuint);
    //void (*glDeleteRenderbuffersEXT) (GLsizei, const GLuint *);
    //void (*glGenRenderbuffersEXT) (GLsizei, GLuint *);
    //void (*glRenderbufferStorageEXT) (GLenum, GLenum, GLsizei, GLsizei);
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
    //void (*glFramebufferRenderbufferEXT) (GLenum, GLenum, GLenum, GLuint);
    //void (*glGetFramebufferAttachmentParameterivEXT) (GLenum, GLenum, GLenum, GLint *);
    //void (*glGenerateMipmapEXT) (GLenum);
#undef CHECK
}
void* getProcAddress(const char* name)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    return wglGetProcAddress(name);
#else
    // a rather ugly hack with the casting... but it works
    return (void*)(size_t)glXGetProcAddress((const GLubyte*)name);
#endif
}

SGuint higherPower(SGuint num)
{
    SGuint ret = 2;
    while(ret < num)
        ret <<= 1;
    return ret;
}

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_INTERFACE_VMAJOR;
    (*minfo)->vminor = SG_INTERFACE_VMINOR;
    (*minfo)->vpatch = SG_INTERFACE_VPATCH;

    // unknown version
    (*minfo)->mmajor = 0;
    (*minfo)->mminor = 0;
    (*minfo)->mpatch = 0;
    (*minfo)->type = SG_MODULE_GRAPHICS;
    (*minfo)->name = "OpenGL";

    return SG_OK;
}

SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    if(minfo == NULL)
        return SG_OK; // SG_INVALID_VALUE

    free(minfo);
    return SG_OK;
}

//SGuint SG_EXPORT sgmModuleFree(void* data)

SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we'll let the core module decide for us...
    return SG_OK;
}

