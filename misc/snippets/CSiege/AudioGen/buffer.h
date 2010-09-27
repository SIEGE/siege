#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "context.h"

#include <stdlib.h>

typedef struct Buffer
{
    struct Context* context;

    size_t flags;

    float length;
    size_t slength;
    float* data;
    char* cdata;
} Buffer;

Buffer* paBufferCreate(Context* context, size_t flags);
void paBufferDestroy(Buffer* buffer);
void paBufferFinalizeS(Buffer* buffer);

#endif // __BUFFER_H__
