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
	float x, y, angle, speed, age;
} SGParticle ;

typedef struct SGParticleGenerator
{
	float x, y, angle, delta_angle, initial_speed, duration, rate, friction;
	SGTexture* texture;
	SGParticle* particles[];
} SGParticleGenerator ;

SGParticleGenerator* SGParticleGeneratorCreate(
		float x,              /* initial x of particles */
		float y,              /* initial y of particles */
		float angle,          /* direction of particles */
		float delta_angle,    /* variation in direction */
		float initial_speed,  /* initial speed of particles */
		float duration,       /* lifetime of particles */
		float rate,           /* production rate of particles */
		float friction,       /* environmental friction to particles */
		SGTexture* texture);  /* texture used by particles */

SGParticle* SGParticleCreate(float x, float y, float angle, float speed);

void SGParticleUpdate(SGParticle* particle, float time);
void SGParticleGeneratorUpdate(SGParticleGenerator* generator, float time);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_PARTICLES_H__
