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
#include <stdio.h>

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = (SGModuleInfo*)calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_VERSION_MAJOR;
    (*minfo)->vminor = SG_VERSION_MINOR;
    (*minfo)->vpatch = SG_VERSION_PATCH;

    char buffer[256];
    /*int buflen;
    buflen = */sf_command(NULL, SFC_GET_LIB_VERSION, buffer, sizeof(buffer) / sizeof(char));
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

