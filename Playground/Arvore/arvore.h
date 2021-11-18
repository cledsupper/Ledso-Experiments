/** arvore.h - cabeçalho da estrutura de dados le_arvore.
 *
 * Este algoritmo de árvore funciona como um endereçamento de
 * arquivos, de tal modo que o método le_arvore_nos() funciona de
 * forma similar a um criador de "diretórios" na memória. */

#ifndef LESSO_ARVORE_H
#define LESSO_ARVORE_H

typedef struct le_arvore_t le_arvore_t;

struct le_arvore_t {
  char * nome;
  /* talvez algum objeto de valor aqui... */
  le_arvore_t * nos;
  int len;
  int h;
};


le_arvore_t * le_arvore(const char * nome);

void le_arvore_no_cerra(le_arvore_t * arv);

void le_arvore_cerra(le_arvore_t * arv);

void le_arvore_no(le_arvore_t * arv, const char * nome);

void le_arvore_nos(le_arvore_t * arv, const char * n1, ...);

le_arvore_t * le_arvore_acessa(
    le_arvore_t * arv,
    const char * n1,
    ...
);

void le_arvore_mostra_tudo(le_arvore_t * arv, int h);

#endif
