#ifndef __SIEGE_AUDIO_SAMPLE_H__
#define __SIEGE_AUDIO_SAMPLE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgAudioSampleCreate(void** sample);
    //SGuint SG_EXPORT sgAudioSampleCreateData(void** sample, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen);
    SGuint SG_EXPORT sgAudioSampleDestroy(void* sample);
    SGuint SG_EXPORT sgAudioSampleSetData(void* sample, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen);
    //SGuint SG_EXPORT sgAudioSampleGetData(void* sample, SGuint* channels, SGuint* format, SGuint* frequency, void* data, SGuint* datalen);
    //SGuint SG_EXPORT sgAudioSampleFreeData(void* data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_AUDIO_SAMPLE_H__
