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
    \private
    \brief Audio source usage handle

    The dispatch helps handle the sources. Each dispatch refers to a backend source, and is (when in use) assigned a frontend source.
    This makes sure that sources are managed in a conservative fashion and recycled whenever possible.
*/
typedef struct SGSourceDispatch
{
    /**
        \brief The source that this dispatch handles
    */
    struct SGSource* source;
    /**
        \private
        \brief Internal handle

        \warning
            For internal use only
    */
    void* handle;
} SGSourceDispatch;

/**
    \brief Audio source

    This is the actual "class" responsible for positioning and playing a sound.
*/
typedef struct SGSource
{
    /**
        \private
        \brief Pointer to the dispatch

        \warning
            For internal use only.
    */
    SGSourceDispatch* dispatch;
    /**
        \brief Priority of the source

        If no more sources can be created in the backend for play, the higher priority sources will have precedence over lower priority sources.
        That way you can, for example, make the explosion near you "override" a bird tweeting on a tree.
    */
    float priority;
} SGSource;

#ifdef SG_BUILD_LIBRARY
SGSourceDispatch* _sg_srcDisList;
SGuint _sg_srcDisLength;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgSourceInit(void);
SGbool SG_EXPORT _sgSourceDeinit(void);

SGSourceDispatch* SG_EXPORT _sgSourceGetFreeDispatch(SGSource* source);

/**
    \memberof SGSource
    \brief Create an audio source
    \param buffer The buffer file to use
    \param priority The source priority
    \param volume Volume of the source, from 0.0 to 1.0
    \param pitch The pitch of the source, 1.0 being no adjustment
    \param looping Should the source loop?
    \warning
        The first parameter may be removed in the very near future!
    \return The newly created source if successful, NULL otherwise.
*/
SGSource* SG_EXPORT sgSourceCreate(SGBuffer* buffer, float priority, float volume, float pitch, SGbool looping);
/**
    \memberof SGSource
    \brief Destroy an audio source
    \param source The source to destroy - it should not be used anymore after this call
*/
void SG_EXPORT sgSourceDestroy(SGSource* source);

/**
    \name Basic functions

    These control the basic source functionality - playing, pausing, stopping, etc...
*/
// @{
/**
    \memberof SGSource
    \brief Play an audio source
    \param source The source to play
*/
void SG_EXPORT sgSourcePlay(SGSource* source);
/**
    \memberof SGSource
    \brief Is an audio source playing?
    \param source The source of which the status should be checked
    \return SG_TRUE if it is playing, SG_FALSE otherwise
*/
SGbool SG_EXPORT sgSourceIsPlaying(SGSource* source);
/**
    \memberof SGSource
    \brief Pause an audio source
    \param source The source to pause
*/
void SG_EXPORT sgSourcePause(SGSource* source);
/**
    \memberof SGSource
    \brief Is an audio source paused?
    \param source The source of which the status should be checked
    \return SG_TRUE if it is paused, SG_FALSE otherwise
*/
SGbool SG_EXPORT sgSourceIsPaused(SGSource* source);
/**
    \memberof SGSource
    \brief Rewind an audio source
    \param source The source to rewind
*/
void SG_EXPORT sgSourceRewind(SGSource* source);
//SGbool SG_EXPORT sgSourceIsRewinded(SGSource* source);
/**
    \memberof SGSource
    \brief Stop an audio source
    \param source The source to stop
*/
void SG_EXPORT sgSourceStop(SGSource* source);
/**
    \memberof SGSource
    \brief Is an audio source stopped?
    \param source The source of which the status should be checked
    \return SG_TRUE if it is stopped, SG_FALSE otherwise
*/
SGbool SG_EXPORT sgSourceIsStopped(SGSource* source);
/**
    \memberof SGSource
    \brief Is an audio source active (in use)?
    \param source The source of which the status should be checked
    \return SG_TRUE if it is active, SG_FALSE otherwise
*/
SGbool SG_EXPORT sgSourceIsActive(SGSource* source);
// @}

/**
    \name Queueing buffers

    Queueing buffers (as opposed to simply putting in one large buffer) can be used for things like smooth streaming of large audio data such as music.
*/
// @{
/**
    \memberof SGSource
    \brief Queue multiple buffers into a source
    \param source The source into which the buffers should be queued
    \param buffers The buffers to queue
    \param numbuffers How many buffers to queue

    This function queues \c numbuffers buffers into \c source.
    \sa
        sgSourceQueueBuffer
*/
void SG_EXPORT sgSourceQueueBuffers(SGSource* source, SGBuffer** buffers, SGuint numbuffers);
/**
    \memberof SGSource
    \brief Queue a single buffer into a source
    \param source The source into which the buffer should be queued
    \param buffer The buffer to queue

    This function queues \c numbuffers buffers into \c source.
    \sa
        sgSourceQueueBuffers
*/
void SG_EXPORT sgSourceQueueBuffer(SGSource* source, SGBuffer* buffer);
// @}

/**
    \name Position
*/
// @{
/**
    \memberof SGSource
    \brief Set the x,y,z position
    \param source The source which we want to set the position of
    \param[in] x X position
    \param[in] y Y position
    \param[in] z Z position

    \sa
        sgSourceSetPosition2f
        sgSourceGetPosition3f
        sgSourceSetVelocity3f
*/
void SG_EXPORT sgSourceSetPosition3f(SGSource* source, float x, float y, float z);
/**
    \memberof SGSource
    \brief Set the x,y position, and z implicitly to 0
    \param source The source which we want to set the position of
    \param[in] x X position
    \param[in] y Y position

    \sa
        sgSourceSetPosition3f
        sgSourceGetPosition2f
        sgSourceSetVelocity2f
*/
void SG_EXPORT sgSourceSetPosition2f(SGSource* source, float x, float y);
/**
    \memberof SGSource
    \brief Get the x,y,z position
    \param source The source which we want to get the position of
    \param[out] x X position
    \param[out] y Y position
    \param[out] z Z position

    \sa
        sgSourceSetPosition3f
        sgSourceGetPosition2f
        sgSourceGetVelocity3f
*/
void SG_EXPORT sgSourceGetPosition3f(SGSource* source, float* x, float* y, float* z);
/**
    \memberof SGSource
    \brief Get the x,y position
    \param source The source which we want to get the position of
    \param[out] x X position
    \param[out] y Y position

    \sa
        sgSourceSetPosition2f
        sgSourceGetPosition3f
        sgSourceGetVelocity2f
*/
void SG_EXPORT sgSourceGetPosition2f(SGSource* source, float* x, float* y);
// @}

/**
    \name Velocity
*/
// @{
/**
    \memberof SGSource
    \brief Set the x,y,z velocity
    \param source The source which we want to set the velocity of
    \param[in] x X velocity
    \param[in] y Y velocity
    \param[in] z Z velocity

    \sa
        sgSourceSetVelocity2f
        sgSourceGetVelocity3f
        sgSourceSetPosition3f
*/
void SG_EXPORT sgSourceSetVelocity3f(SGSource* source, float x, float y, float z);
/**
    \memberof SGSource
    \brief Set the x,y velocity, and z implicitly to 0
    \param source The source which we want to set the velocity of
    \param[in] x X velocity
    \param[in] y Y velocity

    \sa
        sgSourceSetVelocity3f
        sgSourceGetVelocity2f
        sgSourceSetPosition2f
*/
void SG_EXPORT sgSourceSetVelocity2f(SGSource* source, float x, float y);
/**
    \memberof SGSource
    \brief Get the x,y,z velocity
    \param source The source which we want to get the velocity of
    \param[out] x X velocity
    \param[out] y Y velocity
    \param[out] z Z velocity

    \sa
        sgSourceSetVelocity3f
        sgSourceGetVelocity2f
        sgSourceGetPosition3f
*/
void SG_EXPORT sgSourceGetVelocity3f(SGSource* source, float* x, float* y, float* z);
/**
    \memberof SGSource
    \brief Get the x,y velocity
    \param source The source which we want to get the velocity of
    \param[out] x X velocity
    \param[out] y Y velocity

    \sa
        sgSourceSetVelocity2f
        sgSourceGetVelocity3f
        sgSourceGetPosition2f
*/
void SG_EXPORT sgSourceGetVelocity2f(SGSource* source, float* x, float* y);
// @}

//void SG_EXPORT sgSourceSetFalloff(SGSource* source, float falloff);
//float SG_EXPORT sgSourceGetFalloff(SGSource* source);

/**
    \name Pitch
*/
// @{
/**
    \memberof SGSource
    \brief Set the pitch
    \param source The source which we want to set the pitch of
    \param[in] pitch The pitch to set

    Pitch 1.0 leaves the buffer to play as it is in the "original".

    \sa
        sgSourceGetPitch
        sgSourceSetVolume
        sgSourceSetLooping
*/
void SG_EXPORT sgSourceSetPitch(SGSource* source, float pitch);
/**
    \memberof SGSource
    \brief Get the pitch
    \param source The source which we want to get the pitch of
    \return The pitch

    \sa
        sgSourceSetPitch
        sgSourceGetVolume
        sgSourceGetLooping
*/
float SG_EXPORT sgSourceGetPitch(SGSource* source);
// @}

/**
    \name Volume
*/
// @{
/**
    \memberof SGSource
    \brief Set the volume
    \param source The source which we want to set the volume of
    \param[in] volume The volume to set

    Volume 1.0 leaves the buffer to play as it is in the "original".

    \sa
        sgSourceGetVolume
        sgSourceSetPitch
        sgSourceSetLooping
*/
void SG_EXPORT sgSourceSetVolume(SGSource* source, float volume);
/**
    \memberof SGSource
    \brief Get the volume
    \param source The source which we want to get the volume of
    \return The volume

    \sa
        sgSourceSetVolume
        sgSourceGetPitch
        sgSourceGetLooping
*/
float SG_EXPORT sgSourceGetVolume(SGSource* source);
// @}

/**
    \name Looping
*/
// @{
/**
    \memberof SGSource
    \brief Set the source in (or out of) a loop
    \param source The source which we want to loop (or stop looping)
    \param[in] looping The looping to set

    Pitch 1.0 leaves the buffer to play as it is in the "original".

    \sa
        sgSourceGetLooping
        sgSourceSetPitch
        sgSourceSetVolume
*/
void SG_EXPORT sgSourceSetLooping(SGSource* source, SGbool looping);
/**
    \memberof SGSource
    \brief Is the source looping?
    \param source The source of which the status of the loop we want to get
    \return SG_TRUE if the source is in a loop, SG_FALSE otherwise

    \sa
        sgSourceSetLooping
        sgSourceGetPitch
        sgSourceGetVolume
*/
SGbool SG_EXPORT sgSourceGetLooping(SGSource* source);
// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_AUDIO_SOURCE_H__
