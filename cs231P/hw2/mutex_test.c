#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    pthread_mutex_t *pmtx;
    int *count;
} Args;

void* add_ten(void *arg) {
    Args *a = (Args *) arg;
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(a->pmtx);
        *(a->count) += 1;
        pthread_mutex_unlock(a->pmtx);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int const num_thr = 10;
    pthread_t threads[num_thr];
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    int ret, i, shrd_count = 0;
    Args arg_thr = { &mutex, &shrd_count };
    for (int i = 0; i < num_thr; i++)
    {
        ret = pthread_create(&threads[i], NULL, &add_ten, (void*)&arg_thr);
    }

    if (ret) {
        printf("Error creating thread\n");
        exit(-1);
    }
    
    for (i = 0; i < num_thr; i++)
        pthread_join(threads[i], NULL);
    
    if (shrd_count != 100)
        printf("Shared counter: %d\n", shrd_count);
    
    return 0;
}
