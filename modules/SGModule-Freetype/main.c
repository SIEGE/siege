#include "main.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*) calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_INTERFACE_VMAJOR;
    (*minfo)->vminor = SG_INTERFACE_VMINOR;
    (*minfo)->vpatch = SG_INTERFACE_VPATCH;

    int ret = FT_Init_FreeType(&library);
    if(ret != 0)
        return SG_UNKNOWN_ERROR;

    /*int mmajor, mminor, mpatch;
    FT_Library_Version(library, &mmajor, &mminor, &mpatch);
    (*minfo)->mmajor = mmajor;
    (*minfo)->mminor = mminor;
    (*minfo)->mpatch = mpatch;
    (*minfo)->type = SG_MODULE_FONTLOAD;*/
    (*minfo)->name = "Freetype";

    return SG_OK;
}

SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    FT_Done_FreeType(library);

    free(minfo);

    return SG_OK;
}
//SGuint SG_EXPORT sgmModuleFree(void* data)

SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of modules...
    return SG_OK;
}
