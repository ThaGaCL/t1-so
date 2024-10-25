#include "barrier.h"

int main() {
    barrier_t *barreira = malloc(sizeof(barrier_t));
    init_barr(barreira, 5);

    
    destroy_barr(barreira);
    return 0;
}