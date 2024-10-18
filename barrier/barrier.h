#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct barrier_s {
    int n_threads;          // número de threads
    int count;              // contador de threads
} barrier_t;          // tipo barrier_t 


// inicializa a barreira, com n threads
void init_barr( barrier_t *barr, int n );

// espera por todas as threads
void process_barrier( barrier_t *barr );


#endif // BARRIER_H