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
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s type\n", argv[0]);
        exit(1);
    }
    char *type = argv[1];
    if (fork_or_die() == 0)
    {
        if (strcmp(type, "execl") == 0)
        {
            execl("/bin/ls", "/bin/ls", NULL);
        }
        if (strcmp(type, "execlp") == 0)
        {
            execlp("ls", "ls", NULL);
        }
        if (strcmp(type, "execle") == 0)
        {
            char *envs[2];
            envs[0] = "MY_KEY=value";
            envs[1] = NULL;

            execle("ls", "ls", NULL, envs);
        }
        if (strcmp(type, "execv") == 0)
        {
            char *args[2];
            args[0] = "/bin/ls";
            args[1] = NULL;

            execvp(args[0], args);
        }
        if (strcmp(type, "execvp") == 0)
        {
            char *args[2];
            args[0] = "ls";
            args[1] = NULL;

            execvp(args[0], args);
        }
        else if (strcmp(type, "execvpe") == 0)
        {
            char *args[2];
            args[0] = "/bin/ls";
            args[1] = NULL;

            char *envs[2];
            envs[0] = "MY_KEY=value";
            envs[1] = NULL;

            execve(args[0], args, envs);
        }
        else
        {
            exit(1);
        }
    }
    wait_or_die();
    return 0;
}
