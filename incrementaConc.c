//Nome: João Matheus Nascimento Gonçalves
//DRE: 120023786

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define NTHREADS  2 

typedef struct {
   int indice;
   float* vetor; 
} t_Args;


void *incrementa (void *arg) {
  t_Args *args = (t_Args *) arg;
  
  //incrementando as 5000 posições do vetor que competem à thread atual
  for (int i=args->indice;i<(args->indice+5000);i++){

    args->vetor[i] = args->vetor[i] * 1.1;

  }

  pthread_exit(NULL);
}


int main() {
  pthread_t tid_sistema[NTHREADS]; 
  int thread;
  t_Args *arg; 
  t_Args *arg2;

  float *vetor = (float *) malloc(10000*sizeof(float));
  if (vetor == NULL) {
    printf("--ERRO: malloc()\n"); exit(-1);
  }
  
  //preenchendo o vetor
  for(int i=0;i<10000;i++){
    vetor[i] = i+1; //só pros números serem diferentes, sem usar random 
  }
  
  //alocando e setando o valor dos argumentos
  arg = malloc(sizeof(t_Args));
  if (arg == NULL) {
    printf("--ERRO: malloc()\n"); exit(-1);
  }
  arg->indice = 0; 
  arg->vetor = vetor; 

  arg2 = malloc(sizeof(t_Args));
  if (arg2 == NULL) {
    printf("--ERRO: malloc()\n"); exit(-1);
  }
  arg2->indice = 5000; 
  arg2->vetor = vetor;
    
  if (pthread_create(&tid_sistema[0], NULL, incrementa, (void*) arg)) {
    printf("--ERRO: pthread_create()\n"); exit(-1);
  }

  if (pthread_create(&tid_sistema[1], NULL, incrementa, (void*) arg2)) {
    printf("--ERRO: pthread_create()\n"); exit(-1);
  }
  

  //esperando as threads terminarem
  for (thread=0; thread<NTHREADS; thread++) {
    if (pthread_join(tid_sistema[thread], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }
   
  free(arg);
  free(arg2);

  printf("As threads terminaram, testando alguns valores de cada thread:\n");
  printf("nota: com o vetor de 1 a 10001, os valores esperados sao: 1.1, 2.2, 3.3, 5501.1, 5502.2, 5503.3\n");
  printf("primeira thread: %.3f %.3f %.3f \nsegunda thread: %.3f %.3f %.3f", vetor[0], vetor[1], vetor[2], vetor[5000], vetor[5001], vetor[5002]);
  pthread_exit(NULL);
}
