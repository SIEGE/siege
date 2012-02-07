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
#include <siege/util/link.h>
#include <siege/modules/modules.h>
#include <siege/modules/window.h>

void SG_EXPORT _sgModuleLoadWindow(SGLibrary* lib)
{
    void* fptr;

    /// Windowing
    _SG_BIND(sgmCoreWindowCreate);
    _SG_BIND(sgmCoreWindowDestroy);
    _SG_BIND(sgmCoreWindowOpen);
    _SG_BIND(sgmCoreWindowIsOpened);
    _SG_BIND(sgmCoreWindowClose);
    //_SG_BIND(sgmCoreWindowIsClosed);
    _SG_BIND(sgmCoreWindowSetIcon);
    _SG_BIND(sgmCoreWindowSetTitle);
    //_SG_BIND(sgmCoreWindowGetTitle);
    //_SG_BIND(sgmCoreWindowFreeTitle);
    _SG_BIND(sgmCoreWindowSetSize);
    _SG_BIND(sgmCoreWindowGetSize);
    //_SG_BIND(sgmCoreWindowPollEvents);
    _SG_BIND(sgmCoreWindowSwapBuffers);

    _SG_BIND(sgmCoreWindowSetCallbacks);
    //_SG_BIND(sgmCoreWindowGetCallbacks);
}
