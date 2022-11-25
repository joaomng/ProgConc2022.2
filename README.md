# ProgConc2022.2
Repositório para os laboratórios de programação concorrente de 2022.2 na UFRJ

## Laboratório 8

O arquivo java acima é uma aplicação que implementa o padrão produtores/consumidores, onde o "buffer" compartilhado é um vetor de "Dado", uma classe que encapsula um inteiro, que também pode ser nulo (tem um atributo booleano chamado "nulo"). <br>
Os produtores, ao serem iniciados, ficam tentando inserir "Dados" no buffer, enquanto os consumidores ficam tantando retirar.
Há quatro casos de teste, e para mudar entre eles, basta descomentar ou comentar as seções de código correspondente. Atualmente, se o arquivo for compilado e executado sem alterações, é o primeiro caso de teste que será executado.
