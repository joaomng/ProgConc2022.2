# ProgConc2022.2
Repositório para os laboratórios de programação concorrente de 2022.2 na UFRJ

O arquivo lab6.c contém código para executar tres tipos de threads. Conforme enunciado no laboratório:<br>
Há uma variável global denominada x, acessada por diferentes threads: <br>
T1 modifica a variavel incrementando seu valor de 1 <br>
T2 lê a variável e a imprime na tela indicando se  ́é um valor par ou  ́ímpar <br>
T3 primeiro le a variável e a imprime na tela; faz um processamento “bobo” qualquer (mas significativo); e depois modifica a variavel <br>
escrevendo o valor do seu identificador de thread

Essas funcionalidades são implementadas usando o padrão de leitores/escritores, e o número de threads de cada tipo está nos #define no começo do código.

Para compilar:
gcc -o lab6 lab6.c -lpthread <br>
Para executar (linux):
./lab6.exe

Para executar no windows basta remover o ./
