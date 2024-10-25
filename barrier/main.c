#include "barrier.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <número de processos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    barrier_t *barr;

    // Alocar memória compartilhada
    int shm_id = shmget(IPC_PRIVATE, sizeof(barrier_t), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    barr = (barrier_t *)shmat(shm_id, NULL, 0);
    
    // Inicializar a barreira
    init_barr(barr, n);

    pid_t pid;
    for (int i = 0; i < n - 1; i++) {
        if ((pid = fork()) == 0) {  // Processo filho
            int nProc = i + 1; // nProc para processos filhos
            printf("Processo filho: PID=%d, Pai PID=%d, nProc=%d\n", getpid(), getppid(), nProc);

            // Dormir por um tempo aleatório
            int ns = rand() % n;
            printf("Processo %d vai dormir por %d segundos.\n", nProc, ns);
            sleep(ns);

            process_barrier(barr); // Chamar a barreira

            printf("Processo %d saiu da barreira.\n", nProc);
            exit(0);
        }
    }

    // Processo pai
    int nProc = 0;
    printf("Processo pai: PID=%d, nProc=%d\n", getpid(), nProc);

    // Dormir por um tempo aleatório
    int ns = rand() % n;
    printf("Processo pai vai dormir por %d segundos.\n", ns);
    sleep(ns);

    process_barrier(barr); // Chamar a barreira

    printf("Processo pai saiu da barreira.\n");

    // Esperar pelos processos filhos
    for (int i = 0; i < n - 1; i++) {
        wait(NULL);
    }

    // Liberar memória compartilhada
    shmdt(barr);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
