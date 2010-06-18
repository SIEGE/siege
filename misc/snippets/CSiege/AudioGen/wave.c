#include "common.h"
#include "wave.h"

#include "buffer.h"

#include <math.h>

void paWaveSine(Buffer* buffer, float frequency, float length)
{
    buffer->length = length;
    buffer->slength = (size_t)(length * buffer->context->frequency);
    buffer->data = realloc(buffer->data, buffer->slength * sizeof(float));

    size_t i;
    for(i = 0; i < buffer->slength; i++)
        buffer->data[i] = sin(2 * M_PI * i * frequency / buffer->context->frequency);
}
void paWaveSquare(Buffer* buffer, float frequency, float length)
{
    buffer->length = length;
    buffer->slength = (size_t)(length * buffer->context->frequency);
    buffer->data = realloc(buffer->data, buffer->slength * sizeof(float));

    size_t i;
    for(i = 0; i < buffer->slength; i++)
        buffer->data[i] = fmod(i * frequency / buffer->context->frequency, 1.0) >= 0.5 ? 1 : -1;
}
// TODO: does this work?
void paWaveTriangle(Buffer* buffer, float frequency, float length)
{
    buffer->length = length;
    buffer->slength = (size_t)(length * buffer->context->frequency);
    buffer->data = realloc(buffer->data, buffer->slength * sizeof(float));

    size_t i;
    for(i = 0; i < buffer->slength; i++)
    {
        float f = fmod(i * frequency / buffer->context->frequency, 1.0) * 2 - 1;
        buffer->data[i] = (f >= 0) ? f : 1-f;
    }
}
void paWaveSawtooth(Buffer* buffer, float frequency, float length)
{
    buffer->length = length;
    buffer->slength = (size_t)(length * buffer->context->frequency);
    buffer->data = realloc(buffer->data, buffer->slength * sizeof(float));

    size_t i;
    for(i = 0; i < buffer->slength; i++)
        buffer->data[i] = fmod(i * frequency / buffer->context->frequency, 1.0) * 2 - 1;
}
void paWaveSilence(Buffer* buffer, float length)
{
    buffer->length = length;
    buffer->slength = (size_t)(length * buffer->context->frequency);
    buffer->data = realloc(buffer->data, buffer->slength * sizeof(float));

    size_t i;
    for(i = 0; i < buffer->slength; i++)
        buffer->data[i] = 0;
}
