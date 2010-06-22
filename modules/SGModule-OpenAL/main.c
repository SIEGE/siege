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

SGuint SG_EXPORT sgmModuleInit(void* gc, SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*) calloc(1, sizeof(SGModuleInfo));
    (*minfo)->imajor = SG_INTERFACE_VMAJOR;
    (*minfo)->iminor = SG_INTERFACE_VMINOR;
    (*minfo)->ipatch = SG_INTERFACE_VPATCH;

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
    int vmajor, vminor;
    int vpatch = 0;
    if(numdots == 1)
        sscanf(version, "%d.%d", &vmajor, &vminor);
    else
        sscanf(version, "%d.%d.%d", &vmajor, &vminor, &vpatch);

    (*minfo)->vmajor = vmajor;
    (*minfo)->vminor = vminor;
    (*minfo)->vpatch = vpatch;
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
