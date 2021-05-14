#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"
#include "util.h"


typedef struct nofila {
  char *dado;
  struct nofila *proximo;
} NoFila;

struct fila {
  NoFila *inicio;
  NoFila *fim;
  int n;
};


Fila *criaFila () {
  Fila *fila = mallocSafe (sizeof(Fila));
  fila->inicio = fila->fim = NULL;
  fila->n = 0;
  return fila;
}


void liberaFila (Fila *fila) {
  NoFila *aux = fila->inicio;

  while(aux) {
    NoFila *t = aux->proximo;
    free(aux->dado);
    free(aux);
    aux = t;
  }

  free(fila);
  fila = NULL;
}


int buscaFila (Fila *fila, char *palavra) {
  NoFila *aux = fila->inicio;
  int count = 0;

  while (aux) {
    if (strcmp(aux->dado, palavra) == 0) {
      count++;
    }

    aux = aux->proximo;
  }

  return count;
}


void enqueue (Fila *fila, char *palavra) {  
  NoFila *novo = mallocSafe (sizeof(NoFila));
  novo->dado = mallocSafe ((strlen(palavra) + 1) * sizeof(char));
  strcpy(novo->dado, palavra);
  novo->proximo = NULL;

  if(filaVazia(fila)) {
    fila->inicio = novo;
  }
  else {
    fila->fim->proximo = novo;
  }

  fila->fim = novo;
  fila->n++;
}


void printFila (Fila *fila) {
  if (!filaVazia(fila)) {
    NoFila *aux = fila->inicio;

    while(aux) {
      printf("%s ", aux->dado);
      aux = aux->proximo;
    }
    
    putchar('\n');
  }
}


void dequeue (Fila *fila) {
  if (!filaVazia(fila)) {
    NoFila *tmp = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    fila->n--;
    free(tmp->dado);
    free(tmp);
  }
}


char *front (Fila *fila){
  return fila->inicio->dado;
}


int filaVazia (Fila *fila) {
  return fila->n == 0; 
}


int tamanhoFila (Fila *fila) {
  return fila->n;
}
