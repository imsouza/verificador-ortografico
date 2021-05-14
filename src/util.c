#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "abb.h"
#include "avl.h"

#define LIMITE 3

int min(int a, int b) {
  return (a < b ? a : b);
}


int min3(int a, int b, int c) {
  return min(a, min(b, c));
}


void listarPalavras (No *raizArvore, char *palavra) {
  if (raizArvore != NULL) {
    if (distanciaEdicao(getPalavra(raizArvore), palavra) < LIMITE) {
      printf("\033[1;32m%s\033[00m, ", getPalavra(raizArvore));
    }

    listarPalavras(raizArvore->esq, palavra);
    listarPalavras(raizArvore->dir, palavra);
  }
}


int distanciaEdicao(char *a, char *b) {
  int m = strlen(a), n = strlen(b);
  int dp[m+1][n+1];

  for (int i=0; i <= m; i++) {
    dp[i][0] = i;
  }

  for (int j=0; j <= n; j++) {
    dp[0][j] = j;
  }

  for (int i=1; i <= m; i++) {
    for (int j=1; j <= n; j++) {
      if (a[i-1] != b[j-1]) {
        dp[i][j] = min3( 1 + dp[i-1][j], 1 + dp[i][j-1], 1 + dp[i-1][j-1]);
      } else {
        dp[i][j] = dp[i-1][j-1];
      }
    }
  }

  return dp[m][n];
}


void *mallocSafe(size_t nbytes) {
  void *ptr;

  ptr = malloc(nbytes);
  
  if (ptr == NULL) {
    ERRO(Malloc devolveu NULL!);
    exit(EXIT_FAILURE);
  }

  return ptr;
}
