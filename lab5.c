/*Nome: João Matheus Nascimento Gonçalves
DRE: 120023786

Fazer variavel de condição pro fim da primeira thread;
Fazer uma variavel de controle, que as duas threads intermediárias
incrementam ao executar; a ultima thread so pode executar quando essa
variável tiver o valor 2.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 4 //número de threads

int x=0;
int y=0; //pras duas condições lógicas do programa
pthread_mutex_t x_mutex,y_mutex; //variaveis de exclusão mútua
pthread_cond_t x_cond; //variável de condição


void *thread1(void *args){

	printf("Seja bem-vindo!\n");

    pthread_mutex_lock(&x_mutex);  //pegando x e aumentando seu valor para sinalizar que já fez o print
    x++;
	pthread_cond_broadcast(&x_cond); //usa broadcast porque há duas threads esperando e ambas são liberadas
                                     //quando x=1
	pthread_mutex_unlock(&x_mutex);

	pthread_exit(NULL);
}


void *thread2(void *args){

    pthread_mutex_lock(&x_mutex);
    if (x<1){ //podemos usar if porque a condição é irreversível
    	pthread_cond_wait(&x_cond, &x_mutex);  //esperando a primeira thread fazer o print
    }
    pthread_mutex_unlock(&x_mutex);

	printf("Sente-se por favor.\n");

    pthread_mutex_lock(&y_mutex); //pegando y e incrementando para sinalizar que já fez um dos dois
                                  //prints necessários antes da última thread executar
    y++;
	pthread_mutex_unlock(&y_mutex);
    
	pthread_exit(NULL);
}


void *thread3(void*args){
     
    pthread_mutex_lock(&x_mutex);
    if (x<1){ //podemos usar if porque a condição é irreversível
    	pthread_cond_wait(&x_cond, &x_mutex); //esperando a primeira thread fazer o print

    }
    pthread_mutex_unlock(&x_mutex);

	printf("Fique a vontade.\n");
	

    pthread_mutex_lock(&y_mutex); //pegando y e incrementando para sinalizar que já fez um dos dois
                                  //prints necessários antes da última thread executar
    y++;
	pthread_mutex_unlock(&y_mutex);

    pthread_exit(NULL);
	
}

void *thread4(void*args){
    
    while(y<2){  //espera o y ser incrementado até 2
    	;        //não precisa de exclusão mútua aqui porque não escreve em y,
                 //e uma vez que y torna-se 2, esta thread está liberada para fazer seu print
                 //já que as threads 2 e 3 já fizeram seus prints.
    }
	printf("Volte sempre!\n");

	pthread_exit(NULL);
}




int main(){

    pthread_t threads[NTHREADS]; //criando o vetor de threads  

    pthread_mutex_init(&x_mutex,NULL);  //inicializando as variáveis de exclusão mútua e de condição
    pthread_mutex_init(&y_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);

    
    pthread_create(&threads[1], NULL, thread2, NULL);  //chamando as threads numa ordem propositalmente 
    pthread_create(&threads[0], NULL, thread1, NULL);  //diferente da ordem esperada de execução
    pthread_create(&threads[3], NULL, thread4, NULL);
    pthread_create(&threads[2], NULL, thread3, NULL);
    

    for (int i = 0; i < NTHREADS; i++) { //esperando todas as threads terminarem
        pthread_join(threads[i], NULL);
    }
     
  pthread_mutex_destroy(&x_mutex);  //desalocando as variaveis
  pthread_mutex_destroy(&y_mutex);
  pthread_cond_destroy(&x_cond);


	return 0;
}