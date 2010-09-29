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

#ifndef __MAIN_H__
#define __MAIN_H__

#include <siege/siege.h>

#include <vlc/vlc.h>

libvlc_instance_t* vlcInstance;
libvlc_exception_t vlcEx;

int exRaised(libvlc_exception_t* ex);

#endif // __MAIN_H__
