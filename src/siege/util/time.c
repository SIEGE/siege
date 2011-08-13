/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */
#include <siege/util/time.h>

#ifdef __WIN32__
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <unistd.h>
    #include <time.h>
#endif

SGlong SG_EXPORT sgGetTime(void)
{
#ifdef __WIN32__
    #warning "time.c unimplemented on this platform"
    return 0L;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * SG_NANOSECONDS_IN_A_SECOND) + ts.tv_nsec;
#endif
}

void SG_EXPORT sgSleep(SGlong nseconds)
{
#ifdef __WIN32__
    #warning "time.c unimplemented on this platform"
#else
    struct timespec ts, tsr;
    ts.tv_sec = nseconds / SG_NANOSECONDS_IN_A_SECOND;
    ts.tv_nsec = nseconds % SG_NANOSECONDS_IN_A_SECOND;
    SGint ret = nanosleep(&ts, &tsr);
    if(ret < 0) // nanosleep didn't go so well, so we fall back to sleep/usleep combination...
    {
        while(ts.tv_sec)
            ts.tv_sec = sleep(ts.tv_sec); // first the seconds...
        usleep(ts.tv_nsec / 1000);
    }
#endif
}
