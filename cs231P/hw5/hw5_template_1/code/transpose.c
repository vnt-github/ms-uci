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


/**
 * set the i and j corresponding to the nth entry
 * in the lower half of the matrix triangle without the diagnol
 * for example:
 *  n = 0 -> i = 1, j = 0
 *  n = 1 -> i = 1, j = 0
 *  n = 2 -> i = 2, j = 1
 * ..
 * ...
 *  n = 12 -> i = 5, j = 2
 *  ...
 * @param i is the row index
 * @param j is the column index
 * @param n is the nth number in the lower half of the matrix
 * */
void setIndices(int* i, int* j, int n) {
    int new_i = floor((sqrt(8*n+1)+1)/2);
    *i = new_i;
    *j = n - ((new_i)*(new_i-1))/2;
}

/**
 * set the i and j to next entry in the 
 * lower half of the matrix triangle without diagnol
 * @param i is the row index
 * @param j is the column index
 * @param n is the nth number in the lower half of the matrix
 * */
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

/**
 * performs swap of entries across the diagnol in the matrix at index i and j.
 * @param *arg is a pointer to the argument object passed to the function.
 * @return void* is a pointer to the memory location of the return values cast to void.
 * */
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

/**
 * perform multi threaded matrix transposition
 * @param mat is the matrix to be transposed
 * @param grain is the number of elemets to be swapped by a thread
 * @param threads is the number of threads for processing
 * */
void mat_sq_trans_mt(Mat *mat, unsigned int grain, unsigned int threads){
    pthread_t threads_arr[threads];
    Args args[threads];
    int ret;
    int n = mat->n;
    int n_end = n*(n-1)/2;
    // printf("n_end %d\n", n_end);
    int i=0, j=0, t=0;
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

/**
 * perform single threaded matrix transposition
 * @param mat is the matrix to be transposed
 * */
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