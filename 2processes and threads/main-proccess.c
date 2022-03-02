#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

int x = 2;

int main(int argc, char *argv[])
{
    // int x = 2;
    int pid = fork();
    if (pid == -1)
    {
        return 1;
    }

    if (pid == 0)
    {
        x++;
    }
    sleep(2);
    printf("Value of x: %d for the pid : %d\n", x, pid);

    // printf("Process id %d\n", getpid());
    if (pid != 0)
    {
        wait(NULL);
    }

    return 0;
}