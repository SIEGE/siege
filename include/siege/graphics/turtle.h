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

#ifndef __SIEGE_GRAPHICS_TURTLE_H__
#define __SIEGE_GRAPHICS_TURTLE_H__

#include "../common.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/**
 * \brief The state of the turtle, for use with saving/loading SGTurtle states
 * \private
 *
 * \warning
 *	For internal use only.
 */
typedef struct SGTurtleState
{
	/**
	 * \privatesection
	 */

	/**
	 * \name Position
	 */
	/// @{
	float x;		/// < Horizontal position
	float y;		/// < Vertical position
	/// @}

	float angle;	/// < Angle in radians
	SGbool draw;	/// < Pen state
} SGTurtleState;

/**
 * \brief A turtle, for use in turtle graphics
 */
typedef struct SGTurtle
{
	/**
	 * \privatesection
	 */

	SGTurtleState* stack;	/// < Internal position stack
	size_t stacklen;		/// < The size of the turtle's stack

	/**
	 * \name States
	 */
	/// @{
	SGTurtleState start;	/// < The state at turtle's creation
	SGTurtleState prev;		/// < Previous state
	SGTurtleState curr;		/// < Current state
	/// @}
} SGTurtle;

SGbool SG_CALL _sgTurtleInit(void);
SGbool SG_CALL _sgTurtleDeinit(void);

/// @{
/**
 * \brief Create a turtle with angle in radians
 * \memberof SGTurtle
 *
 * \param x Start x position
 * \param y Start y position
 * \param rads Start angle in radians
 * \param draw The initial pen position,
 *	SG_TRUE to draw (down),
 *	SG_FALSE otherwise (up)
 *
 * \return The newly created turtle if successful, NULL otherwise.
 */
SGTurtle* SG_CALL sgTurtleCreateRads(float x, float y, float rads, SGbool draw);
/**
 * \brief Create a turtle with angle in degrees
 * \memberof SGTurtle
 *
 * \param x Start x position
 * \param y Start y position
 * \param degs Start angle in degrees
 * \param draw The initial pen position, SG_TRUE to draw (down), SG_FALSE otherwise (up)
 *
 * \return The newly created turtle if successful, NULL otherwise.
 */
SGTurtle* SG_CALL sgTurtleCreateDegs(float x, float y, float degs, SGbool draw);
/**
 * \brief Destroy a turtle
 * \memberof SGTurtle
 *
 * \param turtle The turtle to destroy
 */
void SG_CALL sgTurtleDestroy(SGTurtle* turtle);
/// @}

/**
 * \name State
 */
/// @{
/**
 * \brief Reset the turtle's state to the start state
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which state to reset
 *
 * This function sets the turtle's state (position, angle, pen state)
 * to what it was when the turtle was first created.
 */
void SG_CALL sgTurtleReset(SGTurtle* turtle);
/**
 * \brief Push the turtle's state to the stack
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which state to push
 *
 * This function pushes the turtle's state (position, angle, pen state)
 * onto its stack, making it available for later.
 *
 * \sa
 * 	sgTurtlePop
 */
void SG_CALL sgTurtlePush(SGTurtle* turtle);
/**
 * \brief Pop the turtle's state off the stack and set it
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which state we want to pop and set
 *
 * This function gets the state on top of its stack,
 * removes it and then sets it as the current state.
 *
 * \sa
 * 	sgTurtlePush
 */
void SG_CALL sgTurtlePop(SGTurtle* turtle);
/// @}

/**
 * \name Basic movement
 */
/// @{
/**
 * \brief Step ahead
 * \memberof SGTurtle
 *
 * \param turtle The turtle to move
 * \param dist The movement distance
 *
 * This function makes the turtle go \a dist steps ahead,
 * drawing a line in between if the pen is down.
 */
void SG_CALL sgTurtleStep(SGTurtle* turtle, float dist);
/**
 * \brief Move the turtle to the absolute coordinates
 * \memberof SGTurtle
 *
 * \param turtle The turtle to move
 * \param x X coordinate
 * \param y Y coordinate
 *
 * This function makes the turtle go to the absolute coordinates,
 * drawing a line in between if the pen is down.
 *
 * \sa
 * 	sgTurtleJump
 */
void SG_CALL sgTurtleMove(SGTurtle* turtle, float x, float y);
/**
 * \brief Teleport the turtle to a new position without drawing
 * \memberof SGTurtle
 *
 * \param turtle The turtle to teleport
 * \param x X coordinate
 * \param y Y coordinate
 *
 * This function is similar to \ref sgTurtleMove "sgTurtleMove", only it doesn't do any drawing even if the pen is down.
 *
 * \sa
 * 	sgTurtleMove
 * 	sgTurtleSetPos
 */
void SG_CALL sgTurtleJump(SGTurtle* turtle, float x, float y);
/// @}

/**
 * \name Pen state
 */
/// @{
/**
 * \brief Bring the pen up (disable drawing)
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which the pen we want to bring up
 *
 * This is equivalent to calling
 * \ref sgTurtleSetPen "sgTurtleSetPen"(turtle, SG_FALSE).
 *
 * \sa
 * 	sgTurtlePenDown
 * 	sgTurtleSetPen
 */
void SG_CALL sgTurtlePenUp(SGTurtle* turtle);
/**
 * \brief Put the pen down (enable drawing)
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which the pen we want to put down
 *
 * This is equivalent to calling
 * \ref sgTurtleSetPen "sgTurtleSetPen"(turtle, SG_TRUE).
 *
 * \sa
 * 	sgTurtlePenUp
 * 	sgTurtleSetPen
 */
void SG_CALL sgTurtlePenDown(SGTurtle* turtle);

/**
 * \brief Change the pen state
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which pen state we want to set
 * \param pen The new pen state
 *
 * Sets the turtle's pen state, thus enabling or disabling drawing.
 *
 * \sa
 * 	sgTurtlePenUp
 * 	sgTurtlePenDown
 */
void SG_CALL sgTurtleSetPen(SGTurtle* turtle, SGbool pen);
/**
 * \brief Get the turtle's pen state
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which pen state we want to get
 *
 * \return SG_TRUE if pen is down (drawing is enabled), SG_FALSE otherwise.
 */
SGbool SG_CALL sgTurtleGetPen(SGTurtle* turtle);
/// @}

/**
 * \name Position
 */
/// @{
/**
 * \brief Set the turtle's position without drawing
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which position to change
 * \param[in] x New x position
 * \param[in] y New y position
 *
 * \note
 *	Alias for \ref sgTurtleJump "sgTurtleJump",
 *	added for consistency and completeness.
 */
void SG_CALL sgTurtleSetPos(SGTurtle* turtle, float x, float y);
/**
 * \brief Set the turtle's x position, preserving y
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which position to change
 * \param[in] x New x position
 */
void SG_CALL sgTurtleSetPosX(SGTurtle* turtle, float x);
/**
 * \brief Set the turtle's y position, preserving x
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which position to change
 * \param[in] y New y position
 */
void SG_CALL sgTurtleSetPosY(SGTurtle* turtle, float y);
/**
 * \brief Get the turtle's current position
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which position to get
 * \param[out] x X position pointer
 * \param[out] y Y position pointer
 */
void SG_CALL sgTurtleGetPos(SGTurtle* turtle, float* x, float* y);
/**
 * \brief Get the turtle's x position
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which position to get
 *
 * \return Turtle's x position
 *
 * \note
 *	If both x and y coordinates are required,
 *	consider \ref sgTurtleGetPos "sgTurtleGetPos".
 */
float SG_CALL sgTurtleGetPosX(SGTurtle* turtle);
/**
 * \brief Get the turtle's y position
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which position to get
 *
 * \return Turtle's y position
 *
 * \note
 *	If both x and y coordinates are required,
 *	consider \ref sgTurtleGetPos "sgTurtleGetPos".
 */
float SG_CALL sgTurtleGetPosY(SGTurtle* turtle);
/// @}

/**
 * \name Angles and rotations
 */
/// @{
/**
 * \brief Turn the turtle left by angle in radians
 * \memberof SGTurtle
 *
 * \param turtle The turtle to turn
 * \param rads The angle in radians
 */
void SG_CALL sgTurtleTurnLeftRads(SGTurtle* turtle, float rads);
/**
 * \brief Turn the turtle left by angle in degrees
 * \memberof SGTurtle
 *
 * \param turtle The turtle to turn
 * \param degs The angle in degrees
 */
void SG_CALL sgTurtleTurnLeftDegs(SGTurtle* turtle, float degs);
/**
 * \brief Turn the turtle right by angle in radians
 * \memberof SGTurtle
 *
 * \param turtle The turtle to turn
 * \param rads The angle in radians
 */
void SG_CALL sgTurtleTurnRightRads(SGTurtle* turtle, float rads);
/**
 * \brief Turn the turtle right by angle in degrees
 * \memberof SGTurtle
 *
 * \param turtle The turtle to turn
 * \param degs The angle in degrees
 */
void SG_CALL sgTurtleTurnRightDegs(SGTurtle* turtle, float degs);

/**
 * \brief Set the turtle's angle in radians
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which angle to set
 * \param[in] rads The angle in radians
 */
void SG_CALL sgTurtleSetAngleRads(SGTurtle* turtle, float rads);
/**
 * \brief Get the turtle's angle in radians
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which angle to get
 *
 * \return Turtle's angle in radians
 */
float SG_CALL sgTurtleGetAngleRads(SGTurtle* turtle);

/**
 * \brief Set the turtle's angle in degrees
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which angle to set
 * \param[in] degs The angle in degrees
 */
void SG_CALL sgTurtleSetAngleDegs(SGTurtle* turtle, float degs);
/**
 * \brief Get the turtle's angle in degrees
 * \memberof SGTurtle
 *
 * \param turtle The turtle of which angle to get
 *
 * \return Turtle's angle in degrees
 */
float SG_CALL sgTurtleGetAngleDegs(SGTurtle* turtle);
/// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TURTLE_H__
