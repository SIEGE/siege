#ifndef __NORMALIZE_H__
#define __NORMALIZE_H__

#include "common.h"
#include "buffer.h"

void _paNormalizeValues(Buffer* buffer, PAbool zero, PAbool minmax, float min, float max, float avg);
void _paNormalizeMinMax(Buffer* buffer, float* min, float* max, float* avg);
void paNormalize(Buffer* buffer, PAbool zero, PAbool minmax);

#endif // __NORMALIZE_H__
