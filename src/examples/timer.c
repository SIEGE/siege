/*
 * A simple example of SIEGE timers without using a SIEGE main loop in core
 * (core calls sgTimerUpdateAll() automagically).
 */

#include <siege/siege.h>

#include <stdio.h>
#include <stdarg.h>

void SG_EXPORT func(SGTimer* timer, void* data)
{
    printf("%s\n", (char*)data);
}

int main(void)
{
    SGTimer* timer1500 = sgTimerCreate(SG_FALSE);
    SGTimer* timer2000 = sgTimerCreate(SG_FALSE);

    sgTimerSetFunction(timer1500, func, "1.5 second timer");
    sgTimerSetFunction(timer2000, func, "2.0 second timer");

    sgTimerMStart(timer1500, 1500);
    sgTimerMStart(timer2000, 2000);

    sgTimerMSingle(5000, func, "5.0 second timer", SG_FALSE);

    SGulong start = sgGetTime();
    while(sgGetTime() - start <= 10 * SG_NANOSECONDS_IN_A_SECOND)
        sgTimerUpdateAll(SG_FALSE, SG_FALSE);

    sgTimerDestroy(timer2000);
    sgTimerDestroy(timer1500);

    return 0;
}
