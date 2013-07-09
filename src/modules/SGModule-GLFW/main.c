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
    if(!glfwInit())
        return SG_UNKNOWN_ERROR;
    glfwEnable(GLFW_KEY_REPEAT);
    glfwDisable(GLFW_AUTO_POLL_EVENTS);
    return SG_OK;
}
SGenum SG_CALL sgmCoreDeinit(void)
{
    glfwTerminate();
    return SG_OK;
}
