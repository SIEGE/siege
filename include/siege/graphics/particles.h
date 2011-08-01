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

typedef SGParticle struct
{
	float x, y, angle, speed, age;
};

typedef SGParticleGenerator struct
{
	float x, y, angle, delta_angle, initial_speed, duration;
	SGTexture* texture;
	SGParticle[] particles;
};


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_GRAPHICS_PARTICLES_H__
