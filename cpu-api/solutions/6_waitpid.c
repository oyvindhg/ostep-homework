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
    int pid = fork_or_die();
    if (pid == 0)
    {
        sleep(3);
        fprintf(stderr, "oh no, an error!\n");
        exit(1);
    }
    int status;
    int rc = waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        printf("Child %d finished with exit code %d\n", rc, WEXITSTATUS(status));
    }

    return 0;
}
