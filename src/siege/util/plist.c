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
#include <siege/util/plist.h>

#include <stdlib.h>
#include <string.h>

SGPList* SG_EXPORT sgPListCreate(SGenum flags)
{
    SGPList* list = sgListCreate();
    if(list == NULL)
        return NULL;

    SGenum* lflags = malloc(sizeof(SGenum));
    *lflags = flags;
    list->internal = lflags;
    list->internalFree = free;
    return list;
}

SGPListNode* SG_EXPORT sgPListInsertPriority(SGPList* list, float priority, void* item)
{
    float* lpriority = malloc(sizeof(float));
    *lpriority = priority;

    SGenum lflags = *(SGenum*)list->internal;

    SGbool op;
    float npriority;
    SGPListNode* node;
    for(node = list->first; node != NULL; node = node->next)
    {
        npriority = *(float*)node->internal;

        if(lflags & SG_PLIST_GT)
            op = npriority > priority;
        else if(lflags & SG_PLIST_GEQ)
            op = npriority >= priority;
        else if(lflags & SG_PLIST_LT)
            op = npriority < priority;
        else// if(flags & SG_PLIST_LEQ)
            op = npriority <= priority;
         // use:
         //     < to have new values with same priority go last (same priority: old value more important)
         //     > to reverse
        if(op)
        {
            node = sgListInsertNode(list, node, item);
            node->internal = lpriority;
            return node;
        }
    }

    //if(i == list->numitems) // the return handles this
    node = sgListAppend(list, item);
    node->internal = lpriority;
    return node;
}
