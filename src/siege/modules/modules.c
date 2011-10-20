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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

static SGList* _sg_modList;
static size_t _sg_modNumDirs = 1;
static char* _sg_modDirs[256] = { "modules" };
static size_t _sg_modDirsMaxLen = 7;

char* SG_EXPORT _sgModuleGetFile(const char* module)
{
	DIR* dir;
	struct dirent* ent;

	char* buf = malloc(_sg_modDirsMaxLen + strlen("/libSGModule-") + strlen(module) + strlen(".debug.") + 25);

    size_t i;
    for(i = 0; i < _sg_modNumDirs; i++)
    {
        dir = opendir(_sg_modDirs[i]);
        if(dir != NULL)
        {
            while((ent = readdir(dir)))
            {
                strcpy(buf, "libSGModule-");
                strcat(buf, module);
                strcat(buf, ".");
                if(strstr(ent->d_name, buf + 3) == ent->d_name) // prefer without "lib"
                {
                    strcpy(buf, _sg_modDirs[i]);
                    strcat(buf, "/");
                    strcat(buf, ent->d_name);
                    break;
                }
                if(strstr(ent->d_name, buf) == ent->d_name)
                {
                    strcpy(buf, _sg_modDirs[i]);
                    strcat(buf, "/");
                    strcat(buf, ent->d_name);
                    break;
                }
            }
            closedir(dir);
            if(ent) // if we've found something
                return buf;
        }
    }

	free(buf);
	return NULL;
}

SGModule* SG_EXPORT sgModuleLoad(const char* name)
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

void SG_EXPORT sgModuleUnload(SGModule* module)
{
	if(module == NULL)
		return;

	if(module->sgmModuleExit != NULL)
		module->sgmModuleExit(module->minfo);

	sgLibraryUnload(module->lib);

	sgListRemoveNode(_sg_modList, module->node);
    if(!_sg_modList->first)
    {
        sgListDestroy(_sg_modList);
        _sg_modList = NULL;
    }

    free(module->name);
	free(module);
}

void SG_EXPORT sgModuleSetLoadDirsv(size_t ndirs, va_list args)
{
    if(!ndirs)
    {
        sgModuleSetLoadDir("modules");
        return;
    }

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
}
void SG_EXPORT sgModuleSetLoadDirs(size_t ndirs, ...)
{
    va_list args;
    va_start(args, ndirs);
    sgModuleSetLoadDirsv(ndirs, args);
    va_end(args);
}
void SG_EXPORT sgModuleSetLoadDir(const char* dir)
{
    if(!dir)
        dir = "modules";
    sgModuleSetLoadDirs(1, dir);
}
char** SG_EXPORT sgModuleGetLoadDirs(size_t* ndirs)
{
    if(ndirs)
        *ndirs = _sg_modNumDirs;
    return _sg_modDirs;
}

SGList* SG_EXPORT sgModuleGetList(void)
{
    return _sg_modList;
}
