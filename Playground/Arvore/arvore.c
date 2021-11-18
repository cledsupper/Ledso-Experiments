#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* COMPILE COM: gcc -c -DNDEBUG arvore.c para excluir os logs */
#ifdef NDEBUG
  #define logf(...)
#else
  #define logf(...) printf(__VA_ARGS__)
#endif

#define le_new(TYPE, N)  (TYPE *) calloc(N, sizeof(TYPE))
#define le_resize(POINTER, N)  (typeof(POINTER)) realloc(POINTER, sizeof(POINTER[0])*N)

le_arvore_t * le_arvore(const char * nome) {
  le_arvore_t * arvore = le_new(le_arvore_t, 1);
  arvore->nome = le_new(char, strlen(nome)+1);
  strcpy(arvore->nome, nome);
  logf(" ... criada árvore vazia '%s'\n", nome);
  return arvore;
}

void le_arvore_no_cerra(le_arvore_t * arv) {
  int n=0;
  le_arvore_t * no;
  logf(" ... cerrando nó '%s'...\n", arv->nome);
  for (; n < arv->len; n++) {
    no = &(arv->nos[n]);
    le_arvore_no_cerra(no);
  }
  if (arv->nos) free(arv->nos);
  if (arv->nome) free(arv->nome);
  memset(arv, 0, sizeof(le_arvore_t));
};

void le_arvore_cerra(le_arvore_t * arv) {
  logf(" ... destruindo árvore '%s'...\n", arv->nome);
  if (arv->len)
    le_arvore_no_cerra(arv);
  free(arv);
}

void le_arvore_no(le_arvore_t * arv, const char * nome) {
  int n = arv->len++;
  arv->nos = le_resize(arv->nos, arv->len);
  memset(&(arv->nos[n]), 0, sizeof(le_arvore_t));
  arv->nos[n].nome = le_new(char, strlen(nome)+1);
  strcpy(arv->nos[n].nome, nome);
  logf(" ... adicionado '%s' em '%s'\n", arv->nos[n].nome, arv->nome);
}

void le_arvore_nos(le_arvore_t * arv, const char * n1, ...) {
  va_list vl;
  const char * nx = n1;
  le_arvore_t * no = arv;
  int n, nolen;

  logf(" ... criando linhagem de nós ...\n");

  va_start(vl, n1);
  while (nx) {
    nolen = no->len;
    for (n=0; n < nolen; n++) {
      if (!strcmp(no->nos[n].nome, nx)) {
        nx = va_arg(vl, char *);
        no = &(no->nos[n]);
        break;
      }
    }
    if (n == nolen) {
      le_arvore_no(no, nx);
      no = &(no->nos[n]);
      nx = va_arg(vl, char *);
    }
  }
  va_end(vl);
}

le_arvore_t * le_arvore_acessa(
    le_arvore_t * arv,
    const char * n1,
    ...
) {
  le_arvore_t * no = arv;
  const char * nx = n1;
  int n, nolen;
  va_list vl;

  if (!no->len && (nx && nx[0]))
    return NULL;
  
  va_start(vl, n1);
  while (nx && nx[0]) {
    nolen = no->len;
    for (n=0; n < nolen; n++)
      if (!strcmp(no->nos[n].nome, nx)) {
        no = &(no->nos[n]);
        nx = va_arg(vl, char *);
        break;
      }
    if (n == nolen)
      break;
  }
  va_end(vl);
  if ((nx && nx[0]) && n == nolen)
    return NULL;
  return no;
}

void le_arvore_mostra_tudo(le_arvore_t * arv, int h) {
  int d, n;

  for (d=0; d < h*2; d++) fputc(' ', stdout);
  printf("--> %s%s", arv->nome, arv->len ? ":\n" : "\n");
  for (n=0; n < arv->len; n++)
    le_arvore_mostra_tudo(&(arv->nos[n]), h+1);
}
