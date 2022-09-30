//Nome: João Matheus Nascimento Gonçalves
//DRE:120023786

#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


int getIndice(int i, int j, int linhas, int colunas){
    /*função que recebe o indice i,j desejado na matriz,
    bem como suas dimensoes, e retorna o valor do indice 
    na representação da matriz como um vetor de números
    (em vez de vetor de vetores de numeros)*/
    return i*colunas+j;
}

typedef struct { //struct para os argumento a serem passados para as threads
    float* matriz1;
    float* matriz2;
    float* resultado;
    int linhas1;
    int colunas1;
    int linhas2;
    int colunas2;

    int col_saida_init;  //em qual coluna devo começar a escrever na matriz de resultado
    int col_saida_fim;   // numero de colunas a partir do inicio em que vou escrever na matriz de resultado
    

}t_args;

void* multiplicaConc(void* args){
   /*função que recebe a primeira matriz, seu número de linhas e de colunas, 
   a segunda matriz, seu número de linhas e de colunas, a matriz de resultado,
   e as colunas que deve escrever na matriz de resultado; 
   e escreve parte de matriz1*matriz2 na sua parte correspondente da
   matriz de resultado.
   Nota: O método usado preenche a matriz resultado uma COLUNA de cada vez,
   em vez de linha.
    */
    int indice,indice2,indice3; 
    //pegando os argumentos
    t_args* arg = (t_args*) args;
    float* matriz1 = arg->matriz1;
    float* matriz2 = arg->matriz2;
    float* resultado =arg->resultado ;
    int linhas1 = arg->linhas1;
    int colunas1 = arg->colunas1;
    int linhas2 = arg->linhas2;
    int colunas2 = arg->colunas2;
    
    //efetivamente multiplicando (parte das) matrizes
    for(int j=arg->col_saida_init;j<arg->col_saida_fim;j++){
        for (int i=0;i<linhas1;i++){
            indice = getIndice(i,j,linhas1,colunas2);
            resultado[indice] = 0;
            //resultado[i][j] = 0
            for(int k=0; k<colunas1;k++){
                indice2 = getIndice(i,k,linhas1,colunas1);
                indice3 = getIndice(k,j,linhas2,colunas2);
                resultado[indice] += matriz1[indice2] * matriz2[indice3];
                //resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    pthread_exit(NULL);

}


int main(int argc, char*argv[] ){

    float* matriz1;
    float* matriz2;
    float* resultado;
    int linhas1, colunas1, linhas2, colunas2, i, j, col_saida_init, intervalo;
    int nthreads = atoi(argv[4]);
    pthread_t threads[nthreads];
    FILE* arq_saida; 
    FILE* arq_matriz1;
    FILE* arq_matriz2;
    double start, finish, elapsed;
    t_args** argumentos;
    GET_TIME(start);
    //alocação da struct de argumentos
    argumentos = (t_args **) malloc(sizeof(t_args*)*nthreads);
    if (argumentos==NULL){
        printf("\nerro na alocacao da struct de argumentos para a thread");
        return 1;
    }    

    for (i=0;i<nthreads;i++){
        argumentos[i] = (t_args*) malloc(sizeof(t_args));
        if (argumentos[i]==NULL){
            printf("\nerro na alocacao da struct de argumentos para a thread");
            return 1;
        }    
    }

    //caso o usuário não tenha colocado os argumentos necessários
    if (argc <4){
        fprintf(stderr, "digite %s <matriz1> <matriz2> <arquivo de saida> <numero de threads> na linha de comando", argv[0]);
        return 1;
    }
    
    arq_matriz1 = fopen(argv[1], "rb");
    //le a primeira matriz
    fread(&linhas1, sizeof(int), 1, arq_matriz1);
    fread(&colunas1, sizeof(int), 1, arq_matriz1);

    //printf("linhas: %d; colunas: %d", linhas1, colunas1);
    
    matriz1 = (float*) malloc(sizeof(float)* linhas1 * colunas1);
    if(matriz1 == NULL){
        printf("erro na alocacao da primeira matriz!");
        return 1;
    }
    fread(matriz1, sizeof(float), linhas1 * colunas1, arq_matriz1);
    fclose(arq_matriz1);
    
    /*
    printf("\n matriz1 a seguir: ");
    for (i=0;i<(linhas1*colunas1);i++){
        if (i%colunas1 == 0){
            printf("\n");
        }
        printf("%f ", matriz1[i]);
    }*/

    arq_matriz2 = fopen(argv[2], "rb");
    //le a segunda matriz
    fread(&linhas2, sizeof(int), 1, arq_matriz1);
    fread(&colunas2, sizeof(int), 1, arq_matriz1);
    //printf("\nlinhas: %d; colunas: %d", linhas2, colunas2);


    
    matriz2 = (float*) malloc(sizeof(float)* linhas2 * colunas2);
    if(matriz2 == NULL){
        printf("erro na alocacao da segunda matriz!");
        return 1;
    }
    fread(matriz2, sizeof(float), linhas2 * colunas2, arq_matriz2);
    fclose(arq_matriz2);
    
    //aloca memória para a matriz de resultado
    resultado = (float *) malloc(sizeof(float)*linhas1*colunas2);
    if (resultado==NULL){
        printf("\nerro na alocacao da matriz de resultado!");
        return 1;
    }    

    GET_TIME(finish);
    elapsed = finish -start;
    printf("\ninicializacao levou %f segundos", elapsed);

    GET_TIME(start);
    intervalo = colunas2/nthreads; //se tivermos 10 colunas e 4 threads, cada thread fica com 10/4=2 colunas, exceto pela ultima
                                   //que fica com as duas mais o resto (portanto 4).
                                   // então a divisão pra cada thread fica 2,2,2,4
    col_saida_init = 0;
    for(i=0;i<nthreads;i++){
        argumentos[i]->matriz1 = matriz1;
        argumentos[i]->matriz2 = matriz2;
        argumentos[i]->resultado = resultado;
        argumentos[i]->linhas1 = linhas1;
        argumentos[i]->colunas1 = colunas1;
        argumentos[i]->linhas2 = linhas2;
        argumentos[i]->colunas2 = colunas2;

        argumentos[i]->col_saida_init = col_saida_init ;
        if(i == nthreads-1){ //se está no último laço, esta thread vai até o final da matriz
            argumentos[i]->col_saida_fim = colunas2;  
        }
        else {
          argumentos[i]->col_saida_fim = col_saida_init + intervalo; //caso normal: cada thread calcula colunas2/nthreads
                                                                     //da matriz de resultado
        }
        col_saida_init += intervalo;
        
        //chamando a função de multiplicar matrizes para a thread atual 
        if (pthread_create(&threads[i], NULL, multiplicaConc, (void*) argumentos[i])) {
             printf("--ERRO: pthread_create()\n"); exit(-1);
        }
        
    }

    //multiplicaMatriz(matriz1, linhas1, colunas1, matriz2, linhas2, colunas2, resultado);
    
    //espera as threads terminarem
    for(i=0;i<nthreads;i++){
        if(pthread_join(threads[i], NULL)){
            printf("Erro ao esperar a thread %d!", i);
            return 1;
        }
    }

    GET_TIME(finish);
    elapsed = finish - start;
    printf("\nprocessamento levou %f segundos", elapsed);
    /*
    printf("\n resultado a seguir: ");
    for (i=0;i<(linhas1*colunas2);i++){
        if (i%colunas2 == 0) 
            printf("\n");
        printf("%f ", resultado[i]);
    
    }*/
   
   
   GET_TIME(start);

   //escrevendo a matriz de resultado no arquivo de saída
   arq_saida = fopen(argv[3], "wb");
   fwrite(&linhas1, sizeof(int), 1, arq_saida);
   fwrite(&colunas2, sizeof(int), 1, arq_saida);
   fwrite(resultado, sizeof(float), linhas1*colunas2, arq_saida);
   fclose(arq_saida);

   GET_TIME(finish);
   elapsed = finish-start;
   printf("\nfinalizacao levou %f segundos", elapsed);

    return 0;
}