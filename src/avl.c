#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "util.h"


No *criaNo(char *palavra) {
  No *novo = mallocSafe (sizeof(No));
  novo->dado = mallocSafe ((strlen(palavra) + 1) * sizeof(char));
  strcpy(novo->dado, palavra);
  novo->esq = NULL;
  novo->dir = NULL;
  novo->altura = 0;
  return novo;
}


void liberaAVL (No* r) {
  if (r != NULL) {
    liberaAVL(r->esq);
    liberaAVL(r->dir); 
    free(r->dado);
    free(r);
  }
}


No* busca (No* r, char *palavra) {
  if (r == NULL || strcmp(r->dado, palavra) == 0) {
    return r;
  } if (strcmp(r->dado, palavra) > 0) {
    return busca(r->esq , palavra);
  } else {
    return busca(r->dir, palavra);
  }
}


int altura (No *r) {
  if (r == NULL) {
    return -1;
  }

  return r->altura;
}


void padding (char ch, int n){
  int i;

  for ( i = 0; i < n; i++ ) {
    putchar ( ch );
  }
}


void imprimeAVL (No *root, int level) {
  if ( root == NULL ) {
    padding ('\t', level );
    puts ("~" );
  } else {
    imprimeAVL(root->dir, level + 1);
    padding('\t', level);
    printf("%s\n", root->dado);
    imprimeAVL(root->esq, level + 1);
  }
}

int max (int a, int b) {
  return (a > b) ? a : b;
}


int getFB (No *r) {
  return altura(r->esq) - altura(r->dir);
}


No *rotacaoDireita(No *A) {
  No *B = A->esq;

  A->esq = B->dir;
  B->dir = A;

  A->altura = max(altura(A->esq), altura(A->dir)) + 1;
  B->altura = max(altura(B->esq), altura(B->dir)) + 1;

  return B;
}


No *rotacaoEsquerda (No *A) {
  No *B = A->dir;

  A->dir = B->esq;
  B->esq = A;

  A->altura = max(altura(A->esq), altura(A->dir)) + 1;
  B->altura = max(altura(B->esq), altura(B->dir)) + 1;

  return B;
}


No *insere (No *r, No* novo) {
  if (r == NULL) {
    return novo;
  } if (strcmp(r->dado, novo->dado) > 0) {
    r->esq = insere(r->esq, novo);
  } else {
    r->dir = insere(r->dir, novo);
  }

  r->altura = max(altura(r->esq), altura(r->dir)) + 1;

  int fb = getFB(r);

  //Rotação RR
  if (fb > 1 && strcmp(novo->dado, r->esq->dado) < 0) {
    return rotacaoDireita(r);
  }
  //Rotação LL
  if (fb < -1 && strcmp(novo->dado, r->dir->dado) > 0) {
    return rotacaoEsquerda(r);
  }
  //Rotação LR
  if (fb > 1 && strcmp(novo->dado, r->esq->dado) > 0) {
    r->esq = rotacaoEsquerda(r->esq);
    return rotacaoDireita(r);
  }
  //Rotação RL
  if (fb < -1 && strcmp(novo->dado, r->dir->dado) < 0) {
    r->dir = rotacaoDireita(r->dir);
    return rotacaoEsquerda(r);
  }

  return r;
}


No *removeNo(No *raiz, char *palavra) {
  if (raiz == NULL) {
    return NULL;
  } else if (strcmp(raiz->dado, palavra) > 0) {
    raiz->esq = removeNo(raiz->esq, palavra);
  } else if (raiz->dado < palavra) {
    raiz->dir = removeNo(raiz->dir, palavra);
  } else {
    if (raiz->esq == NULL && raiz->dir == NULL) {
      free(raiz);
      raiz = NULL;
    } else if (raiz->esq == NULL) {
      No *t = raiz;
      raiz = raiz->dir;
      free(t);
    } else if (raiz->dir == NULL) {
      No *t = raiz;
      raiz = raiz->esq;
      free(t);
    } else {
      No *f = raiz->esq;

      while (f->dir != NULL) {
        f = f->dir;
      }

      strcpy(raiz->dado, f->dado);
      strcpy(f->dado, palavra);

      raiz->esq = removeNo(raiz->esq, palavra);
    }
  }

  if (raiz == NULL) {
    return raiz; 
  }

  raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;

  int fb = getFB(raiz);

  //Rotação RR
  if (fb > 1 && getFB(raiz->esq) >= 0) {
    return rotacaoDireita(raiz);
  }
  //Rotação LL
  if (fb < -1 && getFB(raiz->dir) <= 0) {
    return rotacaoEsquerda(raiz);
  }
  //Rotação LR
  if (fb > 1 && getFB(raiz->esq) < 0) {
    raiz->esq = rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
  }
  //Rotação RL
  if (fb < -1 && getFB(raiz->dir) > 0) {
    raiz->dir = rotacaoDireita(raiz->dir);
    return rotacaoEsquerda(raiz);
  }

  return raiz;
}
