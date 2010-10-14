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

#ifndef __SIEGE_UTIL_PLINKEDLIST_H__
#define __SIEGE_UTIL_PLINKEDLIST_H__

#include "../common.h"
#include "list.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// [lower/greater]-[equal/than]
#define SG_PLIST_LEQ (1<<0)
#define SG_PLIST_LT  (1<<1)
#define SG_PLIST_GEQ (1<<2)
#define SG_PLIST_GT  (1<<3)

// [high/low]-first-[new/old]
#define SG_PLIST_HFN SG_PLIST_LEQ
#define SG_PLIST_HFO SG_PLIST_LT
#define SG_PLIST_LFN SG_PLIST_GEQ
#define SG_PLIST_LFO SG_PLIST_GT

typedef struct SGListNode SGPListNode;
typedef struct SGList SGPList;

SGPList* SG_EXPORT sgPListCreate(SGenum flags);

SGPListNode* SG_EXPORT sgPListInsertPriority(SGPList* list, float priority, void* item);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_UTIL_PLINKEDLIST_H__
