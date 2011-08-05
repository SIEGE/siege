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
#include <stdbool.h>

/*
 * TODO:
 * implement everything in particles.h!
 * add scale in particle drawing
 * add function pointer methods and registration to allow custom update of particles
 */

void _sgParticleInit(SGParticle* particle, float x, float y, float angle, float speed)
{
	particle->x = x;
	particle->y = y;
	particle->angle = angle;
	particle->speed = speed;
	particle->age = 0.0;
}

SGParticle* _sgParticleCreate(float x, float y, float angle, float speed)
{
	SGParticle* particle = (SGParticle*) malloc(sizeof(SGParticle));
	_sgParticleInit(particle, x, y, angle, speed);
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
	int i;
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
	emitter->nb_particles = nb_particles;
	emitter->time_accumulator = 0.0;

	for (i=0; i<emitter->nb_particles; i++)
		emitter->particles[i].age = emitter->duration + 1;

	return emitter;
}

void _sgParticleUpdate(SGParticle* particle, float time, float friction)
{
	particle->speed -= friction * time;
	particle->x += cos(particle->angle) * particle->speed;
	particle->y += sin(particle->angle) * particle->speed;
	particle->age += time;
}


void sgEmitterUpdate(SGEmitter* emitter, float time)
{
	int i;
	bool condition;
	float frac = 1.0/emitter->rate;
	emitter->time_accumulator += time;
	for (i=0; i<emitter->nb_particles; i++)
	{
		if (emitter->particles[i].age < emitter->duration)
		{
			_sgParticleUpdate(&(emitter->particles[i]), time, emitter->friction);
		}
	}
	/* TODO add new particles depending on rate if array not full*/

	while (emitter->time_accumulator >= frac)
	{
		/* use an index to start search from precedent find */
		condition = false;
		for (i=0; i < emitter->nb_particles; i++)
		{
			if (emitter->particles[i].age >= emitter->duration)
			{
				_sgParticleInit(&(emitter->particles[i]),
						emitter->x,
						emitter->y,
						emitter->angle + (random() - 0.5) * emitter->delta_angle,
						emitter->initial_speed);
				emitter->time_accumulator -= frac;
				condition = true;
				break;
			}

		}
		if (condition == false)
		{
			printf("warning, pool of particules emitter full, either reduce lifetime,");
			printf(" or rate, or make pool bigger\n");
			goto out;
		}
	}
	out: NULL;
}

void sgEmitterDraw(SGEmitter* emitter)
{
	int i;
	for (i=0; i< emitter->nb_particles; i++)
	{
		//sgDrawBeginT(SG_GRAPHICS_PRIMITIVE_QUADS, emitter->texture);
		////sgDrawColor4f(1.0, 1.0, 1.0, (1.0));// - emitter->particles[i].age/emitter->duration));
		//	sgDrawTexCoord2f(0.0, 0.0);
		//	sgDrawVertex2f(emitter->particles[i].x, emitter->particles[i].y);
		//	sgDrawTexCoord2f(0.0, 1.0);
		//	sgDrawVertex2f(emitter->particles[i].x, emitter->particles[i].y + 16);
		//	sgDrawTexCoord2f(1.0, 1.0);
		//	sgDrawVertex2f(emitter->particles[i].x + 16, emitter->particles[i].y + 16);
		//	sgDrawTexCoord2f(1.0, 0.0);
		//	sgDrawVertex2f(emitter->particles[i].x + 16, emitter->particles[i].y);
		//sgDrawEnd();
		sgTextureDraw2f(
				emitter->texture,
				emitter->particles[i].x,
				emitter->particles[i].y);

	}
	//sgDrawColor4f(1.0, 1.0, 1.0, 1.0);
}
