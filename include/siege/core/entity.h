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
#include "../util/smap.h"
#include "../util/vector.h"

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
#define SG_EVT_MODULE    0x00010000U
#define SG_EVT_CORE        0x00020000U
#define SG_EVT_WINDOW    0x00040000U
#define SG_EVT_MOUSE    0x00080000U
#define SG_EVT_KEYBOARD 0x00100000U
#define SG_EVT_JOYSTICK 0x00200000U
#define SG_EVT_NETWORK    0x00400000U
#define SG_EVT_PHYSICS    0x00800000U
#define SG_EVT_LEVEL    0x01000000U
#define SG_EVT_LOCAL    0x02000000U
#define SG_EVT_USER     0x80000000U
#define SG_EVT_ALL        0xFFFF0000U
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

#define SG_EVF_WINOPEN     (SG_EVT_WINDOW | 0x0001)
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

#define SG_EVF_KEYKEYH    (SG_EVT_KEYBOARD | 0x0001)
#define SG_EVF_KEYKEYP    (SG_EVT_KEYBOARD | 0x0002)
#define SG_EVF_KEYKEYR    (SG_EVT_KEYBOARD | 0x0004)
#define SG_EVF_KEYKEYA    (SG_EVT_KEYBOARD | 0x0008)
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
#define SG_EVF_LVLEND    (SG_EVT_LEVEL | 0x0002)

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
     *     if required - SIEGE handles this as an opaque pointer and thus
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
     * Variables: mnode, mlnode
     *
     * Map list info. `mnode` holds the entity name.
     */
    SGSMapNode* mnode;
    SGListNode* mlnode;

    // attachments...
    /**
     * Variable: sprite
     *
     * The attached sprite.
     *
     * Warning:
     *     For internal use only.
     */
    struct SGSprite* sprite;
    /**
     * Variable: mask
     *
     * The attached mask.
     *
     * Warning:
     *    For internal use only.
     */
    struct SGMask* mask;
    /**
     * Variable: body
     *
     * The attached physics body.
     *
     * Warning:
     *    For internal use only.
     */
    struct SGPhysicsBody* body;
    /**
     * Variable: source
     *
     * The attached audio source.
     *
     * Warning:
     *    For internal use only.
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
     *    Not used if a body is attached.
     *
     * Warning:
     *    For internal use only.
     */
    SGVec2 pos;
    /**
     * Variable: depth
     *
     * Entity's depth, used for drawing order.
     *
     * Warning:
     *    For internal use only.
     */
    float depth;
    /**
     * Variable: angle
     *
     * Entity's angle in radians.
     *
     * Note:
     *    Not used if a body is attached.
     *
     * Warning:
     *    For internal use only.
     */
    float angle;

    /**
     * Variable: minside
     *
     * Set to SG_TRUE if the mouse was inside in the previous iteration.
     * Will be used to implement <lcMouseEnter> and <lcMouseExit>.
     *
     * Warning:
     *     For internal use only.
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
     *     SG_TRUE if the point is inside and SG_FALSE otherwise.
     */
    SGbool SG_CALL (*cbInside)(struct SGEntity* entity, float x, float y);

    /**
     * Group: Local events
     */

    /**
     * Variable: lcDestroy
     *
     * The entity is about to be destroyed.
     */
    void SG_CALL (*lcDestroy)(struct SGEntity* entity);

    /**
     * Variables: lcCollision*
     *
     * Physical collision events.
     *
     * lcCollision - Two objects are in collision with one another
     * lcCollisionBegin - Two objects have just come into colision with one another
     * lcCollisionEnd - Two objects are no longer in collision with one another
     *
     * Parameters:
     *     entity - The entity which is receiving the message
     *     other - The entity that the collision happened with
     *     col - Collision handler
     *     idx - Object number in the collision (either 0 or 1)
     */

    void SG_CALL (*lcCollision)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* col, SGubyte idx);
    void SG_CALL (*lcCollisionBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* col, SGubyte idx);
    void SG_CALL (*lcCollisionEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGPhysicsCollision* col, SGubyte idx);

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
     *     entity - The entity which is receiving the message
     */
    void SG_CALL (*evInit)(struct SGEntity* entity);
    void SG_CALL (*evDeinit)(struct SGEntity* entity);

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
     *     entity - The entity which is receiving the message
     */
    void SG_CALL (*evStart)(struct SGEntity* entity);
    void SG_CALL (*evExit)(struct SGEntity* entity);

    void SG_CALL (*evTick)(struct SGEntity* entity);
    void SG_CALL (*evTickBegin)(struct SGEntity* entity);
    void SG_CALL (*evTickEnd)(struct SGEntity* entity);
    void SG_CALL (*evDraw)(struct SGEntity* entity);

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
     *     entity - The entity which is receiving the message
     *  width, height - The new window size
     */
    void SG_CALL (*evWindowOpen)(struct SGEntity* entity);
    void SG_CALL (*evWindowClose)(struct SGEntity* entity);
    void SG_CALL (*evWindowResize)(struct SGEntity* entity, SGuint width, SGuint height);

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
     *     entity - The entity which is receiving the message
     *  button - The mouse button
     *  x, y   - New mouse position
     *  wheel  - New mouse wheel position
     */
    void SG_CALL (*evMouseButton)(struct SGEntity* entity, SGuint button);
    void SG_CALL (*evMouseButtonPress)(struct SGEntity* entity, SGuint button);
    void SG_CALL (*evMouseButtonRelease)(struct SGEntity* entity, SGuint button);

    void SG_CALL (*evMouseButtonLeft)(struct SGEntity* entity);
    void SG_CALL (*evMouseButtonLeftPress)(struct SGEntity* entity);
    void SG_CALL (*evMouseButtonLeftRelease)(struct SGEntity* entity);

    void SG_CALL (*evMouseButtonRight)(struct SGEntity* entity);
    void SG_CALL (*evMouseButtonRightPress)(struct SGEntity* entity);
    void SG_CALL (*evMouseButtonRightRelease)(struct SGEntity* entity);

    void SG_CALL (*evMouseButtonMiddle)(struct SGEntity* entity);
    void SG_CALL (*evMouseButtonMiddlePress)(struct SGEntity* entity);
    void SG_CALL (*evMouseButtonMiddleRelease)(struct SGEntity* entity);

    void SG_CALL (*evMouseMove)(struct SGEntity* entity, SGint x, SGint y);
    void SG_CALL (*evMouseWheel)(struct SGEntity* entity, SGint wheel);

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
     *     entity - The entity which is receiving the message
     *  key    - The key that triggered the event
     *  chr    - The UTF-32 character that triggered the event
     */
    void SG_CALL (*evKeyboardKey)(struct SGEntity* entity, SGuint key);
    void SG_CALL (*evKeyboardKeyPress)(struct SGEntity* entity, SGuint key);
    void SG_CALL (*evKeyboardKeyRelease)(struct SGEntity* entity, SGuint key);
    void SG_CALL (*evKeyboardKeyRepeat)(struct SGEntity* entity, SGuint key);

    void SG_CALL (*evKeyboardCharPress)(struct SGEntity* entity, SGdchar chr);

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
     *     entity  - The entity which is receiving the message
     *  joy     - The joystick ID
     *  button  - The button ID
     *  axis    - The axis positions
     *  numaxis - The number of axis
     */
    void SG_CALL (*evJoystickButton)(struct SGEntity* entity, SGuint joy, SGuint button);
    void SG_CALL (*evJoystickButtonPress)(struct SGEntity* entity, SGuint joy, SGuint button);
    void SG_CALL (*evJoystickButtonRelease)(struct SGEntity* entity, SGuint joy, SGuint button);
    void SG_CALL (*evJoystickMove)(struct SGEntity* entity, SGuint joy, SGfloat* axis, size_t numaxis);

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
     *     entity  - The entity which is receiving the message
     */
    void SG_CALL (*evLevelStart)(struct SGEntity* entity);
    void SG_CALL (*evLevelEnd)(struct SGEntity* entity);

    void SG_CALL (*evUser)(struct SGEntity* entity, SGuint id, va_list args);
} SGEntity;

#ifdef SG_BUILD_LIBRARY
SGList* _sg_entList;
SGSMap* _sg_entSMap;
SGbool _sg_entStop;
#endif // SG_BUILD_LIBRARY

/**
 * Group: Functions
 */

SGbool SG_CALL _sgEntityInit(void);
SGbool SG_CALL _sgEntityDeinit(void);

/**
 * Function: sgEntityCreate
 *
 * Create a new entity.
 *
 * Returns:
 *     The newly created entity if successful, NULL otherwise
 */
SGEntity* SG_CALL sgEntityCreate(void);
/**
 * Function: sgEntityDestroy
 *
 * Destroy an entity.
 *
 * Note that destroying an entity automatically triggers its <lcDestroy> event.
 *
 * Parameters:
 *     entity - The entity to destroy. It should not be used anymore after this call.
 */
void SG_CALL sgEntityDestroy(SGEntity* entity);
void SG_CALL sgEntityDestroyAll(void);

void SG_CALL sgEntitySetName(SGEntity* entity, const char* name);
char* SG_CALL sgEntityGetName(SGEntity* entity);

/**
 * Functions: sgEntity*Sprite
 *
 * Attach/get the entity's sprite.
 *
 * sgEntitySetSprite - Setter
 * sgEntityGetSprite - Getter
 *
 * Parameters:
 *     entity - The entity of which the sprite we want to set/get
 *  sprite - The sprite which should be attached (NULL to detach)
 *
 * Returns:
 *     The getter returns the currently attached sprite, or NULL if none.
 */
void SG_CALL sgEntitySetSprite(SGEntity* entity, struct SGSprite* sprite);
struct SGSprite* SG_CALL sgEntityGetSprite(SGEntity* entity);

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
 *     entity - The entity of which the mask we want to set/get
 *  mask   - The mask which should be attached (NULL to detach)
 *
 * Returns:
 *     The getter returns the currently attached mask, or NULL if none.
 */
void SG_CALL sgEntitySetMask(SGEntity* entity, struct SGMask* mask);
struct SGMask* SG_CALL sgEntityGetMask(SGEntity* entity);

/**
 * Functions: sgEntity*PhysicsBody
 *
 * Attach/get the entity's physical body.
 *
 * sgEntitySetPhysicsBody - Setter
 * sgEntityGetPhysicsBody - Getter
 *
 * Parameters:
 *     entity - The entity of which the body we want to set/get
 *  body   - The body which should be attached (NULL to detach)
 *
 * Returns:
 *     The getter returns the currently attached body, or NULL if none.
 */
void SG_CALL sgEntitySetPhysicsBody(SGEntity* entity, struct SGPhysicsBody* body);
struct SGPhysicsBody* SG_CALL sgEntityGetPhysicsBody(SGEntity* entity);

/**
 * Functions: sgEntity*AudioSource
 *
 * Attach/get the entity's audio source.
 *
 * sgEntitySetAudioSource - Setter
 * sgEntityGetAudioSource - Getter
 *
 * Parameters:
 *     entity - The entity of which the source we want to set/get
 *  source - The source which should be attached (NULL to detach)
 *
 * Returns:
 *     The getter returns the currently attached source, or NULL if none.
 */
void SG_CALL sgEntitySetAudioSource(SGEntity* entity, struct SGAudioSource* source);
struct SGAudioSource* SG_CALL sgEntityGetAudioSource(SGEntity* entity);

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
 *     If a physical body is attached, its position will get changed.
 *
 * Parameters:
 *     entity - The entity of which the position we want to set/get
 *  x      - Horizontal position
 *  y      - Vertical position
 *
 * Returns:
 *     PosX/PosY variants return the current x and y position, respectively.
 */
SG_EXPORT void SG_CALL sgEntitySetPos2fv(SGEntity* entity, SGVec2 pos);
SG_EXPORT void SG_CALL sgEntitySetPos2f(SGEntity* entity, float x, float y);
SG_EXPORT SGVec2 SG_CALL sgEntityGetPos2fv(SGEntity* entity);

void SG_CALL sgEntitySetPosX(SGEntity* entity, float x);
float SG_CALL sgEntityGetPosX(SGEntity* entity);

void SG_CALL sgEntitySetPosY(SGEntity* entity, float y);
float SG_CALL sgEntityGetPosY(SGEntity* entity);

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
 *     entity - The entity of which the position we want to set/get
 *  depth  - The entity's depth
 *
 * Returns:
 *     The getter returns the current entity depth.
 */
void SG_CALL sgEntitySetDepth(SGEntity* entity, float depth);
float SG_CALL sgEntityGetDepth(SGEntity* entity);

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
 *     If a physical body is attached, the orientation of that body will be changed.
 *
 * Parameters:
 *     entity - The entity of which the position we want to set/get
 *  rads   - The angle in radians
 *  degs   - The angle in degrees
 *
 * Returns:
 *     The getters return the current angle in its respective units.
 */

void SG_CALL sgEntitySetAngleRads(SGEntity* entity, float rads);
float SG_CALL sgEntityGetAngleRads(SGEntity* entity);

void SG_CALL sgEntitySetAngleDegs(SGEntity* entity, float degs);
float SG_CALL sgEntityGetAngleDegs(SGEntity* entity);

/**
 * Function: sgEntityDraw
 *
 * Draw the entity with its current position and orientation.
 *
 * If a sprite is attached, thus function draws the sprite at the
 * entity's position and orientation, otherwise it does nothing.
 *
 * Parameters:
 *     entity - The entity to draw.
 */
void SG_CALL sgEntityDraw(SGEntity* entity);

SGList* SG_CALL sgEntityFind(const char* name);
SGEntity* SG_CALL sgEntityFindIter(SGEntity* prev, const char* name);

void SG_CALL sgEntityEventSignalv(size_t num, va_list args);
void SG_CALL sgEntityEventSignal(size_t num, ...);
void SG_CALL sgEntityEventStop(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_CORE_ENTITY_H__
