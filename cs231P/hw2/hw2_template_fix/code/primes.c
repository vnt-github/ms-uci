#include "util.h"//implementing
#include <stdio.h> //remove if not using.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>


typedef struct
{
    pthread_mutex_t *pmtx;
    int *count;
    const int max_prime;
    const int verb;
} Args;

static bool isPrime(int num) {
    for (int i = 2; i <= sqrt(num); i++)
        if (!(num%i))
            return false;
    return true;
}


void* logPrimes(void *arg) {
    Args *a = (Args *) arg;
    int curr_num;
    while (*(a->count) < a->max_prime) {

        pthread_mutex_lock(a->pmtx);
        *(a->count) += 1;
        curr_num = *(a->count);
        pthread_mutex_unlock(a->pmtx);

        if (isPrime(curr_num) && a->verb)
            printf("%d\n", curr_num);
    }
    pthread_exit(NULL);
}

void primes_st(unsigned int max, unsigned int verb) {
    for (int i = 2; i < max; i++)
        if (isPrime(i) && verb)
            printf("%d\n", i);
    return;
}

void primes_mt(unsigned int max, unsigned int threads, unsigned int verb) {
    pthread_t threads_arr[threads];
    
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    
    int shrd_count = 1;
    Args arg_thr = { &mutex, &shrd_count, max, verb };

    int ret;

    for (int i = 0; i < threads; i++)
    {
        ret = pthread_create(&threads_arr[i], NULL, &logPrimes, (void*)&arg_thr);
    }

    if (ret) {
        printf("Error creating thread\n");
        exit(-1);
    }

    for (int i = 0; i < threads; i++)
    {
        pthread_join(threads_arr[i], NULL);
    }
    

    return;
}
