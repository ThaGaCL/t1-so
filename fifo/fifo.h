// Trabalho 1 de Sistemas Operacionais
// André Gauer Thomal e Thales Gabriel Carvalho de Lima

#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct Node {
    pid_t pid;         // Identificador do processo
    struct Node *next;       // Ponteiro para o próximo nó
} Node;

typedef struct FifoQT {
    Node *head;              // Início da fila
    Node *tail;              // Fim da fila
    sem_t mutex;             // Semáforo para controle de acesso à fila
    sem_t mutex2;            // Semáforo para alteração da fila
} FifoQT;

void espera(FifoQT *F, Node *nos, int nProc);  // processo chamador deve esperar na fila F

void liberaPrimeiro( FifoQT *F); // libera o primeiro processo que esteja  
                                // "esperando" na fila F

void init_fifoQ( FifoQT *F );  // inicializa uma fila F (prepara para uso)
                        // caso seja necessário colocar valores iniciais
                        // nas variáveis internas da FifoQ 
                        // (ex: inicializar os semaforos usados) 


#endif // FIFO_H