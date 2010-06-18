#include "main.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgModuleInit(void* gc, SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*) calloc(1, sizeof(SGModuleInfo));
    (*minfo)->imajor = SG_INTERFACE_VMAJOR;
    (*minfo)->iminor = SG_INTERFACE_VMINOR;
    (*minfo)->ipatch = SG_INTERFACE_VPATCH;

    int ret = FT_Init_FreeType(&library);
    if(ret != 0)
        return SG_UNKNOWN_ERROR;

    /*int vmajor, vminor, vpatch;
    FT_Library_Version(library, &vmajor, &vminor, &vpatch);
    (*minfo)->vmajor = vmajor;
    (*minfo)->vminor = vminor;
    (*minfo)->vpatch = vpatch;
    (*minfo)->type = SG_MODULE_FONTLOAD;*/
    (*minfo)->name = "Freetype";

    return SG_OK;
}

SGuint SG_EXPORT sgModuleExit(SGModuleInfo* minfo)
{
    FT_Done_FreeType(library);

    free(minfo);

    return SG_OK;
}
//SGuint SG_EXPORT sgModuleFree(void* data)

SGuint SG_EXPORT sgModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    *ok = SG_TRUE; // we're independent of modules...
    return SG_OK;
}
