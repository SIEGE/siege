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

#ifndef __SIEGE_CORE_ENTITY_H__
#define __SIEGE_CORE_ENTITY_H__

#include "../common.h"
#include "event.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

struct SGSprite;
struct SGMask;
struct SGPhysicsBody;
struct SGAudioSource;
struct SGPhysicsCollision;

/**
 * \ingroup Core
 * \brief Entity, the main game "class"
 *
 * This is the "class" which acts as sort of glue for siege - it glues together sprites, physics, audio, etc...
 * It is meant to be used for just about everything in a level.
 */
typedef struct SGEntity
{
	/**
	 * \brief Entity event type
	 *
	 * This controls which events of the entity can be triggered.
	 */
	SGenum type;
	/**
	 * \brief Is the entity active?
	 *
	 * If set to SG_TRUE, the Entity can take events, otherwise it is skipped.
	 */
	SGbool active;
	/**
	 * \brief Is the entity pausable?
	 *
	 * If set to SG_TRUE, then the entity is skipped during event handling if the game is paused.
	 */
	SGbool pausable;
	/**
	 * \private
	 * \brief Entity event handle
	 *
	 * This provides a handle for handling the entity's events.
	 *
	 * \warning
	 *	For internal use only.
	*/
	SGEvent* event;
	/**
	 * \brief User-provided data
	 * \note Don't forget to free the data before destroying the entity!
	 * SIEGE handles this as an opaque pointer.
	 */
	SGvoid* data;

	/**
	 * \brief Is the entity visible?
	 *
	 * If an entity is invisible, it is not automatically drawn.
	 */
	SGbool visible;

	/**
	 * \private
	 * \name Attachments
	 */
	/// @{
	/**
	 * \private
	 * \brief The attached sprite
	 * \warning
	 *	For internal use only.
	 */
	struct SGSprite* sprite;
	/**
	 * \private
	 * \brief The attached mask
	 * \warning
	 *	For internal use only.
	 */
	struct SGMask* mask;
	/**
	 * \private
	 * \brief The attached physics body
	 * \warning
	 *	For internal use only.
	 */
	struct SGPhysicsBody* body;
	/**
	 * \private
	 * \brief The attached audio source
	 * \warning
	 *	For internal use only.
	 */
	struct SGAudioSource* source;
	/// @}

	/**
	 * \private
	 * \brief Entity's x position
	 *
	 * \note
	 *	Not used if a body is attached.
	 *
	 * \warning
	 *	For internal use only.
	 */
	float x;
	/**
	 * \private
	 * \brief Entity's y position
	 *
	 * \note
	 *	Not used if a body is attached.
	 *
	 * \warning
	 *	For internal use only.
	 */
	float y;
	/**
	 * \private
	 * \brief Entity's depth
	 *
	 * \warning
	 *	For internal use only.
	 */
	float depth;
	/**
	 * \private
	 * \brief Entity's angle in radians
	 *
	 * \note
	 *	Not used if a body is attached.
	 *
	 * \warning
	 *	For internal use only.
	 */
	float angle;

	/// Is the mouse currently inside?
	SGbool minside;

	/**
	 * \name Entity-related events
	 * \todo Should two entities with the same
	 * depth both get this called if applicable?
	 */
	/// @{
	/// \brief Return SG_TRUE if the point is inside, SG_FALSE otherwise
	/// \todo Rename to cbPointInside, cbIsInside...?
	SGbool SG_EXPORT (*cbInside)(struct SGEntity* entity, float x, float y);

	/// \brief Called when the entity is about to be destroyed
	SGvoid SG_EXPORT (*lcDestroy)(struct SGEntity* entity);

	/// \brief Mouse has entered/exited the entity's area
	/// \todo Should this do the tests for depth?
	SGvoid SG_EXPORT (*lcMouseEnter)(struct SGEntity* entity);
	SGvoid SG_EXPORT (*lcMouseExit)(struct SGEntity* entity);

	SGvoid SG_EXPORT (*lcMouseButton)(struct SGEntity* entity, SGuint button);
	SGvoid SG_EXPORT (*lcMouseButtonPress)(struct SGEntity* entity, SGuint button);
	SGvoid SG_EXPORT (*lcMouseButtonRelease)(struct SGEntity* entity, SGuint button);

	SGvoid SG_EXPORT (*lcMouseButtonLeft)(struct SGEntity* entity);
	SGvoid SG_EXPORT (*lcMouseButtonLeftPress)(struct SGEntity* entity);
	SGvoid SG_EXPORT (*lcMouseButtonLeftRelease)(struct SGEntity* entity);

	SGvoid SG_EXPORT (*lcMouseButtonRight)(struct SGEntity* entity);
	SGvoid SG_EXPORT (*lcMouseButtonRightPress)(struct SGEntity* entity);
	SGvoid SG_EXPORT (*lcMouseButtonRightRelease)(struct SGEntity* entity);

	SGvoid SG_EXPORT (*lcMouseButtonMiddle)(struct SGEntity* entity);
	SGvoid SG_EXPORT (*lcMouseButtonMiddlePress)(struct SGEntity* entity);
	SGvoid SG_EXPORT (*lcMouseButtonMiddleRelease)(struct SGEntity* entity);

	SGvoid SG_EXPORT (*lcMouseMove)(struct SGEntity* entity, SGint x, SGint y);
	SGvoid SG_EXPORT (*lcMouseWheel)(struct SGEntity* entity, SGint wheel);
	/// @}

        /**
         * \name Collision events
         */
        /// @{
        /**
         * \brief Two objects are in collision with one another
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollision)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
        /**
         * \brief Collision event for the first of two objects
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollisionOne)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
        /**
         * \brief Collision event for the second of two objects
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollisionTwo)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);

        /**
         * \brief Two objects have just come in collision with one another
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollisionBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
        /**
         * \brief Collision start event for the first of two objects
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollisionOneBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
        /**
         * \brief Collision start event for the second of two objects
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollisionTwoBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);

        /**
         * \brief Two objects are no longer in collision with one another
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollisionEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
        /**
         * \brief Collision end event for the first of two objects
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollisionOneEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
        /**
         * \brief Collision end event for the second of two objects
         * \param other The other object
         * \param point Collision point info
         */
        SGvoid SG_EXPORT (*lcCollisionTwoEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);

        /// @}

	/**
	 * \name Module-related events
	 */
	/// @{
	/// \brief Called on \ref sgInit "sgInit"
	SGvoid SG_EXPORT (*evInit)(struct SGEntity* entity);
	/// \brief Called on \ref sgDeinit "sgDeinit"
	SGvoid SG_EXPORT (*evDeinit)(struct SGEntity* entity);
	/// @}

	/**
	 * \name Core events
	 */
	/// @{
	/// \brief Called on the first loop, when \ref sgLoop "sgLoop" is first called or on \ref sgRun "sgRun"
	SGvoid SG_EXPORT (*evStart)(struct SGEntity* entity);
	/// \brief Called before exiting SIEGE loop, usually on \ref sgStop "sgStop"
	SGvoid SG_EXPORT (*evExit)(struct SGEntity* entity);
	/// \brief Second event called in each loop
	SGvoid SG_EXPORT (*evTick)(struct SGEntity* entity);
	/// \brief First event called in each loop
	SGvoid SG_EXPORT (*evTickBegin)(struct SGEntity* entity);
	/// \brief Third event called in each loop
	SGvoid SG_EXPORT (*evTickEnd)(struct SGEntity* entity);
	/// \brief Fourth event called in each loop - drawing should be done here
	SGvoid SG_EXPORT (*evDraw)(struct SGEntity* entity);
	/// @}

	/**
	 * \name Window events
	 */
	/// @{
	/// \brief The window has been opened
	SGvoid SG_EXPORT (*evWindowOpen)(struct SGEntity* entity);
	/// \brief The window has been closed
	SGvoid SG_EXPORT (*evWindowClose)(struct SGEntity* entity);
	/**
	 * \brief The window has been resized
	 * \param width The new window width
	 * \param height The new window height
	 */
	SGvoid SG_EXPORT (*evWindowResize)(struct SGEntity* entity, SGuint width, SGuint height);
	/// @}

	/**
	 * \name Mouse events
	 */
	/// @{
	/**
	 * \brief A mouse button is being held down
	 * \param button The button ID
	 */
	SGvoid SG_EXPORT (*evMouseButton)(struct SGEntity* entity, SGuint button);
	/**
	 * \brief A mouse button has just been pressed
	 * \param button The button ID
	 */
	SGvoid SG_EXPORT (*evMouseButtonPress)(struct SGEntity* entity, SGuint button);
	/**
	 * \brief A mouse button has just been released
	 * \param button The button ID
	 */
	SGvoid SG_EXPORT (*evMouseButtonRelease)(struct SGEntity* entity, SGuint button);

	/// \brief The left mouse button is being held down
	SGvoid SG_EXPORT (*evMouseButtonLeft)(struct SGEntity* entity);
	/// \brief The left mouse button has just been pressed
	SGvoid SG_EXPORT (*evMouseButtonLeftPress)(struct SGEntity* entity);
	/// \brief The left mouse button has just been released
	SGvoid SG_EXPORT (*evMouseButtonLeftRelease)(struct SGEntity* entity);

	/// \brief The right mouse button is being held down
	SGvoid SG_EXPORT (*evMouseButtonRight)(struct SGEntity* entity);
	/// \brief The right mouse button has just been pressed
	SGvoid SG_EXPORT (*evMouseButtonRightPress)(struct SGEntity* entity);
	/// \brief The right mouse button has just been released
	SGvoid SG_EXPORT (*evMouseButtonRightRelease)(struct SGEntity* entity);

	/// \brief The middle mouse button is being held down
	SGvoid SG_EXPORT (*evMouseButtonMiddle)(struct SGEntity* entity);
	/// \brief The middle mouse button has just been pressed
	SGvoid SG_EXPORT (*evMouseButtonMiddlePress)(struct SGEntity* entity);
	/// \brief The middle mouse button has just been released
	SGvoid SG_EXPORT (*evMouseButtonMiddleRelease)(struct SGEntity* entity);

	/**
	 * \brief The mouse has been moved
	 * \param x New x mouse position
	 * \param y New y mouse position
	 */
	SGvoid SG_EXPORT (*evMouseMove)(struct SGEntity* entity, SGint x, SGint y);
	/**
	 * \brief The mouse wheel has been scrolled
	 * \param wheel New mouse wheel position
	 */
	SGvoid SG_EXPORT (*evMouseWheel)(struct SGEntity* entity, SGint wheel);
	/// @}

	/**
	 * \name Keyboard events
	 */
	/// @{
	/**
	 * \brief A key is being held down
	 * \param key The key ID
	 */
	SGvoid SG_EXPORT (*evKeyboardKey)(struct SGEntity* entity, SGuint key);
	/**
	 * \brief A key has just been pressed
	 * \param key The key ID
	 */
	SGvoid SG_EXPORT (*evKeyboardKeyPress)(struct SGEntity* entity, SGuint key);
	/**
	 * \brief A key has just been released
	 * \param key The key ID
	 */
	SGvoid SG_EXPORT (*evKeyboardKeyRelease)(struct SGEntity* entity, SGuint key);
	/**
	 * \brief A key repeat according to the key repeat interval
	 * \param key The key ID
	 */
	SGvoid SG_EXPORT (*evKeyboardKeyRepeat)(struct SGEntity* entity, SGuint key);

	//SGvoid SG_EXPORT (*evKeyboardChar)(struct SGEntity* entity, SGdchar chr);
	/**
	 * \brief A key representing a character has just been pressed
	 * \param chr The character (UTF-32)
	 */
	SGvoid SG_EXPORT (*evKeyboardCharPress)(struct SGEntity* entity, SGdchar chr);
	//SGvoid SG_EXPORT (*evKeyboardCharRelease)(struct SGEntity* entity, SGdchar chr);
	/**
	 * \brief A key representing a character has just been repeated according to the key repeat interval
	 * \param chr The character (UTF-32)
	 */
	SGvoid SG_EXPORT (*evKeyboardCharRepeat)(struct SGEntity* entity, SGdchar chr);
	/// @}

	/**
	 * \name Joystick events
	 */
	/// @{
	/**
	 * \brief A joystick button is being held down
	 * \param joy The joystick ID
	 * \param button The button ID
	 */
	SGvoid SG_EXPORT (*evJoystickButton)(struct SGEntity* entity, SGuint joy, SGuint button);
	/**
	 * \brief A joystick button has just been pressed
	 * \param joy The joystick ID
	 * \param button The button ID
	 */
	SGvoid SG_EXPORT (*evJoystickButtonPress)(struct SGEntity* entity, SGuint joy, SGuint button);
	/**
	 * \brief A joystick button has just been released
	 * \param joy The joystick ID
	 * \param button The button ID
	 */
	SGvoid SG_EXPORT (*evJoystickButtonRelease)(struct SGEntity* entity, SGuint joy, SGuint button);
	/**
	 * \brief The joystick axis have moved
	 * \param joy The joystick ID
	 * \param axis The axis positions
	 * \param numaxus The number of axis
	 */
	SGvoid SG_EXPORT (*evJoystickMove)(struct SGEntity* entity, SGuint joy, SGfloat* axis, size_t numaxis);
	/// @}

	// networking goes here

	/**
	 * \name Level events
	 */
	/// @{
	/// \brief A level has just loaded and started
	SGvoid SG_EXPORT (*evLevelStart)(struct SGEntity* entity);
	/// \brief A level has just ended
	SGvoid SG_EXPORT (*evLevelEnd)(struct SGEntity* entity);
	/// @}
} SGEntity;

SGbool SG_EXPORT _sg_evCall(SGEntity* entity, va_list args);
SGvoid SG_EXPORT _sg_evDraw(SGEntity* entity);

SGbool SG_EXPORT _sgEntityInit(void);
SGbool SG_EXPORT _sgEntityDeinit(void);

/**
 * \memberof SGEntity
 * \brief Create a new entity
 * \param priority The entity's priority - higher priority entities get their events called first
 * \param type The entity's event subtype - these are used to filter which events should be called
 * \return The newly created entity if successful, NULL otherwise
 */
SGEntity* SG_EXPORT sgEntityCreate(float priority, SGenum type);
/**
 * \memberof SGEntity
 * \brief Destroy an entity
 * \param entity The entity to destroy. It should not be used anymore after this call.
 */
void SG_EXPORT sgEntityDestroy(SGEntity* entity);

/**
 * \name Sprites
 */
/// @{
/**
 * \memberof SGEntity
 * \brief Attach a sprite to the entity
 * \param entity The entity of which the sprite we want to attach
 * \param sprite The sprite which should be attached or NULL to detach
 */
void SG_EXPORT sgEntitySetSprite(SGEntity* entity, struct SGSprite* sprite);
/**
 * \memberof SGEntity
 * \brief Get the currently attached sprite
 * \param entity The entity of which the sprite we want to get
 * \return The sprite if one was attached, NULL otherwise
 */
struct SGSprite* SG_EXPORT sgEntityGetSprite(SGEntity* entity);
/// @}

/**
 * \name Masks
 */
/// @{
/**
 * \memberof SGEntity
 * \brief Attach a mask to the entity
 * \param entity The entity of which the mask we want to attach
 * \param mask The mask (sprite) which should be attached or NULL to detach
 *
 * The mask is a simple bitmask which tells SIEGE which pixels are solid (as in,
 * which collide) and which not.
 */
void SG_EXPORT sgEntitySetMask(SGEntity* entity, struct SGMask* mask);
/**
 * \memberof SGEntity
 * \brief Get the currently attached mask
 * \param entity The entity of which the mask we want to get
 * \return The mask if one was attached, NULL otherwise
 */
struct SGMask* SG_EXPORT sgEntityGetMask(SGEntity* entity);
/// @}

/**
 * \name Physical bodies
 */
/// @{
/**
 * \memberof SGEntity
 * \brief Attach a physical body to the entity
 * \param entity The entity of which the physical body we want to attach
 * \param body The physical body which should be attached or NULL to detach
 */
void SG_EXPORT sgEntitySetPhysicsBody(SGEntity* entity, struct SGPhysicsBody* body);
/**
 * \memberof SGEntity
 * \brief Get the currently attached physical body
 * \param entity The entity of which the physical body we want to get
 * \return The physical body if one was attached, NULL otherwise
 */
struct SGPhysicsBody* SG_EXPORT sgEntityGetPhysicsBody(SGEntity* entity);
/// @}

/**
 * \name Audio sources
 */
/// @{
/**
 * \memberof SGEntity
 * \brief Attach an audio source to the entity
 * \param entity The entity of which the audio source we want to attach
 * \param source The audio source which should be attached or NULL to detach
 */
void SG_EXPORT sgEntitySetAudioSource(SGEntity* entity, struct SGAudioSource* source);
/**
 * \memberof SGEntity
 * \brief Get the currently attached audio source
 * \param entity The entity of which the audio source we want to get
 * \return The audio source if one was attached, NULL otherwise
 */
struct SGAudioSource* SG_EXPORT sgEntityGetAudioSource(SGEntity* entity);
/// @}

/**
 * \name Position
 */
/// @{
/**
 * \memberof SGEntity
 * \brief Set the entity's position
 * \param entity The entity of which position we want to set
 * \param[in] x X position
 * \param[in] y Y position
 *
 * \note
 *	If a physical body is attached, its position will get changed.
 *
 * \sa
 *	sgEntityGetPos
 *	sgEntitySetPosX
 *	sgEntitySetPosY
 */
void SG_EXPORT sgEntitySetPos(SGEntity* entity, float x, float y);
/**
 * \memberof SGEntity
 * \brief Get the body's position
 * \param entity The entity of which position we want to get
 * \param[out] x X position pointer
 * \param[out] y Y position pointer
 *
 * \note
 *	If a physical body is attached, this function "returns" its position.
 *
 * \sa
 *	sgEntitySetPos
 *	sgEntityGetPosX
 *	sgEntityGetPosY
 */
void SG_EXPORT sgEntityGetPos(SGEntity* entity, float* x, float* y);

/**
 * \memberof SGEntity
 * \brief Set the body's x position
 * \param entity The entity of which position we want to set
 * \param[in] x X position
 *
 * This function sets the entity's x position while preserving y position.
 *
 * \note
 *	If a physical body is attached, its position will get changed.
 *
 * \sa
 *	sgEntityGetPosX
 *	sgEntitySetPos
 *	sgEntitySetPosY
 */
void SG_EXPORT sgEntitySetPosX(SGEntity* entity, float x);
/**
 * \memberof SGEntity
 * \brief Get the body's x position
 * \param entity The entity of which position we want to get
 * \return The x position
 *
 * This function gets only the x position of the entity. Note that it is more efficient to use \ref sgEntityGetPos "sgEntityGetPos" if both coordinates are required.
 *
 * \note
 *	If a physical body is attached, this function returns its position.
 *
 * \sa
 *	sgEntitySetPosX
 *	sgEntityGetPos
 *	sgEntityGetPosY
 */
float SG_EXPORT sgEntityGetPosX(SGEntity* entity);

/**
 * \memberof SGEntity
 * \brief Set the body's y position
 * \param entity The entity of which position we want to set
 * \param[in] y Y position
 *
 * This function sets the entity's y position while preserving x position.
 *
 * \note
 *	If a physical body is attached, its position will get changed.
 *
 * \sa
 *	sgEntityGetPosY
 *	sgEntitySetPos
 *	sgEntitySetPosX
 */
void SG_EXPORT sgEntitySetPosY(SGEntity* entity, float y);
/**
 * \memberof SGEntity
 * \brief Get the body's y position
 * \param entity The entity of which position we want to get
 * \return The y position
 *
 * This function gets only the y position of the entity. Note that it is more efficient to use \ref sgEntityGetPos "sgEntityGetPos" if both coordinates are required.
 *
 * \note
 *	If a physical body is attached, this function returns its position.
 *
 * \sa
 *	sgEntitySetPosY
 *	sgEntityGetPos
 *	sgEntityGetPosX
 */
float SG_EXPORT sgEntityGetPosY(SGEntity* entity);
/// @}

/**
 * \name Depth
 * \brief Depth controls in front (and behind) of which entities this one should be drawn.
 */
/// @{
/**
 * \memberof SGEntity
 * \brief Set the entity's depth
 * \param entity The entity of which the depth we want to set
 * \param[in] depth The depth to set
 *
 * \sa
 *	sgEntityGetDepth
 */
void SG_EXPORT sgEntitySetDepth(SGEntity* entity, float depth);
/**
 * \memberof SGEntity
 * \brief Get the entity's depth
 * \param entity The entity of which the depth we want to get
 * \return The depth
 *
 * \sa
 *	sgEntitySetDepth
 */
float SG_EXPORT sgEntityGetDepth(SGEntity* entity);
/// }@

/**
 * \name Angle
 */
/// @{
/**
 * \memberof SGEntity
 * \brief Set the entity's angle in radians
 * \param entity The entity of which the angle we want to set
 * \param[in] rads The angle in radians
 *
 * \note
 *	If a physical body is attached, then the orientation of the body is changed.
 *
 * \sa
 *	sgEntityGetAngleRads
 *	sgEntitySetAngleDegs
 */
void SG_EXPORT sgEntitySetAngleRads(SGEntity* entity, float rads);
/**
 * \memberof SGEntity
 * \brief Get the entity's angle in radians
 * \param entity The entity of which the angle we want to get
 * \return The angle in radians
 *
 * \note
 *	If a physical body is attached, then the orientation of the body is returned.
 *
 * \sa
 *	sgEntitySetAngleRads
 *	sgEntityGetAngleDegs
 */
float SG_EXPORT sgEntityGetAngleRads(SGEntity* entity);
/**
 * \memberof SGEntity
 * \brief Set the entity's angle in degrees
 * \param entity The entity of which the angle we want to set
 * \param[in] degs The angle in degrees
 *
 * \note
 *	If a physical body is attached, then the orientation of the body is changed.
 *
 * \sa
 *	sgEntityGetAngleDegs
 *	sgEntitySetAngleRads
 */
void SG_EXPORT sgEntitySetAngleDegs(SGEntity* entity, float degs);
/**
 * \memberof SGEntity
 * \brief Get the entity's angle in degrees
 * \param entity The entity of which the angle we want to get
 * \return The angle in degrees
 * \note
 *	If a physical body is attached, then the orientation of the body is returned.
 *
 * \sa
 *	sgEntitySetAngleDegs
 *	sgEntityGetAngleRads
 */
float SG_EXPORT sgEntityGetAngleDegs(SGEntity* entity);
/// @}

/**
 * \name Drawing
 */
/// @{
/**
 * \memberof SGEntity
 * \brief Draw the entity with its position and orientation
 * \param entity The entity to draw
 *
 * If a sprite is attached and the entity is visible, this function draws the sprite at the entity's position and orientation, otherwise it does nothing.
 */
void SG_EXPORT sgEntityDraw(SGEntity* entity);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_ENTITY_H__
