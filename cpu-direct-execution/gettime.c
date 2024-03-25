#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct timeval currentTime1;
    struct timeval currentTime2;
    struct timeval currentTime3;
    struct timeval currentTime4;
    struct timeval currentTime5;

    char buffer[1];
    gettimeofday(&currentTime1, NULL);
    read(0, buffer, 0);
    gettimeofday(&currentTime2, NULL);
    read(0, buffer, 0);
    gettimeofday(&currentTime3, NULL);
    read(0, buffer, 0);
    gettimeofday(&currentTime4, NULL);
    read(0, buffer, 0);
    gettimeofday(&currentTime5, NULL);

    printf("Time 1: %lds %ldmicros\n", currentTime1.tv_sec, currentTime1.tv_usec);
    printf("Time 2: %lds %ldmicros\n", currentTime2.tv_sec, currentTime2.tv_usec);
    printf("Time 3: %lds %ldmicros\n", currentTime3.tv_sec, currentTime3.tv_usec);
    printf("Time 4: %lds %ldmicros\n", currentTime4.tv_sec, currentTime4.tv_usec);
    printf("Time 5: %lds %ldmicros\n", currentTime5.tv_sec, currentTime5.tv_usec);
    return 0;
}