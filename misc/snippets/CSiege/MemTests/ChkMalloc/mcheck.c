#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHK_NOMALLOC
#include "mcheck.h"
#undef CHK_NOMALLOC

char* chkFile = NULL;
char* chkFunc = NULL;
size_t chkLine = 0;

chkMemory* chkRoot = NULL;
size_t chkUnfreedNum = 0;
void** chkUnfreedArr = NULL;
size_t chkBoundsNum = 0;
void** chkBoundsArr = NULL;
size_t chkBoundsSize = 4;

chkMemory* chkUnfreedArrM = NULL;
chkMemory* chkBoundsArrM = NULL;

bool chkTestBoundsM(chkMemory* mem)
{
    if(mem == NULL)
        return FALSE;
    void* ptr = mem->ptr + mem->bsize;

    void* temp = malloc(mem->bsize);
    memset(temp, 'B', mem->bsize);
    bool cmp = (memcmp(temp, ptr - mem->bsize, mem->bsize) == 0)
            && (memcmp(temp, ptr + mem-> size, mem->bsize) == 0);

    return cmp;
}

bool chkTestBoundsP(void* ptr)
{
    return chkTestBoundsM(chkFindP(ptr));
}

void chkRemoveM(chkMemory* mem)
{
    if(mem == NULL)
        return;
    if(mem->next != NULL)
        mem->next->prev = mem->prev;
    if(mem->prev != NULL)
        mem->prev->next = mem->next;
    else // root
        chkRoot = mem->next;
    free(mem->ptr);
    free(mem);
}

void chkRemoveP(void* ptr)
{
    chkRemoveM(chkFindP(ptr));
}

chkMemory* chkFindP(void* ptr)
{
    chkMemory* mem = chkRoot;
    while(mem != NULL)
    {
        if(mem->ptr + mem->bsize == ptr)
            return mem;
        mem = mem->next;
    }
    return NULL;
}

void* chkMalloc(size_t size)
{
    chkMemory* mem = malloc(sizeof(chkMemory));
    if(mem == NULL)
        return NULL;
    mem->file = chkFile;
    mem->func = chkFunc;
    mem->line = chkLine;

    mem->bsize = chkBoundsSize;
    mem->size = size;
    mem->ptr = malloc(mem->size + 2*mem->bsize);
    if(mem->ptr == NULL)
    {
        free(mem);
        return NULL;
    }
    memset(mem->ptr, 'B', mem->bsize);
    memset(mem->ptr + mem->bsize + mem->size, 'B', mem->bsize);

    mem->prev = NULL;
    mem->next = chkRoot;
    chkRoot = mem;

    return mem->ptr + mem->bsize;
}

void* chkRealloc(void* ptr, size_t size)
{
    if(ptr == NULL)
        return chkMalloc(size);

    chkMemory* mem = chkFindP(ptr);
    if(mem == NULL)
        return NULL;

    /*mem->name = chkName;
    mem->bsize = bsize;*/
    mem->size = size;
    mem->ptr = realloc(ptr - mem->bsize, mem->size + 2*mem->bsize);
    if(mem->ptr == NULL)
    {
        chkRemoveM(mem);
        free(mem);
        return NULL;
    }
    memset(mem->ptr, 'B', mem->bsize);
    memset(mem->ptr + mem->bsize + mem->size, 'B', mem->bsize);
    chkRoot = mem;

    return mem->ptr + mem->bsize;
}

void* chkCalloc(size_t num, size_t size)
{
    void* ptr = chkMalloc(num * size);
    if(ptr == NULL)
        return NULL;
    memset(ptr, 0, size);
    return ptr;
}

void* chkMallocL(size_t size, const char* file, const char* func, size_t line)
{
    chkLocation(file, func, line);
    return chkMalloc(size);
}
void* chkReallocL(void* ptr, size_t size, const char* file, const char* func, size_t line)
{
    chkLocation(file, func, line);
    return chkRealloc(ptr, size);
}
void* chkCallocL(size_t num, size_t size, const char* file, const char* func, size_t line)
{
    chkLocation(file, func, line);
    return chkCalloc(num, size);
}

void chkLocation(const char* file, const char* func, size_t line)
{
    chkFile = (char*)file;
    chkFunc = (char*)func;
    chkLine = line;
}

void chkFree(void* ptr)
{
    chkRemoveP(ptr);
}

void chkStart(size_t bsize)
{
    chkRoot = NULL;
    free(chkUnfreedArr);
    chkUnfreedArr = NULL;
    chkUnfreedNum = 0;
    free(chkBoundsArr);
    chkBoundsArr = NULL;
    chkBoundsNum = 0;

    free(chkUnfreedArrM);
    chkUnfreedArrM = NULL;
    free(chkBoundsArrM);
    chkBoundsArrM = NULL;
}
void** chkBounds(size_t* number)
{
    chkMemory* mem = chkRoot;

    chkBoundsArr = realloc(chkBoundsArr, sizeof(void*));
    while(mem != NULL)
    {
        if(!chkTestBoundsM(mem))
        {
            chkBoundsArr = realloc(chkBoundsArr, (chkBoundsNum + 2) * sizeof(void*));
            chkBoundsArr[chkBoundsNum++] = mem->ptr + mem->bsize;
        }
        mem = mem->next;
    }
    chkBoundsArr[chkBoundsNum] = NULL;

    if(number != NULL)
        *number = chkBoundsNum;
    return chkBoundsArr;

}
void** chkEnd(size_t* number)
{
    chkMemory* mem = chkRoot;

    chkUnfreedArr = realloc(chkUnfreedArr, sizeof(void*));
    while(mem != NULL)
    {
        chkUnfreedArr = realloc(chkUnfreedArr, (chkUnfreedNum + 2) * sizeof(void*));
        chkUnfreedArr[chkUnfreedNum++] = mem->ptr + mem->bsize;
        mem = mem->next;
    }
    chkUnfreedArr[chkUnfreedNum] = NULL;

    if(number != NULL)
        *number = chkUnfreedNum;

    size_t i;
    for(i = 0; i < chkUnfreedNum; i++)
        chkRemoveP(chkUnfreedArr[i]);

    return chkUnfreedArr;
}

chkMemory* chkBoundsM(size_t* number)
{
    chkMemory* mem = chkRoot;

    chkBoundsArrM = realloc(chkBoundsArrM, sizeof(chkMemory));
    while(mem != NULL)
    {
        if(!chkTestBoundsM(mem))
        {
            chkBoundsArrM = realloc(chkBoundsArrM, (chkBoundsNum + 2) * sizeof(chkMemory));
            memcpy(&chkBoundsArrM[chkBoundsNum++], mem, sizeof(chkMemory));
        }
        mem = mem->next;
    }
    memset(&chkBoundsArrM[chkBoundsNum], 0, sizeof(chkMemory));

    if(number != NULL)
        *number = chkBoundsNum;
    return chkBoundsArrM;
}
chkMemory* chkEndM(size_t* number)
{
    chkMemory* mem = chkRoot;

    chkUnfreedArrM = realloc(chkUnfreedArrM, sizeof(chkMemory));
    while(mem != NULL)
    {
        chkUnfreedArrM = realloc(chkUnfreedArrM, (chkUnfreedNum + 2) * sizeof(chkMemory));
        memcpy(&chkUnfreedArrM[chkUnfreedNum++], mem, sizeof(chkMemory));
        mem = mem->next;
    }
    memset(&chkUnfreedArrM[chkUnfreedNum], 0, sizeof(chkMemory));

    if(number != NULL)
        *number = chkUnfreedNum;

    size_t i;
    for(i = 0; i < chkUnfreedNum; i++)
        chkRemoveP(chkUnfreedArrM[i].ptr);

    return chkUnfreedArrM;
}
