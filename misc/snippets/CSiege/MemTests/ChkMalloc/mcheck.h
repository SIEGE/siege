#ifndef __MCHECK_H__
#define __MCHECK_H__

#include <stdlib.h>
#include <string.h>

#ifndef bool
#define bool char
#endif // bool
#ifndef FALSE
#define FALSE 0
#endif // FALSE
#ifndef TRUE
#define TRUE 1
#endif // TRUE

#define PRINT   \
    printf("%s %d %s\n", __FILE__, __LINE__, __FUNCTION__);

#ifndef CHK_NOMALLOC
#ifdef CHK_SIMPLE
#define malloc(size) chkMalloc((size))
#define realloc(ptr, size) chkRealloc((ptr), (size))
#define calloc(num, size) chkCalloc((num), (size))
#else
#define malloc(size) chkMallocL((size), __FILE__, __FUNCTION__, __LINE__)
#define realloc(ptr, size) chkReallocL((ptr), (size), __FILE__, __FUNCTION__, __LINE__)
#define calloc(num, size) chkCallocL((num), (size), __FILE__, __FUNCTION__, __LINE__)
#endif // CHK_SIMPLE
#endif // CHK_NOMALLOC

typedef struct chkMemory
{
    char* file;
    char* func;
    size_t line;

    size_t bsize;
    size_t size;
    void* ptr;

    struct chkMemory* prev;
    struct chkMemory* next;
} chkMemory;

bool chkTestBoundsM(chkMemory* mem);
bool chkTestBoundsP(void* ptr);

void chkRemoveM(chkMemory* mem);
void chkRemoveP(void* ptr);
chkMemory* chkFindP(void* ptr);

void* chkMalloc(size_t size);
void* chkRealloc(void* ptr, size_t size);
void* chkCalloc(size_t num, size_t size);

void* chkMallocL(size_t size, const char* file, const char* func, size_t line);
void* chkReallocL(void* ptr, size_t size, const char* file, const char* func, size_t line);
void* chkCallocL(size_t num, size_t size, const char* file, const char* func, size_t line);
void chkLocation(const char* file, const char* func, size_t line);

void chkFree(void* ptr);

void chkStart(size_t tsize);
void** chkBounds(size_t* number);
void** chkEnd(size_t* number);

chkMemory* chkBoundsM(size_t* number);
chkMemory* chkEndM(size_t* number);

#endif // __MCHECK_H__
