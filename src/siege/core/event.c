/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#define SG_BUILD_LIBRARY
#include <siege/core/event.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

SGbool SG_EXPORT _sgEventInit(void)
{
	_sg_evList = sgListCreate();
	if(_sg_evList != NULL)
		return SG_TRUE;
	return SG_FALSE;
}
SGbool SG_EXPORT _sgEventDeinit(void)
{
	sgListDestroy(_sg_evList);
	return SG_TRUE;
}
SGEvent* SG_EXPORT sgEventCreate(SGenum type, void* data, SGEventCall* func)
{
	SGEvent* event = malloc(sizeof(SGEvent));
	event->type = type;
	event->data = data;
	event->func = func;
    event->node = sgListAppend(_sg_evList, event);
	return event;
}
void SG_EXPORT sgEventDestroy(SGEvent* event)
{
    sgListRemoveNode(_sg_evList, event->node);
}
void SG_EXPORT sgEventCallv(SGenum type, va_list args)
{
	_sg_evStop = SG_FALSE;
	SGbool cont = SG_TRUE;
	SGEvent* event;
	SGListNode* node;
	SGListNode* next;
	va_list curarg;
	for(node = _sg_evList->first; (node != NULL) && cont; node = next)
	{
	    next = node->next;

		if(_sg_evStop)
			break;
		event = node->item;
		if(type == event->type)
		{
		    va_copy(curarg, args);
			cont = event->func(event->data, curarg);
			va_end(curarg);
		}
	}
}
void SG_EXPORT sgEventCall(SGenum type, ...)
{
    va_list args;
    va_start(args, type);
    sgEventCallv(type, args);
    va_end(args);
}
void SG_EXPORT sgEventStop(void)
{
	_sg_evStop = SG_TRUE;
}
