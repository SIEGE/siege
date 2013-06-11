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

#ifndef __SIEGE_GRAPHICS_EMITTER_H__
#define __SIEGE_GRAPHICS_EMITTER_H__

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

typedef void SG_CALL (SGParticleUpdate)(SGParticle* particle, float time, float friction);

typedef struct SGEmitter
{
	float x, y, angle, delta_angle, initial_speed, duration, rate, friction, time_accumulator;
	size_t nb_particles;
	SGTexture* texture;
	SGParticle* particles;
	SGbool silent;
	SGParticleUpdate* cbUpdate;
} SGEmitter;

SGEmitter* SG_CALL sgEmitterCreate(
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

void SG_CALL sgEmitterUpdate(SGEmitter* emitter, float time);

SGParticle* SG_CALL _sgParticleCreate(float x, float y, float angle, float speed);

void SG_CALL _sgParticleUpdate(SGParticle* particle, float time, float friction);

void SG_CALL sgEmitterDraw(SGEmitter* emitter);

void SG_CALL sgEmitterSetUpdateFunc(SGEmitter* emitter, SGParticleUpdate* cbUpdate);

void SG_CALL sgEmitterSetSilent(SGEmitter*, SGbool);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_EMITTER_H__
