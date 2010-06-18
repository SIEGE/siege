#include "main.h"
#include "keyboard.h" // for keysSDL and keysSIEGE

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgModuleInit(void* gc, SGModuleInfo** minfo)
{
    *minfo = calloc(1, sizeof(SGModuleInfo));
    (*minfo)->imajor = SG_INTERFACE_VMAJOR;
    (*minfo)->iminor = SG_INTERFACE_VMINOR;
    (*minfo)->ipatch = SG_INTERFACE_VPATCH;

    SDL_version ver = *SDL_Linked_Version();
    (*minfo)->vmajor = ver.major;
    (*minfo)->vminor = ver.minor;
    (*minfo)->vpatch = ver.patch;
    (*minfo)->type = SG_MODULE_WINDOW | SG_MODULE_INPUT;
    (*minfo)->name = "SDL";

    (*minfo)->data = NULL;
    useGL = SG_FALSE;

    if(SDL_Init(SDL_INIT_EVERYTHING))
        return SG_UNKNOWN_ERROR;
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    return SG_OK;
}

SGuint SG_EXPORT sgModuleExit(SGModuleInfo* minfo)
{
    free(minfo->data);
    free(minfo);

    SDL_Quit();

    return SG_OK;
}
//SGuint SG_EXPORT sgModuleFree(void* data);

SGuint SG_EXPORT sgModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
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
