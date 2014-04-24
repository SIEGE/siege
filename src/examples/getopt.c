#include <siege/siege.h>

#include <stdio.h>

/*
 * Testcase:
 *      ./Example-GetOpt\
 *          -xytesty --none -z -w testw\
 *          --opta --optb=argopt --req=argreq\
 *          -- -x notopt
 * Desired output:
 *      Arguments:
 *          -x
 *          -y=testy
 *          --none
 *          -z
 *          -w=testw
 *          --opta
 *          --optb=argopt
 *          --req=argreq
 *      Non-arguments:
 *          -x
 *          notopt
 */

int main(int argc, char** argv)
{
    SGOption longopts[] = {
        {"none", SG_ARG_NONE, 'n'},
        {"opta", SG_ARG_OPTIONAL, 'a'},
        {"optb", SG_ARG_OPTIONAL, 'b'},
        {"req", SG_ARG_REQUIRED, 'r'},
        {NULL, 0, 0}
    };

    SGGetOpt getopt;
    sgGetOptInit(&getopt, argc, argv, "xy:zw:", longopts);

    SGint ret;
    SGlong longind;
    char* arg;

    printf("Arguments passed in:\n");
    for(;;)
    {
        ret = sgGetOptNext(&getopt, &longind, &arg);
        if(ret == EOF) break;

        if(longind == -1)
            printf("-%c", ret);
        else
            printf("--%s", longopts[longind].name);
        if(arg) printf("=%s", arg);
        printf("\n");
    }

    printf("Non-arguments that follow:\n");
    size_t i;
    for(i = getopt.ind; i < argc; i++)
        printf("%s\n", argv[i]);

    return 0;
}
