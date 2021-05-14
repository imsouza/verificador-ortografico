#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#include "util.h"
#include "avl.h"
#include "abb.h"
#include "fila.h"

#define TAM_MAX_LINHA 1024
#define TAM_MAX_PALAVRA 128

const char *whiteSpace = " \t\v\f\n";

double MyClock () {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000) + tv.tv_usec;
}


void removePontuacao (char *str) {
  int count = 0;
  for (int i = 0; str[i]; i++) {
    if (!ispunct(str[i]) || str[i] == '-' || str[i] == '/') {
      str[count++] = str[i];
    }
  }
  str[count] = '\0';
}


void converteMinusculo (char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}


int main(int argc, char *argv[]) {
  double inicioProg = MyClock();
  char linha[TAM_MAX_LINHA];
  char nomeArqDicionario[TAM_MAX_PALAVRA];
  char nomeArqTexto[TAM_MAX_PALAVRA];
  char palavra[TAM_MAX_PALAVRA];
  char cpypalavra[TAM_MAX_PALAVRA];
  char cpypalavra2[TAM_MAX_PALAVRA];
  bool arvoreAVL = false;

  for (int i = 1; i < argc; ++i) {
    if (!strncmp(argv[i], "-avl", 4)) {
      arvoreAVL = true;
    } else if (!strncmp(argv[i], "-d", 2)){
      strcpy(nomeArqDicionario, argv[i + 1]);
      i++;
    } else if (!strncmp(argv[i], "-t", 2)){
      strcpy(nomeArqTexto, argv[i + 1]);
      i++;
    } else {
      fprintf(stderr, "Uso: ./%s -d <ArquivoDicionario> -t <Texto> [-avl]\n", argv[0]);
      exit(1);
    }
  }

  FILE *fDicionario, *fTexto;

  fDicionario = fopen(nomeArqDicionario, "r");
  if (fDicionario == NULL) {
    printf("Não foi possível abrir o arquivo '%s'\n", nomeArqDicionario);
    exit(EXIT_FAILURE);
  }

  No *raizAVL = NULL;
  No *raizABB = NULL;
  Fila *fila = criaFila();

  while(fscanf(fDicionario, "%s", palavra) == 1) {
    if (arvoreAVL) {
        raizAVL = insere(raizAVL, criaNo(palavra));
    } else {
        raizABB = insereNoABB(raizABB, criaNoABB(palavra));
    }
  }

  fTexto = fopen(nomeArqTexto, "r");
  if (fTexto == NULL) {
    printf("Não foi possível abrir o arquivo '%s'\n", nomeArqTexto);
    exit(EXIT_FAILURE);
  }

  while (fgets(linha, TAM_MAX_LINHA, fTexto) != NULL ) {
    char *word = strtok(linha, whiteSpace);

    while ( word != NULL ) {
      if (isdigit(word[0]) || word[0] == '-') {
        printf("%s ", word);
        word = strtok(NULL, whiteSpace);
        continue;
      }

      strcpy(cpypalavra, word);
      removePontuacao(cpypalavra);
      strcpy(cpypalavra2, cpypalavra);
      converteMinusculo(cpypalavra2);

      if (
        (!arvoreAVL && (busca(raizABB, cpypalavra) != NULL || \
        busca(raizABB, cpypalavra2) != NULL)) || \
        (arvoreAVL && (busca(raizAVL, cpypalavra) != NULL  || \
        busca(raizAVL, cpypalavra2) != NULL))
        ) {
        printf("%s ", word);
      }

      else {
        printf("\033[1;31m%s\033[00m ", word);
        if (buscaFila(fila, word) < 1) {
          //converteMinusculo(word);
          enqueue(fila, word);
        }
      }

      word = strtok(NULL, whiteSpace);
    }
    printf("\n");
  }

  printf("\n\n");
  printf("Palavra(s) incorreta(s) e sugestão(ões)\n");
  printf("----------------------------------------\n");

  int tFila = tamanhoFila(fila);

  for (int i = 0; i < tFila; i++) {
    printf("\033[1;31m%s\033[00m: ", front(fila));
    if (arvoreAVL) {
      listarPalavras(raizAVL, front(fila));
    } else {
      listarPalavras(raizABB, front(fila));
    }

    putchar('\n');

    dequeue(fila);
  }

  printf("----------------------------------------\n");
  printf("\033[1;32mTempo Total: %.10lf seg\n\n\033[00m", \
  (MyClock() - inicioProg) / CLOCKS_PER_SEC);

  fclose(fDicionario);
  fclose(fTexto);

  liberaAVL(raizAVL);
  liberaABB(raizABB);
  liberaFila(fila);
  return 0;
}


