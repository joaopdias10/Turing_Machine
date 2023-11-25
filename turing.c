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

char *turing(nodo **lista, char *fita, int cabecote, int qf, int qatual){ //Primeira função feita - Só aceita deterministico
    while(qatual != qf){
        nodo *aux = lista[qatual];//Copia uma 'linha' da lista adjacente, a do estado inicial no começo
        for(;aux != NULL; aux = aux -> prox){//Enquanto existir uma proxima transição ele avança
            if(fita[cabecote] == aux -> troca[0]){//Se a letra no cabeçote for igual ao simbolo da transição a ser trocado ele avança
                fita[cabecote] = aux -> troca[2];//Troca a letra atual do cabeçote pela simbolo da transição
                qatual = aux -> estado;//Muda o estado atual para o estado de destino
                if(aux -> troca[4] == 'R'){//Cebeçote p/ direita
                    cabecote++;
                }
                if(aux -> troca[4] == 'L'){//Cabeçote p/ esquerda
                    cabecote--;
                }
                break;
            }
        }
        if(aux == NULL){//Se aux for nulo a lista chegou ao fim e não foi possivél nenhuma transição
            return NULL;
        }
    }

    return fita;
}

char *turingMachine(nodo **lista, char *fita, int cabecote, int qf, int qatual){ //Turing recursivo, aceita deterministico e não deterministico
    if(qatual == qf){//Chegou no estado final acabou
        return fita;
    }

    nodo *aux = lista[qatual];
    while (aux != NULL){
        if (fita[cabecote] == aux -> troca[0]){
            char *tape = strdup(fita); //Copia da fita para as alterações que rejeitam a palavra não altere outras transições que vão ser tentadas depois
            int head = cabecote; //Copia do cabeçote para que o cabeçote "original" não seja alterado por transições que serão rejeitadas
            tape[head] = aux->troca[2];

            if (aux->troca[4] == 'R'){
                head++;
            }

            if (aux->troca[4] == 'L'){
                head--;
            }
            //Até aqui msm esquema da função turing
            char *resultado = turingMachine(lista, tape, head, qf, aux->estado); //Aqui ele chama recursivamente, fazendo com que testemos as proximas possiveis transições

            if (resultado != NULL){//Se o resultado não for nulo quer dizer que por aqui é um caminho possivel e ele continua tentando ir pelo caminho atual
                return resultado;
            }
        }
        aux = aux -> prox;//Passa para prox trransição, isso força ele tentar todas transições possiveis de diferentes formas
    }

    return NULL;
}

