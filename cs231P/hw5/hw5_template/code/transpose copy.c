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
    return;
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
    // pthread_exit(NULL);
    Args *a = args;
    Mat* mat = a->mat;
    int i = a->i;
    int j = a->j;
    unsigned int grain = a->grain;
    printf("\ntranspose called with %d %d %d\n", i, j, grain);
    int temp;
    for (int times = 0; times < grain; times++)
    {
        if (!i && !j) break;
        printf("\t%d,%d ", i, j);
        // temp = mat->ptr[i*mat->n+j];
        // mat->ptr[i*mat->n+j] = mat->ptr[j*mat->n+i];
        // mat->ptr[j*mat->n+i] = temp;        
        setNext(&i, &j, 1, mat->n);
    }
    printf("\n");
    pthread_exit(NULL);
}

void mat_sq_trans_mt(Mat *mat, unsigned int grain, unsigned int threads){
    printf("\n\ngrain: %d\n", grain);
    pthread_t threads_arr[threads];
    Args args[10000];
    int i = 1;
    int j = 0;
    int ret;
    for (int t = 0; t < threads; t++)
    {    
        if (i || j) {
            printf("i: %d j: %d\n", i, j);
            args[t].mat = mat;
            args[t].i = i;
            args[t].j = j;
            args[t].grain = grain;
            // transposeChunk(mat, i, j, grain);
            ret = pthread_create(&threads_arr[t], NULL, &transpose, (void*)&args[t]); // (void*)&args[t]);
            if (ret) exit(-1);
            setNext(&i, &j, grain, mat->n);
        }
    }

    int t = 0;
    int count = threads;
    while (i || j) {
        printf("\nwait for %d i: %d j: %d\n", t, i, j);
        pthread_join(threads_arr[t], NULL);
        printf("\ni: %d j: %d\n", i, j);
        t = (t+1)%threads;
        args[count].mat = mat;
        args[count].i = i;
        args[count].j = j;
        args[count].grain = grain;
        count += 1;
        // transposeChunk(mat, i, j, grain);
        ret = pthread_create(&threads_arr[t], NULL, &transpose, (void*)&args[t]);
        if (ret) exit(-1);
        setNext(&i, &j, grain, mat->n);
    }    

}
