#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct FifoQ_s {
    int n;          // número de processos na fila
    int count;      // contador de processos
} FifoQT;          // tipo FifoQT

void espera(FifoQT *F);  // processo chamador deve esperar na fila F

void liberaPrimeiro( FifoQT *F); // libera o primeiro processo que esteja  
                                // "esperando" na fila F

void init_fifoQ( FifoQT *F );  // inicializa uma fila F (prepara para uso)
                        // caso seja necessário colocar valores iniciais
                        // nas variáveis internas da FifoQ 
                        // (ex: inicializar os semaforos usados) 


#endif // FIFO_H