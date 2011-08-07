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


/* TODO:
 * - add deflectors and attractors to interract with particles in a generator
 *
 * */

#ifndef __SIEGE_GRAPHICS_PARTICLES_H__
#define __SIEGE_GRAPHICS_PARTICLES_H__

#include "../common.h"
#include "texture.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGParticle
{
	float x, y, angle, speed, age, width, height, rotation, alpha;
} SGParticle;

typedef struct SGEmitter
{
	float x, y, angle, delta_angle, initial_speed, duration, rate, friction, time_accumulator;
	size_t nb_particles;
	SGTexture* texture;
	SGParticle* particles;
	SGbool silent;
	void (*update_fcn)(SGParticle* particle, float time, float friction);
} SGEmitter;

SGEmitter* sgEmitterCreate(
		float x,              /* initial x of particles */
		float y,              /* initial y of particles */
		float angle,          /* direction of particles */
		float delta_angle,    /* variation in direction */
		float initial_speed,  /* initial speed of particles */
		float duration,       /* lifetime of particles */
		float rate,           /* production rate of particles */
		float friction,       /* environmental friction to particles */
		size_t nb_particles,  /* size of particles pool */
		SGTexture* texture);  /* texture used by particles */

void sgEmitterUpdate(SGEmitter* emitter, float time);

SGParticle* _sgParticleCreate(float x, float y, float angle, float speed);

void _sgParticleUpdate(SGParticle* particle, float time, float friction);

void sgEmitterDraw(SGEmitter* emitter);

void sgEmitterSetUpdateFcn(SGEmitter* emitter, void (*update_fcn)(SGParticle*, float, float));

void sgEmitterSetSilent(SGEmitter*, SGbool);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_PARTICLES_H__
