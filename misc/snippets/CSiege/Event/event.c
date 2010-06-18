#include "event.h"

#include <stdlib.h>
#include <string.h>

void sgEventInit(void)
{
    _evList = sgPListCreate(SG_PLIST_HFO);
}
void sgEventDeinit(void)
{
    size_t i;
    for(i = 0; i < _evList->numitems; i++)
        free(_evList->items[i]);
    sgPListDestroy(_evList);
}
void sgEventAdd(float priority, char* name, void* data, SGEventCall func)
{
    SGEvent* event = malloc(sizeof(SGEvent));
    event->name = name;
    event->data = data;
    event->func = func;
    sgPListAdd(_evList, priority, event);
}
void sgEventCall(char* name, void* args)
{
    SGbool cont = SG_TRUE;
    SGEvent* event;
    size_t i;
    for(i = 0; (i < _evList->numitems) && cont; i++)
    {
        event = (SGEvent*)((SGPItem*)_evList->items[i])->item;
        if(strcmp(name, event->name) == 0)
            cont = event->func(event->data, args);
    }
}
