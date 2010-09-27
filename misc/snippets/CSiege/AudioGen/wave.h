#ifndef __WAVE_H__
#define __WAVE_H__

#include "buffer.h"

void paWaveSine(Buffer* buffer, float frequency, float length);
void paWaveSquare(Buffer* buffer, float frequency, float length);
void paWaveTriangle(Buffer* buffer, float frequency, float length);
void paWaveSawtooth(Buffer* buffer, float frequency, float length);
void paWaveSilence(Buffer* buffer, float length);

#endif // __WAVE_H__
