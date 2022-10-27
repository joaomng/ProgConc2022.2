/*Nome: João Matheus Nascimento Gonçalves 
DRE: 120023786*/ 
 
 
#include <stdio.h> 
#include <stdlib.h>  
#include <pthread.h> 
#include <semaphore.h> 

 
 

 
 
 
 
#define N 5  //número de elementos no buffer 
#define PROD 3 //número de produtores 
#define CONS 11 //número de consumidores 
 
int buffer[N]; 
int out=0;//, count=0;  //out é a posição de retirada do buffer 
      //count é a quantidade de elementos no vetor 
                     //não preciso do count? 
 
sem_t mutex, sem_cons, sem_prod; //exclusão mútua, condição de consumir e condição de produzir, respectivamente 
 
 
int Retira(){ 
   
  int elemento; 
       
  sem_wait(&sem_cons);      //espera para poder retirar 
  sem_wait(&mutex);         //garante exclusão mútua
  elemento = buffer[out];   //retira o elemento
  out = (out+1)%N;          //atualiza a posição de retirada

  /*count--; 
 
  if(count==0){ 
    //após o insere, teremos count = N 
   //sem_post(&sem_prod); 
  }*/ 

  if(out==0){//se voltou a zero, é porque já retiraram  
            //todos os elementos 
            //sabemos disto porque a inserção é feita com todos de uma vez 
 
   sem_post(&sem_prod); //como o buffer tá vazio, o produtor pode inserir 
  } 
 
  sem_post(&mutex); //sai da exclusão mútua
  return elemento; //retorna o elemento
 
} 
 
void Insere(int *elemento,int id){ 
 
 sem_wait(&sem_prod); //espera para poder inserir
 sem_wait(&mutex); //garante exclusão mútua
     
    for(int i=0;i<N;i++){ 
     buffer[i] = elemento[i]; //insere todos os elementos no buffer 
    } 
    printf("thread %d inseriu\n", id); 
    sem_post(&mutex); //o post do mutex aqui permite que alguns consumam  
                      //antes de terminar todos os posts para todos consumidores 
    
    
    for(int j=0; j<N;j++){ //sinalizo que N consumidores podem consumir 
      sem_post(&sem_cons);   //mesmo que haja mais que N consumidores, so há N posições no buffer
    }     //se houver menos que N consumidores, alguns poderão consumir mais de uma vez

  
 
 
 
} 
 
 
 
void* Produtor(void* args){ 
     
    int id = *(int *) args; 
    int* aleatorio = (int*) malloc(N*sizeof(int));

    while(1){ //para rodar até o ctrl c ou ctrl z
       
      for(int i=0; i<N;i++){ 
        aleatorio[i] = (rand())%1000; //coloco números aleatórios no vetor de elementos que
                                      //entrarão no buffer
      } 
 
      printf("thread %d quer inserir\n", id); 
      printf("\nElementos a serem inseridos pela thread %d:\n    ", id);
      for(int i=0;i<N;i++){

        printf("%d(t%d), ", aleatorio[i], id);// (t<id>) é para identificar a thread que quer inseri-los
      }
      printf("\n\n");
      Insere(aleatorio,id); //insiro os elementos
    

    }
 
 
 
 
 pthread_exit(NULL); 
} 
 
 
 
void* Consumidor(void* args){ 
    
    int id = *(int *) args; 
    int elemento; 

    while(1){ //para rodar até o ctrl c ou ctrl z
      printf("thread %d quer retirar\n", id); 
      elemento = Retira(); //retiro o elemento
      printf("thread %d retirou o elemento %d\n", id, elemento); 
    }
 
 pthread_exit(NULL); 
} 
 
 
int main(void){ 
  
 int i; 
 int **id = (int**) malloc((CONS+PROD)*sizeof(int*)); //ids a serem passadas como parâmetro 
 for(i=0;i<(CONS+PROD);i++){ 
  *(id+i) = (int*) malloc(sizeof(int)); //cada posição é um ponteiro 
 } 
 
    sem_init(&mutex,0,1);  //começa com 1 para a primeira thread que tentar conseguir usar
    sem_init(&sem_cons,0,0); //começa com porque precisa esperar que algum produtor libere
    sem_init(&sem_prod,0,1); //começa com 1 porque o primeiro produtor precisa poder inserir
 
    pthread_t consumidores[CONS]; //declaro as threads
    pthread_t produtores[PROD]; 
 
    for(i=0;i<PROD;i++){  //crio efetivamente as threads produtoras
     *(*(id+i)) = i; 
      pthread_create(&produtores[i],NULL,Produtor,(void *) *(id+i)); 
    } 
     
    for(i=0;i<CONS;i++){  //crio efetivamente as threads consumidoras 
     *(*(id+PROD+i)) = i; 
      pthread_create(&consumidores[i],NULL,Consumidor,(void *) *(id+PROD+i)); 
    } 
 
    for (i=0; i<PROD; i++) { 
    if (pthread_join(produtores[i], NULL)) { 
         printf("--ERRO: pthread_join() \n"); exit(-1);  
        } 
    } 
 
    for (i=0; i<CONS; i++) { 
    if (pthread_join(consumidores[i], NULL)) { 
         printf("--ERRO: pthread_join() \n"); exit(-1);  
       }   
    }    
 

     
 return 0; 
}