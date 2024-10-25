#include "fifo/fifo.h"
#include "barrier/barrier.h"
#include <time.h>
#include <unistd.h>

int s(){
    return rand() % 3;
}

int main(){

    srand(0);
    //   1) Processo pai cria estruturas compartilhadas,
    //      inicializa a barreira e a fila fifo,
    //      e cria os filhos
    barrier_t *barreira;
    FifoQT* fila;
    //   2) Todos os processos chegam na barreira
        
    //   3) Ao acordar da barreira um processo deve se dirigir 
    //      ao loop de usos FIFO de recurso.

    // Processo Pi onde Pi é seu número lógico 
    int Pi;
    scanf("%d", &Pi);

    for(int i = 0; i < Pi; i++){
        for(int uso = 0; uso < 3; uso++){
                // (A) simula executar algo no (prologo)
                int time = s();
                printf( "Processo: %d Prologo: %d de %d segundos\n", i, uso, time);
                sleep(time);
                // entra na fila de espera FIFO
                // ou passa direto se estiver vazia
                // ote que, conceitualmente
                // o primeiro que passar pela espera
                // estah DENTRO da fila, mas nao fica bloqueado
                // na espera, ele passa direto

                // (B) simula usar o recurso com exclusividade
                time = s();
                printf( "Processo: %d USO: %d por %d segundos\n", i, uso, time);
                sleep(time);
                
                // liberaPrimeiro(&fila);
                // terminou de usar
                // ao chamar essa funcao o processo estah sinalizando
                // sua "saida" do uso
                // sinaliza e causa a liberacao do primeiro
                // da fila (caso haja processo esperando)
                                        
                // (C) simula executar algo (epilogo)                          
                time = s();
                printf( "Processo: %d Epilogo: %d de %d segundos\n", i, uso, time);
                sleep(time);                                  
            }
            printf("Processo %d terminando\n", i);
    }

    

}