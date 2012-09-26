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

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "common.h"

SGPhysicsCollisionCallbacks* colCallbacks;

int cbCollisionBegin(cpArbiter* arb, cpSpace* space, void* data);
int cbCollisionPreSolve(cpArbiter* arb, cpSpace* space, void* data);
void cbCollisionPostSolve(cpArbiter* arb, cpSpace* space, void* data);
void cbCollisionSeparate(cpArbiter* arb, cpSpace* space, void* data);

#endif // __COLLISION_H__
