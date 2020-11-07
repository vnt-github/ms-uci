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

/**
 * solves single row or matrix multiplication
 * @param *arg is a pointer to the argument object passed to the function.
 * @return void* is a pointer to the memory location of the return values cast to void.
 * */
void* mult_row(void *args) {
    Args *a = (Args*) args;
    Mat* A = a->A;
    Mat* B = a->B;
    Mat* C = a->C;
    int i = a->i;
    for (int j = 0; j < B->m; j++)
        for (int k = 0; k < B->n; k++)
            C->ptr[C->n*i+j] += A->ptr[A->n*i+k]*B->ptr[B->n*k+j];
    pthread_exit(NULL);
}

/**
 * performs multithreaded matrix multiplication
 * @param A 1st matrix for multiplication
 * @param B 2nd matrix for multipliication
 * @param C ans matrix
 * @param thread is the number of threads for computation
 * */
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

/**
 * performs singleThreaded matrix multiplication
 * @param A 1st matrix for multiplication
 * @param B 2nd matrix for multipliication
 * @param C ans matrix
 * */
void mat_multiply_st(Mat *A, Mat *B, Mat *C) {
    for (int i = 0; i < A->n; i++)
        for (int j = 0; j < B->m; j++)
            for (int k = 0; k < A->m; k++)
                C->ptr[C->n*i+j] += A->ptr[A->n*i+k]*B->ptr[B->n*k+j];
}

/**
 * performs matrix multiplication either single or multi threaded
 * @param A 1st matrix for multiplication
 * @param B 2nd matrix for multipliication
 * @param C ans matrix
 * @param thread is the number of threads for computation
 * */
void mat_multiply(Mat *A, Mat *B, Mat *C, unsigned int threads){
    mat_multiply_mt(A, B, C, threads);
    // mat_multiply_st(A, B, C);
    return;
}
