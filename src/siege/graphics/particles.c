/*
 *  Copyright (c) 2007 SIEGE Development Team
 *  All rights reserved.
 *
 *  This file is part of libSIEGE.
 *
 *  This software is copyrighted work licensed under the terms of the
 *  2-clause BSD license. Please consult the file "license.txt" for
 *  details.
 *
 *  If you did not recieve the file with this program, please email
 *  Tim Chas <darkuranium@gmail.com>.
*/


#include <siege/graphics/texture.h>
#include <siege/graphics/particles.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>

/*
 * TODO:
 * implement everything in particles.h!
 */

SGParticle* _sgParticleCreate(float x, float y, float angle, float speed)
{
	SGParticle* particle = (SGParticle*) malloc(sizeof(SGParticle));
	particle->x = x;
	particle->y = y;
	particle->angle = angle;
	particle->speed = speed;
	particle->age = 0.0;
	return particle;
}

SGEmitter* sgEmitterCreate(
		float x,              /* initial x of particles */
		float y,              /* initial y of particles */
		float angle,          /* direction of particles */
		float delta_angle,    /* variation in direction */
		float initial_speed,  /* initial speed of particles */
		float duration,       /* lifetime of particles */
		float rate,           /* production rate of particles */
		float friction,       /* environmental friction to particles */
		int nb_particles,     /* size of particles pool */
		SGTexture* texture)   /* texture used by particles */
{
	SGEmitter* emitter = (SGEmitter*) malloc(sizeof(SGEmitter));
	emitter->x = x;
	emitter->y = y;
	emitter->angle = angle;
	emitter->delta_angle = delta_angle;
	emitter->initial_speed = initial_speed;
	emitter->duration = duration;
	emitter->rate = rate;
	emitter->friction = friction;
	emitter->particles = (SGParticle*) malloc(nb_particles * sizeof(SGParticle));
	emitter->texture = texture;

	return emitter;
}

void _sgParticleUpdate(SGParticle* particle, float time, float friction)
{
	particle->speed -= friction * time;
	particle->x += cos(particle->angle) * particle->speed;
	particle->y += sin(particle->angle) * particle->speed;
	particle->age += time;
}

