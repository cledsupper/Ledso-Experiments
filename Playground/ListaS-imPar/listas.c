/* Este programa envolve um código especial que escrevi na reposição da segunda unidade da componente curricular de Algoritmos e Programação II:
 * -> o lista_par_impar()
 * Era solicitado que, dada uma lista de números inteiros, eu construísse uma função que transformasse ela em duas listas:
 * uma lista de números pares e outra de números ímpares.
 * Eu não poderia alterar os elementos, mas somente os apontadores.
 *
 * Autor: Cledson Cavalcanti
 * UFERSA - Campus de Angicos.
 */ 

#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;

struct lista {
  int valor;
  Lista *prox;
};

Lista *lista_add(Lista *l, int e) {
  if (!l) {
    l = (Lista*) malloc(sizeof(Lista));
    l->valor = e;
    l->prox = NULL;
  } else {
    Lista *no = l;
    while (no->prox)
      no = no->prox;
    no->prox = (Lista*) malloc(sizeof(Lista));
    (no->prox)->valor = e;
    (no->prox)->prox = NULL;
  }
  return l;
}

void lista_remove_tudo(Lista *l) {
  Lista *no = l;
  while (no) {
    l = no->prox;
    free(no);
    no = l;
  }
}

/* Este é o código especial. Eu reescrevi ele enquanto no circular (voltava pra casa), tentando repetir todos os erros que cometi na avaliação manuscrita.
 * Tenho 99% de convicção de que escrevi abaixo o exato mesmo código, sem tirar nem pôr um 'a', exceto os comentários aqui e ali. */
void lista_par_impar(Lista *inicio, Lista **par, Lista **impar) {
  Lista *subpar, *subimpar;
  Lista *no, *prox;
  /* Ok, este é o 1% de incerteza: escrevi "inicio" ou "no"? não sei :s */
  if (inicio->valor%2 == 0) {
    subpar = inicio; subimpar = NULL;
    (*par) = inicio; (*impar) = NULL;
  } else {
    subimpar = inicio; subpar = NULL;
    (*impar) = inicio; (*par) = NULL;
  }
  no = inicio->prox;
  while (no) {
    if (no->valor%2 == 0) {
      if (subpar == NULL) {
	subpar = no;
	(*par) = no;
      } else {
	subpar->prox = no;
	subpar = no;
      }
    } else if (no->valor%2 != 0) {
      if (subimpar == NULL) {
	subimpar = no;
	(*impar) = no;
      } else {
	subimpar->prox = no;
	subimpar = no;
      }
    }
    no = no->prox;
  }
  subpar->prox = NULL;
  subimpar->prox = NULL;
}

int main() {
  Lista *lis = lista_add(NULL, 3);
  lista_add(lis, 5);
  lista_add(lis, 2);
  lista_add(lis, 1);
  lista_add(lis, 4);
  lista_add(lis, 6);

  puts("LISTA ORIGINAL");
  Lista *no = lis;
  while (no) {
    printf("%d\n", no->valor);
    no = no->prox;
  }
  

  Lista *par, *impar;
  lista_par_impar(lis, &par, &impar);
  puts("\nPAR");
  no = par;
  while (no) {
    printf("%d\n", no->valor);
    no = no->prox;
  }

  puts("\nIMPAR");
  no = impar;
  while (no) {
    printf("%d\n", no->valor);
    no = no->prox;
  }

  lista_remove_tudo(par);
  lista_remove_tudo(impar);
  return 0;
}
