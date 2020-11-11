#include <stdio.h> //remove if not using.
#include <pthread.h>
#include <stdlib.h>
#include "util.h"//implementing

typedef struct
{
    Mat *mat;
    int i;
    int j;
    unsigned int grain;
} Args;


void setNext(int* ori_i, int* ori_j, unsigned int grain, int n) {
    int jump = 1 + grain;
    int i = *ori_i;
    int j = *ori_j;
    for(; i < n; i++) {
        for(; j < i; j++) {
            if (!--jump) {
                *ori_i = i;
                *ori_j = j;
                return;
            }
        }
        j = 0;
    }
    *ori_i = 0;
    *ori_j = 0;
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

void transposeChunk(Mat *mat, int i, int j, unsigned int grain) {
    int temp;
    for (int times = 0; times < grain; times++)
    {
        if (!i && !j) return;
        printf("\t%d,%d ", i, j);
        temp = mat->ptr[i*mat->n+j];
        mat->ptr[i*mat->n+j] = mat->ptr[j*mat->n+i];
        mat->ptr[j*mat->n+i] = temp;        
        setNext(&i, &j, 1, mat->n);
    }
    printf("\n");
}

void* transpose(void *args) {
    Args *a = args;
    Mat* mat = a->mat;
    int i = a->i;
    int j = a->j;
    unsigned int grain = a->grain;
    int temp;
    for (int times = 0; times < grain; times++)
    {
        if (!i && !j) break;
        temp = mat->ptr[i*mat->n+j];
        mat->ptr[i*mat->n+j] = mat->ptr[j*mat->n+i];
        mat->ptr[j*mat->n+i] = temp;        
        setNext(&i, &j, 1, mat->n);
    }
    pthread_exit(NULL);
}

void mat_sq_trans_mt(Mat *mat, unsigned int grain, unsigned int threads){
    pthread_t threads_arr[threads];
    int n_args = (mat->n*mat->n)/2;
    Args args[n_args];
    int i = 1;
    int j = 0;
    int ret;
    int a_i = 0;
    while (i || j) {
        args[a_i].mat = mat;
        args[a_i].i = i;
        args[a_i].j = j;
        args[a_i].grain = grain;
        setNext(&i, &j, grain, mat->n);
        a_i += 1;
    }

    // for (int t = 0; t < threads; t++)
    // {
    //     ret = pthread_create(&threads_arr[t], NULL, &transpose, (void*)&args[t]);
    //     if (ret) exit(-1);
    // }

    // for (int i = threads; i < a_i; i++)
    // {
    //     // pthread_join(threads_arr[i%threads], NULL);
    //     ret = pthread_create(&threads_arr[i%threads], NULL, &transpose, (void*)&args[i]);
    //     if (ret) exit(-1);
    // }

}
