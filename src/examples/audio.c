#include <siege/siege.h>

#include <stdlib.h>
#include <stdio.h>

SGAudioBuffer* bufBoom;
SGAudioBuffer* bufMusic;
SGAudioSource* srcMusic;

void SG_CALL evInputButtonPress(SGEntity* entity, SGint id, SGuint button)
{
    if(id != SG_INPUT_ID_MOUSE || button != SG_MOUSE_BUTTON_LEFT) return;

    SGAudioSource* source = sgAudioSourceCreate(0.0, 1.0, 1.0, SG_FALSE);
    sgAudioSourceQueueBuffer(source, bufBoom);
    sgAudioSourcePlay(source);
    sgAudioSourceDestroyLazy(source);
}

int main(void)
{
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);
    sgWindowSetTitle("SIEGE Audio Demo");

    printf("Loading audio data...\n");
    printf("data/audio/boom.ogg..."); fflush(stdout);
    bufBoom = sgAudioBufferCreateFile("data/audio/boom.ogg");
    printf(" Loaded!\n");
    printf("data/audio/WagnerRideOfTheValkyries.ogg..."); fflush(stdout);
    bufMusic = sgAudioBufferCreateFile("data/audio/WagnerRideOfTheValkyries.ogg");
    printf(" Loaded!\n");

    srcMusic = sgAudioSourceCreate(0.0, 1.0, 1.0, SG_TRUE);
    sgAudioSourceQueueBuffer(srcMusic, bufMusic);
    sgAudioSourcePlay(srcMusic);

    SGEntity* handle = sgEntityCreate();
    handle->evInputButtonPress = evInputButtonPress;

    while(sgLoop(NULL))
    {
        sgWindowSwapBuffers();
        sgDrawClear();
    }

    sgAudioSourceDestroy(srcMusic);
    sgAudioBufferDestroy(bufBoom);
    sgAudioBufferDestroy(bufMusic);

    sgDeinit();

    return 0;
}
