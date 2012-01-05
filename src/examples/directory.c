/*
 * A simple directory functionality example.
 *
 * It prompts the user for a directory and then displays its contents.
 */

#include <siege/siege.h>

#include <stdio.h>
#include <stdarg.h>

int main(void)
{
    char dname[1024];
    printf("Directory: ");
    fgets(dname, sizeof(dname), stdin);
    dname[sizeof(dname)-1] = 0;
    *sgLineEnd(dname) = 0;

    SGDirectory* dir = sgDirectoryOpen(dname);

    char* fname;
    while((fname = sgDirectoryNext(dir, NULL, 0)))
        printf("%s\n", fname);

    sgDirectoryClose(dir);

    return 0;
}
