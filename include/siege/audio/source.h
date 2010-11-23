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

#ifndef __SIEGE_AUDIO_SOURCE_H__
#define __SIEGE_AUDIO_SOURCE_H__

#include "../common.h"
#include "buffer.h"
#include "../util/plist.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \ingroup Audio
 * \private
 * \brief Audio source usage handle
 *
 * The dispatch helps handle the sources. Each dispatch refers to a backend source, and is (when in use) assigned a frontend source.
 * This makes sure that sources are managed in a conservative fashion and recycled whenever possible.
 */
typedef struct SGAudioSourceDispatch
{
    /**
	 * \brief The source that this dispatch handles
     */
    struct SGAudioSource* source;
    /**
	 * \private
	 * \brief Internal handle
	 *
	 * \warning
	 *	For internal use only.
     */
    void* handle;
} SGAudioSourceDispatch;

/**
 * \ingroup Audio
 * \brief Audio source
 *
 * This is the actual "class" responsible for positioning and playing a sound.
 */
typedef struct SGAudioSource
{
    /**
	 * \private
	 * \brief Pointer to the dispatch
	 *
	 * \warning
	 *	For internal use only.
     */
    SGAudioSourceDispatch* dispatch;
    /**
	 * \brief Priority of the source
	 *
	 * If no more sources can be created in the backend for play, the higher priority sources will have precedence over lower priority sources.
	 * That way you can, for example, make the explosion near you "override" a bird tweeting on a tree.
     */
    float priority;
} SGAudioSource;

#ifdef SG_BUILD_LIBRARY
SGAudioSourceDispatch* _sg_srcDisList;
SGuint _sg_srcDisLength;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgAudioSourceInit(void);
SGbool SG_EXPORT _sgAudioSourceDeinit(void);

SGAudioSourceDispatch* SG_EXPORT _sgAudioSourceGetFreeDispatch(SGAudioSource* source);

/**
 * \memberof SGAudioSource
 * \brief Create an audio source
 * \param buffer The buffer file to use
 * \param priority The source priority
 * \param volume Volume of the source, from 0.0 to 1.0
 * \param pitch The pitch of the source, 1.0 being no adjustment
 * \param looping Should the source loop?
 * \warning
 *	The first parameter may be removed in the very near future!
 * \return The newly created source if successful, NULL otherwise.
 */
SGAudioSource* SG_EXPORT sgAudioSourceCreate(SGAudioBuffer* buffer, float priority, float volume, float pitch, SGbool looping);
/**
 * \memberof SGAudioSource
 * \brief Destroy an audio source
 * \param source The source to destroy - it should not be used anymore after this call
 */
void SG_EXPORT sgAudioSourceDestroy(SGAudioSource* source);

/**
 * \name Basic functions
 *
 * These control the basic source functionality - playing, pausing, stopping, etc...
 */
/// @{
/**
 * \memberof SGAudioSource
 * \brief Play an audio source
 * \param source The source to play
 */
void SG_EXPORT sgAudioSourcePlay(SGAudioSource* source);
/**
 * \memberof SGAudioSource
 * \brief Is an audio source playing?
 * \param source The source of which the status should be checked
 * \return SG_TRUE if it is playing, SG_FALSE otherwise
 */
SGbool SG_EXPORT sgAudioSourceIsPlaying(SGAudioSource* source);
/**
 * \memberof SGAudioSource
 * \brief Pause an audio source
 * \param source The source to pause
 */
void SG_EXPORT sgAudioSourcePause(SGAudioSource* source);
/**
 * \memberof SGAudioSource
 * \brief Is an audio source paused?
 * \param source The source of which the status should be checked
 * \return SG_TRUE if it is paused, SG_FALSE otherwise
 */
SGbool SG_EXPORT sgAudioSourceIsPaused(SGAudioSource* source);
/**
 * \memberof SGAudioSource
 * \brief Rewind an audio source
 * \param source The source to rewind
 */
void SG_EXPORT sgAudioSourceRewind(SGAudioSource* source);
//SGbool SG_EXPORT sgAudioSourceIsRewinded(SGAudioSource* source);
/**
 * \memberof SGAudioSource
 * \brief Stop an audio source
 * \param source The source to stop
 */
void SG_EXPORT sgAudioSourceStop(SGAudioSource* source);
/**
 * \memberof SGAudioSource
 * \brief Is an audio source stopped?
 * \param source The source of which the status should be checked
 * \return SG_TRUE if it is stopped, SG_FALSE otherwise
 */
SGbool SG_EXPORT sgAudioSourceIsStopped(SGAudioSource* source);
/**
 * \memberof SGAudioSource
 * \brief Is an audio source active (in use)?
 * \param source The source of which the status should be checked
 * \return SG_TRUE if it is active, SG_FALSE otherwise
 */
SGbool SG_EXPORT sgAudioSourceIsActive(SGAudioSource* source);
/// @}

/**
 * \name Queueing buffers
 *
 * Queueing buffers (as opposed to simply putting in one large buffer) can be used for things like smooth streaming of large audio data such as music.
 */
/// @{
/**
 * \memberof SGAudioSource
 * \brief Queue multiple buffers into a source
 * \param source The source into which the buffers should be queued
 * \param buffers The buffers to queue
 * \param numbuffers How many buffers to queue
 *
 * This function queues \c numbuffers buffers into \c source.
 * \sa
 *	sgAudioSourceQueueBuffer
 */
void SG_EXPORT sgAudioSourceQueueBuffers(SGAudioSource* source, SGAudioBuffer** buffers, SGuint numbuffers);
/**
 * \memberof SGAudioSource
 * \brief Queue a single buffer into a source
 * \param source The source into which the buffer should be queued
 * \param buffer The buffer to queue
 *
 * This function queues \c numbuffers buffers into \c source.
 * \sa
 *	sgAudioSourceQueueBuffers
 */
void SG_EXPORT sgAudioSourceQueueBuffer(SGAudioSource* source, SGAudioBuffer* buffer);
/// @}

/**
 * \name Position
 */
/// @{
/**
 * \memberof SGAudioSource
 * \brief Set the x,y,z position
 * \param source The source which we want to set the position of
 * \param[in] x X position
 * \param[in] y Y position
 * \param[in] z Z position
 *
 * \sa
 *	sgAudioSourceSetPosition2f
 *	sgAudioSourceGetPosition3f
 *	sgAudioSourceSetVelocity3f
 */
void SG_EXPORT sgAudioSourceSetPosition3f(SGAudioSource* source, float x, float y, float z);
/**
 * \memberof SGAudioSource
 * \brief Set the x,y position, and z implicitly to 0
 * \param source The source which we want to set the position of
 * \param[in] x X position
 * \param[in] y Y position
 *
 * \sa
 *	sgAudioSourceSetPosition3f
 *	sgAudioSourceGetPosition2f
 *	sgAudioSourceSetVelocity2f
 */
void SG_EXPORT sgAudioSourceSetPosition2f(SGAudioSource* source, float x, float y);
/**
 * \memberof SGAudioSource
 * \brief Get the x,y,z position
 * \param source The source which we want to get the position of
 * \param[out] x X position
 * \param[out] y Y position
 * \param[out] z Z position
 *
 * \sa
 *	sgAudioSourceSetPosition3f
 *	sgAudioSourceGetPosition2f
 *	sgAudioSourceGetVelocity3f
 */
void SG_EXPORT sgAudioSourceGetPosition3f(SGAudioSource* source, float* x, float* y, float* z);
/**
 * \memberof SGAudioSource
 * \brief Get the x,y position
 * \param source The source which we want to get the position of
 * \param[out] x X position
 * \param[out] y Y position
 *
 * \sa
 *	sgAudioSourceSetPosition2f
 *	sgAudioSourceGetPosition3f
 *	sgAudioSourceGetVelocity2f
 */
void SG_EXPORT sgAudioSourceGetPosition2f(SGAudioSource* source, float* x, float* y);
/// @}

/**
 * \name Velocity
 */
/// @{
/**
 * \memberof SGAudioSource
 * \brief Set the x,y,z velocity
 * \param source The source which we want to set the velocity of
 * \param[in] x X velocity
 * \param[in] y Y velocity
 * \param[in] z Z velocity
 *
 * \sa
 *	sgAudioSourceSetVelocity2f
 *	sgAudioSourceGetVelocity3f
 *	sgAudioSourceSetPosition3f
 */
void SG_EXPORT sgAudioSourceSetVelocity3f(SGAudioSource* source, float x, float y, float z);
/**
 * \memberof SGAudioSource
 * \brief Set the x,y velocity, and z implicitly to 0
 * \param source The source which we want to set the velocity of
 * \param[in] x X velocity
 * \param[in] y Y velocity
 *
 * \sa
 *	sgAudioSourceSetVelocity3f
 *	sgAudioSourceGetVelocity2f
 *	sgAudioSourceSetPosition2f
 */
void SG_EXPORT sgAudioSourceSetVelocity2f(SGAudioSource* source, float x, float y);
/**
 * \memberof SGAudioSource
 * \brief Get the x,y,z velocity
 * \param source The source which we want to get the velocity of
 * \param[out] x X velocity
 * \param[out] y Y velocity
 * \param[out] z Z velocity
 *
 * \sa
 *	sgAudioSourceSetVelocity3f
 *	sgAudioSourceGetVelocity2f
 *	sgAudioSourceGetPosition3f
 */
void SG_EXPORT sgAudioSourceGetVelocity3f(SGAudioSource* source, float* x, float* y, float* z);
/**
 * \memberof SGAudioSource
 * \brief Get the x,y velocity
 * \param source The source which we want to get the velocity of
 * \param[out] x X velocity
 * \param[out] y Y velocity
 *
 * \sa
 *	sgAudioSourceSetVelocity2f
 *	sgAudioSourceGetVelocity3f
 *	sgAudioSourceGetPosition2f
 */
void SG_EXPORT sgAudioSourceGetVelocity2f(SGAudioSource* source, float* x, float* y);
/// @}

//void SG_EXPORT sgAudioSourceSetFalloff(SGAudioSource* source, float falloff);
//float SG_EXPORT sgAudioSourceGetFalloff(SGAudioSource* source);

/**
 * \name Pitch
 */
/// @{
/**
 * \memberof SGAudioSource
 * \brief Set the pitch
 * \param source The source which we want to set the pitch of
 * \param[in] pitch The pitch to set
 *
 * Pitch 1.0 leaves the buffer to play as it is in the "original".
 *
 * \sa
 *	sgAudioSourceGetPitch
 *	sgAudioSourceSetVolume
 *	sgAudioSourceSetLooping
 */
void SG_EXPORT sgAudioSourceSetPitch(SGAudioSource* source, float pitch);
/**
 * \memberof SGAudioSource
 * \brief Get the pitch
 * \param source The source which we want to get the pitch of
 * \return The pitch
 *
 * \sa
 *	sgAudioSourceSetPitch
 *	sgAudioSourceGetVolume
 *	sgAudioSourceGetLooping
 */
float SG_EXPORT sgAudioSourceGetPitch(SGAudioSource* source);
/// @}

/**
 * \name Volume
 */
/// @{
/**
 * \memberof SGAudioSource
 * \brief Set the volume
 * \param source The source which we want to set the volume of
 * \param[in] volume The volume to set
 *
 * Volume 1.0 leaves the buffer to play as it is in the "original".
 *
 * \sa
 *	sgAudioSourceGetVolume
 *	sgAudioSourceSetPitch
 *	sgAudioSourceSetLooping
 */
void SG_EXPORT sgAudioSourceSetVolume(SGAudioSource* source, float volume);
/**
 * \memberof SGAudioSource
 * \brief Get the volume
 * \param source The source which we want to get the volume of
 * \return The volume
 *
 * \sa
 *	sgAudioSourceSetVolume
 *	sgAudioSourceGetPitch
 *	sgAudioSourceGetLooping
 */
float SG_EXPORT sgAudioSourceGetVolume(SGAudioSource* source);
/// @}

/**
 * \name Looping
 */
/// @{
/**
 * \memberof SGAudioSource
 * \brief Set the source in (or out of) a loop
 * \param source The source which we want to loop (or stop looping)
 * \param[in] looping The looping to set
 *
 * Pitch 1.0 leaves the buffer to play as it is in the "original".
 *
 * \sa
 *	sgAudioSourceGetLooping
 *	sgAudioSourceSetPitch
 *	sgAudioSourceSetVolume
 */
void SG_EXPORT sgAudioSourceSetLooping(SGAudioSource* source, SGbool looping);
/**
 * \memberof SGAudioSource
 * \brief Is the source looping?
 * \param source The source of which the status of the loop we want to get
 * \return SG_TRUE if the source is in a loop, SG_FALSE otherwise
 *
 * \sa
 *	sgAudioSourceSetLooping
 *	sgAudioSourceGetPitch
 *	sgAudioSourceGetVolume
 */
SGbool SG_EXPORT sgAudioSourceGetLooping(SGAudioSource* source);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_AUDIO_SOURCE_H__
