#include "main.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_VERSION_MAJOR;
    (*minfo)->vminor = SG_VERSION_MINOR;
    (*minfo)->vpatch = SG_VERSION_PATCH;
    // unknown version
    (*minfo)->mmajor = 0;
    (*minfo)->mminor = 0;
    (*minfo)->mpatch = 0;
    (*minfo)->type = SG_MODULE_PHYSICS;
    (*minfo)->name = "Chipmunk";

    cpInitChipmunk();

    return SG_OK;
}

SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    free(minfo);

    return SG_OK;
}

//SGuint SG_EXPORT sgmModuleFree(void* data)

SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of modules...
    return SG_OK;
}

