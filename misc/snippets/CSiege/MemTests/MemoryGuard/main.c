#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int gmemadd(void* ptr, size_t size)
{
    GStackEntry* stack = &gstack[gstacklen - 1];

    memcpy(ptr - gset_guard, gset_guard_start, gset_guard);
    memcpy(ptr + size      , gset_guard_end  , gset_guard);
    stack->mem = realloc(stack->mem, (++stack->memlen) * sizeof(GMemory));
    stack->mem->ptr = ptr;
    stack->mem->size = size;
    if(stack->mem == NULL)
        goto norealloc;

    return 1;

norealloc:
    return 0;
}
int gmemset(void* old, void* ptr, size_t size)
{
    GStackEntry* stack = &gstack[gstacklen - 1];

    // TODO: check memory
    return 1;
}
int gmemrem(void* ptr)
{
    GStackEntry* stack = &gstack[gstacklen - 1];

    return 1;
}

int gtrace()
{
    gstacklen = 0;
    gstack = NULL;
    genter("");
    return 1;
}
int guntrace()
{
    int ret = 1;
    ret &= gexit();
    size_t i;
    for(i = 0; i < gstacklen; i++)
    {
        //gstack[gstacklen]
    }
    free(gstack);
    return 0;
}

int genter(char* name)
{
    gset(G_GUARD, G_GUARD_DEFAULT);
    gset(G_WARN, G_WARN_DEFAULT);
    gset(G_FREE, G_FREE_DEFAULT);

    gstack = realloc(gstack, (++gstacklen) * sizeof(GStackEntry));
    if(gstack == NULL)
        return 0;
    gstack[gstacklen - 1].name = name;
    gstack[gstacklen - 1].memlen = 0;
    gstack[gstacklen - 1].mem = NULL;
    return 1;
}
int gexit()
{
    gstack = realloc(gstack, (--gstacklen) * sizeof(GStackEntry));
    if(gstack == NULL)
        return 0;
    // TODO: check memory
    return 1;
}

void gset(int what, int value)
{
    switch(what)
    {
        case G_GUARD:
            gset_guard = value;
            if(gset_guard_start != NULL)
                free(gset_guard_start);
            if(gset_guard_end != NULL)
                free(gset_guard_end);
            gset_guard_start = malloc(value);
            gset_guard_end = malloc(value);
            int i;
            for(i = 0; i < value; i++)
            {
                ((char*)gset_guard_start)[i] = rand();
                ((char*)gset_guard_end)[i] = rand();
            }
            break;
        case G_WARN:
            gset_warn = value;
            break;
        case G_FREE:
            gset_free = value;
            break;
        default:
            break;
    }
}
int gget(int what)
{
    switch(what)
    {
        case G_GUARD:
            return gset_guard;
        case G_WARN:
            return gset_warn;
        case G_FREE:
            return gset_free;
        default:
            return -1;
    }
}
int gcheck(void* ptr)
{
    return 1;
}
void* gmalloc(size_t size)
{
    void* ptr = malloc(size + gset_guard * 2);
    if(ptr == NULL)
        return NULL;

    int set = gmemadd(ptr + gset_guard, size);
    if(!set)
    {
        free(ptr);
        return NULL;
    }
    return ptr + gset_guard;
}
void* gcalloc(size_t num, size_t size)
{
    void* ptr = malloc(num * size + gset_guard * 2);
    memset(ptr + gset_guard, 0, num * size);
    if(ptr == NULL)
        return NULL;

    int set = gmemadd(ptr + gset_guard, num * size);
    if(!set)
    {
        free(ptr);
        return NULL;
    }
    return ptr + gset_guard;
}
void* grealloc(void* old, size_t size)
{
    void* ptr = realloc(old - gset_guard, size + gset_guard * 2);
    if(ptr == NULL)
        return NULL;

    int set = gmemset(old + gset_guard, ptr + gset_guard, size);
    if(!set)
    {
        free(ptr);
        return NULL;
    }
    return ptr + gset_guard;
}
void gfree(void* ptr)
{
    free(ptr);

    int set = gmemrem(ptr);
    if(!set)
    {
        // free failed for gmemrem
    }
}

int main()
{
    gtrace();

    void* p = gmalloc(5);
    printf("%p\n", p);

    gfree(p);

    guntrace();
    return 0;
}
