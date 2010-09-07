#ifndef __SIEGE_CORE_ENTITY_H__
#define __SIEGE_CORE_ENTITY_H__

#include "../common.h"
#include "event.h"

struct SGSprite;
struct SGPhysicsBody;
struct SGSource;

// employs an EventClient wrapper over the "generalized" events above
typedef struct _SGEntityCall
{
    SGuint num;
    SGenum* types;
    void** args;
} _SGEntityCall;

/**
    \brief Entity, the main game "class"

    This is the "class" which acts as sort of glue for siege - it glues together sprites, physics, audio, etc...
    It is meant to be used for just about everything in a level.
*/
typedef struct SGEntity
{
    SGenum type;
    SGbool active;
    SGbool pausable;
    SGEvent* event;
    SGvoid* data;

    SGbool visible;
    struct SGSprite* sprite;
    struct SGSprite* mask;
    struct SGPhysicsBody* body;
    struct SGSource* source;
    float x;
    float y;
    float depth;
    float angle;

    /**
        \name Initialization/deinitialization events
    */
    // @{
    SGvoid SG_EXPORT (*evInit)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evDeinit)(struct SGEntity* entity);
    // @}

    /**
        \name Core events
    */
    // @{
    SGvoid SG_EXPORT (*evStart)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evExit)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evTick)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evTickBegin)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evTickEnd)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evDraw)(struct SGEntity* entity);
    // @}

    /**
        \name Window events
    */
    // @{
    SGvoid SG_EXPORT (*evWindowOpen)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evWindowClose)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evWindowResize)(struct SGEntity* entity, SGuint width, SGuint height);
    // @}

    /**
        \name Mouse events
    */
    // @{
    SGvoid SG_EXPORT (*evMouseButton)(struct SGEntity* entity, SGuint button);
    SGvoid SG_EXPORT (*evMouseButtonPress)(struct SGEntity* entity, SGuint button);
    SGvoid SG_EXPORT (*evMouseButtonRelease)(struct SGEntity* entity, SGuint button);

    SGvoid SG_EXPORT (*evMouseButtonLeft)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evMouseButtonLeftPress)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evMouseButtonLeftRelease)(struct SGEntity* entity);

    SGvoid SG_EXPORT (*evMouseButtonRight)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evMouseButtonRightPress)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evMouseButtonRightRelease)(struct SGEntity* entity);

    SGvoid SG_EXPORT (*evMouseButtonMiddle)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evMouseButtonMiddlePress)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evMouseButtonMiddleRelease)(struct SGEntity* entity);

    SGvoid SG_EXPORT (*evMouseMove)(struct SGEntity* entity, SGint x, SGint y);
    SGvoid SG_EXPORT (*evMouseWheel)(struct SGEntity* entity, SGint wheel);
    // @}

    /**
        \name Keyboard events
    */
    // @{
    SGvoid SG_EXPORT (*evKeyboardKey)(struct SGEntity* entity, SGuint key);
    SGvoid SG_EXPORT (*evKeyboardKeyPress)(struct SGEntity* entity, SGuint key);
    SGvoid SG_EXPORT (*evKeyboardKeyRelease)(struct SGEntity* entity, SGuint key);
    SGvoid SG_EXPORT (*evKeyboardKeyRepeat)(struct SGEntity* entity, SGuint key);

    //SGvoid SG_EXPORT (*evKeyboardChar)(struct SGEntity* entity, SGdchar chr);
    SGvoid SG_EXPORT (*evKeyboardCharPress)(struct SGEntity* entity, SGdchar chr);
    //SGvoid SG_EXPORT (*evKeyboardCharRelease)(struct SGEntity* entity, SGdchar chr);
    SGvoid SG_EXPORT (*evKeyboardCharRepeat)(struct SGEntity* entity, SGdchar chr);
    // @}

    /**
        \name Joystick events
    */
    // @{
    SGvoid SG_EXPORT (*evJoystickButton)(struct SGEntity* entity, SGuint joy, SGuint button);
    SGvoid SG_EXPORT (*evJoystickButtonPress)(struct SGEntity* entity, SGuint joy, SGuint button);
    SGvoid SG_EXPORT (*evJoystickButtonRelease)(struct SGEntity* entity, SGuint joy, SGuint button);
    SGvoid SG_EXPORT (*evJoystickMove)(struct SGEntity* entity, SGuint joy, SGfloat* axis, SGuint numaxis);
    // @}

    // networking goes here

    /**
        \name Collision events
    */
    // @{
    SGvoid SG_EXPORT (*evCollision)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);
    SGvoid SG_EXPORT (*evCollisionOne)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);
    SGvoid SG_EXPORT (*evCollisionTwo)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);

    SGvoid SG_EXPORT (*evCollisionBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);
    SGvoid SG_EXPORT (*evCollisionOneBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);
    SGvoid SG_EXPORT (*evCollisionTwoBegin)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);

    SGvoid SG_EXPORT (*evCollisionEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);
    SGvoid SG_EXPORT (*evCollisionOneEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);
    SGvoid SG_EXPORT (*evCollisionTwoEnd)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionPoint* point);

    SGvoid SG_EXPORT (*evCollisionResult)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionResult* result);
    SGvoid SG_EXPORT (*evCollisionOneResult)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionResult* result);
    SGvoid SG_EXPORT (*evCollisionTwoResult)(struct SGEntity* entity, struct SGEntity* other, struct SGCollisionResult* result);
    // @}

    /**
        \name Level events
    */
    // @{
    SGvoid SG_EXPORT (*evLevelStart)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evLevelEnd)(struct SGEntity* entity);
    // @}
} SGEntity;

SGbool SG_EXPORT _sg_evCall(SGEntity* entity, _SGEntityCall* call);

SGbool SG_EXPORT _sgEntityInit(void);
SGbool SG_EXPORT _sgEntityDeinit(void);

/**
    \memberof SGEntity
    \brief Create a new entity
    \param priority The entity's priority - higher priority entities get their events called first
    \param type The entity's event subtype - these are used to filter which events should be called
    \return The newly created entity if successful, NULL otherwise
*/
SGEntity* SG_EXPORT sgEntityCreate(float priority, SGenum type);
/**
    \memberof SGEntity
    \brief Destroy an entity
    \param entity The entity to destroy. It should not be used anymore after this call.
*/
void SG_EXPORT sgEntityDestroy(SGEntity* entity);

/**
    \name Sprites
*/
// @{
/**
    \memberof SGEntity
    \brief Attach a sprite to the entity
    \param entity The entity of which the sprite we want to attach
    \param sprite The sprite which should be attached or NULL to detach
*/
void SG_EXPORT sgEntitySetSprite(SGEntity* entity, struct SGSprite* sprite);
/**
    \memberof SGEntity
    \brief Get the currently attached sprite
    \param entity The entity of which the sprite we want to get
    \return The sprite if one was attached, NULL otherwise
*/
struct SGSprite* SG_EXPORT sgEntityGetSprite(SGEntity* entity);
// @}

/**
    \name Masks
*/
// @{
/**
    \memberof SGEntity
    \brief Attach a mask to the entity
    \param entity The entity of which the mask we want to attach
    \param mask The mask (sprite) which should be attached or NULL to detach

    The mask is a simple sprite which tells SIEGE which pixels are solid (as in, which collide). If mask is NULL, then the sprite itself becomes a mask.
*/
void SG_EXPORT sgEntitySetMask(SGEntity* entity, struct SGSprite* mask);
/**
    \memberof SGEntity
    \brief Get the currently attached mask
    \param entity The entity of which the mask we want to get
    \return The mask if one was attached, NULL otherwise
*/
struct SGSprite* SG_EXPORT sgEntityGetMask(SGEntity* entity);
// @}

/**
    \name Physical bodies
*/
// @{
/**
    \memberof SGEntity
    \brief Attach a physical body to the entity
    \param entity The entity of which the physical body we want to attach
    \param body The physical body which should be attached or NULL to detach
*/
void SG_EXPORT sgEntitySetPhysicsBody(SGEntity* entity, struct SGPhysicsBody* body);
/**
    \memberof SGEntity
    \brief Get the currently attached physical body
    \param entity The entity of which the physical body we want to get
    \return The physical body if one was attached, NULL otherwise
*/
struct SGPhysicsBody* SG_EXPORT sgEntityGetPhysicsBody(SGEntity* entity);
// @}

/**
    \name Audio sources
*/
// @{
/**
    \memberof SGEntity
    \brief Attach an audio source to the entity
    \param entity The entity of which the audio source we want to attach
    \param source The audio source which should be attached or NULL to detach
*/
void SG_EXPORT sgEntitySetSource(SGEntity* entity, struct SGSource* source);
/**
    \memberof SGEntity
    \brief Get the currently attached audio source
    \param entity The entity of which the audio source we want to get
    \return The audio source if one was attached, NULL otherwise
*/
struct SGSource* SG_EXPORT sgEntityGetSource(SGEntity* entity);
// @}

/**
    \name Position
*/
// @{
/**
    \memberof SGEntity
    \brief Set the entity's position
    \param entity The entity of which position we want to set
    \param[in] x X position
    \param[in] y Y position
    \note
        If a physical body is attached, its position will get changed.
    \sa
        sgEntityGetPos
        sgEntitySetPosX
        sgEntitySetPosY
*/
void SG_EXPORT sgEntitySetPos(SGEntity* entity, float x, float y);
/**
    \memberof SGEntity
    \brief Get the body's position
    \param entity The entity of which position we want to get
    \param[out] x X position pointer
    \param[out] y Y position pointer
    \note
        If a physical body is attached, this function "returns" its position.
    \sa
        sgEntitySetPos
        sgEntityGetPosX
        sgEntityGetPosY
*/
void SG_EXPORT sgEntityGetPos(SGEntity* entity, float* x, float* y);

/**
    \memberof SGEntity
    \brief Set the body's x position
    \param entity The entity of which position we want to set
    \param[in] x X position

    This function sets the entity's x position while preserving y position.
    \note
        If a physical body is attached, its position will get changed.
    \sa
        sgEntityGetPosX
        sgEntitySetPos
        sgEntitySetPosY
*/
void SG_EXPORT sgEntitySetPosX(SGEntity* entity, float x);
/**
    \memberof SGEntity
    \brief Get the body's x position
    \param entity The entity of which position we want to get
    \return The x position

    This function gets only the x position of the entity. Note that it is more efficient to use \ref sgEntityGetPos "sgEntityGetPos" if both coordinates are required.
    \note
        If a physical body is attached, this function returns its position.
    \sa
        sgEntitySetPosX
        sgEntityGetPos
        sgEntityGetPosY
*/
float SG_EXPORT sgEntityGetPosX(SGEntity* entity);

/**
    \memberof SGEntity
    \brief Set the body's y position
    \param entity The entity of which position we want to set
    \param[in] y Y position

    This function sets the entity's y position while preserving x position.
    \note
        If a physical body is attached, its position will get changed.
    \sa
        sgEntityGetPosY
        sgEntitySetPos
        sgEntitySetPosX
*/
void SG_EXPORT sgEntitySetPosY(SGEntity* entity, float x);
/**
    \memberof SGEntity
    \brief Get the body's y position
    \param entity The entity of which position we want to get
    \return The y position

    This function gets only the y position of the entity. Note that it is more efficient to use \ref sgEntityGetPos "sgEntityGetPos" if both coordinates are required.
    \note
        If a physical body is attached, this function returns its position.
    \sa
        sgEntitySetPosY
        sgEntityGetPos
        sgEntityGetPosX
*/
float SG_EXPORT sgEntityGetPosY(SGEntity* entity);
// @}

/**
    \name Depth
    \brief Depth controls in front (and behind) of which entities this one should be drawn.
*/
// @{
/**
    \memberof SGEntity
    \brief Set the entity's depth
    \param entity The entity of which the depth we want to set
    \param[in] depth The depth to set

    \sa
        sgEntityGetDepth
*/
void SG_EXPORT sgEntitySetDepth(SGEntity* entity, float depth);
/**
    \memberof SGEntity
    \brief Get the entity's depth
    \param entity The entity of which the depth we want to get
    \return The depth

    \sa
        sgEntitySetDepth
*/
float SG_EXPORT sgEntityGetDepth(SGEntity* entity);
// }@

/**
    \name Angle
    \todo Should we add grads (0-400 grad) and "loops" (0.0 - 1.0)?
    \todo Should positive be up or down?
*/
// @{
/**
    \memberof SGEntity
    \brief Set the entity's angle in radians
    \param entity The entity of which the angle we want to set
    \param[in] rads The angle in radians
    \note
        If a physical body is attached, then the orientation of the body is changed.

    \sa
        sgEntityGetAngleRads
        sgEntitySetAngleDegs
*/
void SG_EXPORT sgEntitySetAngleRads(SGEntity* entity, float rads);
/**
    \memberof SGEntity
    \brief Get the entity's angle in radians
    \param entity The entity of which the angle we want to get
    \return The angle in radians
    \note
        If a physical body is attached, then the orientation of the body is returned.

    \sa
        sgEntitySetAngleRads
        sgEntityGetAngleDegs
*/
float SG_EXPORT sgEntityGetAngleRads(SGEntity* entity);
/**
    \memberof SGEntity
    \brief Set the entity's angle in degrees
    \param entity The entity of which the angle we want to set
    \param[in] degs The angle in degrees
    \note
        If a physical body is attached, then the orientation of the body is changed.

    \sa
        sgEntityGetAngleDegs
        sgEntitySetAngleRads
*/
void SG_EXPORT sgEntitySetAngleDegs(SGEntity* entity, float degs);
/**
    \memberof SGEntity
    \brief Get the entity's angle in degrees
    \param entity The entity of which the angle we want to get
    \return The angle in degrees
    \note
        If a physical body is attached, then the orientation of the body is returned.

    \sa
        sgEntitySetAngleDegs
        sgEntityGetAngleRads
*/
float SG_EXPORT sgEntityGetAngleDegs(SGEntity* entity);
// @}

/**
    \name Drawing
    \todo Should this be overloaded?
*/
// @{
/**
    \memberof SGEntity
    \brief Draw the entity with its position and orientation
    \param entity The entity to draw

    If a sprite is attached, this function draws the sprite at the entity's position and orientation, otherwise it does nothing.
*/
void SG_EXPORT sgEntityDraw(SGEntity* entity);
// @}

#endif // __SIEGE_CORE_ENTITY_H__
