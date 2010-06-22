#ifndef __SIEGE_BACKEND_AUDIO_LOAD_H__
#define __SIEGE_BACKEND_AUDIO_LOAD_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT SG_DEPRECATED sgmAudioLoadFile(char* fname, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen);
    //SGuint SG_EXPORT SG_DEPRECATED sgmAudioLoadStream(void* stream, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen);
    SGuint SG_EXPORT SG_DEPRECATED sgmAudioLoadFreeData(void* data);

    SGuint SG_EXPORT sgmAudioFileCreate(void** file, char* fname, SGuint* channels, SGuint* format, SGuint* frequency);
    SGuint SG_EXPORT sgmAudioFileDestroy(void* file);
    SGuint SG_EXPORT sgmAudioFileNumSamples(void* file, SGuint* samples);
    SGuint SG_EXPORT sgmAudioFileRead(void* file, void* data, SGuint* datalen);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_AUDIO_LOAD_H__
