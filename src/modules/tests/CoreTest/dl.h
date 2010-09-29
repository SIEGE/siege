#ifndef __DL_H__
#define __DL_H__

void* dlopen(const char* file, int mode);
int dlclose(void* handle);
void* dlsym(void* handle, const char* name);
char* dlerror(void);

#endif // __DL_H__
