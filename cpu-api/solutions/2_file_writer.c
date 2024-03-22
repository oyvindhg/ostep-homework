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
    FILE *fptr = fopen("my-file.txt", "w");

    if (fptr == NULL)
    {
        perror("Error opening file!");
        return 1;
    }

    fprintf(fptr, "Hello world\n");
    if (fork_or_die() == 0)
    {
        printf("Child trying to write\n");
        fprintf(fptr, "Hello from child\n");
        printf("Child wrote\n");
        sleep(3);
        fprintf(fptr, "Hello from child after sleep\n");
        fclose(fptr);
        printf("Closed file from child\n");
        exit(0);
    }
    printf("Parent trying to write\n");
    fprintf(fptr, "Hello from parent\n");
    printf("Parent wrote\n");
    wait_or_die();
    fprintf(fptr, "Hello from parent afer wait\n");

    fclose(fptr);
    printf("Closed file from parent\n");
    return 0;
}
