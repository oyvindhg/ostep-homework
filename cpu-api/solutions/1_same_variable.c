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
    int x = 1;
    if (fork_or_die() == 0)
    {
        x = 2;
        printf("Value from child: %d\n", x);
        sleep(3);
        printf("Value from child after sleep: %d\n", x);
        exit(0);
    }
    x = 3;
    printf("Value from parent: %d\n", x);
    wait_or_die();
    printf("Value from parent after wait: %d\n", x);
    return 0;
}
