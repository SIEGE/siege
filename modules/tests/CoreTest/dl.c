#include "dl.h"

#include <windows.h>

void* dlopen(const char* file, int mode)
{
    return LoadLibrary(file);
}

int dlclose(void* handle)
{
    return !FreeLibrary(handle);
}

void* dlsym(void* handle, const char* name)
{
    return GetProcAddress(handle, name);
}

char* dlerror(void)
{
    return NULL;
}
