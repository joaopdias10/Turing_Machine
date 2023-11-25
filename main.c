#include <stdio.h>
#include <string.h>
#include "turing.h"

int main(){
    int n = 0, t = 0, i = 0, estado = 0, aux = 0;
    char *fita;
    char palavra[20] = {0};
    char troca[5] = {0};

    scanf("%d %d", &n, &t);

    nodo *lista[n];
    for(; n > i; i++){ //Inicializa a lista adjacente
        lista[i] = NULL;
    }

    for(i = 0;i < t;i++){ //Pega as transiçoes e salva em  uma lista ligada de transições do estado em questão
        scanf("%d %s %d", &aux, &troca, &estado);
        lista[aux] = insere(lista[aux], troca, estado);
    }

    scanf("%d", &aux);
    scanf("%d", &estado);

    while(1){//Onde a magica acontece
        scanf("%s", &palavra);

        if(strcmp(palavra, "*") == 0){
            break;
        }
        printf("%s ", palavra);
        strcat(palavra, "bbbbb"); //Colocando branco na fita

        fita = turingMachine(lista, palavra, 0, estado, 0); //Salva a fita

        if(fita != NULL){ //Se a fita for valida, ele imprime a palavra sem o vazio, vulgo 'b'
            printf("aceita: ");
            for(i = 0 ;i < strlen(fita); i++){
                if(fita[i] != 'b'){
                    printf("%c", fita[i]);
                }
            }
        }

        if(fita == NULL){
            printf("rejeitada.");
        }

        printf("\n");
    }

    for(n--;n >= 0;n--){//Libera a memoria alocada
        free(lista[n]);
    }

    return 0;
}

