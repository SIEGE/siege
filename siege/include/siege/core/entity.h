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

    SGvoid SG_EXPORT (*evInit)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evDeinit)(struct SGEntity* entity);

    SGvoid SG_EXPORT (*evStart)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evExit)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evTick)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evTickBegin)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evTickEnd)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evDraw)(struct SGEntity* entity);

    SGvoid SG_EXPORT (*evWindowOpen)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evWindowClose)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evWindowResize)(struct SGEntity* entity, SGuint width, SGuint height);

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

    SGvoid SG_EXPORT (*evKeyboardKey)(struct SGEntity* entity, SGuint key);
    SGvoid SG_EXPORT (*evKeyboardKeyPress)(struct SGEntity* entity, SGuint key);
    SGvoid SG_EXPORT (*evKeyboardKeyRelease)(struct SGEntity* entity, SGuint key);
    SGvoid SG_EXPORT (*evKeyboardKeyRepeat)(struct SGEntity* entity, SGuint key);

    //SGvoid SG_EXPORT (*evKeyboardChar)(struct SGEntity* entity, SGdchar chr);
    SGvoid SG_EXPORT (*evKeyboardCharPress)(struct SGEntity* entity, SGdchar chr);
    //SGvoid SG_EXPORT (*evKeyboardCharRelease)(struct SGEntity* entity, SGdchar chr);
    SGvoid SG_EXPORT (*evKeyboardCharRepeat)(struct SGEntity* entity, SGdchar chr);

    SGvoid SG_EXPORT (*evJoystickButton)(struct SGEntity* entity, SGuint joy, SGuint button);
    SGvoid SG_EXPORT (*evJoystickButtonPress)(struct SGEntity* entity, SGuint joy, SGuint button);
    SGvoid SG_EXPORT (*evJoystickButtonRelease)(struct SGEntity* entity, SGuint joy, SGuint button);
    SGvoid SG_EXPORT (*evJoystickMove)(struct SGEntity* entity, SGuint joy, SGfloat* axis, SGuint numaxis);

    // networking goes here

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

    SGvoid SG_EXPORT (*evLevelStart)(struct SGEntity* entity);
    SGvoid SG_EXPORT (*evLevelEnd)(struct SGEntity* entity);
} SGEntity;

SGbool SG_EXPORT _sg_evCall(SGEntity* entity, _SGEntityCall* call);

SGbool SG_EXPORT _sgEntityInit(void);
SGbool SG_EXPORT _sgEntityDeinit(void);

SGEntity* SG_EXPORT sgEntityCreate(float priority, SGenum type);
void SG_EXPORT sgEntityDestroy(SGEntity* entity);

void SG_EXPORT sgEntitySetSprite(SGEntity* entity, struct SGSprite* sprite);
struct SGSprite* SG_EXPORT sgEntityGetSprite(SGEntity* entity);

void SG_EXPORT sgEntitySetMask(SGEntity* entity, struct SGSprite* mask);
struct SGSprite* SG_EXPORT sgEntityGetMask(SGEntity* entity);

void SG_EXPORT sgEntitySetPhysicsBody(SGEntity* entity, struct SGPhysicsBody* body);
struct SGPhysicsBody* SG_EXPORT sgEntityGetPhysicsBody(SGEntity* entity);

void SG_EXPORT sgEntitySetSource(SGEntity* entity, struct SGSource* source);
struct SGSource* SG_EXPORT sgEntityGetSource(SGEntity* entity);

void SG_EXPORT sgEntitySetPos(SGEntity* entity, float x, float y);
void SG_EXPORT sgEntityGetPos(SGEntity* entity, float* x, float* y);

void SG_EXPORT sgEntitySetPosX(SGEntity* entity, float x);
float SG_EXPORT sgEntityGetPosX(SGEntity* entity);
void SG_EXPORT sgEntitySetPosY(SGEntity* entity, float y);
float SG_EXPORT sgEntityGetPosY(SGEntity* entity);

void SG_EXPORT sgEntitySetDepth(SGEntity* entity, float depth);
float SG_EXPORT sgEntityGetDepth(SGEntity* entity);

void SG_EXPORT sgEntitySetAngleRads(SGEntity* entity, float rads);
float SG_EXPORT sgEntityGetAngleRads(SGEntity* entity);
void SG_EXPORT sgEntitySetAngleDegs(SGEntity* entity, float degs);
float SG_EXPORT sgEntityGetAngleDegs(SGEntity* entity);

void SG_EXPORT sgEntityDraw(SGEntity* entity);

#endif // __SIEGE_CORE_ENTITY_H__
