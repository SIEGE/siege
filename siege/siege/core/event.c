#define SG_BUILD_LIBRARY
#include <siege/core/event.h>
#include <siege/core/entity.h>

#include <stdlib.h>
#include <string.h>

SGbool SG_EXPORT _sgEventInit(void)
{
    _sg_evList = sgPLinkedListCreate(SG_PLIST_HFO);
    if(_sg_evList != NULL)
        return SG_TRUE;
    return SG_FALSE;
}
SGbool SG_EXPORT _sgEventDeinit(void)
{
    //SGPLinkedNode* node;
    //for(node = _sg_evList->first; node != NULL; node = node->next)
    //    free(node);
    sgLinkedListDestroy(_sg_evList);
    return SG_TRUE;
}
SGEvent* SG_EXPORT sgEventCreate(float priority, SGenum type, void* data, SGEventCall func)
{
    SGEvent* event = malloc(sizeof(SGEvent));
    event->priority = priority;
    event->type = type;
    event->data = data;
    event->func = func;
    sgPLinkedListInsertPriority(_sg_evList, priority, event);
    return event;
}
void SG_EXPORT sgEventDestroy(SGEvent* event)
{
    sgLinkedListRemoveItem(_sg_evList, event);
}
void SG_EXPORT sgEventCall(SGenum type, void* args)
{
    _sg_evStop = SG_FALSE;
    SGbool cont = SG_TRUE;
    SGEvent* event;
    SGPLinkedNode* node;
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
