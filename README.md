# ProgConc2022.2
Repositório para os laboratórios de programação concorrente de 2022.2 na UFRJ
## LAB3

O código nesta seção do repositório gera matrizes, e as multiplica de forma concorrente, com tomada de tempo de execução.
Para compilar o arquivo geraMatrizBinario.c:
gcc -o geraMatriz geraMatrizBinario.c 

Para executar:
(no Linux)
./geraMatriz linhas colunas arquivodesaida.bin
Onde “linhas” é o número de linhas da matriz;
“colunas” é o número de colunas;
E “arquivodesaida” é o nome desejado para o arquivo de saída, necessariamente um arquivo binário.

Para executar no windows basta remover o “./”

Para compilar o arquivo multiplicaConc.c:
gcc -o multiplicaConc multiplicaConc.c -pthread
Nota: para compilar no windows é necessário, no arquivo, “timer.h”, trocar o “#include <sys/time.h>” por “#include <time.h>” 

Para executar:
(no Linux)
./multiplicaConc matriz1.bin matriz2.bin arquivodesaida.bin nthreads
Onde “matriz1” é o nome do arquivo que contém a primeira matriz;
“matriz2” é o nome do arquivo que contém a segunda matriz;
“arquivodesaida” é o nome desejado para o arquivo de saída onde será escrito o resultado de matriz1*matriz2, necessariamente um arquivo binário;
E nthreads é um inteiro, o número de threads desejado na execução

Ao executar, será exibido na tela o tempo de execução para cada segmento do programa (inicialização, processamento e finalização)

Para executar no windows basta remover o “./”


### INFORMAÇÕES DE DESEMPENHO:

MATRIZES 500*500:

Inicialização: 
0.003611 segundo

Processamento:
0.76025 segundo

Finalização:
0.002101 segundo

Ganho de desempenho teórico usando lei de Amdahl:
Nota: usei um processador de 16 threads
G = Tseq/Tconc ~=  (0.003611 + 0.76025 + 0.002101) / (0.003611 + 0.76025/16 + 0.002101) = 14.39030954321181


MATRIZES 1000*1000:

Inicialização: 
0.004013 segundo

Processamento:
6.30399166 segundos

Finalização:
0.00357333 segundo

Ganho de desempenho teórico usando lei de Amdahl:
G = Tseq/Tconc ~=  (0.004013 + 6.30399166 + 0.00357333) / (0.004013 + 6.30399166/16 + 0.00357333) =  15.716636027666901

MATRIZES 2000*2000:

Inicialização: 
0.015514666 segundo

Processamento:
61.41653966 segundos

Finalização:
0.008066333 segundo

Ganho de desempenho teórico usando lei de Amdahl:
G = Tseq/Tconc ~=  (0.015514666 + 61.41653966 + 0.008066333) / (0.015514666 + 61.41653966/16 + 0.008066333) =  15.908414169455275


A corretude da multiplicação de matrizes foi verificada usando a biblioteca LinearAlgebra da linguagem Julia e realizando a multiplicação de matrizes com a operação A*B (onde A e B são as matrizes)

