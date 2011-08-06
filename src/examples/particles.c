#include <siege/siege.h>
#include <siege/graphics/particles.h>

#include <stdlib.h>
#include <math.h>

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
			40,   // duration
			40,  // rate
			0.01, // friction
			2000,  // max nb_particles
			my_texture);


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
