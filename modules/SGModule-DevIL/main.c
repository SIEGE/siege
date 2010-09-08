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

    ilInit();

    /*int version = ilGetInteger(IL_VERSION_NUM);

    (*minfo)->mmajor = version / 100;
    (*minfo)->mminor = version / 10 - (*minfo)->mmajor * 100;
    (*minfo)->mpatch = version / 1 - (*minfo)->mminor * 10 - (*minfo)->mmajor * 100;
    (*minfo)->type = SG_MODULE_GRAPHICSLOAD;*/
    (*minfo)->name = "DevIL";

    return SG_OK;
}

SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    ilShutDown();
    free(minfo);

    return SG_OK;
}

//SGuint SG_EXPORT sgmModuleFree(void* data)

SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of modules...
    return SG_OK;
}

