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

### MATRIZES 500*500; 16 threads: (em média com 3 execuções)<br>
Inicialização: 0,000825 segundo<br>
Processamento: 0,206886 segundo<br>
Finalização: 0,001011 segundo<br>
<br>
Total: 0,208722 segundo<br> 
Ganho de desempenho usando lei de Amdahl:<br>
Tempo sequencial era 0,765962 segundo (vide lab2)<br>
<br>
G = Tseq/Tconc =  0,765962 / 0,208722 = 3,669771274<br>
Este resultado é menor que o ganho teórico estimado no lab2, que era igual a 14,39030954321181<br><br>

### MATRIZES 1000*1000;16 threads:<br><br>

Inicialização: 0,002718 segundo<br>
Processamento: 1,781358 segundo<br>
Finalização: 0,002363 segundo<br><br>

Total: 1,786439 segundo<br>
Ganho de desempenho usando lei de Amdahl:<br>
Tempo sequencial era 6,31557799 segundos<br>
G = Tseq/Tconc =  6,31557799 / 1,786439  = 3,535288912<br>
Este resultado é menor que o ganho teórico estimado no lab2, que era igual a 15,716636027666901<br><br>

### MATRIZES 2000*2000; 16 threads:<br>
Inicialização: 0,011765<br>
Processamento: 17,085341<br>
Finalização: 0,005672<br><br>

Total: 17,102778<br>
Ganho de desempenho usando lei de Amdahl:<br>
Tempo sequencial era 61,44012065 segundos<br>
G = Tseq/Tconc =  61,44012065 / 17,102778 = 3,592405903<br>
Este resultado é menor que o ganho teórico estimado no lab2, que era igual a 15.908414169455275<br>

### MATRIZES 500*500: uma thread<br>
Inicialização: 0,000767 segundo<br>
Processamento: 0,756127 segundo<br>
Finalização: 0.001970 segundo<br>
Total: 0,758864 segundo<br><br>

Ganho de desempenho:<br>
0,765962/0,758864 = 1,009353454<br><br>

### MATRIZES 1000*1000: uma thread<br>
Inicialização: 0,003148 segundo<br>
Processamento: 6,499287 segundos<br>
Finalização: 0,002377 segundo<br>
Total: 6,504812 segundos<br><br>

Ganho de desempenho:<br>
6,31557799/6,504812 = 0,970908611<br><br>

### MATRIZES 2000*2000: uma thread<br>
Inicialização: 0,012864 segundo<br>
Processamento: 63,219010 segundos<br>
Finalização: 0,005325 segundo<br>
Total: 63,237199 segundos<br><br>

Ganho de desempenho:<br>
61,44012065/63,237199 = 0,971582028<br><br> 

### MATRIZES 500*500: 2 threads<br>
Inicialização: 0,001085 segundo<br>
Processamento: 0,429296 segundo<br>
Finalização: 0,002230 segundo<br>
Total: 0,432611<br><br>

Ganho de desempenho:<br>
0,765962/0,432611 = 1,770555996<br><br>

### MATRIZES 1000*1000: 2 threads<br><br>

Inicialização: 0,003613 segundo<br>
Processamento: 4,681116 segundos<br>
Finalização: 0,001911 segundo<br><br>

Total: 4,68664 segundos<br>

Ganho de desempenho:<br>
6,31557799/4,68664 = 1,347570538<br><br> 

### MATRIZES 2000*2000: 2 threads<br><br>

Inicialização: 0,013661 segundo<br>
Processamento: 32,033461 segundos<br>
Finalização: 0,005445 segundo<br><br>

Total: 32,052567 segundos<br>

Ganho de desempenho:<br>
61,44012065/32,052567 = 1,916854916<br><br>  

Note que, com duas threads e matrizes 2000*2000, o ganho de desempenho foi de fato próximo de 2, possivelmente porque<br>
o sistema operacional de fato conseguiu executar as duas threads ao mesmo tempo, e porque os tempos adicionais de execução<br>
sequencial ficaram desprezíveis em relação ao tempo de multiplicação (concorrente) das matrizes.

A corretude da multiplicação de matrizes foi verificada usando (no windows) o comando fc (file compare) entre a solução sequencial e a concorrente, que não encontrou diferença em nenhum dos casos listados.
