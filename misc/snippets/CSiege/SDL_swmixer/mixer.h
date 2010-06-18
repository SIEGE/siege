#ifndef __MIXER_H__
#define __MIXER_H__
#include <SDL/SDL.h>
#include "common.h"
#include "source.h"

SDL_AudioSpec _SWM_obtained;
float* _SWM_convbuf;
size_t _SWM_convbuflen;

void SDLCALL _SWM_SDLCallback(void* userdata, Uint8* stream, int len);
int SWM_Init();
int SWM_Quit();

#endif // __MIXER_H__
