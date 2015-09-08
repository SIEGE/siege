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
#include <siege/common.h>

#include <siege/util/thread/thread.h>

#include <siege/audio/source.h>
#include <siege/core/console.h>
#include <siege/core/core.h>
#include <siege/core/entity.h>
#include <siege/core/window.h>
#include <siege/graphics/light.h>
#include <siege/graphics/surface.h>
#include <siege/graphics/draw.h>
#include <siege/graphics/bitmap.h>
#include <siege/graphics/camera.h>
#include <siege/graphics/viewport.h>
#include <siege/input/keyboard.h>
#include <siege/input/mouse.h>
#include <siege/input/joystick.h>
#include <siege/input/vinput.h>

#include <siege/physics/module.h>
#include <siege/physics/space.h>
#include <siege/util/timer.h>

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>

static SGbool _sg_firstLoop;
static SGbool _sg_exitNow;
static SGint _sg_exitVal;
static SGbool _sg_hasInited = SG_FALSE;
static SGulong _sg_curTick = 0;

static SGThread* _sg_renderThread;
static SGint SG_CALL _sgRenderThread(void* data)
{
    while(!_sg_exitNow)
    {
        sgDrawClear();
        sgEntityEventSignal(1, (SGenum)SG_EVF_DRAW);
        sgWindowSwapBuffers();
    }
    return 0;
}

void SG_CALL sgGetVersionv(SGushort* version)
{
    sgGetVersion(&version[0], &version[1], &version[2]);
}
void SG_CALL sgGetVersion(SGushort* vmajor, SGushort* vminor, SGushort* vpatch)
{
    if(vmajor) *vmajor = SG_VERSION_MAJOR;
    if(vminor) *vminor = SG_VERSION_MINOR;
    if(vpatch) *vpatch = SG_VERSION_PATCH;
}
char* SG_CALL sgGetVersionString(void)
{
    return SG_VERSION_STRING;
}

char* SG_CALL sgGetCompileDate(void)
{
    return __DATE__;
}
char* SG_CALL sgGetCompileTime(void)
{
    return __TIME__;
}

SGbool SG_CALL sgInit(SGenum flags)
{
    if(_sg_hasInited)
        return SG_TRUE;

    // CORE: SDL
    // TODO: change SDL_INIT_EVERYTHING to appropriate values
    if(SDL_Init(SDL_INIT_EVERYTHING))
        return SG_FALSE;
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    _sg_firstLoop = SG_TRUE;
    _sg_exitNow = SG_FALSE;
    _sg_exitVal = 0;

    if(flags & SG_INIT_RENDERTHREAD)
        _sg_renderThread = sgThreadCreate(0, _sgRenderThread, NULL);
    else
        _sg_renderThread = NULL;

    _sgEntityInit();

    sgEntityEventSignal(1, (SGenum)SG_EVF_INIT);
    _sg_hasInited = SG_TRUE;

    _sgBitmapInit();
    _sgCameraInit();
    _sgViewportInit();
    _sgWindowInit();
    _sgSurfaceInit();

    _sgAudioSourceInit();

    _sgKeyboardInit();
    _sgMouseInit();
    _sgJoystickInit();
    _sgVInputInit();

    _sgConsoleInit();

    _sgDrawInit();

    _sgPhysicsLoad();
    if(sgPhysicsIsAvailable())
        _sgPhysicsInit();

    _sgLightInit();

    return SG_TRUE;
}

SGbool SG_CALL sgDeinit(void)
{
    if(!_sg_hasInited)
        return SG_TRUE;

    sgStop(0);
    sgThreadDestroy(_sg_renderThread);

    _sg_hasInited = SG_FALSE;
    sgEntityEventSignal(1, (SGenum)SG_EVF_DEINIT);

    sgEntityDestroyAll();

    _sgLightDeinit();

    if(sgPhysicsIsAvailable())
        _sgPhysicsDeinit();
    _sgPhysicsUnload();

    _sgDrawDeinit();

    _sgConsoleDeinit();

    _sgVInputDeinit();
    _sgJoystickDeinit();
    _sgMouseDeinit();
    _sgKeyboardDeinit();

    _sgAudioSourceDeinit();

    _sgSurfaceDeinit();
    _sgWindowDeinit();
    _sgViewportDeinit();
    _sgCameraDeinit();
    _sgBitmapDeinit();

    _sgEntityDeinit();

    // CORE: SDL
    SDL_Quit();

    return SG_TRUE;
}

SGint SG_CALL sgRun(void)
{
    _sg_firstLoop = SG_TRUE;
    if(_sg_exitNow)
        return _sg_exitVal;
    for(;;)
    {
        if(!_sg_renderThread)
            sgDrawClear();
        if(!sgLoop(&_sg_exitVal))
            break;
        if(!_sg_renderThread)
            sgWindowSwapBuffers();
    }
    return _sg_exitVal;
}

SGbool SG_CALL sgLoop(SGint* code)
{
    _sg_curTick++;

    if(_sg_firstLoop)
    {
        sgEntityEventSignal(1, (SGenum)SG_EVF_START);
        if(_sg_renderThread)
            sgThreadStart(_sg_renderThread);
        _sg_firstLoop = SG_FALSE;
    }

    sgTimerUpdateAll(SG_FALSE, SG_TRUE);

    sgEntityEventSignal(1, (SGenum)SG_EVF_TICKB);

    if(sgPhysicsIsAvailable())
        sgPhysicsSpaceStep(sgPhysicsSpaceGetDefault(), 0.125);

    sgEntityEventSignal(1, (SGenum)SG_EVF_TICK);

    sgWindowHandleEvents();

    if(!_sg_renderThread)
        sgEntityEventSignal(1, (SGenum)SG_EVF_DRAW);

    sgEntityEventSignal(1, (SGenum)SG_EVF_TICKE);

    if(code != NULL)
        *code = _sg_exitVal;
    if(_sg_exitNow)
    {
        sgEntityEventSignal(1, (SGenum)SG_EVF_EXIT);
        return SG_FALSE;
    }
    return SG_TRUE;
}

void SG_CALL sgStop(SGint ret)
{
    _sg_exitNow = SG_TRUE;
    _sg_exitVal = ret;
    if(_sg_renderThread)
        sgThreadJoin(_sg_renderThread);
}

SGulong SG_CALL sgGetTick(void)
{
    return _sg_curTick;
}
