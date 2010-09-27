#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>

#include "mixer.h"
#include "buffer.h"
#include "source.h"

void sleep(time_t seconds)
{
    time_t end = time(NULL);
    while(time(NULL) < end + seconds)
    {
    }
}

#undef main
int main()
{
    SWM_Init();

    sleep(1);

    SWM_Quit();
    return 0;
}
