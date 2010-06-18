#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <stdlib.h>

typedef struct Context
{
    size_t frequency;
    size_t flags;

    struct Buffer** buffers;
    size_t numbuffers;
} Context;

Context* paContextCreate(size_t frequency, size_t flags);
void paContextDestroy(Context* context);

#endif // __CONTEXT_H__
