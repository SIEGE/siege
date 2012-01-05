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

#define SG_BUILD_LIBRARY
#include <siege/util/directory.h>

#include <stdlib.h>
#include <string.h>
#ifdef __WIN32__
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <dirent.h>
#endif

SGDirectory* SG_EXPORT sgDirectoryOpen(const char* fname)
{
    SGDirectory* dir = malloc(sizeof(SGDirectory));

    size_t len = strlen(fname);
	dir->name = malloc(len + 3);
    memcpy(dir->name, fname, len + 1);

#ifdef __WIN32__
    memcpy(dir->name + len, "\\*", 3);

    dir->buflen = MAX_PATH + 1;
    dir->ibuf = malloc(sizeof(WIN32_FIND_DATA));
    dir->handle = FindFirstFile(dir->name, dir->ibuf);
    if(!dir->handle)
    {
		free(dir->name);
		free(dir->ibuf);
		free(dir);
		return NULL;
	}
	else
		FindClose(dir->handle);
#else
	dir->buflen = NAME_MAX + 1;
	// that +1 is just in case, even though dirent has [1] at d_name
	//dir->ibuf = malloc(sizeof(struct dirent) + NAME_MAX + 1);
	dir->ibuf = NULL;
	dir->handle = opendir(dir->name);
	if(!dir->handle)
	{
		free(dir->name);
		free(dir);
		return NULL;
	}
#endif
	dir->buf = malloc(dir->buflen);
	dir->buf[0] = 0;
	dir->buf[dir->buflen - 1] = 0;

    return dir;
}
void SG_EXPORT sgDirectoryClose(SGDirectory* dir)
{
    if(!dir)
        return;
#ifdef __WIN32__
    if(dir->handle)
        FindClose(dir->handle);
#else
    closedir(dir->handle);
#endif
    free(dir->name);
    free(dir->buf);
    free(dir->ibuf);
    free(dir);
}

char* SG_EXPORT sgDirectoryNext(SGDirectory* dir, char* buf, size_t len)
{
    if(!buf || !len)
    {
        buf = dir->buf;
        len = dir->buflen;
    }

#ifdef __WIN32__
    WIN32_FIND_DATA* data = dir->ibuf;
    if(!dir->handle)
    {
        dir->handle = FindFirstFile(dir->name, data);
        if(!dir->handle)
            return NULL;
    }
    else if(!FindNextFile(dir->handle, data))
            return NULL;
    // memcpy?
    strncpy(buf, data->cFileName, SG_MIN(MAX_PATH,len));
    buf[SG_MIN(MAX_PATH,len)-1] = 0;
#else
    struct dirent* ent = readdir(dir->handle);
    if(!ent)
		return NULL;
    // memcpy?
    strncpy(buf, ent->d_name, SG_MIN(NAME_MAX+1,len));
    buf[SG_MIN(NAME_MAX+1,len)-1] = 0;
#endif

    return buf;
}
void SG_EXPORT sgDirectoryRewind(SGDirectory* dir)
{
#ifdef __WIN32__
    if(dir->handle)
    {
        FindClose(dir->handle);
        dir->handle = NULL;
    }
#else
    rewinddir(dir->handle);
#endif
}
