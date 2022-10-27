# ProgConc2022.2
Repositório para os laboratórios de programação concorrente de 2022.2 na UFRJ


## Lab 7

O código no arquivo lab7.c usa semáforos para coordenar um certo número de produtores e consumidores que usam um buffer.<br>
O tamanho do buffer, a quantidade de produtores e de consumidores estão definidos nos #define no início do código.<br>
O código divide a execução em PROD+CONS threads, com PROD produtores e CONS conumidores, que ficam INDEFINIDAMENTE tentando<br>
inserir ou retirar no buffer. Ou seja, para "terminar", <b>o programa precisa de um ctrl+z(linux) ou ctrl+c(windows) </b>.<br>
Ao produzir/consumir ou mesmo tentar fazê-lo, são impressos logs na tela para informar o que está sendo feito e permitir<br>
verificação da corretude. Ainda assim, pela complexidade do problema, é possível ver logs que à primeira vista parecem indevidos<br>
mas que na verdade estão corretos.<br> <br>

Para compilar: 
gcc -o lab7 lab7.c -lpthread

Para executar: (Linux)
./lab7

Para executar:(Windows)
lab7.exe


