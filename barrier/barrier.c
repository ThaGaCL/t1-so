#include "barrier.h"


// inicializa a barreira, com n threads
void init_barr(barrier_t *barr, int n) {
    barr->count = 0;
    barr->total = n;
    sem_init(&barr->mutex, 1, 1);  // Semáforo binário
    sem_init(&barr->semaforo, 1, 0); // Semáforo inicializado para 0
}

void process_barrier(barrier_t *barr) {
    sem_wait(&barr->mutex); // Entrar na seção crítica
    barr->count++;

    if (barr->count == barr->total) {
        // Último processo, libera todos os outros
        for (int i = 0; i < barr->total; i++) {
            sem_post(&barr->semaforo);
        }
    }
    
    sem_post(&barr->mutex); // Sair da seção crítica
    sem_wait(&barr->semaforo); // Esperar ser liberado
}

void destroy_barr(barrier_t *barr){
    sem_destroy(&barr->semaforo);
    sem_destroy(&barr->mutex);
    free(barr);
}
