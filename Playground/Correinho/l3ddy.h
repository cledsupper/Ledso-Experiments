#ifndef _L3DDY_KEY_H_
#define _L3DDY_KEY_H_
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static void get_key_for_l3ddy(key_t *pl3ddy) {
  char cwd[256]="/";
  int cwd_len = 256;
  if (!getcwd(cwd, 256)) exit(1);
  else if (cwd[(cwd_len = strlen(cwd))-1] != '/') {
    cwd[cwd_len++] = '/';
    cwd[cwd_len] = '\0';
  }
  strncat(cwd, "l3ddy.h", 255-cwd_len-5);
  if ((*pl3ddy = ftok(cwd, 'L')) == -1) {
    perror("Falha ao gerar chave");
    exit(1);
  }
}

static void shmget_exclusive(int *id, int size, key_t l3ddy) {
  char cmd[30];
  while ((*id = shmget(l3ddy, size,  IPC_CREAT|IPC_EXCL|SHM_R|SHM_W)) == -1) {
    if (errno == EEXIST) {
      sprintf(cmd, "ipcrm -M %#x", l3ddy);
      printf("Removendo segmento com \"%s\"...\n", cmd);
      if (system(cmd)) {
        printf("Falha ao remover!\n");
        exit(1);
      } else puts("Tentando novamente...");
    } else exit(1);
  }
}

#endif
