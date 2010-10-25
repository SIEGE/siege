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
 * \brief Audio buffer
 *
 * The buffer holds the audio data for the \ref SGAudioSource "sources" to play. Please note that a single buffer can be used in multiple sources.
 */
typedef struct SGAudioBuffer
{
    /**
	 * \private
	 * \brief Internal handle
	 *
	 * \warning
	 *	For internal use only.
     */
    void* handle;
} SGAudioBuffer;

SGbool SG_EXPORT _sgAudioBufferInit(void);
SGbool SG_EXPORT _sgAudioBufferDeinit(void);

/// @{
/**
 * \memberof SGAudioBuffer
 * \brief Create an audio buffer
 * \param fname Filename of the audio file to load
 * \return The newly created buffer if successful, NULL otherwise.
 */
SGAudioBuffer* SG_EXPORT sgAudioBufferCreate(const char* fname);
/**
 * \memberof SGAudioBuffer
 * \brief Destroy an audio buffer
 * \param buffer The buffer to destroy. It should not be used anymore after this call.
 */
void SG_EXPORT sgAudioBufferDestroy(SGAudioBuffer* buffer);
/// @}

/// @{
/**
 * \memberof SGAudioBuffer
 * \brief Set the data of an audio buffer
 * \param buffer The buffer of which the data should be modified
 * \param channels The number of channels in the data
 * \param format The audio format
 * \param frequency The frequency (sample rate) of the data
 * \param data Audio data to pass to the buffer
 * \param datalen Length of the audio data in bytes
 */
void SG_EXPORT sgAudioBufferSetData(SGAudioBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_AUDIO_BUFFER_H__
