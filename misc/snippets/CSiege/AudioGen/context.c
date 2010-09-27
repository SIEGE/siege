#include "context.h"

Context* paContextCreate(size_t frequency, size_t flags)
{
    Context* context = malloc(sizeof(Context));

    context->frequency = frequency;
    context->flags = flags;
    context->buffers = NULL;
    context->numbuffers = 0;

    return context;
}
void paContextDestroy(Context* context)
{
    // todo: check for autofree flag for buffers
    free(context->buffers);
    free(context);
}
