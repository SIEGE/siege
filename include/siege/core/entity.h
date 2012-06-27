/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

/**
 * Title: Entity
 */

#ifndef __SIEGE_CORE_ENTITY_H__
#define __SIEGE_CORE_ENTITY_H__

#include "../common.h"
#include "../util/list.h"
#include "../util/tree.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \name Event types
 */
/// @{
// EventClient types -- these should be OR'd together
#define SG_EVT_MODULE	0x00010000U
#define SG_EVT_CORE		0x00020000U
#define SG_EVT_WINDOW	0x00040000U
#define SG_EVT_MOUSE	0x00080000U
#define SG_EVT_KEYBOARD 0x00100000U
#define SG_EVT_JOYSTICK 0x00200000U
#define SG_EVT_NETWORK	0x00400000U
#define SG_EVT_PHYSICS	0x00800000U
#define SG_EVT_LEVEL	0x01000000U
#define SG_EVT_LOCAL	0x02000000U
#define SG_EVT_USER     0x80000000U
#define SG_EVT_ALL		0xFFFF0000U
/// @}

/**
 * \name Event functions
 * \brief Used in \ref SGEntity "SGEntity"
 */
/// @{
#define SG_EVF_INIT   (SG_EVT_MODULE | 0x0001)
#define SG_EVF_DEINIT (SG_EVT_MODULE | 0x0002)

#define SG_EVF_START (SG_EVT_CORE | 0x0001)
#define SG_EVF_EXIT  (SG_EVT_CORE | 0x0002)
#define SG_EVF_TICK  (SG_EVT_CORE | 0x0004)
#define SG_EVF_TICKB (SG_EVT_CORE | 0x0008)
#define SG_EVF_TICKE (SG_EVT_CORE | 0x0010)
#define SG_EVF_DRAW  (SG_EVT_CORE | 0x0020)

#define SG_EVF_WINOPEN	 (SG_EVT_WINDOW | 0x0001)
#define SG_EVF_WINCLOSE  (SG_EVT_WINDOW | 0x0002)
#define SG_EVF_WINRESIZE (SG_EVT_WINDOW | 0x0004)

/*
 * H: held
 * P: press
 * R: release
 * A: repeat ("again")
 */

#define SG_EVF_MOUSEBUTH  (SG_EVT_MOUSE | 0x0001)
#define SG_EVF_MOUSEBUTP  (SG_EVT_MOUSE | 0x0002)
#define SG_EVF_MOUSEBUTR  (SG_EVT_MOUSE | 0x0004)
#define SG_EVF_MOUSEBUTLH (SG_EVT_MOUSE | 0x0008)
#define SG_EVF_MOUSEBUTLP (SG_EVT_MOUSE | 0x0010)
#define SG_EVF_MOUSEBUTLR (SG_EVT_MOUSE | 0x0020)
#define SG_EVF_MOUSEBUTRH (SG_EVT_MOUSE | 0x0040)
#define SG_EVF_MOUSEBUTRP (SG_EVT_MOUSE | 0x0080)
#define SG_EVF_MOUSEBUTRR (SG_EVT_MOUSE | 0x0100)
#define SG_EVF_MOUSEBUTMH (SG_EVT_MOUSE | 0x0200)
#define SG_EVF_MOUSEBUTMP (SG_EVT_MOUSE | 0x0400)
#define SG_EVF_MOUSEBUTMR (SG_EVT_MOUSE | 0x0800)
#define SG_EVF_MOUSEMOVE  (SG_EVT_MOUSE | 0x1000)
#define SG_EVF_MOUSEWHEEL (SG_EVT_MOUSE | 0x2000)

#define SG_EVF_KEYKEYH	(SG_EVT_KEYBOARD | 0x0001)
#define SG_EVF_KEYKEYP	(SG_EVT_KEYBOARD | 0x0002)
#define SG_EVF_KEYKEYR	(SG_EVT_KEYBOARD | 0x0004)
#define SG_EVF_KEYKEYA	(SG_EVT_KEYBOARD | 0x0008)
#define SG_EVF_KEYCHARP (SG_EVT_KEYBOARD | 0x0020)

#define SG_EVF_JOYSTICKBUTH (SG_EVT_JOYSTICK | 0x0001)
#define SG_EVF_JOYSTICKBUTP (SG_EVT_JOYSTICK | 0x0002)
#define SG_EVF_JOYSTICKBUTR (SG_EVT_JOYSTICK | 0x0004)
#define SG_EVF_JOYSTICKMOVE (SG_EVT_JOYSTICK | 0x0008)

//#define SG_EVF_NET (SG_EVT_NETWORK | 0x0001)

#define SG_EVF_PHYSCOLH  (SG_EVT_PHYSICS | 0x0001)
#define SG_EVF_PHYSCOL1  (SG_EVT_PHYSICS | 0x0002)
#define SG_EVF_PHYSCOL2  (SG_EVT_PHYSICS | 0x0004)
#define SG_EVF_PHYSCOLBH (SG_EVT_PHYSICS | 0x0008)
#define SG_EVF_PHYSCOLB1 (SG_EVT_PHYSICS | 0x0010)
#define SG_EVF_PHYSCOLB2 (SG_EVT_PHYSICS | 0x0020)
#define SG_EVF_PHYSCOLEH (SG_EVT_PHYSICS | 0x0040)
#define SG_EVF_PHYSCOLE1 (SG_EVT_PHYSICS | 0x0080)
#define SG_EVF_PHYSCOLE2 (SG_EVT_PHYSICS | 0x0100)
#define SG_EVF_PHYSCOLRH (SG_EVT_PHYSICS | 0x0200)
#define SG_EVF_PHYSCOLR1 (SG_EVT_PHYSICS | 0x0400)
#define SG_EVF_PHYSCOLR2 (SG_EVT_PHYSICS | 0x0800)

#define SG_EVF_LVLSTART (SG_EVT_LEVEL | 0x0001)
#define SG_EVF_LVLEND	(SG_EVT_LEVEL | 0x0002)

#define SG_EVF_USER     SG_EVT_USER

#define SG_EV_USERMASK  0x7FFFFFFFU // available bits for the user, same as ~SG_EVF_USER
/// @}

struct SGSprite;
struct SGMask;
struct SGPhysicsBody;
struct SGAudioSource;
struct SGPhysicsCollision;

/**
 * Struct: SGEntity
 *
 * Entity, the main game object.
 *
 * This is the object which acts as sort of glue for siege -
 * it glues together sprites, physics, audio, etc...
 *
 * It is meant to be used for just about everything in a level.
 */
typedef struct SGEntity
{
	/**
	 * Variable: active
	 *
	 * Is the entity active?
	 *
	 * If set to SG_TRUE, the Entity can take events, otherwise it is skipped.
	 */
	SGbool active;
	/**
	 * Variable: pausable
	 *
	 * Is the entity pausable?
	 *
	 * If set to SG_TRUE, then the entity is skipped during event handling if the game is paused.
	 */
	SGbool pausable;
	/**
	 * Variable: node
	 *
	 * Handle to the linked list holding the entity.
	 *
	 * Warning:
	 *  For internal use only.
	 */
    SGListNode* node;
	/**
	 * Variable: data
	 *
	 * User-provided data.
	 *
	 * Note:
	 *  Do not forget to free the data before destroying the entity
	 * 	if required - SIEGE handles this as an opaque pointer and thus
	 *  will not do *anything* with this data.
	 */
	void* data;

	/**
	 * Variable: visible
	 *
	 * Is the entity visible?
	 *
	 * If an entity is invisible, it is not automatically drawn. This
	 * does not affect manually drawing the entity via <SGEntityDraw>.
	 */
	SGbool visible;

    /**
     * Variables: tnode, tlnode
     *
     * Tree node, for use with name lookups. Holds the entity's name,
     * can be NULL.
     */
    SGTreeNode* tnode;
    SGListNode* tlnode;

	// attachments...
	/**
	 * Variable: sprite
	 *
	 * The attached sprite.
	 *
	 * Warning:
	 * 	For internal use only.
	 */
	struct SGSprite* sprite;
	/**
	 * Variable: mask
	 *
	 * The attached mask.
	 *
	 * Warning:
	 *	For internal use only.
	 */
	struct SGMask* mask;
	/**
	 * Variable: body
	 *
	 * The attached physics body.
	 *
	 * Warning:
	 *	For internal use only.
	 */
	struct SGPhysicsBody* body;
	/**
	 * Variable: source
	 *
	 * The attached audio source.
	 *
	 * Warning:
	 *	For internal use only.
	 */
	struct SGAudioSource* source;

	/**
	 * Variables: x,y
	 *
	 * Entity's position.
	 *
	 * x - horizontal position
	 * y - vertical position
	 *
	 * Note:
	 *	Not used if a body is attached.
	 *
	 * Warning:
	 *	For internal use only.
	 */
	float x;
	float y;
	/**
	 * Variable: depth
	 *
	 * Entity's depth, used for drawing order.
	 *
	 * Warning:
	 *	For internal use only.
	 */
	float depth;
	/**
	 * Variable: angle
	 *
	 * Entity's angle in radians.
	 *
	 * Note:
	 *	Not used if a body is attached.
	 *
	 * Warning:
	 *	For internal use only.
	 */
	float angle;

	/**
	 * Variable: minside
	 *
	 * Set to SG_TRUE if the mouse was inside in the previous iteration.
	 * Will be used to implement <lcMouseEnter> and <lcMouseExit>.
	 *
	 * Warning:
	 * 	For internal use only.
	 */
	SGbool minside;

	/**
	 * Group: Callbacks
	 */
	/**
	 * Variable: cbInside
	 *
	 * Is the point considered to be inside the entity?
	 *
	 * Returns:
	 * 	SG_TRUE if the point is inside and SG_FALSE otherwise.
	 */
	SGbool SG_EXPORT (*cbInside)(struct SGEntity* entity, float x, float y);

	/**
	 * Group: Local events
	 */

	/**
	 * Variable: lcDestroy
	 *
	 * The entity is about to be destroyed.
	 */
	void SG_EXPORT (*lcDestroy)(struct SGEntity* entity);

	/**
	 * Variables: lcMouse*
	 *
	 * Mouse-related local events.
	 *
	 * lcMouseEnter - Mouse has just entered the entity's area
	 * lcMouseExit - Mouse has just leaved the entity's area
	 *
	 * lcMouseButton - A mouse button is being held over the object
	 * lcMouseButtonPress - A mouse button has just been pressed over the object
	 * lcMouseButtonRelease - A mouse button has just been released over the object
	 *
	 * lcMouseButtonLeft - Left mouse button is being held over the object
	 * lcMouseButtonLeftPress - Left mouse button has just been pressed over the object
	 * lcMouseButtonLeftRelease - Left mouse button has just been released over the object
	 *
	 * lcMouseButtonRight - Right mouse button is being held over the object
	 * lcMouseButtonRightPress - Right mouse button has just been pressed over the object
	 * lcMouseButtonRightRelease - Right mouse button has just been released over the object
	 *
	 * lcMouseButtonMiddle - Middle mouse button is being held over the object
	 * lcMouseButtonMiddlePress - Middle mouse button has just been pressed over the object
	 * lcMouseButtonMiddleRelease - Middle mouse button has just been released over the object
	 *
	 * lcMouseMove - The mouse has just been moved over the object
	 * lcMouseWheel - The mouse wheel has just been scrolled over the object
	 *
	 * Parameters:
	 * 	entity - The entity which is receiving the message
	 *  button - The mouse button
	 *  x, y   - New mouse position
	 *  wheel  - New mouse wheel position
	 *
	 * TODO:
	 * 	- Should two entities with the same depth both get this called
	 *    if applicable?
	 *  - Should lcMouseExit be renamed to lcMouseLeave?
	 */
	void SG_EXPORT (*lcMouseEnter)(struct SGEntity* entity);
	void SG_EXPORT (*lcMouseExit)(struct SGEntity* entity);

	void SG_EXPORT (*lcMouseButton)(struct SGEntity* entity, SGuint button);
	void SG_EXPORT (*lcMouseButtonPress)(struct SGEntity* entity, SGuint button);
	void SG_EXPORT (*lcMouseButtonRelease)(struct SGEntity* entity, SGuint button);

	void SG_EXPORT (*lcMouseButtonLeft)(struct SGEntity* entity);
	void SG_EXPORT (*lcMouseButtonLeftPress)(struct SGEntity* entity);
	void SG_EXPORT (*lcMouseButtonLeftRelease)(struct SGEntity* entity);

	void SG_EXPORT (*lcMouseButtonRight)(struct SGEntity* entity);
	void SG_EXPORT (*lcMouseButtonRightPress)(struct SGEntity* entity);
	void SG_EXPORT (*lcMouseButtonRightRelease)(struct SGEntity* entity);

	void SG_EXPORT (*lcMouseButtonMiddle)(struct SGEntity* entity);
	void SG_EXPORT (*lcMouseButtonMiddlePress)(struct SGEntity* entity);
	void SG_EXPORT (*lcMouseButtonMiddleRelease)(struct SGEntity* entity);

	void SG_EXPORT (*lcMouseMove)(struct SGEntity* entity, SGint x, SGint y);
	void SG_EXPORT (*lcMouseWheel)(struct SGEntity* entity, SGint wheel);

	/**
	 * Variables: lcCollision*
	 *
	 * Physical collision events.
	 *
	 * lcCollision - Two objects are in collision with one another
	 * lcCollisionOne - Collision event for the first of the two objects
	 * lcCollisionTwo - Collision event for the second of the two objects
	 *
	 * lcCollisionBegin - Two objects have just come into colision with one another
	 * lcCollisionOneBegin - Collision start event for the first of the two objects
	 * lcCollisionTwoBegin - Collision start event for the second of the two objects
	 *
	 * lcCollisionEnd - Two objects are no longer in collision with one another
	 * lcCollisionOneEnd - Collision end event for the first of the two objects
	 * lcCollisionTwoEnd - Collision end event for the second of the two objects
	 *
	 * Parameters:
	 * 	entity - The entity which is receiving the message
	 *  other - The entity that the collision happened with
	 *  coll - Collision handler
	 */

	void SG_EXPORT (*lcCollision)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
	void SG_EXPORT (*lcCollisionOne)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
	void SG_EXPORT (*lcCollisionTwo)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);

	void SG_EXPORT (*lcCollisionBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
	void SG_EXPORT (*lcCollisionOneBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
	void SG_EXPORT (*lcCollisionTwoBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);

	void SG_EXPORT (*lcCollisionEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
	void SG_EXPORT (*lcCollisionOneEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);
	void SG_EXPORT (*lcCollisionTwoEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* coll);

	/**
	 * Group: Global events
	 */

	/**
	 * Variables: Init/deinit
	 *
	 * Called just after <sgInit> or just before <sgDeinit>, respectively.
	 *
	 * evInit - Called on <sgInit>
	 * evDeinit - Called on <sgDeinit>
	 *
	 * Parameters:
	 * 	entity - The entity which is receiving the message
	 */
	void SG_EXPORT (*evInit)(struct SGEntity* entity);
	void SG_EXPORT (*evDeinit)(struct SGEntity* entity);

	/**
	 * Variables: Looping
	 *
	 * These are called regarding iterations in SIEGE.
	 *
	 * evStart - Called on the first loop, when <sgLoop> is first called or on <sgRun>
	 * evExit - Called before exiting SIEGE loop, usually on <sgStop>
	 *
	 * evTick - Second event called in each loop
	 * evTickBegin - First event called in each loop
	 * evTickEnd - Third event called in each loop
	 * evDraw - Fourth event called in each loop - drawing (but nothing else!) should be done here
	 *
	 * Parameters:
	 * 	entity - The entity which is receiving the message
	 */
	void SG_EXPORT (*evStart)(struct SGEntity* entity);
	void SG_EXPORT (*evExit)(struct SGEntity* entity);

	void SG_EXPORT (*evTick)(struct SGEntity* entity);
	void SG_EXPORT (*evTickBegin)(struct SGEntity* entity);
	void SG_EXPORT (*evTickEnd)(struct SGEntity* entity);
	void SG_EXPORT (*evDraw)(struct SGEntity* entity);

	/**
	 * Variables: evWindow*
	 *
	 * Window-related events.
	 *
	 * evWindowOpen - The window has just been opened
	 * evWindowClose - The window has just been closed
	 * evWindowResize - The window has been resized
	 *
	 * Parameters:
	 * 	entity - The entity which is receiving the message
	 *  width, height - The new window size
	 */
	void SG_EXPORT (*evWindowOpen)(struct SGEntity* entity);
	void SG_EXPORT (*evWindowClose)(struct SGEntity* entity);
	void SG_EXPORT (*evWindowResize)(struct SGEntity* entity, SGuint width, SGuint height);

	/**
	 * Variables: evMouse*
	 *
	 * Mouse-related global events.
	 *
	 * evMouseButton - A mouse button is being held down
	 * evMouseButtonPress - A mouse button has just been pressed
	 * evMouseButtonRelease - A mouse button has just been released
	 *
	 * evMouseButtonLeft - Left mouse button is being held down
	 * evMouseButtonLeftPress - Left mouse button has just been pressed
	 * evMouseButtonLeftRelease - Left mouse button has just been released
	 *
	 * evMouseButtonRight - Right mouse button is being held down
	 * evMouseButtonRightPress - Right mouse button has just been pressed
	 * evMouseButtonRightRelease - Right mouse button has just been released
	 *
	 * evMouseButtonMiddle - Middle mouse button is being held down
	 * evMouseButtonMiddlePress - Middle mouse button has just been pressed
	 * evMouseButtonMiddleRelease - Middle mouse button has just been released
	 *
	 * evMouseMove - The mouse has just been moved
	 * evMouseWheel - The mouse wheel has just been scrolled
	 *
	 * Parameters:
	 * 	entity - The entity which is receiving the message
	 *  button - The mouse button
	 *  x, y   - New mouse position
	 *  wheel  - New mouse wheel position
	 */
	void SG_EXPORT (*evMouseButton)(struct SGEntity* entity, SGuint button);
	void SG_EXPORT (*evMouseButtonPress)(struct SGEntity* entity, SGuint button);
	void SG_EXPORT (*evMouseButtonRelease)(struct SGEntity* entity, SGuint button);

	void SG_EXPORT (*evMouseButtonLeft)(struct SGEntity* entity);
	void SG_EXPORT (*evMouseButtonLeftPress)(struct SGEntity* entity);
	void SG_EXPORT (*evMouseButtonLeftRelease)(struct SGEntity* entity);

	void SG_EXPORT (*evMouseButtonRight)(struct SGEntity* entity);
	void SG_EXPORT (*evMouseButtonRightPress)(struct SGEntity* entity);
	void SG_EXPORT (*evMouseButtonRightRelease)(struct SGEntity* entity);

	void SG_EXPORT (*evMouseButtonMiddle)(struct SGEntity* entity);
	void SG_EXPORT (*evMouseButtonMiddlePress)(struct SGEntity* entity);
	void SG_EXPORT (*evMouseButtonMiddleRelease)(struct SGEntity* entity);

	void SG_EXPORT (*evMouseMove)(struct SGEntity* entity, SGint x, SGint y);
	void SG_EXPORT (*evMouseWheel)(struct SGEntity* entity, SGint wheel);

	/**
	 * Variables: evKeyboard*
	 *
	 * Keyboard-related events.
	 *
	 * evKeyboardKey - A key is being held down
	 * evKeyboardKeyPress - A key has just been pressed
	 * evKeyboardKeyRelease - A key has just been released
	 * evKeyboardKeyRepeat - A key repeat according to the key repeat interval
	 *
	 * evKeyboardKeyPress - A key representing a character has just been pressed
	 * evKeyboardKeyRepeat - A key representing a character has just been repeated according to the key repeat interval
	 *
	 * Parameters:
	 * 	entity - The entity which is receiving the message
	 *  key    - The key that triggered the event
	 *  chr    - The UTF-32 character that triggered the event
	 */
	void SG_EXPORT (*evKeyboardKey)(struct SGEntity* entity, SGuint key);
	void SG_EXPORT (*evKeyboardKeyPress)(struct SGEntity* entity, SGuint key);
	void SG_EXPORT (*evKeyboardKeyRelease)(struct SGEntity* entity, SGuint key);
	void SG_EXPORT (*evKeyboardKeyRepeat)(struct SGEntity* entity, SGuint key);

	void SG_EXPORT (*evKeyboardCharPress)(struct SGEntity* entity, SGdchar chr);

	/**
	 * Variables: evJoystick*
	 *
	 * Joystick-related events.
	 *
	 * evJoystickButton - A joystick button is being held down
	 * evJoystickButtonPress - A joystick button has just been pressed
	 * evJoystickButtonRelease - A joystick button has just been released
	 * evJoystickMode - The joystick axis have moved
	 *
	 * Parameters:
	 * 	entity  - The entity which is receiving the message
	 *  joy     - The joystick ID
	 *  button  - The button ID
	 *  axis    - The axis positions
	 *  numaxis - The number of axis
	 */
	void SG_EXPORT (*evJoystickButton)(struct SGEntity* entity, SGuint joy, SGuint button);
	void SG_EXPORT (*evJoystickButtonPress)(struct SGEntity* entity, SGuint joy, SGuint button);
	void SG_EXPORT (*evJoystickButtonRelease)(struct SGEntity* entity, SGuint joy, SGuint button);
	void SG_EXPORT (*evJoystickMove)(struct SGEntity* entity, SGuint joy, SGfloat* axis, size_t numaxis);

	// networking goes here

	/**
	 * Variables: evLevel*
	 *
	 * Level-related events.
	 *
	 * evLevelStart - A level has just loaded and started
	 * evLevelEnd - A level has just ended
	 *
	 * Parameters:
	 * 	entity  - The entity which is receiving the message
	 */
	void SG_EXPORT (*evLevelStart)(struct SGEntity* entity);
	void SG_EXPORT (*evLevelEnd)(struct SGEntity* entity);

    void SG_EXPORT (*evUser)(struct SGEntity* entity, SGuint id, va_list args);
} SGEntity;

#ifdef SG_BUILD_LIBRARY
SGList* _sg_entList;
SGTree* _sg_entTree;
SGbool _sg_entStop;
#endif // SG_BUILD_LIBRARY

/**
 * Group: Functions
 */

SGbool SG_EXPORT _sgEntityInit(void);
SGbool SG_EXPORT _sgEntityDeinit(void);

/**
 * Function: sgEntityCreate
 *
 * Create a new entity.
 *
 * Returns:
 * 	The newly created entity if successful, NULL otherwise
 */
SGEntity* SG_EXPORT sgEntityCreate(void);
/**
 * Function: sgEntityDestroy
 *
 * Destroy an entity.
 *
 * Note that destroying an entity automatically triggers its <lcDestroy> event.
 *
 * Parameters:
 * 	entity - The entity to destroy. It should not be used anymore after this call.
 */
void SG_EXPORT sgEntityDestroy(SGEntity* entity);
void SG_EXPORT sgEntityDestroyAll(void);

void SG_EXPORT sgEntitySetName(SGEntity* entity, const char* name);
char* SG_EXPORT sgEntityGetName(SGEntity* entity);

/**
 * Functions: sgEntity*Sprite
 *
 * Attach/get the entity's sprite.
 *
 * sgEntitySetSprite - Setter
 * sgEntityGetSprite - Getter
 *
 * Parameters:
 * 	entity - The entity of which the sprite we want to set/get
 *  sprite - The sprite which should be attached (NULL to detach)
 *
 * Returns:
 * 	The getter returns the currently attached sprite, or NULL if none.
 */
void SG_EXPORT sgEntitySetSprite(SGEntity* entity, struct SGSprite* sprite);
struct SGSprite* SG_EXPORT sgEntityGetSprite(SGEntity* entity);

/**
 * Functions: sgEntity*Mask
 *
 * Attach/get the entity's collision mask.
 *
 * sgEntitySetMask - Setter
 * sgEntityGetMask - Getter
 *
 * The mask is a simple bitmask which tells SIEGE which pixels are solid
 * (as in, which collide) and which not.
 *
 * Parameters:
 * 	entity - The entity of which the mask we want to set/get
 *  mask   - The mask which should be attached (NULL to detach)
 *
 * Returns:
 * 	The getter returns the currently attached mask, or NULL if none.
 */
void SG_EXPORT sgEntitySetMask(SGEntity* entity, struct SGMask* mask);
struct SGMask* SG_EXPORT sgEntityGetMask(SGEntity* entity);

/**
 * Functions: sgEntity*PhysicsBody
 *
 * Attach/get the entity's physical body.
 *
 * sgEntitySetPhysicsBody - Setter
 * sgEntityGetPhysicsBody - Getter
 *
 * Parameters:
 * 	entity - The entity of which the body we want to set/get
 *  body   - The body which should be attached (NULL to detach)
 *
 * Returns:
 * 	The getter returns the currently attached body, or NULL if none.
 */
void SG_EXPORT sgEntitySetPhysicsBody(SGEntity* entity, struct SGPhysicsBody* body);
struct SGPhysicsBody* SG_EXPORT sgEntityGetPhysicsBody(SGEntity* entity);

/**
 * Functions: sgEntity*AudioSource
 *
 * Attach/get the entity's audio source.
 *
 * sgEntitySetAudioSource - Setter
 * sgEntityGetAudioSource - Getter
 *
 * Parameters:
 * 	entity - The entity of which the source we want to set/get
 *  source - The source which should be attached (NULL to detach)
 *
 * Returns:
 * 	The getter returns the currently attached source, or NULL if none.
 */
void SG_EXPORT sgEntitySetAudioSource(SGEntity* entity, struct SGAudioSource* source);
struct SGAudioSource* SG_EXPORT sgEntityGetAudioSource(SGEntity* entity);

/**
 * Functions: sgEntity*Pos*
 *
 * Set/get the entity's position.
 *
 * sgEntitySetPos - Set the x and y position
 * sgEntityGetPos - Get the x and y position
 *
 * sgEntitySetPosX - Set the x position, leaving y unchanged
 * sgEntityGetPosX - Get the x position
 *
 * sgEntitySetPosY - Set the y position, leaving x unchanged
 * sgEntityGetPosY - Get the y position
 *
 * Note:
 * 	If a physical body is attached, its position will get changed.
 *
 * Parameters:
 * 	entity - The entity of which the position we want to set/get
 *  x      - Horizontal position
 *  y      - Vertical position
 *
 * Returns:
 * 	PosX/PosY variants return the current x and y position, respectively.
 */
void SG_EXPORT sgEntitySetPos(SGEntity* entity, float x, float y);
void SG_EXPORT sgEntityGetPos(SGEntity* entity, float* x, float* y);

void SG_EXPORT sgEntitySetPosX(SGEntity* entity, float x);
float SG_EXPORT sgEntityGetPosX(SGEntity* entity);

void SG_EXPORT sgEntitySetPosY(SGEntity* entity, float y);
float SG_EXPORT sgEntityGetPosY(SGEntity* entity);

/**
 * Functions: sgEntity*Depth
 *
 * Set/get the entity's depth.
 *
 * sgEntitySetDepth - Setter
 * sgEntityGetDepth - Getter
 *
 * The depth controls on what "layer" the entity should get drawn -
 * those with higher depth are higher up, and are thus drawn over those
 * with a lower depth.
 *
 * Parameters:
 * 	entity - The entity of which the position we want to set/get
 *  depth  - The entity's depth
 *
 * Returns:
 * 	The getter returns the current entity depth.
 */
void SG_EXPORT sgEntitySetDepth(SGEntity* entity, float depth);
float SG_EXPORT sgEntityGetDepth(SGEntity* entity);

/**
 * Functions: sgEntity*Angle*
 *
 * Set/get the entity's angle.
 *
 * sgEntitySetAngleRads - Set the angle in radians
 * sgEntityGetAngleRads - Get the angle in radians
 *
 * sgEntitySetAngleDegs - Set the angle in degrees
 * sgEntityGetAngleDegs - Get the angle in degrees
 *
 * Note:
 * 	If a physical body is attached, the orientation of that body will be changed.
 *
 * Parameters:
 * 	entity - The entity of which the position we want to set/get
 *  rads   - The angle in radians
 *  degs   - The angle in degrees
 *
 * Returns:
 * 	The getters return the current angle in its respective units.
 */

void SG_EXPORT sgEntitySetAngleRads(SGEntity* entity, float rads);
float SG_EXPORT sgEntityGetAngleRads(SGEntity* entity);

void SG_EXPORT sgEntitySetAngleDegs(SGEntity* entity, float degs);
float SG_EXPORT sgEntityGetAngleDegs(SGEntity* entity);

/**
 * Function: sgEntityDraw
 *
 * Draw the entity with its current position and orientation.
 *
 * If a sprite is attached, thus function draws the sprite at the
 * entity's position and orientation, otherwise it does nothing.
 *
 * Parameters:
 * 	entity - The entity to draw.
 */
void SG_EXPORT sgEntityDraw(SGEntity* entity);

SGList* SG_EXPORT sgEntityFind(const char* name);

void SG_EXPORT sgEntityEventSignalv(size_t num, va_list args);
void SG_EXPORT sgEntityEventSignal(size_t num, ...);
void SG_EXPORT sgEntityEventStop(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_ENTITY_H__
