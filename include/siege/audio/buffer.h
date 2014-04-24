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
#include "../util/stream.h"

/**
 * \name Audio formats
 *
 * These are used to indicate the format of the data passed to audio buffers.
 */
/// @{
#define SG_AUDIO_FORMAT_S8  0x01
#define SG_AUDIO_FORMAT_S16 0x02
#define SG_AUDIO_FORMAT_S24 0x03
#define SG_AUDIO_FORMAT_S32 0x04

#define SG_AUDIO_FORMAT_U8  0x05
#define SG_AUDIO_FORMAT_U16 0x06
#define SG_AUDIO_FORMAT_U24 0x07
#define SG_AUDIO_FORMAT_U32 0x08

#define SG_AUDIO_FORMAT_F   0x0A
#define SG_AUDIO_FORMAT_D   0x0B
/// @}

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \ingroup Audio
 * \brief Audio buffer
 *
 * The buffer holds the audio data for the \ref SGAudioSource "sources" to play. Please note that a single buffer can be used in multiple sources.
 */
typedef struct SGAudioBuffer
{
    /**
     * \brief Internal handle
     * \private
     *
     * \warning
     *    For internal use only.
     */
    void* handle;

    SGStream* stream;
    SGbool del;
} SGAudioBuffer;

SGAudioBuffer* SG_CALL sgAudioBufferCreateStream(SGStream* stream, SGbool delstream);
/// @{
/**
 * \memberof SGAudioBuffer
 * \brief Create an audio buffer
 *
 * \param fname Filename of the audio file to load
 *
 * \return The newly created buffer if successful, NULL otherwise.
 */
SGAudioBuffer* SG_CALL sgAudioBufferCreateFile(const char* fname);
/**
 * \memberof SGAudioBuffer
 * \brief Destroy an audio buffer
 *
 * \param buffer The buffer to destroy.
 * It should not be used anymore after this call.
 */
void SG_CALL sgAudioBufferDestroy(SGAudioBuffer* buffer);
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
void SG_CALL sgAudioBufferSetData(SGAudioBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, size_t datalen);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_AUDIO_BUFFER_H__
