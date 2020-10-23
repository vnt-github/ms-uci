#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>


/**
 * Defines the structure of Args, that contains the mutex pointer and the counter.
 * */
typedef struct
{
    pthread_mutex_t *pmtx;
    int *count;
    const int max_prime;
    const int verb;
} Args;

/**
 * Checks whether a particular input is prime.
 * @param num is the number which is to be checked.
 * @return a boolean value depending on whether the number is prime.
 * */
static bool isPrime(int num) {
    for (int i = 2; i <= sqrt(num); i++)
        if (!(num%i))
            return false;
    return true;
}

/**
 * A helper function to be executed by all threads in parallel to obtain a particular number to check for prime.
 * @param *arg is a pointer to the argument object passed to the function.
 * @return void* is a pointer to the memory location of the return values cast to void.
 * */
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

/**
 * A function to execute a prime number check using a single thread.
 * @param max is the maximum range to which we are checking for prime numbers.
 * @param verb is the verbosity variable which determines whether the prime numbers are printed or not.
 * */
void primes_st(unsigned int max, unsigned int verb) {
    for (int i = 2; i < max; i++)
        if (isPrime(i) && verb)
            printf("%d\n", i);
    return;
}

/**
 * A function to execute a prime number check implementing the concept of multi-threading.
 * @param max is the maximum range to which we are checking for prime numbers.
 * @param threads is the maximum number of threads to be spawned to run in parallel performing prime number checking.
 * @param verb is the verbosity variable which determines whether the prime numbers are printed or not.
 * */
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
