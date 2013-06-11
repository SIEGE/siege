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

#include "common.h"
#include "window.h"
#include "joystick.h"
#include "keyboard.h"
#include "mouse.h"

#include <stdlib.h>

static SDL_Surface* windowIcon;

void windowOpen()
{
    if(main_window->cbWindow->open != NULL)
        main_window->cbWindow->open(main_window);
}
int windowClose()
{
    if(main_window->cbWindow->close != NULL)
        main_window->cbWindow->close(main_window);

    return 1;
}
void windowResize(int x, int y)
{
    if(main_window->cbWindow->resize != NULL)
        main_window->cbWindow->resize(main_window, x, y);
}

SGenum SG_CALL sgmCoreWindowCreate(void** window)
{
    *window = calloc(1, sizeof(Window));
    Window** cwindow = (Window**)window;
    (*cwindow)->cbWindow = calloc(1, sizeof(SGCoreWindowCallbacks));
    (*cwindow)->cbJoystick = calloc(1, sizeof(SGCoreJoystickCallbacks));
    (*cwindow)->cbKeyboard = calloc(1, sizeof(SGCoreKeyboardCallbacks));
    (*cwindow)->cbMouse = calloc(1, sizeof(SGCoreMouseCallbacks));

    main_window = *window;

    windowIcon = NULL;

    return SG_OK;
}

SGenum SG_CALL sgmCoreWindowDestroy(void* window)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Window* cwindow = (Window*)window;

    sgmCoreWindowClose(window);
    free(cwindow->cbWindow);
    free(cwindow->cbJoystick);
    free(cwindow->cbKeyboard);
    free(cwindow->cbMouse);
    free(cwindow);

    SDL_FreeSurface(windowIcon);
    windowIcon = NULL;

    return SG_OK;
}
SGenum SG_CALL sgmCoreWindowOpen(void* window, SGuint width, SGuint height, SGubyte bpp, SGenum flags)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Window* cwindow = window;

    Uint32 sdlflags = 0;
    if(useGL)
        sdlflags |= SDL_OPENGL;
    else
        sdlflags |= SDL_HWSURFACE;
    if(flags & SG_WINDOW_FULLSCREEN)
        sdlflags |= SDL_FULLSCREEN;
    if(flags & SG_WINDOW_RESIZABLE)
        sdlflags |= SDL_RESIZABLE;

    cwindow->surface = SDL_SetVideoMode(width, height, bpp, sdlflags);
    cwindow->opened = SG_TRUE;

    windowOpen();
    windowResize(width, height);

    return SG_OK;
}
SGenum SG_CALL sgmCoreWindowIsOpened(void* window, SGbool* opened)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Window* cwindow = window;

    *opened = cwindow->opened;
    return SG_OK;
}
SGenum SG_CALL sgmCoreWindowClose(void* window)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Window* cwindow = window;

    cwindow->opened = SG_FALSE;
    windowClose();

    return SG_OK;
}
//SGenum SG_CALL sgmCoreWindowIsClosed(void* window, SGbool* closed);
SGenum SG_CALL sgmCoreWindowSetIcon(void* window, size_t width, size_t height, SGenum bpp, void* data)
{
    if(!window) return SG_OK; // SG_INVALID_VALUE

    if(windowIcon)
        SDL_FreeSurface(windowIcon);

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
    switch(bpp)
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
            return SG_INVALID_VALUE;
    }

    windowIcon = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, width, height, bpp, rmask, gmask, bmask, amask);
    SDL_LockSurface(windowIcon);
    size_t i;
    for(i = 0; i < height; i++)
        memcpy(&((char*)windowIcon->pixels)[i * windowIcon->pitch], ((char*)data) + bypp * width * i, bypp * width);
    SDL_UnlockSurface(windowIcon);
    SDL_WM_SetIcon(windowIcon, NULL);

    return SG_OK;
}
SGenum SG_CALL sgmCoreWindowSetTitle(void* window, const char* title) /// TODO: icon title + icon
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    SDL_WM_SetCaption(title, title);

    return SG_OK;
}
//SGenum SG_CALL sgmCoreWindowGetTitle(void* window, char** title);
//SGenum SG_CALL sgmCoreWindowFreeTitle(char* title);
SGenum SG_CALL sgmCoreWindowSetSize(void* window, SGuint width, SGuint height)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Window* cwindow = window;

    cwindow->surface = SDL_SetVideoMode(width, height, cwindow->surface->format->BitsPerPixel, cwindow->surface->flags);
    windowResize(width, height);

    return SG_OK;
}
SGenum SG_CALL sgmCoreWindowGetSize(void* window, SGuint* width, SGuint* height)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Window* cwindow = window;

    *width = cwindow->surface->w;
    *height = cwindow->surface->h;

    return SG_OK;
}
//SGenum SG_CALL sgmCoreWindowPollEvents(void* window);
SGenum SG_CALL sgmCoreWindowSwapBuffers(void* window)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE
    Window* cwindow = window;

    /*SGbool opened;
    sgmCoreWindowIsOpened(window, &opened);*/
    if(!cwindow->opened)
        return SG_OK;

    Joystick* joy;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
			// commented out to fix a bug with the mouse!
            /*case SDL_ACTIVEEVENT:
                //SDL_PollEvent(&event); // next one is SDL_KEYUP
                break;*/
            case SDL_VIDEORESIZE:
                sgmCoreWindowSetSize(window, event.resize.w, event.resize.h);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                keyboardKey(event.key.keysym.sym, event.key.state == SDL_PRESSED);
                if(event.key.state == SDL_PRESSED && event.key.keysym.unicode != 0)
                    keyboardChar(event.key.keysym.unicode);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                if(event.button.button == SDL_BUTTON_WHEELUP)
                {
                    if(event.button.state == SDL_PRESSED)
                    {
                        mouseW++;
                        mouseWheel(mouseW);
                    }
                }
                else if(event.button.button == SDL_BUTTON_WHEELDOWN)
                {
                    if(event.button.state == SDL_PRESSED)
                    {
                        mouseW--;
                        mouseWheel(mouseW);
                    }
                }
                else
                    mouseButton(event.button.button, event.button.state == SDL_PRESSED);
                break;

            case SDL_MOUSEMOTION:
                mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                mouseMove(event.motion.x, event.motion.y);
                break;

            case SDL_JOYAXISMOTION:
                joy = &joylist[event.jaxis.which];
                if(!joy->ref) // if we've just destroyed the joystick
                    break;
                joy->axis[event.jaxis.axis] = (event.jaxis.value + 0.5) / 32767.5;
                if(main_window->cbJoystick->move)
                    main_window->cbJoystick->move(joy, joy->axis);
                break;
            case SDL_JOYBALLMOTION:
            case SDL_JOYHATMOTION: /// \todo TODO
                break;
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                joy = &joylist[event.jbutton.which];
                if(!joy->ref) // if we've just destroyed the joystick
                    break;
                if(main_window->cbJoystick->button)
                    main_window->cbJoystick->button(joy, event.jbutton.button, event.jbutton.state);
                break;

            case SDL_QUIT:
                sgmCoreWindowClose(window);
                return SG_OK;

            default:
                break;
        }
    }

    if(useGL)
        SDL_GL_SwapBuffers();
    else
        SDL_Flip(cwindow->surface);

    return SG_OK;
}

SGenum SG_CALL sgmCoreWindowSetCallbacks(void* window, SGCoreWindowCallbacks* callbacks)
{
    if(window == NULL)
        return SG_OK; // SG_INVALID_VALUE

    Window* cwindow = (Window*)window;
    if(!callbacks)
        cwindow->cbWindow = NULL;
    else
        memcpy(cwindow->cbWindow, callbacks, sizeof(SGCoreWindowCallbacks));

    return SG_OK;
}
//SGenum SG_CALL sgmCoreWindowGetCallbacks(void* window, SGCoreWindowCallbacks** callbacks);
