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
	return particle;
}


