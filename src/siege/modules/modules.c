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

char* SG_EXPORT _sgModuleGetFile(const char* module)
{
	DIR* dir;
	struct dirent* ent;

	char* buf = malloc(strlen("modules/libSGModule-") + strlen(module) + strlen(".debug.") + 25);

	dir = opendir("modules");
	if(dir != NULL)
	{
		while((ent = readdir(dir)))
		{
			strcpy(buf, "libSGModule-");
			strcat(buf, module);
			strcat(buf, ".");
			if(strstr(ent->d_name, buf + 3) == ent->d_name) // prefer without "lib"
			{
				strcpy(buf, "modules/");
				strcat(buf, ent->d_name);
				return buf;
			}
			if(strstr(ent->d_name, buf) == ent->d_name)
			{
				strcpy(buf, "modules/");
				strcat(buf, ent->d_name);
				return buf;
			}
		}
		closedir(dir);
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

SGList* SG_EXPORT sgModuleGetList(void)
{
    return _sg_modList;
}
