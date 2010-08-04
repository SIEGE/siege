#ifndef __EVENT_H__
#define __EVENT_H__

#include "../physics/collision.h"
#include "../util/plist.h"
#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define SG_EV_INTERNAL ((SGenum)-1)

// EventClient types -- these should be OR'd together
#define SG_EVT_MODULE   0x00010000
#define SG_EVT_CORE     0x00020000
#define SG_EVT_WINDOW   0x00040000
#define SG_EVT_MOUSE    0x00080000
#define SG_EVT_KEYBOARD 0x00100000
#define SG_EVT_JOYSTICK 0x00200000
#define SG_EVT_NETWORK  0x00400000
#define SG_EVT_PHYSICS  0x00800000
#define SG_EVT_LEVEL    0x01000000
#define SG_EVT_ALL      0xFFFF0000

// EventClient functions -- used in calls
#define SG_EVF_INIT   (SG_EVT_MODULE | 0x0001)
#define SG_EVF_DEINIT (SG_EVT_MODULE | 0x0002)

#define SG_EVF_START (SG_EVT_CORE | 0x0001)
#define SG_EVF_EXIT  (SG_EVT_CORE | 0x0002)
#define SG_EVF_TICK  (SG_EVT_CORE | 0x0004)
#define SG_EVF_TICKB (SG_EVT_CORE | 0x0008)
#define SG_EVF_TICKE (SG_EVT_CORE | 0x0010)
#define SG_EVF_DRAW  (SG_EVT_CORE | 0x0020)

#define SG_EVF_WINOPEN   (SG_EVT_WINDOW | 0x0001)
#define SG_EVF_WINCLOSE  (SG_EVT_WINDOW | 0x0002)
#define SG_EVF_WINRESIZE (SG_EVT_WINDOW | 0x0004)

/*
    H: held
    P: press
    R: release
    A: repeat ("again")
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

#define SG_EVF_KEYKEYH  (SG_EVT_KEYBOARD | 0x0001)
#define SG_EVF_KEYKEYP  (SG_EVT_KEYBOARD | 0x0002)
#define SG_EVF_KEYKEYR  (SG_EVT_KEYBOARD | 0x0004)
#define SG_EVF_KEYKEYA  (SG_EVT_KEYBOARD | 0x0008)
//#define SG_EVF_KEYCHARH (SG_EVT_KEYBOARD | 0x0010)
#define SG_EVF_KEYCHARP (SG_EVT_KEYBOARD | 0x0020)
//#define SG_EVF_KEYCHARR (SG_EVT_KEYBOARD | 0x0040)
#define SG_EVF_KEYCHARA (SG_EVT_KEYBOARD | 0x0080)

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
#define SG_EVF_LVLEND   (SG_EVT_LEVEL | 0x0002)

/**
    \param data Used-provided data
    \param args Event arguments (depends on the type of event)
    \return SG_TRUE to continue with the next event, SG_FALSE to stop
*/
typedef SGbool SG_EXPORT (*SGEventCall)(void* data, void* args);

#ifdef SG_BUILD_LIBRARY
SGPList* _sg_evList;
SGPList* _sg_cList;
SGbool _sg_evStop;
#endif // SG_BUILD_LIBRARY

typedef struct SGEvent
{
    float priority;
    SGenum type;
    void* data;
    SGEventCall func;
} SGEvent;

SGbool SG_EXPORT _sgEventInit(void);
SGbool SG_EXPORT _sgEventDeinit(void);
SGEvent* SG_EXPORT sgEventCreate(float priority, SGenum type, void* data, SGEventCall func);
void SG_EXPORT sgEventDestroy(SGEvent* event);
void SG_EXPORT sgEventCall(SGenum type, void* args);
void SG_EXPORT sgEventStop(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __EVENT_H__
