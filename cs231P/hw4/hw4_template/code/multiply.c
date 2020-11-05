#include <stdio.h> //remove if not using.
#include <pthread.h>
#include <stdlib.h>
#include "util.h"//implementing

typedef struct { //example structure
    int example;
    int e_g;
} Example_Structure;

typedef struct
{
    Mat *A;
    Mat *B;
    Mat *C;
    int i;
} Args;


void* mult_row(void *args) {
    Args *a = (Args*) args;
    Mat* A = a->A;
    Mat* B = a->B;
    Mat* C = a->C;
    int i = a->i;
    for (int j = 0; j < B->n; j++)
        for (int k = 0; k < B->n; k++)
            C->ptr[C->n*i+j] += A->ptr[A->n*i+k]*B->ptr[B->n*k+j];
    pthread_exit(NULL);
}

void mat_multiply_mt(Mat *A, Mat *B, Mat *C, unsigned int threads) {
    pthread_t threads_arr[threads];
    int ret;
    Args args[A->n];
    for (int i = 0; i < A->n; i++) {
        args[i].A = A;
        args[i].B = B;
        args[i].C = C;
        args[i].i = i;
    }
    
    for (int t = 0; t < threads; t++)
    {
        ret = pthread_create(&threads_arr[t], NULL, &mult_row, (void*)&args[t]);
    }

    for (int i = threads; i < A->n; i++)
    {
        pthread_join(threads_arr[i%threads], NULL);
        ret = pthread_create(&threads_arr[i%threads], NULL, &mult_row, (void*)&args[i]);
        if (ret)
            exit(-1);
    }
    
    for (int t = 0; t < threads; t++)
        pthread_join(threads_arr[t], NULL);
    
    return;
}

void mat_multiply_st(Mat *A, Mat *B, Mat *C) {
    for (int i = 0; i < A->n; i++)
    {
        for (int j = 0; j < B->m; j++)
        {
            for (int k = 0; k < A->m; k++)
            {
                C->ptr[C->n*i+j] += A->ptr[A->n*i+k]*B->ptr[B->n*k+j];
            }
        }
    }
}

void mat_multiply(Mat *A, Mat *B, Mat *C, unsigned int threads){
    //Put your code here.
    //Remember to set the correct values for C->m, and C->n
    //after doing the multiplication.
    //example_helper_function(1000);
    mat_multiply_mt(A, B, C, threads);
    // mat_multiply_st(A, B, C);
    return;
}
