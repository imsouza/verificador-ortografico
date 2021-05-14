#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "util.h"

No *criaNoABB (char *palavra) {
  No *novo = mallocSafe (sizeof(No));
  novo->dado = mallocSafe ((strlen(palavra) + 1) * sizeof(char));
  strcpy(novo->dado, palavra);
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}


void paddingABB (char ch, int n){
  for (int i = 0; i < n; i++ )
    putchar(ch);
}


void imprimeArvoreABB (No *root, int nivel){
  if ( root == NULL ) {
    paddingABB('\t', nivel );
    puts("~");
  } else {
    imprimeArvoreABB ( root->dir, nivel + 1 );
    paddingABB('\t', nivel );
    printf("%s\n", root->dado );
    imprimeArvoreABB ( root->esq, nivel + 1 );
  }
}


char *getPalavra (No *root) {
  return root->dado;
}


void liberaABB (No *r) {
  if(r != NULL) {
    liberaABB(r->esq);
    liberaABB(r->dir);
    free(r->dado);
    free(r);
  }
}


No* buscaABB (No* r, char *palavra) {
  if (r == NULL || strcmp(r->dado, palavra) == 0) {
    return r;
  } if (strcmp(r->dado, palavra) > 0) {
    return buscaABB(r->esq , palavra);
  } else {
    return buscaABB(r->dir, palavra);
  }
}


int alturaABB (No *r) {
  if(r == NULL) {
    return -1;
  }

  int hSAE = alturaABB(r->esq);
  int hSAD = alturaABB(r->dir);

  if (hSAE > hSAD) {
    return hSAE + 1;
  } else {
    return hSAD + 1;
  }
}


int numeroNoABB (No *raiz) {
  if (raiz == NULL) {
    return 0;
  } else {
    return numeroNoABB(raiz->esq) + numeroNoABB(raiz->dir) + 1;
  }
}


No *insereNoABB (No *raiz, No *novo) {
  if(raiz == NULL) {
    return novo;
  } if(strcmp(raiz->dado, novo->dado) > 0) {
    raiz->esq = insereNoABB(raiz->esq, novo);
  } else {
    raiz->dir = insereNoABB(raiz->dir, novo);
  }

  return raiz;
}


No *removeNoABB (No *raiz, char *palavra) {
  No *pai = NULL;
  No *atual = raiz;

  while (atual != NULL && strcmp(atual->dado, palavra) != 0) {
    pai = atual;

    if (strcmp(atual->dado, palavra) > 0) {
      atual = atual->esq;
    } else {
      atual = atual->dir;
    }
  }

  if (atual == NULL) {
    printf("Palavra não encontrada!\n");
    return raiz;
  }
  
  if (atual->dir == NULL && atual->esq == NULL) {
    if(atual != raiz) {
      if(pai->esq == atual) {
        pai->esq = NULL;
      } else {
        pai->dir = NULL;
      }
    } else {
      raiz = NULL;
    }

    free(atual);
  }

  else if (atual->dir == NULL) {
    if(atual != raiz){ 
      if(pai->esq == atual) {
        pai->esq = atual->esq;
      }
      else {
        pai->dir = atual->esq;
      }
    } else {
      raiz = atual->esq;
    }

    free(atual);
  }

  else if (atual->esq == NULL) {
    if (atual != raiz) { 
      if(pai->esq == atual) {
        pai->esq = atual->dir;
      } else {
        pai->dir = atual->dir; 
      }
    } else {
      raiz = atual->dir;
    }

    free(atual);
  }

  else {
    No *t = atual->esq;
    pai = NULL;

    while (t->dir != NULL) {
      pai = t;
      t = t->dir;
    }

    if (pai != NULL) {
      pai->dir = t->esq;
    } else {
      atual->esq = t->esq;
    }

    strcpy(atual->dado, t->dado);
    free(t);
  }

  return raiz;
}
