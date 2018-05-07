#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char buf[256];
    const char *shm_name = "l3ddy"; // '-'
    int fd = shm_open(shm_name, O_RDWR, S_IWUSR|S_IRUSR);
    int tries=0, len=0;
    if (fd < 0) {
        perror("Erro ao abrir memória compartilhada: ");
        return 1;
    }
    printf("Mensagem para enviar a 'sh_create': ");
    fgets(buf, sizeof(buf), stdin);
    len = strlen(buf);
    buf[len>0 ? len : 0]=0; // retirar quebra de linha e delimitar a string
    write(fd, buf, sizeof(buf));
    printf("Bye bye!\n");
    close(fd);
    return 0;
}
