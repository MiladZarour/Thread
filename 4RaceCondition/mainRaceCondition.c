#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;

void *routine()
{
    for (size_t i = 0; i < 1000000; i++)
    {
        mails++;
        // read mailsmovl	mails(%rip), %eax
        // increment        addl $1, % eax
        // write mails      movl % eax, mails(% rip)
    }
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL))
    {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, NULL))
    {
        return 2;
    }
    if (pthread_join(t1, NULL))
    {
        return 3;
    }
    if (pthread_join(t2, NULL))
    {
        return 4;
    }
    printf("number of mails: %d\n", mails);
    return 0;
}