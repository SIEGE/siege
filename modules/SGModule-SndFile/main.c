#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_INTERFACE_VMAJOR;
    (*minfo)->vminor = SG_INTERFACE_VMINOR;
    (*minfo)->vpatch = SG_INTERFACE_VPATCH;

    char buffer[256];
    int buflen;
    buflen = sf_command(NULL, SFC_GET_LIB_VERSION, buffer, sizeof(buffer) / sizeof(char));
    int mmajor, mminor, mpatch;
    sscanf(buffer, "%d.%d.%d", &mmajor, &mminor, &mpatch);

    (*minfo)->mmajor = mmajor;
    (*minfo)->mminor = mminor;
    (*minfo)->mpatch = mpatch;
    (*minfo)->type = SG_MODULE_AUDIOLOAD;
    (*minfo)->name = "SndFile";

    return SG_OK;
}

SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    free(minfo);
    return SG_OK;
}

SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of other modules...
    return SG_OK;
}

//SGuint SG_EXPORT sgmModuleFree(void* data)

