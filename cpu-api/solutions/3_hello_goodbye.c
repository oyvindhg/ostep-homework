#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_or_die()
{
    int rc = wait(NULL);
    assert(rc > 0);
}

int fork_or_die()
{
    int rc = fork();
    assert(rc >= 0);
    return rc;
}

int main(int argc, char *argv[])
{
    if (fork_or_die() == 0)
    {
        printf("Hello\n");
        exit(0);
    }
    sleep(1);
    printf("Goodbye\n");
    return 0;
}
