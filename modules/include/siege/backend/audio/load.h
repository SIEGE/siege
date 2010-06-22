#ifndef __SIEGE_AUDIO_LOAD_H__
#define __SIEGE_AUDIO_LOAD_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgAudioLoadFile(char* fname, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen);
    //SGuint SG_EXPORT sgAudioLoadStream(void* stream, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen);
    SGuint SG_EXPORT sgAudioLoadFreeData(void* data);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_AUDIO_LOAD_H__
