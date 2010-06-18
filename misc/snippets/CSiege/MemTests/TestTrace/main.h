#ifndef __MAIN_H__
#define __MAIN_H__

#ifndef T_DL
#define T_DL 0
#endif // T_DL

typedef struct TMemory
{
    size_t size;
    void* ptr;

    struct TMemory* prev;
    struct TMemory* next;
} TMemory;

TMemory* _tlist;
void* _tguard_begincmp;
void* _tguard_endcmp;
int _tguard;
int _twarn;

int _tlist_checkmem(TMemory* item);
size_t _tlist_nelem(void);
int _tlist_add(size_t len, void* ptr);
TMemory* _tlist_findmem(TMemory* memory);
TMemory* _tlist_findptr(void* ptr);
int _tlist_remmem(TMemory* memory);
int _tlist_remptr(void* ptr);
int _tlist_each(int (*func)(TMemory* item, void* data), void* data);

void tbegin();
void tend();

void* tmalloc(size_t size);
void* tcalloc(size_t num, size_t size);
void* trealloc(void* ptr, size_t size);
void tfree(void* ptr);

#endif // __MAIN_H__
