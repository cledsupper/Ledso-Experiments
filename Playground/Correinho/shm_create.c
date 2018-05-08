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
    /*
     * shm_open() cria/abre uma memória compartilhada com o nome 'shm_name'.
     *
     * O segundo parâmetro desta função são flags indicando como a memória
     * deve ser aberta:
     * [OBRIGATÓRIO] O_RDONLY:
     *   indica que o ojeto deve ser aberto para leitura.
     *   Se nós quiséssemos ESCREVER na memória (veja shm_write.c), em vez de
     *   O_RDONLY, deveria ser configurado O_WRONLY.
     * O_CREAT:
     *   se 'shm_name' não existir, então ela deve ser criada.
     * [DEPENDE DE 'O_CREAT'] O_EXCL:
     *   somente criar a memória. (Se ela já existe, a função retorna -1).
     *
     * No terceiro parâmetro deve se configurar as permissões (modes) da
     * memória a ser criada:
     * S_IWUSR: usuário tem permissão de escrita;
     * S_IRUSR: usuário tem permissão de leitura.
     */
    int fd = shm_open(shm_name, O_RDONLY|O_CREAT|O_EXCL, S_IWUSR|S_IRUSR);
    int tries, ret;
    if (fd < 0) {
        perror("Erro ao criar memória compartilhada: ");
        return 1;
    }
    printf("Aguardando a mensagem...\n");
    /* Usamos read() e write() para manipular descritores de arquivos (
     * file descriptors), que são representados como números inteiros.
     */
    for (tries=0; !read(fd, buf, sizeof(buf)); tries++) {
        if (tries == 60) {
            printf("\nNenhum byte encontrado na memória compartilhada :/\n");
            shm_unlink(shm_name); // remove a memória
            return 1;
        }
        sleep(1);
    }
    printf("\nString encontrada: %s\n", buf);
    printf("\nBye bye :)\n");
    shm_unlink(shm_name); // ...
    return 0;
}

/* Você pode aprender mais sobre como programar essas coisas em:
 * [shm_open() - create/open or unlink POSIX shared memory objects]
 *  -> https://www.systutorials.com/docs/linux/man/3-shm_open/
 *
 * [open(3): open file] - isso é importante para entender os modes.
 *  -> https://linux.die.net/man/3/open
 *
 * [How to use shared memory with Linux in C] - uma forma diferente
 * de fazer isso, que usa ponteiros em vez de descritores de
 * arquivos.
 *  -> https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
 *
 * [IPC: Shared Memory] - continuação do ítem anterior.
 *  -> http://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html
 */
