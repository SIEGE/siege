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

#ifndef __SIEGE_BACKEND_H__
#define __SIEGE_BACKEND_H__

#define SG_BUILD_BACKEND

#include "backend/physics/init.h"
// Physics
#include "backend/physics/body.h"
#include "backend/physics/collision.h"
#include "backend/physics/constraint.h"
#include "backend/physics/shape.h"
#include "backend/physics/space.h"

// Test (things in a state of flux, will be removed or at least renamed)
#ifdef SIEGE_TEST
#   include "backend/physics/test.h"
#endif // SIEGE_TEST

#include "backend/debug.h"

#endif // __SIEGE_BACKEND_H__
