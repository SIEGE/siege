#ifndef __SIEGE_AUDIO_BUFFER_H__
#define __SIEGE_AUDIO_BUFFER_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGBuffer
{
    void* handle;
} SGBuffer;

SGbool SG_EXPORT _sgBufferInit(void);
SGbool SG_EXPORT _sgBufferDeinit(void);

SGBuffer* SG_EXPORT sgBufferCreate(char* fname);
void SG_EXPORT sgBufferDestroy(SGBuffer* buffer);

void SG_EXPORT sgBufferSetData(SGBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_AUDIO_BUFFER_H__
