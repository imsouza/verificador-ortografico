#ifndef AVL_H
#define AVL_H

#include "no.h"

No *criaNo(char *palavra);
void liberaAVL(No* r);
No* busca(No* r, char *palavra);
int altura(No *r);
void padding(char ch, int n);
void imprimeAVL(No *root, int level);
int max(int a, int b);
int getFB(No *r);
No *rotacaoDireita(No *A);
No *rotacaoEsquerda(No *A);
No *insere(No *r, No* novo) ;
No *removeNo(No *raiz, char *palavra);
#endif
