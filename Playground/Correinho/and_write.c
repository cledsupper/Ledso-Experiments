/* and_write.c - escreve em memória compartilhada criada por and_create.c
 * Veja and_create.c para mais detalhes.
 * Autor: Cledson Ferreira. */
#include <sys/ipc.h>   // ftok(), shmget()
#include <sys/shm.h>   // shmget(), shmat(), shmdt()
#include <stdio.h>
#include <string.h>

#include "l3ddy.h"

int main() {
  key_t shm_l3ddy;
  get_key_for_l3ddy(&shm_l3ddy);
  int shm_id = shmget(shm_l3ddy, 128, 0);
  if (shm_id == -1) {
    perror("Erro");
    return 1;
  }

  char *shm = shmat(shm_id, NULL, 0);
  if (shm == (char*)-1) {
    perror("Erro ao mapear");
    return 1;
  }
  while (shm[49] != 'A')
    usleep(500000);
  printf("Enviar mensagem: ");
  fflush(stdout); // mosttar o aviso imediatamente
  // 49 é o caractere que vamos usar para indicar se houve alteração
  int len = read(STDIN_FILENO, shm, 49);
  shm[len-1] = 0; // trocar quebra de linha por delimitador
  shm[49] = 0;
  return 0;
}
