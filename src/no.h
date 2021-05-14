#ifndef NO_H
#define NO_H

typedef struct no {
  char *dado;
  struct no *esq;
  struct no *dir;
  int altura;
}No;

char *getPalavra(No *root);

#endif