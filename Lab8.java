import java.util.Arrays;



class Produtor extends Thread{

    private int id;
    private Buffer buffer;
    private int qtd; //é a quantidade de vezes que o produtor vai tentar inserir no buffer

    public Produtor(int id, Buffer buffer,int qtd){ //construtor
        this.id = id;
        this.buffer = buffer;
        this.qtd = qtd;
    }

    public int get_id(){
        return this.id;
    }

    public void run(){ //gera qtd "Dados" e fica tentando inserir

        System.out.println("Produtor "+id+" vai entrar no for pra inserir");

        for (int i = 0; i < qtd; i++) {
            Dado dado = new Dado(i); //o número é i

            System.out.println("Produtor " + id + " vai tentar inserir " + dado.numero);
            buffer.inserir(dado, id);
            System.out.println("Produtor " + id + " conseguiu inserir " + dado.numero);
        }

    }
}


class Consumidor extends Thread{

    private int id;
    private Buffer buffer;
    private int qtd; //quantidade de vezes que o consumidor vai tentar retirar elementos do buffer

    public Consumidor(int id, Buffer buffer,int qtd){ //construtor
        this.id = id;
        this.buffer = buffer;
        this.qtd =qtd;
    }

    public int get_id(){
        return this.id;
    }

    public void run(){ //fica tentando retirar qtd vezes

        System.out.println("Consumidor "+id+" vai entrar no for pra retirar");
        for(int i=0;i<qtd;i++){


            System.out.println("Consumidor "+id+" vai tentar retirar");
            Dado dado = buffer.retirar(id);
            System.out.println("Consumidor "+id+" conseguiu retirar o numero " +dado.numero);



        }

    }
}



class Buffer { //é a classe cuja instância será compartilhada pelas threads


    Dado[] buffer; //Buffer.buffer é um vetor de Dados
    int length;
    int inseridos; //número de elementos no buffer no momento
    int in; //posição de inserção
    int out; //posição de retirada

    //de certa forma um construtor
    public void init(int tam){
        this.buffer = new Dado[tam];
        Arrays.fill(this.buffer, null);
        this.length = tam;
        inseridos = 0;
        in = 0;
        out = 0;
    }

    public synchronized void imprime(){


        for (Dado dado : buffer) { //"for each"

            if (dado.nulo) {
                System.out.println("nulo");
            } else {
                System.out.println(dado.numero);
            }
        }

    }

    public synchronized void inserir(Dado dado, int id){

        if(this.inseridos < this.length){//se houver alguma posição vazia podemos inserir
            buffer[in] = dado;//insere
            inseridos++; //mais um elemento foi inserido

            in = (in+1)%length;//muda o indice pra inserção

            this.notify(); //libera alguma eventual thread esperando pra retirar
        }

        else{

            try {
                while(inseridos==length) {//enquanto o buffer estiver cheio
                    System.out.println("Produtor "+id+" vai se bloquear");
                    this.wait();//se bloqueia
                }//se saiu do while é porque existe alguma posição vazia no buffer
                System.out.println("Produtor "+id+" foi liberado");
                buffer[in] = dado;//insere
                inseridos++; //mais um elemento foi inserido

                in = (in+1)%length;//muda o indice pra inserção

                this.notify(); //libera alguma eventual thread esperando pra retirar


            } catch (InterruptedException e) {
                e.printStackTrace();
            }




        }
    }

    public synchronized Dado retirar(int id){

        if(inseridos>0){//se houver algo no buffer

            Dado dado = new Dado(buffer[out].numero); //pegando o elemento da posição
            buffer[out].nulo = true; //"esvaziou a posição"
            out = (out+1)%length;//atualizando a posição de retirada
            inseridos--; //tem um elemento a menos no buffer agora
            this.notify(); //liberando eventual produtor na fila
            return dado; //retornando o dado
        }

        else{

            try {
                while(inseridos==0) {//enquanto o buffer estiver vazio
                    System.out.println("Consumidor "+id+" vai se bloquear");
                    this.wait();//bloqueia a thread
                }//se saiu do while é porque exoste algo no buffer
                System.out.println("Consumidor "+id+" foi liberado");

                Dado dado = new Dado(buffer[out].numero); //pegando o elemento da posição
                buffer[out].nulo = true; //"esvaziou a posição"
                out = (out+1)%length;//atualizando a posição de retirada
                inseridos--; //tem um elemento a menos no buffer agora
                this.notify(); //liberando eventual produtor na fila
                return dado; //retornando o dado

            } catch (InterruptedException e) {
                e.printStackTrace();
            }




        }

        return null; //só chega aqui se der exceção (mas não importa, porque já terá havido exceção)
    }






}


class Dado {


    //sempre inicia não-nulo, com um número, mas pode ter o atributo "nulo" mudado posteriormente
    public int numero;
    public boolean nulo;

    public Dado(int num){ //construtor
        this.numero = num;
        this.nulo = false;
    }
}




public class Lab8 { //a main está aqui



    public static void main(String[] args) {

        int produtores; //número de threads produtoras
        int consumidores;  //número de threads consumidoras
        int tam = 5;

        //criando o buffer
        Buffer buffer = new Buffer();
        buffer.init(tam);


        //(a): um produtor e um consumidor:
        Thread prod = new Produtor(0,buffer,10);//vai tentar inserir 10 itens
        Thread cons = new Consumidor(1,buffer,10);//vai tentar retirar 10 itens

        prod.start();
        cons.start();




        //espera pelo termino de todas as threads
        try { prod.join(); } catch (InterruptedException e) { return; }
        try { cons.join(); } catch (InterruptedException e) { return; }

        System.out.println("FIM");


        /*
        //(b) um produtor e varios consumidores:

        produtores = 1;
        consumidores = 4;

        Thread[] threads = new Thread[produtores+consumidores];
        for(int i = 0;i<produtores;i++){
            threads[i] = new Produtor(i,buffer,20); //vai tentar inserir 20 vezes
        }


        for(int i = produtores;i<produtores+consumidores;i++){ //as 4 ultimas posições sao consumidores
            threads[i] = new Consumidor(i,buffer,5); //vai tentar retirar 5 vezes
        }

        for(int i=0;i<produtores+consumidores;i++){
            threads[i].start();
        }

        for(int i=0;i<produtores+consumidores;i++){
            try { threads[i].join(); } catch (InterruptedException e) { return; }
        }
        System.out.println("FIM");
        */

        /*
        //(c) vários produtores e um consumidor


        produtores = 4;
        consumidores = 1;

        Thread[] threads = new Thread[produtores+consumidores];
        for(int i = 0;i<produtores;i++){
            threads[i] = new Produtor(i,buffer,5); //vai tentar inserir 5 vezes
        }


        for(int i = produtores;i<produtores+consumidores;i++){ //a última posição é consumidor
            threads[i] = new Consumidor(i,buffer,20); //vai tentar retirar 20 vezes
        }

        for(int i=0;i<produtores+consumidores;i++){
            threads[i].start();
        }

        for(int i=0;i<produtores+consumidores;i++){
            try { threads[i].join(); } catch (InterruptedException e) { return; }
        }
        System.out.println("FIM");


         */


        /*
        //(d) vários produtores e vários consumidores


        produtores = 5;
        consumidores = 5;

        Thread[] threads = new Thread[produtores+consumidores];
        for(int i = 0;i<produtores;i++){
            threads[i] = new Produtor(i,buffer,4); //vai tentar inserir 4 vezes
        }


        for(int i = produtores;i<produtores+consumidores;i++){ //a última posição é consumidor
            threads[i] = new Consumidor(i,buffer,4); //vai tentar retirar 4 vezes
        }

        for(int i=0;i<produtores+consumidores;i++){
            threads[i].start();
        }

        for(int i=0;i<produtores+consumidores;i++){
            try { threads[i].join(); } catch (InterruptedException e) { return; }
        }
        System.out.println("FIM");
        */

        buffer.imprime();
    }
}
