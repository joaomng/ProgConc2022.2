# ProgConc2022.2
Repositório para os laboratórios de programação concorrente de 2022.2 na UFRJ
## Lab5
Para compilar:
gcc -o lab5 lab5.c -lpthread

Para executar (no Linux):
./lab5.exe

Para executar no windows basta remover o ./

O arquivo lab5.c imprime, com uma implementação concorrente, as frases:<br>
1:"Seja bem-vindo!"<br>
2:"Sente-se por favor." <br>
3:"Fique a vontade." <br>
4:"Volte sempre!" <br>
De modo que uma thread diferente imprime cada uma das frases, e a frase 1 é sempre impressa primeiro, <br>
a frase 4 é sempre impressa por último, e as frases 2 e 3 podem ser impressas em qualquer ordem entre si, <br>
contanto que depois da frase 1 e antes da frase 4.<br>

Para isso, a thread1 usa uma variável de condição, dando broadcast para as threads 2 e 3 para que estas possam<br>
imprimir suas frases uma vez que a da thread 1 foi impressa.<br>
As threads 2 e 3, ao imprimir suas frases, incrementam a variável y, e a thread4 espera (através de um while) a<br>
variável tornar-se 2 (como foi inicializada como 0, ter y=2 significa que as threads 2 e 3 já executaram) para então <br>
imprimir sua frase.
