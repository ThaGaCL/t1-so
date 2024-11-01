#include "fifo/fifo.h"
#include "barrier/barrier.h"
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int generate_rand(){
    return rand() % 3 + 1;
}

int main(int argc, char* argv[]){
    // Processo Pi onde Pi é seu número lógico
    int Pi;
    pid_t pid;
    barrier_t *barreira;
    FifoQT *fila;

    if(argc < 2){
        printf("Uso correto ./t1 <numero de processos>\n");
        return 0;
    }

    Pi = atoi(argv[1]);

    if (Pi < 0){
        printf("Numero de processos deve ser maior ou igual a 0\n");
        return 0;
    }

    // Cria as regiões de memória compartilhada
    int shm_id = shmget(IPC_PRIVATE, sizeof(barrier_t), IPC_CREAT | 0666);
    if (shm_id < 0)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    int shm_id_2 = shmget(IPC_PRIVATE, sizeof(FifoQT), IPC_CREAT | 0666);
    if (shm_id < 0)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Aloca o espaço na memória compartilhada para as structs
    barreira = (barrier_t *)shmat(shm_id, NULL, 0);
    fila = (FifoQT *)shmat(shm_id_2, NULL, 0);

    // Inicializa as structs
    init_barr(barreira, Pi);
    init_fifoQ(fila);

    // Seta o nProc do processo pai
    int nProc = 0;

    // Cria os processos
    for (int i = 1; i < Pi; i++){
        pid = fork();
        if (pid < 0) {
            perror("Fork falhou");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            nProc = i;
            break;
        }
    }

    // Gera uma seed para o rand diferente para cada processo
    srand(time(NULL) + getpid());
    int psleep = generate_rand();
    printf("PID: %d, PID Pai: %d, nProc: %d vai dormir por %d segundos\n", getpid(), getppid(), nProc, psleep);
    sleep(psleep);

    // Processa a barreira
    process_barrier(barreira);

    // For para os usos
    for (int uso = 0; uso < 3; uso++)
    {
        // (A) simula executar algo no (prologo)
        int time = generate_rand();
        printf("Processo: %d Prologo: %d de %d segundos\n", nProc, uso, time);
        sleep(time);
        // entra na fila de espera FIFO
        espera(fila);

        // (B) simula usar o recurso com exclusividade
        time = generate_rand();
        printf("Processo: %d USO: %d por %d segundos\n", nProc, uso, time);
        sleep(time);

        liberaPrimeiro(fila);

        // (C) simula executar algo (epilogo)
        time = generate_rand();
        printf("Processo: %d Epilogo: %d de %d segundos\n", nProc, uso, time);
        sleep(time);
    }

    // Processo pai espera os filhos terminarem
    if (nProc == 0) {
    for (int i = 0; i < Pi; i++)
        {
            wait(NULL);
        }
    }

    // Libera as memórias alocadas
    shmdt(barreira);
    shmdt(fila);
    shmctl(shm_id, IPC_RMID, NULL);
    shmctl(shm_id_2, IPC_RMID, NULL);

    return 0;
}