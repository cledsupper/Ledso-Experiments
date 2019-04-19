/* Este será o plugin do nPlayer?
   Este código é um teste de execução e controle de programas externos via sinais.

   Autor: Cledson Cavalcanti
   Você deve ter encontrado este programa em: https://github.com/cledsupper
*/

#include <errno.h>  // errno
#include <signal.h> // kill()
#include <ncurses.h> // printw(), clear(), getch(), etc.
#include <glib.h>   // g_get_current_dir(), g_spawn_async()
#include <time.h>   // time(agora = 0)
#include <stdlib.h> // atexit(procedimento)

#ifndef __ANDROID__
#define SYSTEM_COMPATIBLE_PLAYER_PATH "/usr/bin/mpg321"
#else
#define SYSTEM_COMPATIBLE_PLAYER_PATH "/data/data/com.termux/files/usr/bin/play"
#endif

/* Calcula o tempo corrido desde o último reset = 1.
   Para pausar a contagem: pause = 1.
   Após uma pausa, a próxima chamada deve ser feita para a continuação da contagem. */
void show_time(int reset, int pause) {
  static time_t inicio;
  static time_t paused = 0;
  if (reset) {
    /* Reiniciamos a contagem trocando inicio pelo tempo atual*/
    inicio = time(NULL);
    return;
  }

  /* Bem simples: a diferença entre este tempo e o de 'inicio' é o tempo corrido. */
  time_t tempo = time(NULL) - inicio;
  /* Vamos salvar esse tempo pra continuar a partir dele depois.  */
  if (pause) {
    paused = tempo;
  }
  else if (paused) {
    /* A continuação da contagem pode ser feita salvando o tempo atual subtraído do tempo corrido. */
    inicio = time(NULL)-paused;
    paused = 0;
  }

  int minutes = tempo/60;
  int secs = tempo%60;
  mvprintw(LINES/2, COLS-7, "%2d:%02d", minutes, secs);
  refresh();
}

void aviso_licenca();

int main(int argc, char *argv[]) {
  // coisas da Glib, isso pode ajudar caso o programa dê erro
  GError *error = NULL;
  char *cwd;
  char *cargv[] = {SYSTEM_COMPATIBLE_PLAYER_PATH, NULL, NULL};
  // pid do decodificador (mpg321 no Linux, ou o play do SoX no Termux) que executaremos
  GPid pid;
  int ch = 0, playing = 0;

  atexit(aviso_licenca);

  if (argc <= 1) {
    printf("Uso: %s (/endereco/para/arquivo.mp3)\n", argv[0]);
    return 0;
  }
  /* O segundo parâmetro é a música que executaremos em um decoder externo */
  cargv[1] = argv[1];

  // pega o endereo do diretório em que este programa está trabalhando
  cwd = g_get_current_dir();

  initscr();
  clear();

  /* Vamos spawnar o decoder assincronamente (sem pausar nosso programa)!*/
  if (!g_spawn_async(cwd, cargv, NULL, G_SPAWN_STDERR_TO_DEV_NULL | G_SPAWN_STDOUT_TO_DEV_NULL, NULL, NULL,
                     &pid, &error)) {
    int ecode = error->code;
    printw("Erro (%d) ao tentar reproduzir música!\n"
            "Mensagem de erro:\n%s", ecode, error->message);
    g_error_free(error);
    g_free(cwd);
    endwin();
    return ecode;
  }

  noecho();
  nodelay(stdscr, TRUE);
  clear();
  move(1, 1);
  printw("Reproduzindo '%s' via '%s' %d...", argv[1],
	 SYSTEM_COMPATIBLE_PLAYER_PATH, pid);
  show_time(1, 0);
  playing = 1;
  while (ch != 3) {
    move(4, 1);
    printw("Breves instruções:\n"
	       " 1. Pausar\n"
	       " 2. Continuar\n"
	       " 3. Parar\n");
    if (playing)
      show_time(0, 0);
 
    if (kill(pid, 0) == -1)
      if (errno == ESRCH) {
        clear();
        move(1, 1);
        printw("Reprodução de '%s' terminada!\n"
	       "Pressione ENTER para sair", argv[1]);
	refresh();
	nodelay(stdscr, FALSE);
	getch();
        break;
      }
    ch = getch();
    switch (ch) {
      case '1':
        clear();
        move(1, 1);
        printw("Reprodução de '%s' pausada!\n", argv[1]);
        refresh();
	show_time(0, 1); // salva tempo
	playing = 0;
	// sinal para parar o processo do decoder temporariamente
	kill(pid, SIGSTOP);
	break;
      case '2':
        clear();
        move(1, 1);
        printw("Reproduzindo '%s' via '%s'...\n", argv[1],
	       SYSTEM_COMPATIBLE_PLAYER_PATH);
        refresh();
	playing = 1;
	// sinal para continuar o do decoder
	kill(pid, SIGCONT);
	break;
      case '3':
        clear();
        move(1, 1);
        printw("Reprodução de '%s' interrompida! Encerrando...\n", argv[1]);
	napms(1000);
        refresh();
	// sinal para terminar o decoder
	kill(pid, SIGTERM);
	break;
    }
    napms(300);
  }

  endwin();
  if (error) {
    printf("\nLimpa a memória de 'error'\n");
    g_error_free(error);
  }
  g_free(cwd);
  //g_spawn_close_pid(pid);
  return 0;
}

void aviso_licenca() {
  printf("\npor Cledson F. Cavalcanti\n"
	 "\tVocê deve ter obtido este programa em https://github.com/cledsupper/ ou no https://ledsotips.blogspot.com, ou ainda por um fã ou seguidor meu\n"
	 "\tLeia a WTFPL versão 2 em http://www.wtfpl.net/ para saber os seus direitos sobre este software\n");
}
