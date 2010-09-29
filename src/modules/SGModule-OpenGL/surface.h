#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "texture.h"

typedef struct SurfaceData
{
    void* context;

    struct TextureData* texture;

    int isFBO;
    GLuint fboid;
} SurfaceData;

#endif // __SURFACE_H__
