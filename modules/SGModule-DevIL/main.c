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

    ilInit();

    /*int version = ilGetInteger(IL_VERSION_NUM);

    (*minfo)->vmajor = version / 100;
    (*minfo)->vminor = version / 10 - (*minfo)->vmajor * 100;
    (*minfo)->vpatch = version / 1 - (*minfo)->vminor * 10 - (*minfo)->vmajor * 100;
    (*minfo)->type = SG_MODULE_GRAPHICSLOAD;*/
    (*minfo)->name = "DevIL";

    return SG_OK;
}

SGuint SG_EXPORT sgModuleExit(SGModuleInfo* minfo)
{
    ilShutDown();
    free(minfo);

    return SG_OK;
}

//SGuint SG_EXPORT sgModuleFree(void* data)

SGuint SG_EXPORT sgModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of modules...
    return SG_OK;
}

