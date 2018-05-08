/* and_create.c - em termos práticos é a mesma coisa de shm_create.c. Cria uma memória compartilhada para leitura.
 * Autor: Cledson Ferreira.
 * Este código é para compatibilidade com o Android, através da biblioteca libandroid-shmem que emula as funções de memória compartilhada POSIX.
 * Ele também deverá funcionar em outros sistemas Linux normalmente.
 *
 * Compile com:
 * make to-android */
#include <errno.h>
#include <sys/ipc.h>   // ftok(), shmget()
#include <sys/shm.h>   // shmget(), shmat(), shmdt()
#include <stdio.h>
#include <string.h>

#include "l3ddy.h"

int main() {
  int tries;
  int shm_id;
  key_t shm_l3ddy;
  get_key_for_l3ddy(&shm_l3ddy);
  printf("(Chave: %d)\n", shm_l3ddy);
  shmget_exclusive(&shm_id, 128, shm_l3ddy);

  char *shm = shmat(shm_id, NULL, 0);
  if (shm == (char*)-1) {
    perror("Erro ao mapear");
    return 1;
  }
  memset(shm, 0, 49);
  shm[49] = 'A';
  printf("Aguardando mensagem...\n");
  // quando o caractere número 49 for alterado, imprimimos a string.
  for (tries=0; shm[49] == 'A'; tries++) {
    if (tries == 120) {
        fprintf(stderr, "Tempo de recepção expirado!\n");
        shmdt(shm);
        exit(1);
    }
    usleep(500000);
  }
  printf("Mensagem recebida: %s\n", shm);
  shmdt(shm);
  if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
    perror("Falha ao remover segmento de memória");
    return 1;
  }
  return 0;
}
