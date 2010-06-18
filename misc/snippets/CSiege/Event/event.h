#ifndef __EVENT_H__
#define __EVENT_H__

#include "plist.h"
#include <siege/common.h>

/**
    \param data Used-provided data
    \param args Event arguments (depends on the type of event)
    \return SG_TRUE to continue with the next event, SG_FALSE to stop
*/
typedef SGbool SG_EXPORT (*SGEventCall)(void* data, void* args);

typedef struct SGEvent
{
    char* name;
    void* data;
    SGEventCall func;
} SGEvent;
SGPList* _evList;

void sgEventInit(void);
void sgEventDeinit(void);
void sgEventAdd(float priority, char* name, void* data, SGEventCall func);
void sgEventCall(char* name, void* args);

#endif // __EVENT_H__
