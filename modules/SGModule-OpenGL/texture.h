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
} TextureData;

#endif // __TEXTURE_H__
