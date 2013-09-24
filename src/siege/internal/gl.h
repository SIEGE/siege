#ifndef __SIEGE_INTERNAL_GL_H__
#define __SIEGE_INTERNAL_GL_H__

#if defined(APPLE) || defined(_APPLE) || defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#else   /* not Apple */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#endif  /* Apple */

#ifndef GL_EXT_framebuffer_object
#error "SIEGE requires EXT_framebuffer_object"
#endif /* GL_EXT_framebuffer_object */
PFNGLISRENDERBUFFERPROC                         glIsRenderbufferEXT;
PFNGLBINDRENDERBUFFERPROC                       glBindRenderbufferEXT;
PFNGLDELETERENDERBUFFERSPROC                    glDeleteRenderbuffersEXT;
PFNGLGENRENDERBUFFERSPROC                       glGenRenderbuffersEXT;
PFNGLRENDERBUFFERSTORAGEPROC                    glRenderbufferStorageEXT;
PFNGLGETRENDERBUFFERPARAMETERIVPROC             glGetRenderbufferParameterivEXT;
PFNGLISFRAMEBUFFERPROC                          glIsFramebufferEXT;
PFNGLBINDFRAMEBUFFERPROC                        glBindFramebufferEXT;
PFNGLDELETEFRAMEBUFFERSPROC                     glDeleteFramebuffersEXT;
PFNGLGENFRAMEBUFFERSPROC                        glGenFramebuffersEXT;
PFNGLCHECKFRAMEBUFFERSTATUSPROC                 glCheckFramebufferStatusEXT;
PFNGLFRAMEBUFFERTEXTURE1DPROC                   glFramebufferTexture1DEXT;
PFNGLFRAMEBUFFERTEXTURE2DPROC                   glFramebufferTexture2DEXT;
PFNGLFRAMEBUFFERTEXTURE3DPROC                   glFramebufferTexture3DEXT;
PFNGLFRAMEBUFFERRENDERBUFFERPROC                glFramebufferRenderbufferEXT;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC    glGetFramebufferAttachmentParameterivEXT;
PFNGLGENERATEMIPMAPPROC                         glGenerateMipmapEXT;

#ifndef GL_EXT_blend_minmax
#error "SIEGE requires EXT_blend_minmax"
#endif /* GL_EXT_blend_minmax */
PFNGLBLENDEQUATIONPROC                          glBlendEquationEXT;

#define GLTEX(x) (*(GLuint*)(x)->handle)
#define GLFBO(x) (*(GLuint*)(x)->fboid)
#define GLRB(x) (*(GLuint*)(x)->rbid)

#endif /* __SIEGE_INTERNAL_GL_H__ */
