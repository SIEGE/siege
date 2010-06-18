#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgModuleInit(void* gc, SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));
    (*minfo)->imajor = SG_INTERFACE_VMAJOR;
    (*minfo)->iminor = SG_INTERFACE_VMINOR;
    (*minfo)->ipatch = SG_INTERFACE_VPATCH;

    char buffer[256];
    int buflen;
    buflen = sf_command(NULL, SFC_GET_LIB_VERSION, buffer, sizeof(buffer) / sizeof(char));
    int vmajor, vminor, vpatch;
    sscanf(buffer, "%d.%d.%d", &vmajor, &vminor, &vpatch);

    (*minfo)->vmajor = vmajor;
    (*minfo)->vminor = vminor;
    (*minfo)->vpatch = vpatch;
    (*minfo)->type = SG_MODULE_AUDIOLOAD;
    (*minfo)->name = "SndFile";

    return SG_OK;
}

SGuint SG_EXPORT sgModuleExit(SGModuleInfo* minfo)
{
    free(minfo);
    return SG_OK;
}

SGuint SG_EXPORT sgModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of modules...
    return SG_OK;
}

//SGuint SG_EXPORT sgModuleFree(void* data)

