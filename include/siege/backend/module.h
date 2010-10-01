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

#ifndef __SIEGE_BACKEND_MODULE_H__
#define __SIEGE_BACKEND_MODULE_H__

#include "../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmModuleInit(SGModuleInfo** minfo);
    SGuint SG_EXPORT sgmModuleExit(SGModuleInfo* minfo);
    //SGuint SG_EXPORT sgmModuleFree(void* data);

    SGuint SG_EXPORT sgmModuleMatch(SGModuleInfo** minfos, SGuint numinfos, SGbool* ok);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_MODULE_H__
