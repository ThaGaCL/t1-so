#include "fifo/fifo.h"
#include "barrier/barrier.h"
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int s(){
    return rand() % 3;
}

int main(){
    srand(0);
    // Processo Pi onde Pi é seu número lógico 
    int Pi;
    pid_t pid;
    scanf("%d", &Pi);
    //   1) Processo pai cria estruturas compartilhadas,
    //      inicializa a barreira e a fila fifo,
    //      e cria os filhos
    barrier_t *barreira;
    FifoQT* fila = malloc(sizeof(FifoQT));
    init_fifoQ(fila);

    int shm_id = shmget(IPC_PRIVATE, sizeof(barrier_t), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    barreira = (barrier_t *)shmat(shm_id, NULL, 0);
    // Inicializar a barreira
    init_barr(barreira, Pi);
    //   2) Todos os processos chegam na barreira
        
    //   3) Ao acordar da barreira um processo deve se dirigir 
    //      ao loop de usos FIFO de recurso.



    for(int i = 0; i < Pi; i++){
        if((pid = fork()) == 0){
            int nProc = i + 1;
            for(int uso = 0; uso < 3; uso++){
                    // (A) simula executar algo no (prologo)
                    // int time = s();
                    // printf( "Processo: %d Prologo: %d de %d segundos\n", i, uso, time);
                    // sleep(time);
                    // entra na fila de espera FIFO
                    // ou passa direto se estiver vazia
                    // ote que, conceitualmente
                    // o primeiro que passar pela espera
                    // estah DENTRO da fila, mas nao fica bloqueado
                    // na espera, ele passa direto

                    // (B) simula usar o recurso com exclusividade
                    int time = s();
                    printf( "Processo: %d USO: %d por %d segundos\n", nProc, uso, time);
                    sleep(time);

                    process_barrier(barreira); // Chamar a barreira

                    // Esperar pelos processos filhos
                    // for (int i = 0; i < Pi; i++) {
                    //     wait(NULL);
                    // }

                    // liberaPrimeiro(&fila);
                    // terminou de usar
                    // ao chamar essa funcao o processo estah sinalizando
                    // sua "saida" do uso
                    // sinaliza e causa a liberacao do primeiro
                    // da fila (caso haja processo esperando)
                                            
                    // (C) simula executar algo (epilogo)                          
                    // time = s();
                    // printf( "Processo: %d Epilogo: %d de %d segundos\n", i, uso, time);
                    // sleep(time); 
                    printf("aaaaaaa\n");                                 
                }
                printf("Processo %d terminando\n", i);
                exit(0);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < Pi; i++) {
        wait(NULL);
    }

    shmdt(barreira);
    shmctl(shm_id, IPC_RMID, NULL);;

    free(fila);
    return 0;
}