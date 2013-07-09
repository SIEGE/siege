#include <siege/siege.h>

int main(void)
{
    sgInit(0);
    sgWindowOpen(640, 480, 32, 0);

    SGint ret = sgRun();

    sgDeinit();

    return ret;
}
