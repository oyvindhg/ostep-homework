#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

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
        printf("Child process id: %d\n", (int)getpid());
        int rc = wait(NULL);
        printf("Child wait returned %d\n", rc);
        if (rc == -1)
        {
            if (errno == ECHILD)
            {
                printf("Child has no children to wait for!\n");
            }
        }
        exit(0);
    }
    printf("Parent process id: %d\n", (int)getpid());
    int rc = wait(NULL);
    printf("Parent wait returned %d\n", rc);

    return 0;
}
