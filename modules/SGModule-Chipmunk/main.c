#include "main.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

SGuint SG_EXPORT sgModuleInit(void* gc, SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));
    (*minfo)->imajor = SG_INTERFACE_VMAJOR;
    (*minfo)->iminor = SG_INTERFACE_VMINOR;
    (*minfo)->ipatch = SG_INTERFACE_VPATCH;
    // unknown version
    (*minfo)->vmajor = 0;
    (*minfo)->vminor = 0;
    (*minfo)->vpatch = 0;
    (*minfo)->type = SG_MODULE_PHYSICS;
    (*minfo)->name = "Chipmunk";

    cpInitChipmunk();

    return SG_OK;
}

SGuint SG_EXPORT sgModuleExit(SGModuleInfo* minfo)
{
    free(minfo);

    return SG_OK;
}

//SGuint SG_EXPORT sgModuleFree(void* data)

SGuint SG_EXPORT sgModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of modules...
    return SG_OK;
}

