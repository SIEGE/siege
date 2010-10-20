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
#include <siege/core/event.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

SGbool SG_EXPORT _sgEventInit(void)
{
    _sg_evList = sgPListCreate(SG_PLIST_HFO);
    if(_sg_evList != NULL)
        return SG_TRUE;
    return SG_FALSE;
}
SGbool SG_EXPORT _sgEventDeinit(void)
{
    //SGPListNode* node;
    //for(node = _sg_evList->first; node != NULL; node = node->next)
    //    free(node);
    sgListDestroy(_sg_evList);
    return SG_TRUE;
}
SGEvent* SG_EXPORT sgEventCreate(float priority, SGenum type, void* data, SGEventCall func)
{
    SGEvent* event = malloc(sizeof(SGEvent));
    event->priority = priority;
    event->type = type;
    event->data = data;
    event->func = func;
    sgPListInsertPriority(_sg_evList, priority, event);
    return event;
}
void SG_EXPORT sgEventDestroy(SGEvent* event)
{
    sgListRemoveItem(_sg_evList, event);
}
void SG_EXPORT sgEventCall(SGenum type, void* args)
{
    _sg_evStop = SG_FALSE;
    SGbool cont = SG_TRUE;
    SGEvent* event;
    SGPListNode* node;
    for(node = _sg_evList->first; (node != NULL) && cont; node = node->next)
    {
        if(_sg_evStop)
            break;
        event = node->item;
        if(type == event->type)
            cont = event->func(event->data, args);
    }
}
void SG_EXPORT sgEventStop(void)
{
    _sg_evStop = SG_TRUE;
}
