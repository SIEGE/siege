#ifndef __MAIN_H__
#define __MAIN_H__

#include <siege/siege.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

typedef struct FBOFunctions
{
    int hasFBO;

    //GLboolean (*glIsRenderbufferEXT) (GLuint);
    //void (*glBindRenderbufferEXT) (GLenum, GLuint);
    //void (*glDeleteRenderbuffersEXT) (GLsizei, const GLuint *);
    //void (*glGenRenderbuffersEXT) (GLsizei, GLuint *);
    //void (*glRenderbufferStorageEXT) (GLenum, GLenum, GLsizei, GLsizei);
    //void (*glGetRenderbufferParameterivEXT) (GLenum, GLenum, GLint *);
    //GLboolean (*glIsFramebufferEXT) (GLuint);
    GLboolean (*glIsFramebufferEXT) (GLuint);
    void (*glBindFramebufferEXT) (GLenum, GLuint);
    void (*glDeleteFramebuffersEXT) (GLsizei, const GLuint *);
    void (*glGenFramebuffersEXT) (GLsizei, GLuint *);
    GLenum (*glCheckFramebufferStatusEXT) (GLenum);
    //void (*glFramebufferTexture1DEXT) (GLenum, GLenum, GLenum, GLuint, GLint);
    void (*glFramebufferTexture2DEXT) (GLenum, GLenum, GLenum, GLuint, GLint);
    //void (*glFramebufferTexture3DEXT) (GLenum, GLenum, GLenum, GLuint, GLint, GLint);
    //void (*glFramebufferRenderbufferEXT) (GLenum, GLenum, GLenum, GLuint);
    //void (*glGetFramebufferAttachmentParameterivEXT) (GLenum, GLenum, GLenum, GLint *);
    //void (*glGenerateMipmapEXT) (GLenum);
} FBOFunctions;

void checkFBO(FBOFunctions* fbo);
void* getProcAddress(const char* name);
SGuint higherPower(SGuint num);

#endif // __MAIN_H__
