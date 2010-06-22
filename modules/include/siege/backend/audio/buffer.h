#ifndef __SIEGE_AUDIO_BUFFER_H__
#define __SIEGE_AUDIO_BUFFER_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmAudioBufferCreate(void** buffer);
    //SGuint SG_EXPORT sgmAudioBufferCreateData(void** buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen);
    SGuint SG_EXPORT sgmAudioBufferDestroy(void* buffer);
    SGuint SG_EXPORT sgmAudioBufferSetData(void* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen);
    //SGuint SG_EXPORT sgmAudioBufferGetData(void* buffer, SGuint* channels, SGuint* format, SGuint* frequency, void* data, SGuint* datalen);
    //SGuint SG_EXPORT sgmAudioBufferFreeData(void* data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_AUDIO_BUFFER_H__
