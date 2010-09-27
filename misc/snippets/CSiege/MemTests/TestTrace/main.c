#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int _tlist_checkmem(TMemory* item)
{
    int cmp1 = memcmp(item->ptr - _tguard, _tguard_begincmp, _tguard);
    int cmp2 = memcmp(item->ptr + item->size, _tguard_endcmp, _tguard);

    if(cmp1 != 0)
    {
        if(_twarn)
            printf("TMEM: Out of bounds error at %p-%X\n", item->ptr, (cmp1 > 0) ? cmp1 : -cmp1);
        return 0;
    }
    if(cmp2 != 0)
    {
        if(_twarn)
            printf("TMEM: Out of bounds error at %p+%X\n", item->ptr, (cmp2 > 0) ? cmp2 : -cmp2);
        return 0;
    }
    return 1;
}

size_t _tlist_nelem(void)
{
    TMemory* current;
    size_t i = 0;
    for(current = _tlist; current != NULL; current = current->next)
        i++;
    return i;
}
int _tlist_add(size_t size, void* ptr)
{
    TMemory* item = malloc(sizeof(TMemory));
    if(item == NULL)
        return 0;
    item->size = size;
    item->ptr = ptr;

    item->prev = NULL;
    item->next = _tlist;
    if(_tlist != NULL)
        _tlist->prev = item;
    _tlist = item;

    return 1;
}
TMemory* _tlist_findmem(TMemory* memory)
{
    TMemory* current;
    for(current = _tlist; current != NULL; current = current->next)
        if(current == memory)
            return current;
    return NULL;
}
TMemory* _tlist_findptr(void* ptr)
{
    TMemory* current;
    for(current = _tlist; current != NULL; current = current->next)
        if(current->ptr == ptr)
            return current;
    return NULL;
}
int _tlist_remmem(TMemory* memory)
{
    TMemory* item = _tlist_findmem(memory);
    if(item == NULL)
        return 0;

    if((item->prev == NULL) && (item->next == NULL))
        _tlist = NULL;

    if(item->prev != NULL)
        item->prev->next = item->next;
    else
        _tlist = item->next;
    if(item->next != NULL)
        item->next->prev = item->prev;
    free(item);
    return 1;
}
int _tlist_remptr(void* ptr)
{
    TMemory* item = _tlist_findptr(ptr);
    if(item == NULL)
        return 0;

    if((item->prev == NULL) && (item->next == NULL))
        _tlist = NULL;

    if(item->prev != NULL)
        item->prev->next = item->next;
    else
        _tlist = item->next;
    if(item->next != NULL)
        item->next->prev = item->prev;
    free(item);
    return 1;
}
int _tlist_each(int (*func)(TMemory* item, void* data), void* data)
{
    TMemory* current;
    int ret;
    for(current = _tlist; current != NULL; current = current->next)
    {
        ret = func(current, data);
        if(ret != 0)
            break;
    }
    return ret;
}

void tbegin(int warn, int guard)
{
    _tguard_begincmp = malloc(guard);
    memset(_tguard_begincmp, 0xDE, guard);
    _tguard_endcmp = malloc(guard);
    memset(_tguard_endcmp, 0xAD, guard);

    _tguard = guard;
    _twarn = warn;
    _tlist = NULL;
}
void tend(int autofree)
{
    TMemory* current;
    TMemory* next;
    for(current = _tlist; current != NULL;)
    {
        if(_twarn)
        {
            printf("TMEM: Memory not freed: %p (size %d)\n", current->ptr, current->size);
            _tlist_checkmem(current);
        }
        if(autofree)
            free(current->ptr);
        next = current->next;
        free(current);
        current = next;
    }
    _tlist = NULL;
}

void* tmalloc(size_t size)
{
    void* ptr = malloc(size + _tguard * 2);
    if(ptr != NULL)
    {
        memset(ptr, 0xDE, _tguard);
        //memset(ptr + _tguard, 0, size);
        memset(ptr + _tguard + size, 0xAD, _tguard);
        _tlist_add(size, ptr + _tguard);
    }
    else if(_twarn)
        printf("TMEM: Cannot allocate memory of size %d\n", size);
    return ptr + _tguard;
}
void* tcalloc(size_t num, size_t size)
{
    void* ptr = malloc(num * size + _tguard * 2);//calloc(num, size);
    if(ptr != NULL)
    {
        memset(ptr, 0xDE, _tguard);
        memset(ptr + _tguard, 0, num * size);
        memset(ptr + _tguard + num * size, 0xAD, _tguard);
        _tlist_add(num * size, ptr + _tguard);
    }
    else if(_twarn)
        printf("TMEM: Cannot allocate memory of size %dx%d\n", num, size);
    return ptr + _tguard;
}
void* trealloc(void* ptr, size_t size)
{
    TMemory* prevmem = _tlist_findptr(ptr);
    if(prevmem == NULL)
    {
        if(_twarn)
            printf("TMEM: Cannot resize %p to %d - invalid address\n", ptr, size);
        return NULL;
    }

    _tlist_checkmem(prevmem);

    ptr = realloc(ptr - _tguard, size + _tguard * 2);
    if(ptr != NULL)
    {
        memset(ptr, 0xDE, _tguard);
        //memset(ptr + _tguard, 0, size);
        memset(ptr + _tguard + size, 0xAD, _tguard);
        prevmem->size = size;
        prevmem->ptr = ptr + _tguard;
    }
    else if(_twarn)
        printf("TMEM: Cannot resize %p from %d to %d\n", ptr, prevmem->size, size);
    return ptr + _tguard;
}
void tfree(void* ptr)
{
    TMemory* item = _tlist_findptr(ptr);
    if(item == NULL)
    {
        if(_twarn)
            printf("TMEM: Cannot free %p - invalid address\n", ptr);
        return;
    }

    _tlist_checkmem(item);

    free(ptr - _tguard);

    _tlist_remptr(ptr);
}
void** tlist(void)
{
    int nelem = _tlist_nelem();
    void** list = calloc(nelem, sizeof(TMemory));

    TMemory* current;
    int i = 0;
    for(current = _tlist; current != NULL; current = current->next)
        list[i++] = current->ptr;
    return list;
}

int main()
{
    tbegin(1, 10);

    int* ptr1 = tmalloc(sizeof(int));
    int* ptr2 = tcalloc(1, sizeof(int));
    int* ptr3 = trealloc(ptr1, sizeof(int) * 2);

    ptr2[1] = 5;

    void** ptrs;
    int i;

    printf("%p\n%p\n%p\n", ptr1, ptr2, ptr3);
    printf("----------\n");
    ptrs = tlist();
    for(i = 0; ptrs[i] != NULL; i++)
        printf("%p\n", ptrs[i]);
    printf("----------\n");
    //tfree((void*)0xDEADBEEF);
    //tfree(ptr1);
    tfree(ptr2);
    tfree(ptr3);
    printf("----------\n");
    ptrs = tlist();
    for(i = 0; ptrs[i] != NULL; i++)
        printf("%p\n", ptrs[i]);

    tend(1);

    return 0;
}
