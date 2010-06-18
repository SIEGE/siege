#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "plist.h"

SGbool dump(SGPList* list, void* item, void* data, size_t i, float p)
{
    printf("%.1f: %d\n", p, (int)item);
    return SG_TRUE;
}

int main()
{
    SGPList* list = sgPListCreate(SG_PLIST_HFN);

    sgPListAdd(list, 1.0, (void*)1);
    sgPListAdd(list, 2.0, (void*)2);
    sgPListAdd(list, 3.0, (void*)3);

    sgPListAdd(list, 2.5, (void*)4);
    sgPListAdd(list, 2.5, (void*)5);
    sgPListAdd(list, 2.5, (void*)6);

    sgPListEach(list, NULL, dump);

    sgPListDestroy(list);

    return 0;
}
