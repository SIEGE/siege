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
#include "keyboard.h" // for keysSDL and keysSIEGE

#include <stdlib.h>

SGenum SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_VERSION_MAJOR;
    (*minfo)->vminor = SG_VERSION_MINOR;
    (*minfo)->vpatch = SG_VERSION_PATCH;

    //const SDL_version* ver = SDL_Linked_Version();
    SDL_version ver;
    SDL_VERSION(&ver);
    (*minfo)->mmajor = ver.major;
    (*minfo)->mminor = ver.minor;
    (*minfo)->mpatch = ver.patch;
    (*minfo)->type = SG_MODULE_WINDOW | SG_MODULE_INPUT;
    (*minfo)->name = "SDL";

    (*minfo)->data = NULL;
    useGL = SG_FALSE;

    if(SDL_Init(SDL_INIT_EVERYTHING))
        return SG_UNKNOWN_ERROR;
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    return SG_OK;
}

SGenum SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    free(minfo->data);
    free(minfo);

    SDL_Quit();

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
            if(strcmp(minfos[i]->name, "SDL") == 0)
                useGL = SG_FALSE;
            else if(strcmp(minfos[i]->name, "OpenGL") == 0)
                useGL = SG_TRUE;
            else if(strcmp(minfos[i]->name, "Mesa") == 0)
                useGL = SG_TRUE;
            else
                *ok = SG_FALSE;
        }
    }

    if(useGL)
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return SG_OK;
}
