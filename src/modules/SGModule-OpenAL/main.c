#include "main.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

ALint state(ALuint source)
{
    ALint s;
    alGetSourcei(source, AL_SOURCE_STATE, &s);
    return s;
}

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*) calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_VERSION_MAJOR;
    (*minfo)->vminor = SG_VERSION_MINOR;
    (*minfo)->vpatch = SG_VERSION_PATCH;

    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    const char* version = alGetString(AL_VERSION);
    char* space = strchr(version, ' ');
    char* ptr = (char*)version;
    int numdots = 0;
    while(ptr < space && ptr != NULL)
    {
        ptr = strchr(ptr, '.') + 1;
        numdots++;
    }
    numdots--;
    int mmajor, mminor;
    int mpatch = 0;
    if(numdots == 1)
        sscanf(version, "%d.%d", &mmajor, &mminor);
    else
        sscanf(version, "%d.%d.%d", &mmajor, &mminor, &mpatch);

    (*minfo)->mmajor = mmajor;
    (*minfo)->mminor = mminor;
    (*minfo)->mpatch = mpatch;
    (*minfo)->type = SG_MODULE_AUDIO;
    (*minfo)->name = "OpenAL";

    return SG_OK;
}

SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    alcDestroyContext(context);
    alcCloseDevice(device);

    free(minfo);

    return SG_OK;
}
//SGuint SG_EXPORT sgmModuleFree(void* data)

SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of other modules
    return SG_OK;
}
