#include <stdio.h> //remove if not using.
#include <pthread.h>
#include <stdlib.h>
#include "util.h"//implementing
#include "math.h"

typedef struct
{
    Mat *mat;
    int i;
    int j;
    unsigned int grain;
} Args;


void setIndices(int* i, int* j, int n) {
    int new_i = floor((sqrt(8*n+1)+1)/2);
    *i = new_i;
    *j = n - ((new_i)*(new_i-1))/2;
    // printf("\nn: %d i: %d j: %d\n", n, *i, *j);
}

void setNext(int* i, int* j, int n) {
    if (*i >= n-1 && *j == *i-1) {
        *i = 0;
        *j = 0;
    } else if (*j+1 < *i) {
        *j += 1;
    } else {
        *i +=1;
        *j = 0;
    }
}

void mat_sq_trans_st(Mat *mat){
    int temp;
    for (int i = 0; i < mat->n; i++)
    {
        for (int j = i+1; j < mat->n; j++)
        {
            temp = mat->ptr[i*mat->n+j];
            mat->ptr[i*mat->n+j] = mat->ptr[j*mat->n+i];
            mat->ptr[j*mat->n+i] = temp;     
        }
    }    
}

void* transpose(void *args) {
    Args *a = (Args*) args;
    Mat* mat = a->mat;
    int i = a->i;
    int j = a->j;
    unsigned int grain = a->grain;
    // printf("\nstart: i: %d j:%d\n", i, j);
    int temp;
    for (int times = 0; times < grain; times++)
    {
        if (!i && !j) break;
        // printf("\ttimes: %d i: %d j:%d", times, i, j);
        temp = mat->ptr[i*mat->n+j];
        mat->ptr[i*mat->n+j] = mat->ptr[j*mat->n+i];
        mat->ptr[j*mat->n+i] = temp;        
        setNext(&i, &j, mat->n);
    }
    // printf("\n");
    pthread_exit(NULL);
}

void mat_sq_trans_mt(Mat *mat, unsigned int grain, unsigned int threads){
    pthread_t threads_arr[threads];
    Args args[threads];
    int ret;
    int n = mat->n;
    int n_end = n*(n-1)/2;
    // printf("n_end %d\n", n_end);
    int i, j, t;
    int count = 0;
    for (int times = 0; times < n_end; times+=grain)
    {
        // printf("t: %d times: %d\n", t, times);
        if (count >= threads) {
            pthread_join(threads_arr[t], NULL);
        }
        setIndices(&i, &j, times);
        args[t].mat = mat;
        args[t].i = i;
        args[t].j = j;
        args[t].grain = grain;
        ret = pthread_create(&threads_arr[t], NULL, &transpose, (void*)&args[t]);
        if (ret) exit(-1);
        count += 1;
        // printf("\ndone %d\n", times);
        t = (t+1)%threads;
    }
    for (int t = 0; t < count && t < threads; t++)
    {
        pthread_join(threads_arr[t], NULL);
    }
}

// todo: 10 10 1 1