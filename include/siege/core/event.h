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
 * Title: Event
 */

#ifndef __EVENT_H__
#define __EVENT_H__

#include "../physics/collision.h"
#include "../util/list.h"
#include "../common.h"

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \name Event types
 */
/// @{
/**
 * \private
 * \def SG_EV_INTERNAL
 *
 *	Used internally for \ref SGEntity "SGEntity"
 */
#define SG_EV_INTERNAL ((SGenum)-1)

// EventClient types -- these should be OR'd together
#define SG_EVT_MODULE	0x00010000
#define SG_EVT_CORE		0x00020000
#define SG_EVT_WINDOW	0x00040000
#define SG_EVT_MOUSE	0x00080000
#define SG_EVT_KEYBOARD 0x00100000
#define SG_EVT_JOYSTICK 0x00200000
#define SG_EVT_NETWORK	0x00400000
#define SG_EVT_PHYSICS	0x00800000
#define SG_EVT_LEVEL	0x01000000
#define SG_EVT_LOCAL	0x02000000
#define SG_EVT_ALL		0xFFFF0000
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
#define SG_EVF_LVLEND	(SG_EVT_LEVEL | 0x0002)
/// @}

/**
 * \brief Event callback function pointer type
 * \param data Used-provided data
 * \param args Event arguments (depends on the type of event)
 * \return SG_TRUE to continue with the next event, SG_FALSE to stop
 */
typedef SGbool SG_EXPORT (SGEventCall)(void* data, va_list args);

#ifdef SG_BUILD_LIBRARY
SGList* _sg_evList;
SGList* _sg_cList;
SGbool _sg_evStop;
#endif // SG_BUILD_LIBRARY

/**
 * \brief SIEGE event handler "container"
 */
typedef struct SGEvent
{
    /**
     * \brief The list node that holds the event
     */
    SGListNode* node;
	/**
	 * \brief The event's type
	 */
	SGenum type;
	/**
	 * \brief User-provided data
	 *
	 * This is treated as an opaque pointer by SIEGE.
	 */
	void* data;
	/**
	 * \brief Event callback function
	 *
	 * This function is called when the event is triggered.
	 */
    SGEventCall* func;
} SGEvent;

SGbool SG_EXPORT _sgEventInit(void);
SGbool SG_EXPORT _sgEventDeinit(void);

/// @{
/**
 * \memberof SGEvent
 * \brief Create an event handler
 * \param type Event handler type
 * \param data User data for the event handler
 * \param func Function to call when the event is triggered
 * \return The newly created event handler if successful, NULL otherwise.
 */
SGEvent* SG_EXPORT sgEventCreate(SGenum type, void* data, SGEventCall* func);
/**
 * \memberof SGEvent
 * \brief Destroy an event handler
 * \param event The event handler to destroy. It should not be used anymore after this call.
 */
void SG_EXPORT sgEventDestroy(SGEvent* event);
/// @}

/// @{
/**
 * \memberof SGEvent
 * \brief Trigger an event
 * \param type The event type to trigger
 * \param args The arguments to pass (treated as an opaque pointer by SIEGE)
 *
 * This function triggers an event, and in turn, every event handler of the correct type (unless previously stopped).
 */
void SG_EXPORT sgEventCallv(SGenum type, va_list args);
void SG_EXPORT sgEventCall(SGenum type, ...);
/**
 * \memberof SGEvent
 * \brief Stop an event
 *
 * This function stops an event in its tracks, meaning that it doesn't "propagate" to event handlers further down.
 */
void SG_EXPORT sgEventStop(void);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __EVENT_H__
