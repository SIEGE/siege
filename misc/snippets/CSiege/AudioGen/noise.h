#ifndef __NOISE_H__
#define __NOISE_H__

#include "buffer.h"

void paNoiseWhite(Buffer* buffer, float length);
void paNoisePink(Buffer* buffer, float length);
void paNoiseBrown(Buffer* buffer, float length);

#endif // __NOISE_H__
