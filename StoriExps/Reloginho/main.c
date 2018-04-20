/* main.c - interface do contador de segundos
 * Autor: Cledson Ferreira
 *
 * Este código está disponível em algum lugar em:
 * https://github.com/cledsupper/ */
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "clock.h"

static bool stop = false;
pthread_t td_display;

/* parâmetros serão passados via estrutura de
 * de dados para a função startDisplay() */
struct d_args {
  Clock *clk;
  int lc[2];
};

/* é aqui que mostramos o contador bonitinho
 * na tela (com ajuda da biblioteca Ncurses).
 * Esta função é executada em uma tarefa adicional */
void *startDisplay(void *args) {
  struct d_args *da = (struct d_args*)args;
  stop = false;
  /* Criar uma janela com 3 linhas e 32 colunas
   * numa posição definida pelo usuário */
  WINDOW *win = newwin(3, 32, da->lc[0], da->lc[1]);
  while (!stop) {
    int secs = (*((long*)(da->clk))/1000)%60;
    int mins = *((long*)(da->clk))/60000;
    wclear(win);
    wprintw(win, "-------\n");
    wprintw(win, "|%02d:%02d|\n", mins,secs);
    wprintw(win, "-------\n");
    wrefresh(win);
    move(5, 1);
    refresh();
    sleep(1);
    // nós estamos observando apenas uma mudança
    // de segundos `-´
  }
  // destrói a janela do reloginho!
  delwin(win);
  free(da);
  return 0;
}

void setDisplay(Clock *clk) {
  stop = true; // mandar mensagem pro display parar
  // e agora esperaremos o display encerrar parar
  clear();
  move(4, 8); // vamo pra linha 4, na coluna 8
  printw("aguarde...\n");
  refresh(); // e mostramos o texto nesse lugar
  pthread_join(td_display, NULL);
  // esperar a thread encerrar

  clear();
  move(1, 1);
  // perguntamos ao usuário qual lugar ele quer o
  // reloginho :?
  printw("Qual local posicionar o relógio? [ex: 1 2 | linha 1, coluna 2]\n");
  refresh();

  /* vamos alocar memória para a estrutura de
   * que vamos passar como parâmetro para a
   * função startDisplay()! */
  struct d_args *da = (struct d_args*)malloc(sizeof(struct d_args));
  // aqui pegamos a linha e a coluna :)
  scanw("%d %d", &da->lc[0], &da->lc[1]);
  /* sim, o contador vai junto, senão startDisplay
   * vai ficar sem saber qual counter mostrar! */
  da->clk = clk; // yeeeyy

  // pronto, é hora de mostrar o reloginho!!!
  pthread_create(&td_display, NULL, startDisplay, da);
  // viu? "da" é o parâmetro de startDisplay()!
}

int main() {
  Clock *clk = newClock();
  initscr();
  // vamos descobrir onde mostrar o relógio?
  setDisplay(clk);

  /* menu */
  bool hide = false;
  char q=0;
  while (q!='q') {
    clear();
    if (!hide) {
      move(1, 1);
      printw(" -- Contador --\n");
      printw("1 - Alterar posição\n");
      printw("2 - Ocultar/exibir este menu\n");
      printw("q - Sair\n");
      refresh();
    }
    q = getch();
    switch(q) {
    case '1':
      setDisplay(clk);
      break;
    case '2':
      hide = !hide;
      break;
    }
  }
  stop = true;
  move(4, 7);
  printw("Encerrando...");
  refresh();
  pthread_join(td_display, NULL);
  destroyClock(clk);
  endwin();
  return 0;
}
