#include "barrier.h"


// inicializa a barreira, com n threads
void init_barr(barrier_t *barr, int n){
    barr->n_threads = n;
    barr->count = 0;
    sem_init(&barr->semaforo, 1, 0);
}

void destroy_barr(barrier_t *barr){
    sem_destroy(&barr->semaforo);
    free(barr);
}
// espera por todas as threads
void process_barrier(barrier_t *barr){}
