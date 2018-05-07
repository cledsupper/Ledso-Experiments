#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char ch=0, buf[256];
    const char *shm_name = "l3ddy";
    int fd = shm_open(shm_name, O_RDWR|O_CREAT|O_EXCL, S_IWUSR|S_IRUSR);
    int tries, ret;
    if (fd < 0) {
        perror("Erro ao criar memória compartilhada: ");
        return 1;
    }
    printf("Aguardando a mensagem...\n");
    for (tries=0; !read(fd, buf, sizeof(buf)); tries++) {
        if (tries == 60) {
            printf("\nNenhum byte encontrado na memória compartilhada :/\n");
            close(fd);
            shm_unlink(shm_name);
            return 1;
        }
        sleep(1);
    }
    printf("\nString encontrada: %s\n", buf);
    printf("\nBye bye :)\n");
    close(fd);
    shm_unlink(shm_name);
    return 0;
}
