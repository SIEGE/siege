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
#include <siege/core/core.h>
#include <siege/core/entity.h>
#include <siege/core/window.h>
#include <siege/graphics/viewport.h>
#include <siege/input/joystick.h>
#include <siege/input/keyboard.h>
#include <siege/input/mouse.h>
#include <siege/util/string.h>
#include <siege/util/time.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#include <SDL/SDL.h>
#include "../internal/gl.h"

#define BIND(name)  \
    do {            \
        gl##name##EXT = SDL_GL_GetProcAddress("gl" #name);                          \
        if(!gl##name##EXT) gl##name##EXT = SDL_GL_GetProcAddress("gl" #name "EXT"); \
        if(!gl##name##EXT) {                                                        \
            fprintf(stderr, "Unable to load extension function %s\n", "gl" #name);  \
            return SG_FALSE;                                                        \
        }                                                                           \
    } while(0)

static SGbool bindGL(void)
{
    BIND(IsRenderbuffer);
    BIND(BindRenderbuffer);
    BIND(DeleteRenderbuffers);
    BIND(GenRenderbuffers);
    BIND(RenderbufferStorage);
    BIND(GetRenderbufferParameteriv);
    BIND(IsFramebuffer);
    BIND(BindFramebuffer);
    BIND(DeleteFramebuffers);
    BIND(GenFramebuffers);
    BIND(CheckFramebufferStatus);
    BIND(FramebufferTexture1D);
    BIND(FramebufferTexture2D);
    BIND(FramebufferTexture3D);
    BIND(FramebufferRenderbuffer);
    BIND(GetFramebufferAttachmentParameteriv);
    BIND(GenerateMipmap);

    BIND(BlendEquation);
    return SG_TRUE;
}
static SGbool initGL(void)
{
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    if(!bindGL())
        return SG_FALSE;
    return SG_TRUE;
}
static void resizeGL(SGuint width, SGuint height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, height, 0, 127, -128);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static char*        winTitle;
static SDL_Surface* winIcon;
static SDL_Surface* winSurface;

static SGfloat _sg_FPS = -1.0f;
static SGlong _sg_FrameLength = -1L;
static SGfloat _sg_achievedFramerate = -1.0f;

static const int keysSDL[] = {
         SDLK_SPACE    , SDLK_ESCAPE
        ,SDLK_F1       , SDLK_F2         , SDLK_F3       , SDLK_F4      , SDLK_F5  , SDLK_F6
        ,SDLK_F7       , SDLK_F8         , SDLK_F9       , SDLK_F10     , SDLK_F11 , SDLK_F12
        ,SDLK_F13      , SDLK_F14        , SDLK_F15
        ,SDLK_UP       , SDLK_DOWN       , SDLK_LEFT     , SDLK_RIGHT
        ,SDLK_LSHIFT   , SDLK_RSHIFT     , SDLK_LCTRL    , SDLK_RCTRL   , SDLK_LALT, SDLK_RALT
        ,SDLK_TAB      , SDLK_RETURN     , SDLK_BACKSPACE
        ,SDLK_INSERT   , SDLK_DELETE     , SDLK_PAGEUP   , SDLK_PAGEDOWN, SDLK_HOME, SDLK_END
        ,SDLK_KP0      , SDLK_KP1        , SDLK_KP2      , SDLK_KP3     , SDLK_KP4
        ,SDLK_KP5      , SDLK_KP6        , SDLK_KP7      , SDLK_KP8     , SDLK_KP9
        ,SDLK_KP_DIVIDE, SDLK_KP_MULTIPLY, SDLK_KP_MINUS , SDLK_KP_PLUS
        ,SDLK_KP_PERIOD, SDLK_KP_EQUALS  , SDLK_KP_ENTER
        ,SDLK_UNKNOWN
    };
static const SGenum keysSIEGE[] = {
         SG_KEY_SPACE     , SG_KEY_ESC
        ,SG_KEY_F1        , SG_KEY_F2         , SG_KEY_F3         , SG_KEY_F4      , SG_KEY_F5  , SG_KEY_F6
        ,SG_KEY_F7        , SG_KEY_F8         , SG_KEY_F9         , SG_KEY_F10     , SG_KEY_F11 , SG_KEY_F12
        ,SG_KEY_F13       , SG_KEY_F14        , SG_KEY_F15
        ,SG_KEY_UP        , SG_KEY_DOWN       , SG_KEY_LEFT       , SG_KEY_RIGHT
        ,SG_KEY_LSHIFT    , SG_KEY_RSHIFT     , SG_KEY_LCTRL      , SG_KEY_RCTRL   , SG_KEY_LALT, SG_KEY_RALT
        ,SG_KEY_TAB       , SG_KEY_ENTER      , SG_KEY_BACKSPACE
        ,SG_KEY_INSERT    , SG_KEY_DELETE     , SG_KEY_PAGEUP     , SG_KEY_PAGEDOWN, SG_KEY_HOME, SG_KEY_END
        ,SG_KEY_KP0       , SG_KEY_KP1        , SG_KEY_KP2        , SG_KEY_KP3     , SG_KEY_KP4
        ,SG_KEY_KP5       , SG_KEY_KP6        , SG_KEY_KP7        , SG_KEY_KP8     , SG_KEY_KP9
        ,SG_KEY_KP_DIVIDE , SG_KEY_KP_MULTIPLY, SG_KEY_KP_SUBTRACT, SG_KEY_KP_ADD
        ,SG_KEY_KP_DECIMAL, SG_KEY_KP_EQUAL   , SG_KEY_KP_ENTER
        ,SG_KEY_UNKNOWN
    };
/* TODO: change into O(1) conversion by using direct table access */
static SGenum keySDLtoSIEGE(int key)
{
    SGuint sgkey = key;
    int i;
    for(i = 0; keysSDL[i] != 0; i++)
        if(keysSDL[i] == key)
        {
            sgkey = keysSIEGE[i];
            break;
        }
    if(keysSDL[i] == 0) // if we didn't find a key
        sgkey = toupper(sgkey);
    return sgkey;
}

void SG_CALL _sg_cbWindowOpen(void)
{
    sgEntityEventSignal(1, (SGenum)SG_EVF_WINOPEN);
}
void SG_CALL _sg_cbWindowClose(void)
{
    sgEntityEventSignal(1, (SGenum)SG_EVF_WINCLOSE);
    sgStop(0);
}
void SG_CALL _sg_cbWindowResize(SGuint width, SGuint height)
{
    sgEntityEventSignal(1, (SGenum)SG_EVF_WINRESIZE, width, height);
}

SGbool SG_CALL _sgWindowInit(void)
{
    winTitle = NULL;
    winIcon = NULL;
    winSurface = NULL;

    return SG_TRUE;
}

SGbool SG_CALL _sgWindowDeinit(void)
{
    sgWindowClose();

    if(winTitle)
        free(winTitle);
    if(winIcon)
    {
        SDL_FreeSurface(winIcon);
        winIcon = NULL;
    }

    return SG_TRUE;
}

SGbool SG_CALL sgWindowOpen(SGuint width, SGuint height, SGuint bpp, SGenum flags)
{
    if(!width)  width = 640;
    if(!height) height = 480;
    if(!bpp)    bpp = 32;

    if(sgWindowIsOpened())
        sgWindowClose();

    Uint32 sdlflags = SDL_OPENGL;
    if(flags & SG_WINDOW_FULLSCREEN)
        sdlflags |= SDL_FULLSCREEN;
    if(flags & SG_WINDOW_RESIZABLE)
        sdlflags |= SDL_RESIZABLE;

    winSurface = SDL_SetVideoMode(width, height, bpp, sdlflags);
    if(!winSurface)
        return SG_FALSE;    // TODO: ERRORMSG

    sgWindowGetSize(&width, &height);
    if(!initGL())
        return SG_FALSE;

    _sg_viewMain = sgViewportCreate4i(0, 0, width, height);

    _sg_cbWindowOpen();
    _sg_cbWindowResize(width, height);
    return SG_TRUE;
}
SGbool SG_CALL sgWindowIsOpened(void)
{
    return winSurface != NULL;
}
void SG_CALL sgWindowClose(void)
{
    // TODO: Actually close the window (SDL2 ...)
    _sg_cbWindowClose();
}
void SG_CALL sgWindowSetIcon(SGImageData* idata)
{
    if(winIcon)
        SDL_FreeSurface(winIcon);

    // TODO: Move this to an utility function somewhere (as I'm sure it'll come in handy elsewhere)
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xFF000000;
    gmask = 0x00FF0000;
    bmask = 0x0000FF00;
    amask = 0x000000FF;
#else
    rmask = 0x000000FF;
    gmask = 0x0000FF00;
    bmask = 0x00FF0000;
    amask = 0xFF000000;
#endif

    SGubyte bypp;
    switch(idata->bpp)
    {
        case 8:
            bypp = 1;
            break;
        case 15:
            bypp = 2;
            break;
        case 16:
            bypp = 2;
            break;
        case 24:
            bypp = 3;
            break;
        case 32:
            bypp = 4;
            break;
        default:
            return; // TODO: Report error
    }

    winIcon = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, idata->width, idata->height, idata->bpp, rmask, gmask, bmask, amask);
    SDL_LockSurface(winIcon);
    size_t i;
    for(i = 0; i < idata->height; i++)
        memcpy(&((char*)winIcon->pixels)[i * winIcon->pitch], ((char*)idata->data) + bypp * idata->width * i, bypp * idata->width);
    SDL_UnlockSurface(winIcon);
    SDL_WM_SetIcon(winIcon, NULL);
}
void SG_CALL sgWindowSetTitlef(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    sgWindowSetTitlefv(format, args);
    va_end(args);
}
void SG_CALL sgWindowSetTitlefv(const char* format, va_list args)
{
    char* title = sgAPrintfv(format, args);
    sgWindowSetTitle(title);
    sgAPrintFree(title);
}
void SG_CALL sgWindowSetTitle(const char* title)
{
    size_t len = strlen(title);
    winTitle = realloc(winTitle, len + 1);
    memcpy(winTitle, title, len + 1);

    SDL_WM_SetCaption(winTitle, winTitle);
}
char* SG_CALL sgWindowGetTitle(void)
{
    return winTitle;
}
void SG_CALL sgWindowSetSize(SGuint width, SGuint height)
{
    winSurface = SDL_SetVideoMode(width, height, winSurface->format->BitsPerPixel, winSurface->flags);
    resizeGL(width, height);
    _sg_cbWindowResize(width, height);
}
void SG_CALL sgWindowGetSize(SGuint* width, SGuint* height)
{
    SGuint tmp;
    if(!width)  width = &tmp;
    if(!height) height = &tmp;

    if(!winSurface)
        *width = *height = 0;
    else
    {
        *width = winSurface->w;
        *height = winSurface->h;
    }
}
void SG_CALL sgWindowSetWidth(SGuint width)
{
    sgWindowSetSize(width, sgWindowGetHeight());
}
SGuint SG_CALL sgWindowGetWidth(void)
{
    SGuint width;
    sgWindowGetSize(&width, NULL);
    return width;
}
void SG_CALL sgWindowSetHeight(SGuint height)
{
    sgWindowSetSize(sgWindowGetWidth(), height);
}
SGuint SG_CALL sgWindowGetHeight(void)
{
    SGuint height;
    sgWindowGetSize(NULL, &height);
    return height;
}
void SG_CALL sgWindowHandleEvents(void)
{
    if(!winSurface)
        return;

    // TODO: Rework this completely.

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_VIDEORESIZE:
                sgWindowSetSize(event.resize.w, event.resize.h);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                _sg_cbKeyboardKey(keySDLtoSIEGE(event.key.keysym.sym), event.key.state == SDL_PRESSED);
                if(event.key.state == SDL_PRESSED && event.key.keysym.unicode != 0)
                    _sg_cbKeyboardChar(event.key.keysym.unicode);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_WHEELUP)
                {
                    if(event.button.state == SDL_PRESSED)
                        _sg_cbMouseWheel(_sg_mouseWheel + 1);
                }
                else if(event.button.button == SDL_BUTTON_WHEELDOWN)
                {
                    if(event.button.state == SDL_PRESSED)
                        _sg_cbMouseWheel(_sg_mouseWheel - 1);
                }
                else
                {
                    if(event.button.button == SDL_BUTTON_RIGHT)
                        event.button.button = SDL_BUTTON_MIDDLE;
                    else if(event.button.button == SDL_BUTTON_MIDDLE)
                        event.button.button = SDL_BUTTON_RIGHT;
                    _sg_cbMouseButton(event.button.button, event.button.state == SDL_PRESSED);
                }
                break;

            case SDL_MOUSEMOTION:
                _sg_cbMouseMove(event.motion.x, event.motion.y);
                break;

            case SDL_JOYAXISMOTION:
                _sg_cbJoystickMove(event.jaxis.which, event.jaxis.axis, (event.jaxis.value + 0.5) / 32767.5);
                break;
            case SDL_JOYBALLMOTION:
            case SDL_JOYHATMOTION: /// \todo TODO
                break;
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                _sg_cbJoystickButton(event.jbutton.which, event.jbutton.button, event.jbutton.state);
                break;

            case SDL_QUIT:
                sgWindowClose();
                return;

            default:
                break;
        }
    }
    _sgMouseUpdate();
    _sgKeyboardUpdate();
    _sgJoystickUpdate();
}
void SG_CALL sgWindowSwapBuffers(void)
{
    SGlong origin = sgGetTime();

    SDL_GL_SwapBuffers();

    SGlong time = sgGetTime();
    SGlong updateLength = time - origin;

    if(_sg_FPS > 0.0f)
    {
        if(updateLength < _sg_FrameLength)
        {
            sgNSleep(_sg_FrameLength - updateLength);
        }
    }

    SGlong frameLength = updateLength + (sgGetTime() - time);
    _sg_achievedFramerate = (SGfloat) SG_NANOSECONDS_IN_A_SECOND / frameLength;
}
SGfloat SG_CALL sgWindowGetFPSLimit(void)
{
    return _sg_FPS;
}
void SG_CALL sgWindowSetFPSLimit(SGfloat limit)
{
    _sg_FPS = limit;
    _sg_FrameLength = (1 / _sg_FPS) * SG_NANOSECONDS_IN_A_SECOND;
}
SGfloat SG_CALL sgWindowGetFPS(void)
{
    return _sg_achievedFramerate;
}
