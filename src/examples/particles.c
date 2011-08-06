#include <siege/siege.h>
#include <siege/graphics/particles.h>

#include <stdlib.h>
#include <math.h>

void _myParticleUpdate(SGParticle* particle, float time, float friction)
{
	particle->speed -= friction * time;
	if (particle->speed < 0)
		particle->speed = 0;
	particle->x += cos(particle->angle) * particle->speed;
	particle->y += sin(particle->angle) * particle->speed;
	particle->age += time;
	particle->alpha = 1.0 - (particle->age/20);
	particle->rotation += time / 10;
}

int main(void)
{
	sgLoadModule("SDL");
	sgLoadModule("OpenGL");
	sgLoadModule("DevIL");
	sgInit(640, 480, 32, 0);
	sgWindowSetTitle("SIEGE Particles Demo");

	SGTexture* my_texture = sgTextureCreateFile("data/sprites/CrateSmall.png");
	SGEmitter* my_particle_emitter = sgEmitterCreate(
			320, // x
			240, // y
			0,  // angle
			2 * 3.1471,  // delta_angle
			1,  // speed
			20,   // duration
			40,  // rate
			0.05, // friction
			2000,  // max nb_particles
			my_texture);

	sgEmitterSetUpdateFcn(my_particle_emitter, _myParticleUpdate);


	while(sgLoop(NULL))
	{
		sgEmitterUpdate(my_particle_emitter, 0.1);
		sgEmitterDraw(my_particle_emitter);

		sgWindowSwapBuffers();
		sgDrawClear();
	}

	sgDeinit();

	return 0;
}
