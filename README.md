ci1215 - Sistemas Operacionais - 
2o semestre de 2024    
por W.Zola/UFPR

## trabalho 1: barreira e fila FIFO para processos (v1.2)
----------------------------------
Histórico:
- v1.0 a versão inicial da especificação
- v1.1 apenas escrito corretamente a data de entrega
- v1.2 melhor especificado o que deve ser impresso
       no loop de usos dos recursos em ordem FIFO
      
----------------------------------  
Data do enunciado: 16/out/2024
Data da entrega: 30/out/2024 (será aproximadamente 2 semanas) 

Você pode fazer sozinho OU em dupla.
NÃO serão aceitos trabalhos com mais de 2 alunos.
---------------------------------

Objetivos:
// Trabalhar com processos, semaforos do SO,
// alocar e usar "shared memory" entre os processos,
// fazer implementação de 
//   - uma primitiva de barreira para
//     um conjunto de processos
//   - uma primitiva de fila FIFO para processos
//  Implementar tudo isso em um sistema de processos
//  e demonstrar que funciona

// Esse trabalho será composto de 2 partes
//   A parte A) 
//   deve implementar uma primitiva de barreira para
//     sincronizar um conjunto de processos
//     verificar a descriçao mais detalhada
//     dessa primitiva (estrutura e funcoes)
//     conforme descrito no 
//     "Exercício 7: barreira para processos"
//     
//   A parte B) 
//   deve implementar uma primitiva de fila FIFO 
//     para processos o mesmo conjunto de processos
//     verificar a descriçao mais detalhada
//     dessa primitiva (estrutura e funcoes)
//     conforme descrito no 
//     "Exercício 6: FIFO Queue de processos (versao 1.2)"
//     ou mais recente, caso exista
//
//   Juntar as duas partes no mesmo programa fonte
//   os processos devem executar 
//       a parte A) e depois a parte B)
//
//   Preparar um bom RELATORIO
//
//   Em breve poderemos colocar aqui mais detalhes
//   do que deve ser entregue, mas a especificacao
//   segue o que eh dito acima e nos exercicios
//     "Exercício 7: barreira para processos"
//     e
//     "Exercício 6: FIFO Queue de processos (versao 1.2)"
//     ou mais recente, caso exista
//
//   MAIS detalhes de implementação
//   ------------------------------
//   
//   O processo 0 e seus filhos deve funcionar como descrito acima
//   e nos exercicios de barreira de processos e fila fifo de processos
//
//   porém como o exercicio de fila fifo de processos era APENAS um exercicio
//   ele nao detalhou muito sobre o que os processos devem fazer
//   na parte da fila fifo. 
//   Entao esses detalhes sao apresentados ABAIXO: 
//       
   Ao sair da barreira os processos devem se dirigir a parte do codigo
que usa a fila fifo (como uma fila de uso de um recurso em ordem FIFO).
Como foi definido no exercicio o uso do recurso exclusivo em ordem FIFO
deve estar dentro de um loop e nesse loop os processos entram na fila FIFO. 
Ocorre que seria necessario algum processo liberar o primeiro da fila,
assim o primeiro a "entrar" deve passar direto e iniciar uso,
e ao terminar o uso deve sinalizar o fato chamando a funcao
liberaPrimeiro.
Note que o primeiro processo que passar pela funcao espera está "conceitualmente"
dentro da fila, mas na verdade ele estah usando.
 
- Simularemos o uso dos recursos com nas partes (A) (B) e (C)
  executando um sleep de tempo aleatório entre 1 e 3 segundos
  e imprimindo o numero logico do processo e quantos segundos vai dormir e
  se está usando o recurso ou se está na parte (A) (B) ou (C) do loop
  deve imprimir o numero da iteração do processo no uso do recurso.
  Cada processo deve usar o recurso 3 vezes no loop
  ou seja, passa 3 vezes no loop de uso FIFO.
  
  Pseudo-codigo com mais detalhe
  -------------------------------
  
  1) Processo pai cria estruturas compartilhadas,
     inicializa a barreira e a fila fifo,
     e cria os filhos
     
  2) Todos os processos chegam na barreira
     
  3) Ao acordar da barreira um processo deve se dirigir 
     ao loop de usos FIFO de recurso.
     
     // Processo Pi onde Pi é seu número lógico
     
     int uso;    // uso é variável local
     for( uso=0; uso<3; uso++ ) {  // esse é o loop de uso FIFO do recurso
                                   // deve usar somente 3 vezes o recurso
     
        // (A) simula executar algo no (prologo)
        - sorteia um inteiro aleatorio s (0,1,2 ou 3)
        imprime: printf( "Processo: %d Prologo: %d de %d segundos\n", Pi, uso, s );
        - dorme s segundos
        espera( &fila );  // entra na fila de espera FIFO
                          // ou passa direto se estiver vazia
                          // note que, conceitualmente
                          //  o primeiro que passar pela espera
                          //  estah DENTRO da fila, mas nao fica bloqueado
                          //  na espera, ele passa direto
                          
           // (B) simula usar o recurso com exclusividade
           - sorteia um inteiro aleatorio s (0,1,2 ou 3)
           imprime: printf( "Processo: %d USO: %d por %d segundos\n", Pi, uso, s );
           - dorme s segundos
        
        liberaPrimeiro( &fila );  // terminou de usar
                                  // ao chamar essa funcao o processo estah sinalizando
                                  // sua "saida" do uso
                                  // sinaliza e causa a liberacao do primeiro
                                  // da fila (caso haja processo esperando)
                                  
        // (C) simula executar algo (epilogo)                          
        - sorteia um inteiro aleatorio s (0,1,2 ou 3)
        imprime: printf( "Processo: %d Epilogo: %d de %d segundos\n", Pi, uso, s );
        - dorme s segundos
                                  
      }
  
      imprime: Processo Pi terminando
  



## Exercícios sobre semáforos
--------------------------

Problema FifoQ.txt  (versao 1.3)
------------------
Fila de processos (ou threads).
FIFO: First-In-First-Out

---------------------
Histórico: 
  versão 1.0        Inicial (exercicio)
  versao 1.1 a 1.3  Adições para falar sobre implementação
                    dessa fila em trabalho da disciplina
---------------------

- A implementacão de barreiras (e.g. barrier em pThreads) 
  não força nenhuma ordem à "saida" dos processos 
  que estão na barreira (nenhuma ordem no desbloqueio).

- Como visto, a definicão de semáforos também 
  nao exige ordem para a liberacão de processos que estão esperando em um semáforo. 
  Isso depende da implementacão do semaforo, 
  pondendo ser ordem: FIFO, LIFO, random, por prioridades... etc

Nesse exercício você deve implementar uma 
fila de processos (ou threads) usando semaforos 
comuns (contadores ou mutexes), que garantam a ordem FIFO na saida.
Sua implementacao deve garantir a ordem FIFO 
independentemente de como é a ordem do 
semáforo utilizado (i.e. não sabemos a ordem do semáforo).

Definir o tipo FifoQT que irá ser usada nas operacões 
abaixo para "enfileiramento" dos processos (ou threads).
Voce deve implementar no mínimo as funcões abaixo:

void espera( FifoQT *F )  // processo chamador deve esperar na fila F

void liberaPrimeiro( FifoQT *F ) // libera o primeiro processo que esteja  
                                // "esperando" na fila F

void init_fifoQ( FifoQT *F )  // inicializa uma fila F (prepara para uso)
                        // caso seja necessário colocar valores iniciais
                        // nas variáveis internas da FifoQ 
                        // (ex: inicializar os semaforos usados) 
                        
--------------------------------------------------
# Exemplo de uso
--------------

Suponha que existam n processos (ou threads) denominadas processos 
clientes (processos C1 até Cn). 
Esses processos necessitam usar um recurso no sistema,
MAS gostariamos que os processos usem esse recurso em ordem de "chegada"
ou seja, em ordem FIFO (ou também poderia ser chamado de ordem FCFS, 
FCFS = First Come First Served, ou seja, o primeiro a chegar é o primeiro
a ser servido).

Suponha que vamos controlar o uso do recurso 
compartilhado em ordem FIFO.
Para isso, suponha que temos uma fila global de processos
compartilhada entre os processos, 
usando as nossas funcoes que implementaremos 
(definidas ACIMA, no inicio dese texto).
Ou seja, 
- antes de usar o recurso um processo chama a funcao
  espera( &fila ), para esperar na fila em ordem de chegada.
- Se o recurso *nao* estiver sendo usado e a fila estiver vazia, 
  o processo nao espera, e inicia imediatamente o uso do recurso.
- Se o recurso estiver sendo usado e a fila estiver vazia, 
  o processo deve esperar na fila 
  (lembrando: a fila é em ordem FIFO).
- Quando um processo termina de usar o recurso, ele deve
  sinalizar a fila usando a funcao liberaPrimeiro( &fila )
  que vai liberar o uso do recurso ao primeiro processo 
  que estiver na fila.
  OBS: nesse caso, se nao tiver nenhum processo na fila
  nada acontece, se tiver algum o primeiro que chegou
  deve ser liberado (sai da fila) para usar o recurso.

Suponha que os processos clientes funcionem em um loop de trabalho 
conforme abaixo, executando algo antes (secao prologo), em seguida
usa o recurso controlado por nossa fila de processos e depois
executa outro código (secao epilogo).
Suponha que para usar o recurso em ordem FIFO os processos
chamam nossas funcoes :

     Pseudo código do processo Ci
     ----------------------------
     
     loop {
     
        // (A) executa algo (prologo)
        espera( &fila );  // entra na fila de espera FIFO
                          // ou passa direto se estiver vazia
                          // e recurso estiver disponível
                          
           // (B) usa o recurso com exclusividade
        
        liberaPrimeiro( &fila );  // terminou de usar
                                  // sinaliza a liberacao do primeiro
                                  // da fila (caso haja processo esperando)
                                  
        // (C) executa algo (epilogo)                          
                                  
      }
      
      // OBS: 
      // esse pseudo-codigo é APENAS uma idéia
      //   de como devem funcionar os processos
      //   para que saber como as funcoes da fila serão usadas
      //   e dessa maneira podemos codificaĺas como exercicio
      //
      //   Para implementação REAL no trabalho 1 
      //     esse pseudo-codigo incluirá mais detalhes
      //     para que voce codifique tudo em linguagem C
      //     e implemente o que for pedido no trabalho
        
-------------------------------------------

# OBSERVACOES finais:
-------------------

A parte 1 desse exercicio:

  Voce deve fazer APENAS
  as 3 funcoes enunciadas no inicio desse texto.
  Ou seja, espera(...), liberaPrimeiro(...) e
  init_fifoQ(...), 
  bem como definir o tipo FifoQT, assim:
  
    typedef struct fifoQ_s {
    
      // definir aqui o que vai na struct
      // podendo usar semaforo OU mutex
      
    } FifoQT;          // tipo FifoQueue 
  
A parte 2 desse exercicio: 
(nao precisa fazer a parte 2 agora!
poderiamos deixar isso para depois quando for implementar o TRABALHO!)

  A parte 2, deve ser feita no trabalho 1
  seria completar o codigo do processo
  (ou thread) cliente.
  Nele voce deve declarar tudo que for necessario,
  implementar TODO o programa incluindo essa parte 2
  (variaveis globais, SUAS funcoes fifo e qq outra
   funcao ou variavel necessaria para fazer 
   funcionar o problema)
   

## Exercícios sobre semáforos
--------------------------

# Problema barreira-para-processos.txt
------------------
- A biblioteca pthreads possui funções
  para que varias threads possam sincronizar entre si
  com estrutura(s) de barreira(s).
- Porém essa possibilidade de sincronização 
  não está disponível para sincronização entre
  processos   
- A implementacão de barreiras (e.g. barrier em pThreads) 
  não força nenhuma ordem à "saida" dos processos 
  que estão na barreira (nenhuma ordem no desbloqueio).

Nesse exercício você deve implementar estrutura de barreiras
para sincronização entre processos.
Voce deve assumir que nossas barreiras para processos, 
só funcionarão com um conjunto de processos "irmãos" e "pai".
Suponha temos n processos que irão sincronizar
em uma barreira B.
  Vamos numerar os processos com uma variável interna nProc que 
  indica o número lógico do processo
  - o processo com nProc=0 deve ser o processo pai de todos os outros
  - os processos com nProc=1 até nProc=n-1 
    devem ser filhos do processo com nProc=0
    
O processo 0 deve inicializar sua variável nProc e
criar uma área de memória compartilhada no SO
(ver infos sobre shared memory IPC nos links informados no curso).
Nessa área o processo 0 deve preencher sua estrutura de barreira,
com todas as veriáveis internas que serão compartilhadas
nessa estrutura, que forem necessárias para funcionamento da 
barreira de processos, incluindo semáforos do SO se necessário.

Voce deve fazer e chamar uma funçao para inicializar as
variaveis internas da barreira com o seguinte protótipo:

  void init_barr( barrier_t *barr, int n );
  onde: barr deve apontar para a barreira em shared memory
        que deve ser uma struct definida por voce
        com tipo barrier_t (ver ao final, abaixo)
        n deve indicar o numero total de processos
        (lidos da linha de comando)
         
# -ATENCAO: 
  A) nesse exercicio voce NAO precisa chamar as funcoes
     exatas da IPC de shared memory, basta indicar
     o que deve ser alocado na estrutura de barreira
     a ser alocada em shared memory.
  B) Quando formos implementar nosso trabalho 1
     provavelmente utilizaremos uma sincronização de barreira
     de processos, e aí sim, voce deverá chamar exatamente
     as funções de shared memory necessárias
     
Depois que o processo com nProc=0 aloca a barreira ele deve criar
seus n-1 processos filhos. Cada processo filho deve
"herdar" o "pointer" para a área de memória compartilhada
criada pelo processo pai. 
- A primeira coisa a ser feita por cada
  processo filho deve ser incializar seu valor de nProc a partir de alguma
  informação herdada do pai. 
- Uma vez incializado o nProc, cada processo deve
  imprimir na tela o seu PID, o PID do seu pai, 
  e seu valor de nProc (número lógico).
- Nesse ponto, se necessario, os processos filhos devem
  obter o pointer para a estrutura de barreira compartilhada
  pelo pai em "shared memory" (fazer attach da área compartilhada
  SE NECESSARIO, ou não, caso tenha sido "herdado" do pai e possa 
  simplesmente ser acessado)
- Por fim todos os n processos, devem inicializar um numero ns aleatorio
  no intervalo [0,n-1] e fazer um sleep de ns segundos, imprimindo na tela,
  antes de fazer o sleep, o seu numero nProc e quantos segundos irá dormir.
- Ao acordar do sleep cada processo dos n processos (incluindo o pai)
  deve chamar a funcao process_barrier, definida por voce, com o seguinte 
  protótipo:
  
    void process_barrier( barrier_t *barr );
    onde: barr deve apontar para a barreira em shared memory
 
    Ao chamar process_barrier cada processo deve esperar pelos outros
    em um semaforo do SO colocado na barreira para possibilitar tal espera.
    O último processo a chamar a função process_barrier deve 
    liberar todos os outros da espera no semaforo da barreira.
    
- Ao sair da barreira, cada processo deve 
  imprimir seu nProc e indicar que saiu da barreira.
     
Ao final, todos os processos devem terminar.


## OBSERVACOES finais:
-------------------

Para esse exercicio:

  Voce deve fazer APENAS
  as 2 funcoes enunciadas acima nesse texto
  e o codigo do programa principal
  (as chamadas de função que trabalham com "shared memory"
  voce pode deixar apenas indicado o que deve ser feito,
  todo o resto deve estar em codigo 
  mais perto possivel de "compilavel" em linguagem C)
 
  Além disso, declarar o tipo barrier_t, 
  seguindo o modelo abaixo e 
  implementando corretamente os campos que vão
  dentro da estrutura:
  
    typedef struct barrier_s {
    
      // definir aqui o que vai na struct
      // podendo usar semaforo do SO
      // e outras variaveis necessarias
      
    } barrier_t;          // tipo barrier_t 
  

   
   
      
                                               
        
        
        


