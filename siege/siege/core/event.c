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
    size_t i;
    for(i = 0; i < _sg_evList->numitems; i++)
        free(_sg_evList->items[i]);
    sgPListDestroy(_sg_evList);
    return SG_TRUE;
}
SGEvent* SG_EXPORT sgEventCreate(float priority, SGenum type, void* data, SGEventCall func)
{
    SGEvent* event = malloc(sizeof(SGEvent));
    event->priority = priority;
    event->type = type;
    event->data = data;
    event->func = func;
    sgPListAdd(_sg_evList, priority, event);
    return event;
}
void SG_EXPORT sgEventDestroy(SGEvent* event)
{
    sgPListRemoveItem(_sg_evList, event);
}
void SG_EXPORT sgEventCall(SGenum type, void* args)
{
    _sg_evStop = SG_FALSE;
    SGbool cont = SG_TRUE;
    SGEvent* event;
    size_t i;
    for(i = 0; (i < _sg_evList->numitems) && cont; i++)
    {
        if(_sg_evStop)
            break;
        event = (SGEvent*)((SGPItem*)_sg_evList->items[i])->item;
        if(type == event->type)
            cont = event->func(event->data, args);
    }
}
void SG_EXPORT sgEventStop(void)
{
    _sg_evStop = SG_TRUE;
}
