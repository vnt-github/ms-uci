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

        if (isPrime(curr_num))
            printf("%d ", curr_num);
    }
    pthread_exit(NULL);
}

void primes_st(unsigned int max, unsigned int verb) {
    for (int i = 2; i < max; i++)
        if (isPrime(i))
            printf("%d ", i);
    
    return;
}

void primes_mt(unsigned int max, unsigned int threads, unsigned int verb) {
    pthread_t threads_arr[threads];
    
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    
    int shrd_count = 1;
    Args arg_thr = { &mutex, &shrd_count, max };

    int ret;

    for (int i = 0; i < threads; i++)
    {
        ret = pthread_create(&threads_arr[i], NULL, &logPrimes, (void*)&arg_thr);
    }

    if (ret) {
        printf("Error creating thread\n");
        exit(-1);
    }
    
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    int const num_thr = 10;
    primes_mt(1000, num_thr, 0);
    // primes_st(1000, 0);
    return 0;
}
