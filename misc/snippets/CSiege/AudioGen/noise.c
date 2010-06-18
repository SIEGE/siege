#include "common.h"
#include "noise.h"

#include "normalize.h"

void paNoiseWhite(Buffer* buffer, float length)
{
    buffer->length = length;
    buffer->slength = (size_t)(length * buffer->context->frequency);
    buffer->data = realloc(buffer->data, buffer->slength * sizeof(float));

    size_t i;
    for(i = 0; i < buffer->slength; i++)
        buffer->data[i] = rand() / (float)RAND_MAX * 2 - 1;
}
// todo: do this...
void paNoisePink(Buffer* buffer, float length)
{
}
// todo: way too silent...
void paNoiseBrown(Buffer* buffer, float length)
{
    buffer->length = length;
    buffer->slength = (size_t)(length * buffer->context->frequency);
    buffer->data = realloc(buffer->data, buffer->slength * sizeof(float));

    if(length == 0)
        return;
    buffer->data[0] = 0;

    float min = 0;
    float max = 0;
    float avg = 0;

    size_t i;
    for(i = 1; i < buffer->slength; i++)
    {
        buffer->data[i] = buffer->data[i-1] + rand() / (float)RAND_MAX
                                            - rand() / (float)RAND_MAX;
        avg += buffer->data[i];
        if(buffer->data[i] < min)
            min = buffer->data[i];
        if(buffer->data[i] > max)
            max = buffer->data[i];
    }
    avg /= buffer->slength;
    _paNormalizeValues(buffer, PA_TRUE, PA_FALSE, min, max, avg);
}
