#ifndef ABB_H
#define ABB_H

#include "no.h"

No *criaNoABB(char *palavra);
void imprimeArvoreABB(No *root, int nivel);
void liberaABB(No *r);
No* buscaABB(No* r, char *palavra);
int alturaABB(No *r);
void paddingABB( char ch, int n);
No *insereNoABB(No *raiz, No *novo);
No *removeNoABB(No *raiz, char *palavra);
int numeroNoABB(No *raiz);
#endif
