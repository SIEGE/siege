#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdlib.h>
#include <stdint.h>

#define G_GUARD_DEFAULT 0x04
#define G_WARN_DEFAULT  0xFF
#define G_FREE_DEFAULT  1

#define G_GUARD 0x01
#define G_WARN  0x02
#define G_FREE  0x03

typedef struct GMemory
{
    size_t size;
    void* ptr;
} GMemory;

typedef struct GStackEntry
{
    char* name;
    size_t memlen;
    GMemory* mem;
} GStackEntry;

size_t gstacklen;
GStackEntry* gstack;
void (*gcb_log)(GStackEntry* stack) = NULL;
int gset_guard = G_GUARD_DEFAULT;
void* gset_guard_start = NULL;
void* gset_guard_end = NULL;
int gset_warn = G_WARN_DEFAULT;
int gset_free = G_FREE_DEFAULT;
int gmemadd(void* ptr, size_t size);
int gmemset(void* ptr, void* to, size_t size);
int gmemrem(void* ptr);

int gtrace();
int guntrace();

int genter(char* name);
int gexit();

void gset(int what, int value);
int gget(int what);
int gcheck(void* ptr);
void* gmalloc(size_t size);
void* gcalloc(size_t num, size_t size);
void* grealloc(void* ptr, size_t size);
void gfree(void* ptr);

#endif
