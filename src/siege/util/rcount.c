#include <siege/util/rcount.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(__FreeBSD__) /* optimize for FreeBSD */
#include <sys/param.h>
#include <sys/refcount.h>
#else /* other POSIX */
#include <pthread.h>
#include <stdlib.h>

typedef struct RCHandle
{
    SGuint val;
    pthread_spinlock_t lock;
} RCHandle;
#define RCHANDLE(cnt)   ((RCHandle*)(cnt)->handle)
#endif

SG_EXPORT SGRCount* SG_CALL sgRCountInit(SGRCount* cnt)
{
    if(!cnt) return NULL;
#ifdef _WIN32
    cnt->handle = malloc(sizeof(LONG));
    *(LONG*)cnt->handle = 1;
#elif defined(__FreeBSD__)
    cnt->handle = malloc(sizeof(u_int));
    refcount_init(cnt->handle, 1);
#else /* other POSIX */
    cnt->handle = malloc(sizeof(RCHandle));
    RCHANDLE(cnt)->val = 1;
    pthread_spin_init(&RCHANDLE(cnt)->lock, 0);
#endif
    if(!cnt->handle) return NULL;
    cnt->wasz = SG_FALSE;
    return cnt;
}
SG_EXPORT void SG_CALL sgRCountDeinit(SGRCount* cnt)
{
    if(!cnt) return;
#ifdef _WIN32
#elif defined(__FreeBSD__)
#else /* other POSIX */
    pthread_spin_destroy(&RCHANDLE(cnt)->lock);
#endif
    free(cnt->handle);
}

SG_EXPORT void SG_CALL sgRCountInc(SGRCount* cnt)
{
#ifdef _WIN32
    InterlockedIncrement(cnt->handle);
#elif defined(__FreeBSD__)
    refcount_acquire(cnt->handle);
#else /* other POSIX */
    pthread_spin_lock(&RCHANDLE(cnt)->lock);
    RCHANDLE(cnt)->val++;
    pthread_spin_unlock(&RCHANDLE(cnt)->lock);
#endif
    cnt->wasz = SG_FALSE;
}
SG_EXPORT SGbool SG_CALL sgRCountDec(SGRCount* cnt)
{
    SGbool ret;
#ifdef _WIN32
    ret = !!InterlockedDecrement(cnt->handle);
#elif defined(__FreeBSD__)
    ret = !refcount_release(cnt->handle);
#else /* other POSIX */
    pthread_spin_lock(&RCHANDLE(cnt)->lock);
    ret = !!--RCHANDLE(cnt)->val;
    pthread_spin_unlock(&RCHANDLE(cnt)->lock);
#endif
    if(!ret)
        cnt->wasz = SG_TRUE;
    return ret;
}

SG_EXPORT SGbool SG_CALL sgRCountCheck(SGRCount* cnt)
{
    return cnt->wasz;
}

SG_EXPORT SGuint SG_CALL sgRCountGetValDBG(SGRCount* cnt)
{
#ifdef _WIN32
    return *(LONG*)cnt->handle;
#elif defined(__FreeBSD__)
    return *(u_int*)cnt->handle;
#else /* other POSIX */
    SGuint val;
    pthread_spin_lock(&RCHANDLE(cnt)->lock);
    val = RCHANDLE(cnt)->val;
    pthread_spin_unlock(&RCHANDLE(cnt)->lock);
    return val;
#endif
}
