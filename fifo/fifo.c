#include "fifo.h"

void init_fifoQ(FifoQT *F) {
    F->head = NULL;
    F->tail = NULL;
    sem_init(&F->mutex, 1, 1); // Inicializa o semáforo mutex
}

void espera(FifoQT *F) {
    sem_wait(&F->mutex);
}

void liberaPrimeiro(FifoQT *F) {
    sem_post(&F->mutex);
}

