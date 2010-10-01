/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
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
    \private
    \brief The state of the turtle, for use with saving/loading SGTurtle states
    \warning
        For internal use only.
*/
typedef struct SGTurtleState
{
    /**
        \private
        \brief Turtle's horizontal position
        \warning
            For internal use only.
    */
    float x;
    /**
        \private
        \brief Turtle's vertical position
        \warning
            For internal use only.
    */
    float y;
    /**
        \private
        \brief Turtle's angle, in radians
        \warning
            For internal use only.
    */
    float angle;
    /**
        \private
        \brief Turtle's pen state
        \warning
            For internal use only.
    */
    SGbool draw;
} SGTurtleState;

/**
    \brief A turtle, for use in turtle graphics
*/
typedef struct SGTurtle
{
    /**
        \private
        \brief Turtle's internal position stack
        \warning
            For internal use only.
    */
    SGTurtleState* stack;
    /**
        \private
        \brief The size of the turtle's stack
        \warning
            For internal use only.
    */
    size_t stacklen;

    /**
        \name States
    */
    // @{
    /**
        \private
        \brief Turtle's state at its creation

        Used in \ref sgTurtleReset "sgTurtleReset".

        \warning
            For internal use only.
    */
    SGTurtleState start;
    /**
        \private
        \brief Turtle's previous state
        \warning
            For internal use only.
    */
    SGTurtleState prev;
    /**
        \private
        \brief Turtle's current
        \warning
            For internal use only.
    */
    SGTurtleState curr;
    // @}
} SGTurtle;

SGbool SG_EXPORT _sgTurtleInit(void);
SGbool SG_EXPORT _sgTurtleDeinit(void);

// @{
/**
    \memberof SGTurtle
    \brief Create a turtle with angle in radians
    \param x Start x position
    \param y Start y position
    \param rads Start angle in radians
    \param draw The initial pen position, SG_TRUE to draw (down), SG_FALSE otherwise (up)
    \return The newly created turtle if successful, NULL otherwise.
*/
SGTurtle* SG_EXPORT sgTurtleCreateRads(float x, float y, float rads, SGbool draw);
/**
    \memberof SGTurtle
    \brief Create a turtle with angle in degrees
    \param x Start x position
    \param y Start y position
    \param degs Start angle in degrees
    \param draw The initial pen position, SG_TRUE to draw (down), SG_FALSE otherwise (up)
    \return The newly created turtle if successful, NULL otherwise.
*/
SGTurtle* SG_EXPORT sgTurtleCreateDegs(float x, float y, float degs, SGbool draw);
/**
    \memberof SGTurtle
    \brief Destroy a turtle
    \param turtle The turtle to destroy
*/
void SG_EXPORT sgTurtleDestroy(SGTurtle* turtle);
// @}

/**
    \name State
*/
// @{
/**
    \memberof SGTurtle
    \brief Reset the turtle's state to the start state
    \param turtle The turtle of which state to reset

    This function sets the turtle's state (position, angle, pen state) to what it was when the turtle was first created.
*/
void SG_EXPORT sgTurtleReset(SGTurtle* turtle);
/**
    \memberof SGTurtle
    \brief Push the turtle's state to the stack
    \param turtle The turtle of which state to push

    This function pushes the turtle's state (position, angle, pen state) onto its stack, making it available for later.

    \sa
        sgTurtlePop
*/
void SG_EXPORT sgTurtlePush(SGTurtle* turtle);
/**
    \memberof SGTurtle
    \brief Pop the turtle's state off the stack and set it
    \param turtle The turtle of which state we want to pop and set

    This function gets the state on top of its stack, removes it and then sets it as the current state.

    \sa
        sgTurtlePush
*/
void SG_EXPORT sgTurtlePop(SGTurtle* turtle);
// @}

/**
    \name Basic movement
*/
// @{
/**
    \memberof SGTurtle
    \brief Step ahead
    \param turtle The turtle to move
    \param dist The movement distance

    This function makes the turtle go dist steps ahead, drawing a line in between if the pen is down.
*/
void SG_EXPORT sgTurtleStep(SGTurtle* turtle, float dist);
/**
    \memberof SGTurtle
    \brief Move the turtle to the absolute coordinates
    \param turtle The turtle to move
    \param x X coordinate
    \param y Y coordinate

    This function makes the turtle go to the absolute coordinates, drawing a line in between if the pen is down.

    \sa
        sgTurtleJump
*/
void SG_EXPORT sgTurtleMove(SGTurtle* turtle, float x, float y);
/**
    \memberof SGTurtle
    \brief "Teleport" the turtle to a new position without drawing
    \param turtle The turtle to teleport
    \param x X coordinate
    \param y Y coordinate

    This function is similar to \ref sgTurtleMove "sgTurtleMove", only it doesn't do any drawing even if the pen is down.

    \sa
        sgTurtleMove
        sgTurtleSetPos
*/
void SG_EXPORT sgTurtleJump(SGTurtle* turtle, float x, float y);
// @}

/**
    \name Pen state
*/
// @{
/**
    \memberof SGTurtle
    \brief Bring the pen up (disable drawing)
    \param turtle The turtle of which the pen we want to bring up

    This is equivalent to calling \ref sgTurtleSetPen "sgTurtleSetPen"(turtle, SG_FALSE).

    \sa
        sgTurtlePenDown
        sgTurtleSetPen
*/
void SG_EXPORT sgTurtlePenUp(SGTurtle* turtle);
/**
    \memberof SGTurtle
    \brief Put the pen down (enable drawing)
    \param turtle The turtle of which the pen we want to put down

    This is equivalent to calling \ref sgTurtleSetPen "sgTurtleSetPen"(turtle, SG_TRUE).

    \sa
        sgTurtlePenUp
        sgTurtleSetPen
*/
void SG_EXPORT sgTurtlePenDown(SGTurtle* turtle);

/**
    \memberof SGTurtle
    \brief Change the pen state
    \param turtle The turtle of which pen state we want to set
    \param pen The new pen state

    This function sets the turtle's pen state, thus enabling or disabling drawing.

    \sa
        sgTurtlePenUp
        sgTurtlePenDown
*/
void SG_EXPORT sgTurtleSetPen(SGTurtle* turtle, SGbool pen);
/**
    \memberof SGTurtle
    \brief Get the turtle's pen state
    \param turtle The turtle of which pen state we want to get
    \return SG_TRUE if pen is down (drawing is enabled), SG_FALSE otherwise.
*/
SGbool SG_EXPORT sgTurtleGetPen(SGTurtle* turtle);
// @}

/**
    \name Position
*/
// @{
/**
    \memberof SGTurtle
    \brief Set the turtle's position without drawing
    \param turtle The turtle of which position to change
    \param[in] x New x position
    \param[in] y New y position
    \note
        Alias for \ref sgTurtleJump "sgTurtleJump", added for consistency and completeness.
*/
void SG_EXPORT sgTurtleSetPos(SGTurtle* turtle, float x, float y);
/**
    \memberof SGTurtle
    \brief Set the turtle's x position, preserving y
    \param turtle The turtle of which position to change
    \param[in] x New x position
*/
void SG_EXPORT sgTurtleSetPosX(SGTurtle* turtle, float x);
/**
    \memberof SGTurtle
    \brief Set the turtle's y position, preserving x
    \param turtle The turtle of which position to change
    \param[in] y New y position
*/
void SG_EXPORT sgTurtleSetPosY(SGTurtle* turtle, float y);
/**
    \memberof SGTurtle
    \brief Get the turtle's current position
    \param turtle The turtle of which position to get
    \param[out] x X position pointer
    \param[out] y Y position pointer
*/
void SG_EXPORT sgTurtleGetPos(SGTurtle* turtle, float* x, float* y);
/**
    \memberof SGTurtle
    \brief Get the turtle's x position
    \param turtle The turtle of which position to get
    \return Turtle's x position
    \note
        If both x and y coordinates are required, consider \ref sgTurtleGetPos "sgTurtleGetPos".
*/
float SG_EXPORT sgTurtleGetPosX(SGTurtle* turtle);
/**
    \memberof SGTurtle
    \brief Get the turtle's y position
    \param turtle The turtle of which position to get
    \return Turtle's y position
    \note
        If both x and y coordinates are required, consider \ref sgTurtleGetPos "sgTurtleGetPos".
*/
float SG_EXPORT sgTurtleGetPosY(SGTurtle* turtle);
// @}

/**
    \name Angles and rotations
*/
// @{
/**
    \memberof SGTurtle
    \brief Turn the turtle left by angle in radians
    \param turtle The turtle to turn
    \param rads The angle in radians
*/
void SG_EXPORT sgTurtleTurnLeftRads(SGTurtle* turtle, float rads);
/**
    \memberof SGTurtle
    \brief Turn the turtle left by angle in degrees
    \param turtle The turtle to turn
    \param degs The angle in degrees
*/
void SG_EXPORT sgTurtleTurnLeftDegs(SGTurtle* turtle, float degs);
/**
    \memberof SGTurtle
    \brief Turn the turtle right by angle in radians
    \param turtle The turtle to turn
    \param rads The angle in radians
*/
void SG_EXPORT sgTurtleTurnRightRads(SGTurtle* turtle, float rads);
/**
    \memberof SGTurtle
    \brief Turn the turtle right by angle in degrees
    \param turtle The turtle to turn
    \param degs The angle in degrees
*/
void SG_EXPORT sgTurtleTurnRightDegs(SGTurtle* turtle, float degs);

/**
    \memberof SGTurtle
    \brief Set the turtle's angle in radians
    \param turtle The turtle of which angle to set
    \param[in] rads The angle in radians
*/
void SG_EXPORT sgTurtleSetAngleRads(SGTurtle* turtle, float rads);
/**
    \memberof SGTurtle
    \brief Get the turtle's angle in radians
    \param turtle The turtle of which angle to get
    \return Turtle's angle in radians
*/
float SG_EXPORT sgTurtleGetAngleRads(SGTurtle* turtle);

/**
    \memberof SGTurtle
    \brief Set the turtle's angle in degrees
    \param turtle The turtle of which angle to set
    \param[in] degs The angle in degrees
*/
void SG_EXPORT sgTurtleSetAngleDegs(SGTurtle* turtle, float degs);
/**
    \memberof SGTurtle
    \brief Get the turtle's angle in degrees
    \param turtle The turtle of which angle to get
    \return Turtle's angle in degrees
*/
float SG_EXPORT sgTurtleGetAngleDegs(SGTurtle* turtle);
// @}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_TURTLE_H__
