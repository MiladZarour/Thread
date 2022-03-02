#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int id = fork();
    if (id != 0)
    {
        fork();
    }

    printf("Hello World\n");
    // if (id == 0)
    // {
    //     printf("Hello from child process : %d\n", id);
    // }
    // else
    // {
    //     printf("Hello from the main process : %d\n", id);
    // }
    return 0;
}