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

SGenum SG_CALL sgmCoreInit(void)
{
    useGL = SG_TRUE;

    if(SDL_Init(SDL_INIT_EVERYTHING))
        return SG_UNKNOWN_ERROR;
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return SG_OK;
}
SGenum SG_CALL sgmCoreDeinit(void)
{
    SDL_Quit();

    return SG_OK;
}
