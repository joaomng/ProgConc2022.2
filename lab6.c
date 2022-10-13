/* Nome:João Matheus Nascimento Gonçalves
DRE: 120023786*/


#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define X 2 //numero de threads t1
#define Y 3 //numero de threads t2
#define Z 4 //numero de threads t3



int x = 0;  //a variável que será modificada durante a execução
 
pthread_mutex_t mutex; //variável do lock 
pthread_cond_t cond_leit, cond_escr; //variáveis de condição

int leit=0; //contador de threads lendo
int escr=0; //contador de threads escrevendo


void InicLeit (int id) {
   pthread_mutex_lock(&mutex);
   printf("thread %d quer ler\n", id);
   while(escr > 0) { //escr >0 significa que há thread escrevendo
     printf("thread %d bloqueou\n", id);
     pthread_cond_wait(&cond_leit, &mutex); //espera a thread parar de escrever
     printf("thread %d desbloqueou\n", id);   
   }
   leit++; //agora que não tem thread escrevendo, pode ler
   pthread_mutex_unlock(&mutex);
}


//saida leitura
void FimLeit (int id) {
   pthread_mutex_lock(&mutex);
   printf("thread %d terminou de ler\n", id);
   leit--; //sinaliza que terminou de ler para eventuais threads de escrita poderem executar...
   if(leit==0) pthread_cond_signal(&cond_escr); //...caso leit chegue a zero
   pthread_mutex_unlock(&mutex);
}


//entrada escrita
void InicEscr (int id) {
   pthread_mutex_lock(&mutex);
   printf("thread %d quer escrever\n", id);
   while((leit>0) || (escr>0)) { //não pode haver thread lendo nem escrevendo na hora da escrita
     printf("thread %d bloqueou\n", id);
     pthread_cond_wait(&cond_escr, &mutex); //espera todas as eventuais threads de leitura e escrita
     printf("thread %d desbloqueou\n", id);
   }
   escr++; //para sinalizar que há thread escrevendo

   pthread_mutex_unlock(&mutex);
}

//saida escrita
void FimEscr (int id) {
   pthread_mutex_lock(&mutex);
   printf("thread %d terminou de escrever\n", id);
   escr--; //para sinalizar que a thread não está mais escrevendo
   pthread_cond_signal(&cond_escr);
   pthread_cond_broadcast(&cond_leit);
   pthread_mutex_unlock(&mutex);
}


void* thread1(void *id){

   int *ident = (int *) id; //ponteiro para inteiro 
   InicEscr(*ident);   //começa a escrita
   
    printf("thread %d (T1) vai incrementar x, de %d para %d\n", *ident, x, x+1);
    x += 1;
    printf("thread %d (T1)incrementou, x agora eh %d\n",*ident, x);
    FimEscr(*ident); //termina a escrita

    pthread_exit(NULL);
}


void* thread2(void *id){
    
    int *ident = (int *) id; //ponteiro para inteiro

    InicLeit(*ident); //inicia a leitura

    if(x%2){ //ímpar, pq resto é 1
      printf("x e impar: %d\n", x);
    }
    else{
        printf("x e par: %d\n", x);
    }

    FimLeit(*ident); //termina a leitura

    pthread_exit(NULL);
}


void* thread3(void*id){
    int j=0;//variavel para o processamento "bobo"
    int *ident = (int *) id; //ponteiro para inteiro
    
    InicLeit(*ident); //inicia a leitura

    printf("(thread %d (T3)) Valor de x: %d\n",*ident, x); 
    for(int i=0;i<1000000;i++){//processamento "bobo"
        
        j += 1;
    }
    
    FimLeit(*ident); //termina a leitura

    //escrita:

    InicEscr(*ident); //inicia a escrita

    printf("thread %d (T3)vai escrever sua id em x, que no momento eh %d\n", *ident, x);

    x = *ident;
    printf("thread %d (T3) escreveu, agora x tem o valor %d\n", *ident, x);//os dois valores printados devem ser iguais

    FimEscr(*ident); //termina a escrita

    pthread_exit(NULL);
}




int main(){
    
    

    //declarando os vetores para os tres tipos de threads
    pthread_t t1[X]; 
    pthread_t t2[Y];
    pthread_t t3[Z];

    int i; //variável auxiliar 
    int ids[X+Y+Z];
    for(i=0;i<(X+Y+Z);i++){
      ids[i] = i+1;
    } 
  

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_leit, NULL);
    pthread_cond_init(&cond_escr, NULL);

    printf("Threads de %d a %d sao T1, de %d a %d sao T2, de %d a %d sao T3\n", 1, X, X+1, X+Y, X+Y+1, X+Y+Z);

    for(i=0;i<X;i++){

        pthread_create(&t1[i], NULL, thread1, (void*) &ids[i]); //cria a thread e chama a função para a thread tipo 1
        //*id = (*id)+1; // incrementa a id para a próxima chamada

    }
    //printf("\nchamou todas as T1, id = %d\n" , *id);

    for(i=0;i<Y;i++){

        pthread_create(&t2[i], NULL, thread2, (void*) &ids[X+i]); //cria a thread e chama a função para a thread tipo 2
        //*id = (*id)+1; // incrementa a id para a próxima chamada
    }
    // printf("\nchamou todas as T2, id = %d\n" , *id);
    

    for(i=0;i<Z;i++){
        pthread_create(&t3[i], NULL, thread3, (void*) &ids[X+Y+i]); //cria a thread e chama a função para a thread tipo 3
        //*id = (*id)+1; // incrementa a id para a próxima chamada
    }
    printf("chamou todas as Threads\n");

    for(i=0;i<X;i++){
      pthread_join(t1[i],NULL);
    }
    
    for(i=0;i<Y;i++){
      pthread_join(t2[i],NULL);
    }
    
     for(i=0;i<Z;i++){
      pthread_join(t3[i],NULL);
    }


    printf("\nFIM");
    return 0;
}