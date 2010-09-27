#include "common.h"
#include "buffer.h"
#include "context.h"

#include <string.h>

Buffer* paBufferCreate(Context* context, size_t flags)
{
    Buffer* buffer = malloc(sizeof(Buffer));

    context->buffers = realloc(context->buffers, (context->numbuffers + 1) * sizeof(Buffer*));
    context->numbuffers++;

    buffer->context = context;
    buffer->flags = flags;

    buffer->length = 0.0f;
    buffer->slength = 0;
    buffer->data = NULL;
    buffer->cdata = NULL;

    return buffer;
}
void paBufferDestroy(Buffer* buffer)
{
    size_t i;
    for(i = 0; i < buffer->context->numbuffers; i++)
        if(buffer->context->buffers[i] == buffer)
        {
            buffer->context->numbuffers--;
            memmove(buffer->context->buffers[i], buffer->context->buffers[i+1], (buffer->context->numbuffers - i) * sizeof(Buffer*));
            buffer->context->buffers = realloc(buffer->context->buffers, buffer->context->numbuffers * sizeof(Buffer*));
            break;
        }

    free(buffer->data);
    free(buffer->cdata);
    free(buffer);
}
void paBufferFinalizeS(Buffer* buffer)
{
    buffer->cdata = realloc(buffer->cdata, buffer->slength * sizeof(int16_t));

    int16_t* ptr = (int16_t*)buffer->cdata;
    size_t i;
    for(i = 0; i < buffer->slength; i++)
        ptr[i] = (int16_t)(buffer->data[i] * 32767);
}
