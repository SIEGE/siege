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
/**
 * \file siege/audio/source.h
 * \brief Audio sources and dispatches.
 * \ingroup Audio
 */

#ifndef __SIEGE_AUDIO_SOURCE_H__
#define __SIEGE_AUDIO_SOURCE_H__

#include "../common.h"
#include "buffer.h"
#include "../util/list.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \brief Audio source usage handle.
 * \private
 * \ingroup Audio
 *
 * The dispatch helps handle the sources. Each dispatch refers to a backend source,
 * and is (when in use) assigned a frontend source.
 *
 * This makes sure that sources are managed in a conservative fashion and recycled
 * whenever possible.
 */
typedef struct SGAudioSourceDispatch
{
    /**
     * \privatesection
     */

    struct SGAudioSource* source;    /// < The source that this dispatch handles.
    void* handle;                    /// < Internal handle.
} SGAudioSourceDispatch;

/**
 * Audio source.
 * \ingroup Audio
 *
 * This is the actual object responsible for positioning and playing a sound.
 */
typedef struct SGAudioSource
{
    /**
     * \privatesection
     */

    SGAudioSourceDispatch* dispatch; /// < Pointer to the dispatch.

    /**
     * \brief Priority of the source.
     *
     * If no more sources can be created in the backend for play, the higher priority
     * sources will have precedence over lower priority sources.
     *
     * That way you can, for example, make the explosion near you "override" a bird
     * tweeting on a tree.
     */
    float priority;
} SGAudioSource;

#ifdef SG_BUILD_LIBRARY
SGAudioSourceDispatch* _sg_srcDisList;
SGuint _sg_srcDisLength;
SGList* _sg_srcDestroy;
#endif // SG_BUILD_LIBRARY

SGbool SG_CALL _sgAudioSourceInit(void);
SGbool SG_CALL _sgAudioSourceDeinit(void);

SGAudioSourceDispatch* SG_CALL _sgAudioSourceGetFreeDispatch(SGAudioSource* source);

/**
 * \brief Create an audio source.
 *
 * \param priority The source priority
 * \param volume Volume of the source, from 0.0 to 1.0
 * \param pitch The pitch of the source, 1.0 being no adjustment
 * \param looping Should the source loop?
 *
 * \return The newly created source if successful, NULL otherwise.
 */
SGAudioSource* SG_CALL sgAudioSourceCreate(float priority, float volume, float pitch, SGbool looping);
/**
 * \brief Destroy an audio source.
 *
 * \param source The source to destroy - it should not be used anymore after this call
 */
void SG_CALL sgAudioSourceDestroy(SGAudioSource* source);
void SG_CALL sgAudioSourceDestroyLazy(SGAudioSource* source); /// < destroy when done playing

/**
 * \name Basic functions
 *
 * These control the basic source functionality - playing, pausing, stopping, etc...
 */
/// @{
/**
 * \brief Play an audio source.
 *
 * \param source The source to play
 */
void SG_CALL sgAudioSourcePlay(SGAudioSource* source);
/**
 * \brief Is an audio source playing?
 *
 * \param source The source of which the status should be checked
 *
 * \return SG_TRUE if it is playing, SG_FALSE otherwise
 */
SGbool SG_CALL sgAudioSourceIsPlaying(SGAudioSource* source);
/**
 * \brief Pause an audio source.
 *
 * \param source The source to pause
 */
void SG_CALL sgAudioSourcePause(SGAudioSource* source);
/**
 * \brief Is an audio source paused?
 *
 * \param source The source of which the status should be checked
 *
 * \return SG_TRUE if it is paused, SG_FALSE otherwise
 */
SGbool SG_CALL sgAudioSourceIsPaused(SGAudioSource* source);
/**
 * \brief Rewind an audio source.
 *
 * \param source The source to rewind
 */
void SG_CALL sgAudioSourceRewind(SGAudioSource* source);
//SGbool SG_CALL sgAudioSourceIsRewinded(SGAudioSource* source);
/**
 * \brief Stop an audio source.
 *
 * \param source The source to stop
 */
void SG_CALL sgAudioSourceStop(SGAudioSource* source);
/**
 * \brief Is an audio source stopped?
 *
 * \param source The source of which the status should be checked
 *
 * \return SG_TRUE if it is stopped, SG_FALSE otherwise
 */
SGbool SG_CALL sgAudioSourceIsStopped(SGAudioSource* source);
/**
 * \brief Is an audio source active (in use)?
 *
 * \param source The source of which the status should be checked
 *
 * \return SG_TRUE if it is active, SG_FALSE otherwise
 */
SGbool SG_CALL sgAudioSourceIsActive(SGAudioSource* source);
/// @}

/**
 * \name Queueing buffers
 *
 * Queueing buffers (as opposed to simply putting in one large buffer) can be used for things like smooth streaming of large audio data such as music.
 */
/// @{
size_t SG_CALL sgAudioSourceGetNumProcessedBuffers(SGAudioSource* source);
size_t SG_CALL sgAudioSourceGetNumQueuedBuffers(SGAudioSource* source);
/**
 * \brief Queue multiple buffers into a source
 *
 * \param source The source into which the buffers should be queued
 * \param buffers The buffers to queue
 * \param numbuffers How many buffers to queue
 *
 * This function queues \a numbuffers buffers into \a source.
 *
 * \see sgAudioSourceQueueBuffer
 */
void SG_CALL sgAudioSourceQueueBuffers(SGAudioSource* source, SGAudioBuffer** buffers, size_t numbuffers);
/**
 * \brief Queue a single buffer into a source
 *
 * \param source The source into which the buffer should be queued
 * \param buffer The buffer to queue
 *
 * This function queues a \a buffer into \a source.
 *
 * \see sgAudioSourceQueueBuffers
 */
void SG_CALL sgAudioSourceQueueBuffer(SGAudioSource* source, SGAudioBuffer* buffer);
/// @}

void SG_CALL sgAudioSourceUnqueueBuffers(SGAudioSource* source, size_t numbuffers);
void SG_CALL sgAudioSourceUnqueueBuffer(SGAudioSource* source);

/**
 * \name Position
 */
/// @{
/**
 * \brief Set the x,y,z position
 *
 * \param source The source which we want to set the position of
 * \param[in] x X position
 * \param[in] y Y position
 * \param[in] z Z position
 *
 * \see    sgAudioSourceSetPosition2f
 * \see    sgAudioSourceGetPosition3f
 * \see    sgAudioSourceSetVelocity3f
 */
void SG_CALL sgAudioSourceSetPosition3f(SGAudioSource* source, float x, float y, float z);
/**
 * \brief Set the x,y position, and z implicitly to 0
 *
 * \param source The source which we want to set the position of
 * \param[in] x X position
 * \param[in] y Y position
 *
 * \see    sgAudioSourceSetPosition3f
 * \see    sgAudioSourceGetPosition2f
 * \see    sgAudioSourceSetVelocity2f
 */
void SG_CALL sgAudioSourceSetPosition2f(SGAudioSource* source, float x, float y);
/**
 * \brief Get the x,y,z position
 *
 * \param source The source which we want to get the position of
 * \param[out] x X position
 * \param[out] y Y position
 * \param[out] z Z position
 *
 * \see    sgAudioSourceSetPosition3f
 * \see    sgAudioSourceGetPosition2f
 * \see    sgAudioSourceGetVelocity3f
 */
void SG_CALL sgAudioSourceGetPosition3f(SGAudioSource* source, float* x, float* y, float* z);
/**
 * \brief Get the x,y position
 *
 * \param source The source which we want to get the position of
 * \param[out] x X position
 * \param[out] y Y position
 *
 * \see    sgAudioSourceSetPosition2f
 * \see    sgAudioSourceGetPosition3f
 * \see    sgAudioSourceGetVelocity2f
 */
void SG_CALL sgAudioSourceGetPosition2f(SGAudioSource* source, float* x, float* y);
/// @}

/**
 * \name Velocity
 */
/// @{
/**
 * \brief Set the x,y,z velocity
 *
 * \param source The source which we want to set the velocity of
 * \param[in] x X velocity
 * \param[in] y Y velocity
 * \param[in] z Z velocity
 *
 * \see    sgAudioSourceSetVelocity2f
 * \see    sgAudioSourceGetVelocity3f
 * \see    sgAudioSourceSetPosition3f
 */
void SG_CALL sgAudioSourceSetVelocity3f(SGAudioSource* source, float x, float y, float z);
/**
 * \brief Set the x,y velocity, and z implicitly to 0
 *
 * \param source The source which we want to set the velocity of
 * \param[in] x X velocity
 * \param[in] y Y velocity
 *
 * \see    sgAudioSourceSetVelocity3f
 * \see    sgAudioSourceGetVelocity2f
 * \see    sgAudioSourceSetPosition2f
 */
void SG_CALL sgAudioSourceSetVelocity2f(SGAudioSource* source, float x, float y);
/**
 * \brief Get the x,y,z velocity
 *
 * \param source The source which we want to get the velocity of
 * \param[out] x X velocity
 * \param[out] y Y velocity
 * \param[out] z Z velocity
 *
 * \see    sgAudioSourceSetVelocity3f
 * \see    sgAudioSourceGetVelocity2f
 * \see    sgAudioSourceGetPosition3f
 */
void SG_CALL sgAudioSourceGetVelocity3f(SGAudioSource* source, float* x, float* y, float* z);
/**
 * \brief Get the x,y velocity
 *
 * \param source The source which we want to get the velocity of
 * \param[out] x X velocity
 * \param[out] y Y velocity
 *
 * \see    sgAudioSourceSetVelocity2f
 * \see    sgAudioSourceGetVelocity3f
 * \see    sgAudioSourceGetPosition2f
 */
void SG_CALL sgAudioSourceGetVelocity2f(SGAudioSource* source, float* x, float* y);
/// @}

//void SG_CALL sgAudioSourceSetFalloff(SGAudioSource* source, float falloff);
//float SG_CALL sgAudioSourceGetFalloff(SGAudioSource* source);

/**
 * \name Pitch
 */
/// @{
/**
 * \brief Set the pitch
 *
 * \param source The source which we want to set the pitch of
 * \param[in] pitch The pitch to set
 *
 * Pitch 1.0 leaves the buffer to play as it is in the "original".
 *
 * \see    sgAudioSourceGetPitch
 * \see    sgAudioSourceSetVolume
 * \see    sgAudioSourceSetLooping
 */
void SG_CALL sgAudioSourceSetPitch(SGAudioSource* source, float pitch);
/**
 * \brief Get the pitch
 *
 * \param source The source which we want to get the pitch of
 *
 * \return The pitch
 *
 * \see    sgAudioSourceSetPitch
 * \see    sgAudioSourceGetVolume
 * \see    sgAudioSourceGetLooping
 */
float SG_CALL sgAudioSourceGetPitch(SGAudioSource* source);
/// @}

/**
 * \name Volume
 */
/// @{
/**
 * \brief Set the volume
 *
 * \param source The source which we want to set the volume of
 * \param[in] volume The volume to set
 *
 * Volume 1.0 leaves the buffer to play as it is in the "original".
 *
 * \see    sgAudioSourceGetVolume
 * \see    sgAudioSourceSetPitch
 * \see    sgAudioSourceSetLooping
 */
void SG_CALL sgAudioSourceSetVolume(SGAudioSource* source, float volume);
/**
 * \brief Get the volume
 *
 * \param source The source which we want to get the volume of
 *
 * \return The volume
 *
 * \see    sgAudioSourceSetVolume
 * \see    sgAudioSourceGetPitch
 * \see    sgAudioSourceGetLooping
 */
float SG_CALL sgAudioSourceGetVolume(SGAudioSource* source);
/// @}

/**
 * \name Looping
 */
/// @{
/**
 * \brief Set the source in (or out of) a loop
 *
 * \param source The source which we want to loop (or stop looping)
 * \param[in] looping The looping to set
 *
 * Pitch 1.0 leaves the buffer to play as it is in the "original".
 *
 * \see    sgAudioSourceGetLooping
 * \see    sgAudioSourceSetPitch
 * \see    sgAudioSourceSetVolume
 */
void SG_CALL sgAudioSourceSetLooping(SGAudioSource* source, SGbool looping);
/**
 * \brief Is the source looping?
 *
 * \param source The source of which the status of the loop we want to get
 *
 * \return SG_TRUE if the source is in a loop, SG_FALSE otherwise
 *
 * \see    sgAudioSourceSetLooping
 * \see    sgAudioSourceGetPitch
 * \see    sgAudioSourceGetVolume
 */
SGbool SG_CALL sgAudioSourceGetLooping(SGAudioSource* source);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_AUDIO_SOURCE_H__
