/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#define SG_BUILD_LIBRARY
#include <siege/modules/modules.h>
#include <siege/modules/audio.h>
#include <siege/modules/window.h>
#include <siege/modules/graphics.h>
#include <siege/modules/input.h>
#include <siege/modules/physics.h>
#include <siege/modules/fonts.h>

#include <siege/util/directory.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static SGList* _sg_modList;

static size_t _sg_modNumDirs = 1;
static char* _sg_modDirs[256] = { "modules" };
static size_t _sg_modDirsMaxLen = 7;

static size_t _sg_modNumPrefs = 2;
static char* _sg_modPrefs[256] = { "SGModule-", "libSGModule-" };
static size_t _sg_modPrefsMaxLen = 12;

char* SG_CALL _sgModuleGetFile(const char* module)
{
    SGDirectory* dir;
    char* dname;

    char* buf = malloc(_sg_modDirsMaxLen + strlen("/") + _sg_modPrefsMaxLen + strlen(module) + strlen(".debug.") + 25);

    size_t i, j;
    for(i = 0; i < _sg_modNumDirs; i++)
    {
        dir = sgDirectoryOpen(_sg_modDirs[i]);
        if(dir != NULL)
        {
            while((dname = sgDirectoryNext(dir, NULL, 0)))
            {
                for(j = 0; j < _sg_modNumPrefs; j++)
                {
                    strcpy(buf, _sg_modPrefs[i]);
                    strcat(buf, module);
                    strcat(buf, ".");
                    if(strstr(dname, buf) == dname)
                    {
                        strcpy(buf, _sg_modDirs[i]);
                        strcat(buf, "/");
                        strcat(buf, dname);
                        goto found;
                    }
                }
            }
        found:
            sgDirectoryClose(dir);
            if(dname) // if we've found something
                return buf;
        }
    }

    free(buf);
    return NULL;
}

SGModule* SG_CALL sgModuleLoad(const char* name)
{
    char* fname = _sgModuleGetFile(name);
    if(fname == NULL)
    {
        fprintf(stderr, "Warning: Unable to load module %s: Not found\n", name);
        return NULL;
    }

    SGModule* module = malloc(sizeof(SGModule));
    module->name = malloc(strlen(name) + 1);
    strcpy(module->name, name);
    module->lib = sgLibraryLoad(fname);
    //fprintf(stderr, "Loading %s: %s\n", name, fname);
    if(module->lib == NULL)
        fprintf(stderr, "Warning: Unable to load module %s: Unknown error\n", name);
    free(fname);

    module->sgmModuleInit = (SGMModuleInitFunction*)sgGetProcAddress(module->lib, "sgmModuleInit");
    module->sgmModuleExit = (SGMModuleExitFunction*)sgGetProcAddress(module->lib, "sgmModuleExit");
    module->sgmModuleTick = (SGMModuleTickFunction*)sgGetProcAddress(module->lib, "sgmModuleTick");
    module->sgmModuleMatch = (SGMModuleMatchFunction*)sgGetProcAddress(module->lib, "sgmModuleMatch");

    _sgModuleLoadAudio(module->lib);
    _sgModuleLoadWindow(module->lib);
    _sgModuleLoadGraphics(module->lib);
    _sgModuleLoadInput(module->lib);
    _sgModuleLoadPhysics(module->lib);
    _sgModuleLoadFonts(module->lib);

    if(module->sgmModuleInit != NULL)
        module->sgmModuleInit(&module->minfo);

    if(!_sg_modList)
        _sg_modList = sgListCreate();
    module->node = sgListAppend(_sg_modList, module);
    return module;
}

void SG_CALL sgModuleUnload(SGModule* module)
{
    if(module == NULL)
        return;

    if(module->sgmModuleExit != NULL)
        module->sgmModuleExit(module->minfo);

    sgLibraryUnload(module->lib);

    sgListRemoveNode(_sg_modList, module->node);
    if(!_sg_modList->head)
    {
        sgListDestroy(_sg_modList);
        _sg_modList = NULL;
    }

    free(module->name);
    free(module);
}

void SG_CALL sgModuleSetLoadDirsv(size_t ndirs, va_list args)
{
    // we only allow up to "ndirs" directories.
    if(ndirs > sizeof(_sg_modDirs) / sizeof(*_sg_modDirs))
        ndirs = sizeof(_sg_modDirs) / sizeof(*_sg_modDirs);

    _sg_modDirsMaxLen = 0;
    size_t len;

    size_t i;
    for(i = 0; i < ndirs; i++)
    {
        _sg_modDirs[i] = va_arg(args, char*);
        // if it was NULL, then take next arg from this pos
        if(!_sg_modDirs[i])
        {
            ndirs--;
            i--;
            continue;
        }

        len = strlen(_sg_modDirs[i]);
        if(_sg_modDirsMaxLen < len)
            _sg_modDirsMaxLen = len;
    }
    _sg_modNumDirs = ndirs;

    if(!_sg_modNumDirs)
        sgModuleSetLoadDir(NULL);
}
void SG_CALL sgModuleSetLoadDirs(size_t ndirs, ...)
{
    va_list args;
    va_start(args, ndirs);
    sgModuleSetLoadDirsv(ndirs, args);
    va_end(args);
}
void SG_CALL sgModuleSetLoadDir(const char* dir)
{
    if(!dir)
        sgModuleSetLoadDirs(1, "modules");
    else
        sgModuleSetLoadDirs(1, dir);
}
char** SG_CALL sgModuleGetLoadDirs(size_t* ndirs)
{
    if(ndirs)
        *ndirs = _sg_modNumDirs;
    return _sg_modDirs;
}

void SG_CALL sgModuleSetLoadPrefixesv(size_t nprefs, va_list args)
{
    // we only allow up to "ndirs" directories.
    if(nprefs > sizeof(_sg_modPrefs) / sizeof(*_sg_modPrefs))
        nprefs = sizeof(_sg_modPrefs) / sizeof(*_sg_modPrefs);

    _sg_modPrefsMaxLen = 0;
    size_t len;

    size_t i;
    for(i = 0; i < nprefs; i++)
    {
        _sg_modPrefs[i] = va_arg(args, char*);
        // if it was NULL, then take next arg from this pos
        if(!_sg_modPrefs[i])
        {
            nprefs--;
            i--;
            continue;
        }

        len = strlen(_sg_modPrefs[i]);
        if(_sg_modPrefsMaxLen < len)
            _sg_modPrefsMaxLen = len;
    }
    _sg_modNumPrefs = nprefs;

    if(!_sg_modNumPrefs)
        sgModuleSetLoadPrefix(NULL);
}
void SG_CALL sgModuleSetLoadPrefixes(size_t nprefs, ...)
{
    va_list args;
    va_start(args, nprefs);
    sgModuleSetLoadPrefixesv(nprefs, args);
    va_end(args);
}
void SG_CALL sgModuleSetLoadPrefix(const char* prefix)
{
    if(!prefix)
        sgModuleSetLoadPrefixes(2, "SGModule-", "libSGModule-");
    else
        sgModuleSetLoadPrefixes(1, prefix);
}
char** SG_CALL sgModuleGetLoadPrefixes(size_t* nprefs)
{
    if(nprefs)
        *nprefs = _sg_modNumPrefs;
    return _sg_modPrefs;
}

SGList* SG_CALL sgModuleGetList(void)
{
    return _sg_modList;
}
