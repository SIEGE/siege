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

#ifndef __SIEGE_BACKEND_PHYSICS_COLLISION_H__
#define __SIEGE_BACKEND_PHYSICS_COLLISION_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)   name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct SGPhysicsCollisionCallbacks
    {
        void SG_CALL (*begin)(void* shandle1, void* shandle2, void* handle);
        void SG_CALL (*step)(void* shandle1, void* shandle2, void* handle);
        void SG_CALL (*post)(void* shandle1, void* shandle2, void* handle);
        void SG_CALL (*end)(void* shandle1, void* shandle2, void* handle);
    } SGPhysicsCollisionCallbacks;

    SGenum SG_CALL SG_FPTR(sgmPhysicsCollisionIgnore)(void* handle);
    SGenum SG_CALL SG_FPTR(sgmPhysicsCollisionGetNumContacts)(void* handle, size_t* numpoints);
    SGenum SG_CALL SG_FPTR(sgmPhysicsCollisionGetPoint)(void* handle, size_t index, float* x, float* y);
    SGenum SG_CALL SG_FPTR(sgmPhysicsCollisionGetNormal)(void* handle, size_t index, float* x, float* y);
    SGenum SG_CALL SG_FPTR(sgmPhysicsCollisionGetDistance)(void* handle, size_t index, float* distance);
    SGenum SG_CALL SG_FPTR(sgmPhysicsCollisionGetImpulse)(void* handle, float* x, float* y, SGbool friction);
    SGenum SG_CALL SG_FPTR(sgmPhysicsCollisionSetCallbacks)(SGPhysicsCollisionCallbacks* callbacks);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_PHYSICS_COLLISION_H__
