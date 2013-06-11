/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#ifndef __SIEGE_AUDIO_BUFFER_H__
#define __SIEGE_AUDIO_BUFFER_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \struct SGAudioBuffer
 *
 * A buffer holding audio data.
 *
 * The buffer holds the audio data for the ${SGAudioSource sources} to play.
 * Please note that a single buffer can be used in multiple sources.
 *
 * Future directions:
 * - Audio buffers could be merged with other types of buffers.
 * - There is currently no way to create a buffer without specifying a filename
 * 	 to load it from.
 */
typedef struct SGAudioBuffer
{
	void* handle;
} SGAudioBuffer;

SGbool SG_CALL _sgAudioBufferInit(void);
SGbool SG_CALL _sgAudioBufferDeinit(void);

/**
 * \function SGAudioBuffer* sgAudioBufferCreateFile(const char* fname)
 *
 * Create an audio buffer.
 *
 * Arguments:
 * - fname: Filename of the audio file to load.
 *
 * Returns:
 * The newly created buffer if successful, NULL otherwise.
 */
SGAudioBuffer* SG_CALL sgAudioBufferCreateFile(const char* fname);
/**
 * \function SGAudioBuffer* sgAudioBufferDestroy(SGAudioBuffer* buffer)
 *
 * Destroy an audio buffer.
 *
 * The buffer should not be used anymore after this call.
 *
 * Arguments:
 * - buffer: The buffer to destroy.
 */
void SG_CALL sgAudioBufferDestroy(SGAudioBuffer* buffer);

/**
 * \function void sgAudioBufferSetData(SGAudioBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, size_t datalen)
 *
 * Set the data of an audio buffer.
 *
 * Arguments:
 * - buffer   : The buffer of which the data should be modified
 * - channels : The number of channels in the data
 * - format   : The audio format
 * - frequency: The frequency (sample rate) of the data
 * - data     : Audio data to pass to the buffer
 * - datalen  : Length of the audio data in bytes
 */
void SG_CALL sgAudioBufferSetData(SGAudioBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, size_t datalen);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_AUDIO_BUFFER_H__
