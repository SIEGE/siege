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

#ifdef linux
#include <time.h>

SGlong SG_EXPORT sgGetTime(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000000000L) + ts.tv_nsec;
}

void SG_EXPORT sgSleep(SGint useconds)
{
    usleep(useconds);
}
#else
#warning "time.c unimplemented on your platform."
SGlong SG_EXPORT sgGetTime(void)
{
    return 0L;
}
#endif
