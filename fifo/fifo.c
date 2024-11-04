// Trabalho 1 de Sistemas Operacionais
// André Gauer Thomal e Thales Gabriel Carvalho de Lima

#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/mman.h>

void verifica_primeiro(FifoQT *F) {
    // printf("pid: %d e %d\n", getpid(), F->head->pid);
    while (F->head->pid != getpid()) {
        sem_post(&F->mutex);
        sem_wait(&F->mutex);
    }
    if (F->head->next == NULL) {
        F->head = NULL;
        F->tail = NULL;
    }
    else {
        F->head = F->head->next;
    }
    
    //
}

void init_fifoQ(FifoQT *F) {
    F->head = NULL;
    F->tail = NULL;
    sem_init(&F->mutex, 1, 1); // Inicializa o semáforo mutex
    sem_init(&F->mutex2, 1, 1);
}

void espera(FifoQT *F, Node *nos, int nProc) {
    sem_wait(&F->mutex2);
    Node* N;
    N = &nos[nProc];

    N->pid = getpid();
    N->next = NULL;

    if (F->head == NULL) {
        F->head = N;
        F->tail = N;
    }
    else {
        F->tail->next = N;
        F->tail = N;
    }
    sem_post(&F->mutex2);

    sem_wait(&F->mutex);
    verifica_primeiro(F);
}

void liberaPrimeiro(FifoQT *F) {
    sem_post(&F->mutex);
}

