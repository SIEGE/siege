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
#include "keyboard.h" // for keysGLFW and keysSIEGE

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGenum SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_VERSION_MAJOR;
    (*minfo)->vminor = SG_VERSION_MINOR;
    (*minfo)->vpatch = SG_VERSION_PATCH;

    int mmajor, mminor, mpatch;
    glfwGetVersion(&mmajor, &mminor, &mpatch);;
    (*minfo)->mmajor = mmajor;
    (*minfo)->mminor = mminor;
    (*minfo)->mpatch = mpatch;
    (*minfo)->type = SG_MODULE_CORE;
    (*minfo)->name = "GLFW";

    if(!glfwInit())
        return SG_UNKNOWN_ERROR;
    glfwEnable(GLFW_KEY_REPEAT);
    glfwDisable(GLFW_AUTO_POLL_EVENTS);

    return SG_OK;
}

SGenum SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    free(minfo);

    glfwTerminate();

    return SG_OK;
}

SGenum SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
{
    SGint i;
    *ok = SG_TRUE;
    for(i = numinfos - 1; i >= 0; i--) // we do it reverse because we know that an earlier module overrides the newer one
    {
        if(minfos[i]->type & SG_MODULE_GRAPHICS)
        {
            *ok = SG_TRUE;
            if(strcmp(minfos[i]->name, "OpenGL") != 0)
                *ok = SG_FALSE;
        }
    }

    return SG_OK;
}
