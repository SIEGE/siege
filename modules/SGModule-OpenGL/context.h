#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "texture.h"
#include "surface.h"

typedef struct ContextData
{
    SGubyte bpp;
    struct TextureData* temp;
    struct SurfaceData* target;

    struct FBOFunctions fbo;
} ContextData;

#endif // __CONTEXT_H__
