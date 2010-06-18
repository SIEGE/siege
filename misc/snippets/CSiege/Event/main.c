#include <stdio.h>
#include <stdlib.h>

#include "event.h"

typedef struct SGEventTest
{
    int x;
    int y;
} SGEventTest;

SGbool SG_EXPORT evTest(void* data, SGEventTest* args)
{
    printf("evTest %p %d,%d\n", data, args->x, args->y);
    return SG_TRUE;
}

int main()
{
    sgEventInit();
    sgEventAdd(3.0, "evTest", (void*)1, (SGEventCall)evTest);
    sgEventAdd(2.5, "evTest", (void*)2, (SGEventCall)evTest);
    sgEventAdd(2.5, "evTest", (void*)3, (SGEventCall)evTest);
    sgEventAdd(1.0, "evTest", (void*)4, (SGEventCall)evTest);
    sgEventAdd(3.0, "evTest", (void*)5, (SGEventCall)evTest);

    sgEventCall("evTest", &(SGEventTest){1, 2});

    sgEventDeinit();

    return 0;
}
