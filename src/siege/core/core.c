/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#define SG_BUILD_LIBRARY
#include <siege/audio/buffer.h>
#include <siege/audio/source.h>
#include <siege/core/console.h>
#include <siege/core/core.h>
#include <siege/core/event.h>
#include <siege/core/entity.h>
#include <siege/core/window.h>
#include <siege/graphics/surface.h>
#include <siege/graphics/draw.h>
#include <siege/graphics/turtle.h>
#include <siege/graphics/viewport.h>
#include <siege/input/keyboard.h>
#include <siege/input/mouse.h>
#include <siege/input/joystick.h>
#include <siege/modules/modules.h>
#include <siege/util/color.h>
#include <siege/util/link.h>
#include <siege/util/rand.h>
#include <siege/util/string.h>
#include <siege/physics/space.h>

#include <stdlib.h>
#include <stdio.h>

SGbool _sg_firstModule = SG_TRUE;
SGbool _sg_firstLoop = SG_TRUE;
SGbool _sg_exitNow = SG_FALSE;
SGint _sg_exitVal = 0;
SGbool _sg_hasInited = SG_FALSE;
SGulong _sg_curTick = 0;

SGuint SG_EXPORT sgLoadModulesv(int n, va_list args)
{
    SGuint loaded = 0;
    size_t i;
    for(i = 0; i < n; i++)
        loaded += sgLoadModule(va_arg(args, char*));
    return loaded;
}
SGuint SG_EXPORT sgLoadModules(int n, ...)
{
    va_list args;
    va_start(args, n);
    SGuint ret = sgLoadModulesv(n, args);
    va_end(args);
    return ret;
}
SGbool SG_EXPORT sgLoadModule(const char* name)
{
    if(_sg_firstModule)
    {
        _sgLibraryInit();
        _sgModuleInit();
        _sg_firstModule = SG_FALSE;
    }

    SGModule* module = sgModuleLoad(name);
    if(module == NULL)
        return SG_FALSE;
    return SG_TRUE;
}

SGbool SG_EXPORT sgInit(SGuint width, SGuint height, SGuint bpp, SGenum flags)
{
    _sgStringInit();

    _sgEventInit();
    _sgEntityInit();

    size_t i;
    size_t nmodules = sgLinkedListLength(_sg_modList);
    SGLinkedNode* node;
    SGModuleInfo** infos = malloc(nmodules * sizeof(SGModuleInfo*));
    SGModule* module;
    for(i = 0, node = _sg_modList->first; node != NULL; node = node->next, i++)
    {
        module = node->item;
        infos[i] = module->minfo;
    }
    SGbool ok = SG_TRUE;
    SGbool mok;
    for(node = _sg_modList->first; node != NULL; node = node->next)
    {
        module = node->item;
        mok = SG_TRUE;
        if(module->sgmModuleMatch != NULL)
            module->sgmModuleMatch(infos, nmodules, &mok);
        if(!mok)
        {
            fprintf(stderr, "Could not load module %s: Incompatible with other modules\n", module->minfo->name);
            ok = SG_FALSE;
        }
    }
    free(infos);
    if(!ok)
        return SG_FALSE;

    _SGEntityCall call;
    call = (_SGEntityCall){1, (SGenum[]){SG_EVF_INIT}, (void*[]){NULL}};
    sgEventCall(SG_EV_INTERNAL, &call);
    _sg_hasInited = SG_TRUE;

    _sgColorInit();
    _sgWindowInit();
    _sgViewportInit();
    _sgTurtleInit();
    _sgSurfaceInit();

    _sgAudioBufferInit();
    _sgAudioSourceInit();

    _sgKeyboardInit();
    _sgMouseInit();
    _sgJoystickInit();

    _sgConsoleInit();

    _sgDrawInit();

    _sgRandInit();
    _sgPhysicsSpaceInit();

    sgWindowOpen(width, height, bpp, flags);

    return SG_TRUE;
}

SGbool SG_EXPORT sgDeinit(void)
{
    _SGEntityCall call;
    _sg_hasInited = SG_FALSE;
    call = (_SGEntityCall){1, (SGenum[]){SG_EVF_DEINIT}, (void*[]){NULL}};
    sgEventCall(SG_EV_INTERNAL, &call);

    _sgPhysicsSpaceDeinit();
    _sgRandDeinit();

    _sgDrawDeinit();

    _sgConsoleDeinit();

    _sgJoystickDeinit();
    _sgMouseDeinit();
    _sgKeyboardDeinit();

    _sgAudioSourceDeinit();
    _sgAudioBufferDeinit();

    _sgSurfaceDeinit();
    _sgTurtleDeinit();
    _sgViewportDeinit();
    _sgWindowDeinit();
    _sgColorDeinit();

    _sgEntityDeinit();
    _sgEventDeinit();

    _sgStringDeinit();

    _sgModuleDeinit();
    _sgLibraryDeinit();

    return SG_TRUE;
}

SGint SG_EXPORT sgRun(void)
{
    _sg_firstLoop = SG_TRUE;
    if(_sg_exitNow)
        return _sg_exitVal;
    while(sgLoop(&_sg_exitVal))
    {
        sgWindowSwapBuffers();
        sgDrawClear();
    }
    return _sg_exitVal;
}

SGbool SG_EXPORT sgLoop(SGint* code)
{
    _sg_curTick++;

    _SGEntityCall call;

    if(_sg_firstLoop)
    {
        call = (_SGEntityCall){1, (SGenum[]){SG_EVF_START}, (void*[]){NULL}};
        sgEventCall(SG_EV_INTERNAL, &call);
        _sg_firstLoop = SG_FALSE;
    }

    call = (_SGEntityCall){1, (SGenum[]){SG_EVF_TICKB}, (void*[]){NULL}};
    sgEventCall(SG_EV_INTERNAL, &call);

    sgPhysicsSpaceStep(_sg_physSpaceMain, 0.125);

    call = (_SGEntityCall){1, (SGenum[]){SG_EVF_TICK}, (void*[]){NULL}};
    sgEventCall(SG_EV_INTERNAL, &call);

    call = (_SGEntityCall){1, (SGenum[]){SG_EVF_TICKE}, (void*[]){NULL}};
    sgEventCall(SG_EV_INTERNAL, &call);

    call = (_SGEntityCall){1, (SGenum[]){SG_EVF_DRAW}, (void*[]){NULL}};
    sgEventCall(SG_EV_INTERNAL, &call);

    if(code != NULL)
        *code = _sg_exitVal;
    if(_sg_exitNow)
    {
        call = (_SGEntityCall){1, (SGenum[]){SG_EVF_EXIT}, (void*[]){NULL}};
        sgEventCall(SG_EV_INTERNAL, &call);
        _sg_exitNow = SG_FALSE;

        return SG_FALSE;
    }
    return SG_TRUE;
}

void SG_EXPORT sgStop(SGint ret)
{
    _sg_exitNow = SG_TRUE;
    _sg_exitVal = ret;
}

SGulong SG_EXPORT sgGetTick(void)
{
    return _sg_curTick;
}
