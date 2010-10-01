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

#ifndef __SIEGE_PHYSICS_COLLISION_H__
#define __SIEGE_PHYSICS_COLLISION_H__

#include "../common.h"

typedef struct SGCollisionPoint
{
    float xpos;
    float ypos;
    float xvel;
    float yvel;
    float xnorm;
    float ynorm;
    float separation;
    float friction;
    float restitution;
} SGCollisionPoint;

typedef struct SGCollisionResult
{
    float xpos;
    float ypos;
    float xvel;
    float yvel;
    float xnorm;
    float ynorm;
} SGCollisionResult;

#endif // __SIEGE_PHYSICS_COLLISION_H__
