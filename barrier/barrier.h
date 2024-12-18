// Trabalho 1 de Sistemas Operacionais
// André Gauer Thomal e Thales Gabriel Carvalho de Lima

#ifndef BARRIER_H
#define BARRIER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

typedef struct barrier_s {
    int count;          // Contador de processos que chegaram à barreira
    int total;          // Total de processos
    sem_t mutex;       // Semáforo para exclusão mútua
    sem_t semaforo;   // Semáforo para esperar os processos
} barrier_t;

// inicializa a barreira, com n threads
void init_barr(barrier_t *barr, int n);

// espera por todas as threads
void process_barrier(barrier_t *barr);

void destroy_barr(barrier_t *barr);

#endif // BARRIER_H