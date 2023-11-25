#include <stdio.h>
#include <string.h>

typedef struct nodo{
    int estado;
    char troca[5];
    struct nodo *prox;
} nodo;

nodo *insere(nodo *lista, char *mov, int est);

char *turing(nodo **lista, char *fita, int cabecote, int qf, int qatual);

char *turingMachine(nodo **lista, char *fita, int cabecote, int qf, int qatual);
