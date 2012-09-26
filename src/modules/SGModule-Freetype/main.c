/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "common.h"

#include <stdlib.h>

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*) calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_VERSION_MAJOR;
    (*minfo)->vminor = SG_VERSION_MINOR;
    (*minfo)->vpatch = SG_VERSION_PATCH;

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
