#include <stdio.h> //remove if not using.
#include <pthread.h>
#include <stdlib.h>
#include "util.h"//implementing
#include "math.h"

typedef struct
{
    pthread_mutex_t *pmtx;
    int *count;
    int max_num;
    unsigned int grain;
    Mat *mat;
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
 * @param n is the last number in lower half of the matrix
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
 * perform swap of element st mat[i][j] <-> mat[j][i]
 * @param mat is the matrix whose elements are to be swapped
 * @param i is the row index
 * @param j is the column index
 * */
void swapMat(Mat *mat, int i, int j) {
    int temp = mat->ptr[i*mat->n+j];
    mat->ptr[i*mat->n+j] = mat->ptr[j*mat->n+i];
    mat->ptr[j*mat->n+i] = temp; 
}

/**
 * performs swap of grain number of entries at a time 
 * across the diagnol in the matrix.
 * @param *arg is a pointer to the argument object passed to the function.
 * @return void* is a pointer to the memory location of the return values cast to void.
 * */
void* transpose(void *args) {
    Args *a = (Args*) args;
    int i = 0, j = 0;
    int curr_num=0;
    int max_num=a->max_num;
    unsigned int grain = a->grain;

    do
    {
        pthread_mutex_lock(a->pmtx);
        curr_num = *(a->count);
        *(a->count) += grain;
        pthread_mutex_unlock(a->pmtx);

        if (curr_num >= max_num) break;

        setIndices(&i, &j, curr_num);
        for (int g = 0; g < grain; g++)
        {
            if (curr_num >= max_num || g >= max_num || (!i && !j)) break;
            // printf("%d %d %d %d\n", curr_num, grain, i, j);
            swapMat(a->mat, i, j);
            setNext(&i, &j, a->mat->n);
        }
    } while (curr_num < max_num);

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

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    int shrd_count = 0;

    int max_num = floor(mat->n*(mat->n-1)/2);
    Args arg_thr = { &mutex, &shrd_count, max_num, grain, mat };

    int ret;

    for (int i = 0; i < threads; i++)
    {
        ret = pthread_create(&threads_arr[i], NULL, &transpose, (void*)&arg_thr);
        if (ret) {
            // printf("Error creating thread\n");
            exit(-1);
        }
    }


    for (int i = 0; i < threads; i++)
    {
        pthread_join(threads_arr[i], NULL);
    }


    return;
}

/**
 * perform single threaded matrix transposition
 * @param mat is the matrix to be transposed
 * */
void mat_sq_trans_st(Mat *mat){
    double temp;
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