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

#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "common.h"

void GLFWCALL mouseButton(int button, int action);
void GLFWCALL mouseMove(int x, int y);
void GLFWCALL mouseWheel(int w);

#endif // __MOUSE_H__
