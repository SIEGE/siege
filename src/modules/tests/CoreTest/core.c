#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "core.h"

#define SYM(x) (x) = dlsym(module, #x)

void loadCore(char* name)
{
    char* fullname = malloc(strlen("SGModule-") + strlen(name) + 1);
    strcpy(fullname, "SGModule-");
    strcat(fullname, name);

    module = dlopen(fullname, 0);

    SYM(sgModuleInit);
    SYM(sgModuleExit);
    //SYM(sgModuleFree);

    SYM(sgCoreWindowCreate);
    SYM(sgCoreWindowDestroy);
    SYM(sgCoreWindowOpen);
    SYM(sgCoreWindowIsOpened);
    SYM(sgCoreWindowClose);
    //SYM(sgCoreWindowIsClosed);
    SYM(sgCoreWindowSetTitle);
    //SYM(sgCoreWindowGetTitle);
    //SYM(sgCoreWindowFreeTitle);
    SYM(sgCoreWindowSetSize);
    SYM(sgCoreWindowGetSize);
    //SYM(sgCoreWindowPollEvents);
    SYM(sgCoreWindowSwapBuffers);

    SYM(sgCoreWindowSetCallbacks);
    //SYM(sgCoreWindowGetCallbacks);

    free(fullname);
}

void freeCore()
{
    dlclose(module);
}

#undef SYM
