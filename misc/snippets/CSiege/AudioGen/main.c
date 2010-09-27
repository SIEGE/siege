#include <stdio.h>
#include <stdlib.h>

#include <al.h>
#include <alc.h>

#include "common.h"
#include "buffer.h"
#include "context.h"
#include "noise.h"
#include "normalize.h"
#include "wave.h"
#include "save.h"

Context* context;
Buffer* buffer;

ALCdevice* aldev;
ALCcontext* alcon;
ALuint albuf;
ALuint alsrc;
int main()
{
    context = paContextCreate(44100, 0);
    buffer = paBufferCreate(context, 0);
    paNoiseBrown(buffer, 1);
    //paWaveTriangle(buffer, 220, 1);
    paBufferFinalizeS(buffer);
    paBufferSaveWAV16(buffer, "triangle220.wav");

    aldev = alcOpenDevice(NULL);
    alcon = alcCreateContext(aldev, NULL);
    alcMakeContextCurrent(alcon);

    alGenBuffers(1, &albuf);
    alGenSources(1, &alsrc);
    alBufferData(albuf, AL_FORMAT_MONO16, buffer->cdata, buffer->slength * 2, context->frequency);

    alSourcei(alsrc, AL_BUFFER, albuf);
    alSourcePlay(alsrc);

    int p = AL_PLAYING;
    while(p == AL_PLAYING)
        alGetSourcei(alsrc, AL_SOURCE_STATE, &p);

    alDeleteBuffers(1, &albuf);
    alDeleteSources(1, &alsrc);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(alcon);
    alcCloseDevice(aldev);

    paContextDestroy(context);
    paBufferDestroy(buffer);
    return 0;
}
