#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

int diceValues[8];
int status[8] = {0};

pthread_barrier_t barrierRolledDice;
pthread_barrier_t barrierCalculated;

void *rollDice(void *args)
{
    int index = *(int *)args;
    while (1)
    {
        diceValues[index] = rand() % 6 + 1;
        pthread_barrier_wait(&barrierRolledDice);
        pthread_barrier_wait(&barrierCalculated);
        if (status[index] == 1)
        {
            printf("(%d rolled %d) I won\n", index, diceValues[index]);
        }
        else
        {
            printf("(%d rolled %d) I lost\n", index, diceValues[index]);
        }
    }

    free(args);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_barrier_init(&barrierRolledDice, NULL, THREAD_NUM + 1);
    pthread_barrier_init(&barrierCalculated, NULL, THREAD_NUM + 1);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &rollDice, a) != 0)
        {
            perror("Failed to create thread");
        }
    }

    while (1)
    {
        pthread_barrier_wait(&barrierRolledDice);
        // Calculate the winner
        int max = 0;
        for (int i = 0; i < THREAD_NUM; i++)
        {
            if (diceValues[i] > max)
            {
                max = diceValues[i];
            }
        }
        for (int i = 0; i < THREAD_NUM; i++)
        {
            if (diceValues[i] == max)
            {
                status[i] = 1;
            }
            else
            {
                status[i] = 0;
            }
        }
        printf("====== NEW ROUND STARTED =====\n");
        sleep(1);
        pthread_barrier_wait(&barrierCalculated);
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }
    pthread_barrier_destroy(&barrierRolledDice);
    pthread_barrier_destroy(&barrierCalculated);

    return 0;
}