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
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe error");
        exit(1);
    }

    if (fork_or_die() == 0)
    {
        close(pipefd[0]); // Close the reading end of the pipe
        char *message = "Hello from first child\n";
        write(pipefd[1], message, strlen(message));
        close(pipefd[1]);
        exit(0);
    }
    if (fork_or_die() == 0)
    {
        char buf;
        sleep(1);
        close(pipefd[1]); // Close the writing end of the pipe
        while (read(pipefd[0], &buf, 1) > 0)
        {
            write(STDOUT_FILENO, &buf, 1);
        }
        close(pipefd[0]);
        exit(0);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    wait_or_die();
    wait_or_die();
    return 0;
}
