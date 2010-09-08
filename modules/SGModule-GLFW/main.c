#include "main.h"
#include "keyboard.h" // for keysGLFW and keysSIEGE

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo)
{
    *minfo = calloc(1, sizeof(SGModuleInfo));
    (*minfo)->vmajor = SG_INTERFACE_VMAJOR;
    (*minfo)->vminor = SG_INTERFACE_VMINOR;
    (*minfo)->vpatch = SG_INTERFACE_VPATCH;

    int mmajor, mminor, mpatch;
    glfwGetVersion(&mmajor, &mminor, &mpatch);;
    (*minfo)->mmajor = mmajor;
    (*minfo)->mminor = mminor;
    (*minfo)->mpatch = mpatch;
    (*minfo)->type = SG_MODULE_CORE;
    (*minfo)->name = "GLFW";

    if(!glfwInit())
        return SG_UNKNOWN_ERROR;

    return SG_OK;
}

SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo)
{
    free(minfo);

    glfwTerminate();

    return SG_OK;
}
//SGuint SG_EXPORT sgmModuleFree(void* data);

SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok)
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
