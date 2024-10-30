#include "fifo/fifo.h"
#include "barrier/barrier.h"
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int s()
{
    return rand() % 3 + 1;
}

int main(int argc, char* argv[])
{
    // Processo Pi onde Pi é seu número lógico
    int Pi;
    pid_t pid;

    if(argc < 2){
        printf("Uso correto ./t1 <numero de processos>\n");
        return 0;
    }

    Pi = atoi(argv[1]);

    if (Pi < 0)
    {
        printf("Numero de processos deve ser maior ou igual a 0\n");
        return 0;
    }

    barrier_t *barreira;
    FifoQT *fila;

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

    barreira = (barrier_t *)shmat(shm_id, NULL, 0);
    fila = (FifoQT *)shmat(shm_id_2, NULL, 0);

    // Inicializar a barreira
    init_barr(barreira, Pi);

    // Inicializa fila
    init_fifoQ(fila);

    int nProc = 0;

    for (int i = 1; i < Pi; i++)
    {
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

    srand(time(NULL) + getpid());
    int psleep = s();
    printf("PID: %d, PID Pai: %d, nProc: %d vai dormir por %d segundos\n", getpid(), getppid(), nProc, psleep);
    sleep(psleep);

    process_barrier(barreira);

    for (int uso = 0; uso < 3; uso++)
    {
        // (A) simula executar algo no (prologo)
        int time = s();
        printf("Processo: %d Prologo: %d de %d segundos\n", nProc, uso, time);
        sleep(time);
        // entra na fila de espera FIFO
        espera(fila);

        // (B) simula usar o recurso com exclusividade
        time = s();
        printf("Processo: %d USO: %d por %d segundos\n", nProc, uso, time);
        sleep(time);

        liberaPrimeiro(fila);

        // (C) simula executar algo (epilogo)
        time = s();
        printf("Processo: %d Epilogo: %d de %d segundos\n", nProc, uso, time);
        sleep(time);
    }



// Parent waits for all children
if (nProc == 0) {
for (int i = 0; i < Pi; i++)
    {
        wait(NULL);
    }
}

shmdt(barreira);
shmdt(fila);
shmctl(shm_id, IPC_RMID, NULL);

return 0;
}