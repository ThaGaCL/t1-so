#include "barrier.h"


// inicializa a barreira, com n threads
void init_barr(barrier_t *barr, int n) {
    barr->count = 0;
    barr->total = n;
    sem_init(&barr->mutex, 1, 1);  // Semáforo binário
    sem_init(&barr->semaforo, 1, 0); // Semáforo inicializado para 0
}


void destroy_barr(barrier_t *barr){
    sem_destroy(&barr->semaforo);
    sem_destroy(&barr->mutex);
    free(barr);
}
// espera por todas as threads
void process_barrier(barrier_t *barr){}
