#define SG_BUILD_LIBRARY
#include <siege/audio/buffer.h>
#include <siege/modules/audio.h>

#include <stdlib.h>

SGbool SG_EXPORT _sgBufferInit(void)
{
    return SG_TRUE;
}
SGbool SG_EXPORT _sgBufferDeinit(void)
{
    return SG_TRUE;
}

SGBuffer* SG_EXPORT sgBufferCreate(char* fname)
{
    SGBuffer* buffer = malloc(sizeof(SGBuffer));

    if(_sg_modAudio.sgmAudioBufferCreate != NULL)
        _sg_modAudio.sgmAudioBufferCreate(&buffer->handle);

    SGuint channels = 0;
    SGuint format = 0;
    SGuint frequency = 0;
    void* data = NULL;
    SGuint datalen = 0;
    if(_sg_modAudio.sgmAudioLoadFile != NULL)
        _sg_modAudio.sgmAudioLoadFile(fname, &channels, &format, &frequency, &data, &datalen);
    if(_sg_modAudio.sgmAudioBufferSetData != NULL)
        _sg_modAudio.sgmAudioBufferSetData(buffer->handle, channels, format, frequency, data, datalen);
    if(_sg_modAudio.sgmAudioLoadFreeData != NULL)
        _sg_modAudio.sgmAudioLoadFreeData(data);

    return buffer;
}
void SG_EXPORT sgBufferDestroy(SGBuffer* buffer)
{
    if(buffer == NULL)
        return;

    if(_sg_modAudio.sgmAudioBufferDestroy != NULL)
        _sg_modAudio.sgmAudioBufferDestroy(buffer->handle);
    free(buffer);
}

void SG_EXPORT sgBufferSetData(SGBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen)
{
    if(buffer == NULL)
        return;
    if(_sg_modAudio.sgmAudioBufferSetData != NULL)
        _sg_modAudio.sgmAudioBufferSetData(buffer->handle, channels, format, frequency, data, datalen);
}
