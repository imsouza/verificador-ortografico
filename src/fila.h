#ifndef FILA_H
#define FILA_H

typedef struct fila Fila;

Fila *criaFila();
void liberaFila(Fila *fila);
void enqueue(Fila *fila, char *palavra);
void dequeue(Fila *fila);
char *front(Fila *fila);
int filaVazia(Fila *fila);
int tamanhoFila(Fila *fila);
void printFila(Fila *fila);
int buscaFila(Fila *fila, char *palavra);

#endif