#include <siege/siege.h>

#include <stdlib.h>
#include <stdio.h>

SGAudioBuffer* bufBoom;
SGAudioBuffer* bufMusic;
SGAudioSource* srcBoom;
SGAudioSource* srcMusic;

void SG_EXPORT evMouseButtonLeftPress(SGEntity* entity)
{
    SGAudioSource* source = sgAudioSourceCreate(0.0, 1.0, 1.0, SG_FALSE);
    sgAudioSourceQueueBuffer(source, bufBoom);
    sgAudioSourcePlay(source);
    sgAudioSourceDestroyLazy(source);

    //sgAudioSourcePlay(srcBoom);
}

int main(void)
{
	sgLoadModule("SDL");
	sgLoadModule("OpenGL");
    sgLoadModule("OpenAL");
    sgLoadModule("SndFile");
    sgInit(0);
	sgWindowOpen(640, 480, 32, 0);
	sgWindowSetTitle("SIEGE Audio Demo");

    printf("Loading audio data...\n");
    printf("data/audio/boom.flac..."); fflush(stdout);
    bufBoom = sgAudioBufferCreateFile("data/audio/boom.flac");
    printf(" Loaded!\n");
    printf("data/audio/WagnerRideOfTheValkyries.ogg..."); fflush(stdout);
    bufMusic = sgAudioBufferCreateFile("data/audio/WagnerRideOfTheValkyries.ogg");
    printf(" Loaded!\n");

    srcMusic = sgAudioSourceCreate(0.0, 1.0, 1.0, SG_TRUE);
    sgAudioSourceQueueBuffer(srcMusic, bufMusic);
    sgAudioSourcePlay(srcMusic);

    srcBoom = sgAudioSourceCreate(0.0, 1.0, 1.0, SG_FALSE);
    sgAudioSourceQueueBuffer(srcBoom, bufBoom);

    SGEntity* handle = sgEntityCreate(0.0);
    handle->evMouseButtonLeftPress = evMouseButtonLeftPress;

	while(sgLoop(NULL))
	{
		sgWindowSwapBuffers();
		sgDrawClear();
	}

    sgAudioSourceDestroy(srcBoom);
    sgAudioSourceDestroy(srcMusic);
    sgAudioBufferDestroy(bufBoom);
    sgAudioBufferDestroy(bufMusic);

	sgDeinit();

	return 0;
}
