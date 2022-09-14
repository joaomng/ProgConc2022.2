#include "timer.h"
#include <stdlib.h>
#include <stdio.h>


int getIndice(int i, int j, int linhas, int colunas){
    /*função que recebe o indice i,j desejado na matriz,
    bem como suas dimensoes, e retorna o valor do indice 
    na representação da matriz como um vetor de números
    (em vez de vetor de vetores de numeros)*/
    return i*colunas+j;
}

void multiplicaMatriz(float* matriz1, int linhas1, int colunas1, float* matriz2, int linhas2, int colunas2, float* resultado){
   /*função que recebe a primeira matriz, seu número de linhas e de colunas, 
   a segunda matriz, seu número de linhas e de colunas, e a matriz de resultado; 
   e escreve matriz1*matriz2 na matriz de resultado.
   Nota: O método usado preenche a matriz resultado uma COLUNA de cada vez,
   em vez de linha.
    */
    int indice,indice2,indice3; 

    for(int j=0;j<colunas2;j++){
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

}


int main(int argc, char*argv[] ){

    float* matriz1;
    float* matriz2;
    float* resultado;
    int linhas1, colunas1, linhas2, colunas2, i, j;
    FILE* arq_saida; 
    FILE* arq_matriz1;
    FILE* arq_matriz2;
    double start, finish, elapsed;
    GET_TIME(start);

    if (argc <3){
        fprintf(stderr, "digite %s <matriz1> <matriz2> <arquivo de saida> na linha de comando", argv[0]);
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

    resultado = (float *) malloc(sizeof(float)*linhas1*colunas2);
    if (resultado==NULL){
        printf("\nerro na alocacao da matriz de resultado!");
        return 1;
    }    

    GET_TIME(finish);
    elapsed = finish -start;
    printf("\ninicializacao levou %f segundos", elapsed);

    GET_TIME(start);
    multiplicaMatriz(matriz1, linhas1, colunas1, matriz2, linhas2, colunas2, resultado);
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

   arq_saida = fopen(argv[3], "wb");
   fwrite(&linhas1, sizeof(int), 1, arq_saida);
   fwrite(&colunas2, sizeof(int), 1, arq_saida);
   fwrite(resultado, sizeof(float), linhas1*colunas2, arq_saida);
   fclose(arq_saida);

   GET_TIME(finish);
   elapsed = finish- start;
   printf("\nfinalizacao levou %f segundos", elapsed);

    return 0;
}