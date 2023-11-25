#include <stdio.h>
#include <string.h>

typedef struct nodo{
    int estado;
    char troca[5];
    struct nodo *prox;
} nodo;

nodo *insere(nodo *lista, char *mov, int est){ //Cria e incremente na lista ligada
    if(lista == NULL){
        nodo *novo = (nodo*)malloc(sizeof(nodo));
        strcpy(novo->troca, mov);
        novo -> estado = est;
        novo -> prox = lista;
        return novo;
    }
    lista -> prox = insere(lista -> prox, mov, est);
    return lista;
}

char *turing(nodo **lista, char *fita, int cabecote, int qf, int qatual){ //Primeira fun��o feita - S� aceita deterministico
    while(qatual != qf){
        nodo *aux = lista[qatual];//Copia uma 'linha' da lista adjacente, a do estado inicial no come�o
        for(;aux != NULL; aux = aux -> prox){//Enquanto existir uma proxima transi��o ele avan�a
            if(fita[cabecote] == aux -> troca[0]){//Se a letra no cabe�ote for igual ao simbolo da transi��o a ser trocado ele avan�a
                fita[cabecote] = aux -> troca[2];//Troca a letra atual do cabe�ote pela simbolo da transi��o
                qatual = aux -> estado;//Muda o estado atual para o estado de destino
                if(aux -> troca[4] == 'R'){//Cebe�ote p/ direita
                    cabecote++;
                }
                if(aux -> troca[4] == 'L'){//Cabe�ote p/ esquerda
                    cabecote--;
                }
                break;
            }
        }
        if(aux == NULL){//Se aux for nulo a lista chegou ao fim e n�o foi possiv�l nenhuma transi��o
            return NULL;
        }
    }

    return fita;
}

char *turingMachine(nodo **lista, char *fita, int cabecote, int qf, int qatual){ //Turing recursivo, aceita deterministico e n�o deterministico
    if(qatual == qf){//Chegou no estado final acabou
        return fita;
    }

    nodo *aux = lista[qatual];
    while (aux != NULL){
        if (fita[cabecote] == aux -> troca[0]){
            char *tape = strdup(fita); //Copia da fita para as altera��es que rejeitam a palavra n�o altere outras transi��es que v�o ser tentadas depois
            int head = cabecote; //Copia do cabe�ote para que o cabe�ote "original" n�o seja alterado por transi��es que ser�o rejeitadas
            tape[head] = aux->troca[2];

            if (aux->troca[4] == 'R'){
                head++;
            }

            if (aux->troca[4] == 'L'){
                head--;
            }
            //At� aqui msm esquema da fun��o turing
            char *resultado = turingMachine(lista, tape, head, qf, aux->estado); //Aqui ele chama recursivamente, fazendo com que testemos as proximas possiveis transi��es

            if (resultado != NULL){//Se o resultado n�o for nulo quer dizer que por aqui � um caminho possivel e ele continua tentando ir pelo caminho atual
                return resultado;
            }
        }
        aux = aux -> prox;//Passa para prox trransi��o, isso for�a ele tentar todas transi��es possiveis de diferentes formas
    }

    return NULL;
}

