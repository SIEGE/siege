#include <siege/siege.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * This file is an example on how to use and abuse the particle generator of SIEGE
 * */

/*
 * Here we define an update function, that will be used by the particle
 * generator instead of it's default one when passed to sgEmitterSetUpdateFcn
 */
void _myParticleUpdate1(SGParticle* particle, float time, float friction)
{
    particle->speed -= friction * time;
    if (particle->speed < 0)
        particle->speed = 0;
    particle->x += cos(particle->angle) * particle->speed;
    particle->y += sin(particle->angle) * particle->speed;
    particle->age += time;
    particle->alpha = 1.0 - (particle->age/20);
    particle->rotation += time / 10;
    particle->width = cos(particle->rotation * particle->age / 10) * 48;
    particle->height = cos(particle->rotation * particle->age / 10) * 48;
}

/*
 * Another update function, because we will alternate them :]
 */
void _myParticleUpdate2(SGParticle* particle, float time, float friction)
{
    particle->speed -= friction * time;
    if (particle->speed < 0)
        particle->speed = 0;
    particle->x += cos(particle->angle) * particle->speed;
    particle->y += sin(particle->angle) * particle->speed;
    particle->age += time;
    particle->alpha = 1.0 - (particle->age/20);
    particle->rotation += time / 10;
    particle->width = particle->alpha * 48;
    particle->height = particle->alpha * 48;
    if (particle->alpha > 0.5)
        particle->alpha = 0.5;
}

/*
 * our main function
 */
int main(void)
{
    int state = 0;
    float time = 0;
    /* necessary initialisations of siege */
    sgLoadModule("SDL");
    sgLoadModule("OpenGL");
    sgLoadModule("STB-Image");
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Emitter Demo");

    /* create a texture for our particle generator */
    SGTexture* my_texture = sgTextureCreateFile("data/sprites/CrateSmall.png");

    /* create our particle generator
     * , at this point, we can use it just with sgEmitterUpdate and sgEmitterDraw,
     * but we will abuse it a little to show the flexibility :)
     */
    SGEmitter* my_particle_emitter = sgEmitterCreate(
            320, // x
            240, // y
            0,  // angle
            3.14159/2,  // delta_angle
            1,  // speed
            20,   // duration
            10,  // rate
            0.005, // friction
            2000,  // max nb_particles
            my_texture);
    /*
     * set our first update function
     */
    sgEmitterSetUpdateFunc(my_particle_emitter, _myParticleUpdate1);

    /*
     * if there is not enough room in the particles queu, the particle manager
     * shows errors, if this is intended (to have short periodic bursts of
     * particles), we might want to shut the messages down, it's done like this
     */
    sgEmitterSetSilent(my_particle_emitter, SG_TRUE);


    while(sgLoop(NULL))
    {
        time += 0.001;
        if (state == 0)
        {
            if((int) time % 10 > 5)
            {
                printf("change to state 1\n");
                state = 1;
                /*
                 * change the update function of particles, and reduce the max number of
                 * them, the array won't reduce in reality, but particles after 1000 won't
                 * get updated nor displayed, please not you should not set the
                 * nb_particles to a size superior than the initial size, or you'll crash
                 */
                sgEmitterSetUpdateFunc(my_particle_emitter, _myParticleUpdate2);
                my_particle_emitter->nb_particles = 500;
                my_particle_emitter->duration = 40;
            }
            /* it's nice to see our particles manager rotate :)*/
            my_particle_emitter->angle += 0.005;

        }
        else
        if (state == 1 && (int) time % 10 < 5)
        {
            printf("change to state 0\n");
            state = 0;
            /*
             * restaure inirial update function and initial nb_particles
             */
            sgEmitterSetUpdateFunc(my_particle_emitter, _myParticleUpdate1);
            my_particle_emitter->nb_particles = 2000;
        }

        /* tell the Emitter to update all particles, delete old ones, create new
         * ones, all the hard and not funny job
         */
        sgEmitterUpdate(my_particle_emitter, 0.1);

        /*
         * oh, and draw them, too :)
         */
        sgEmitterDraw(my_particle_emitter);

        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgDeinit();

    return 0;
}
