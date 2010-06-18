#include "common.h"
#include "normalize.h"
#include "buffer.h"

#include <math.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
void _paNormalizeValues(Buffer* buffer, PAbool zero, PAbool minmax, float min, float max, float avg)
{
    size_t i;
    for(i = 0; i < buffer->slength; i++)
    {
        buffer->data[i] -= avg;
        buffer->data[i] /= MAX(max - avg, avg - min);
    }

    _paNormalizeMinMax(buffer, &min, &max, &avg);
}
#undef MAX
#undef MIN
void _paNormalizeMinMax(Buffer* buffer, float* min, float* max, float* avg)
{
    *min = HUGE_VAL;
    *max = -HUGE_VAL;
    *avg = 0;

    size_t i;
    for(i = 0; i < buffer->slength; i++)
    {
        *avg += buffer->data[i];
        if(buffer->data[i] < *min)
            *min = buffer->data[i];
        if(buffer->data[i] > *max)
            *max = buffer->data[i];
    }
    *avg /= buffer->slength;
}
void paNormalize(Buffer* buffer, PAbool zero, PAbool minmax)
{
    float min;
    float max;
    float avg;

    _paNormalizeMinMax(buffer, &min, &max, &avg);
    _paNormalizeValues(buffer, zero, minmax, min, max, avg);
}
