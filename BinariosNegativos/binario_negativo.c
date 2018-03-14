/* binario_negativo.c - um exemplo prático de números negativos */
// Para que seja possível chamar a função printf()
#include <stdio.h>
// Para as variáveis inteiras de 8 bits ( = 1 byte)
#include <stdint.h>

/* Estas funções representam o número em binário e decimal */
void imprime_natural(uint8_t num);

void imprime_inteiro(int8_t num);

int main() {
    /* uint8_t = variável inteira SEM SINAL de 1 byte (8 bits) */
    uint8_t num_natural = 126; // unsigned = número sem sinal

    printf("\nNÚMERO NATURAL (sem negativos, sem sinal)\n");
    while (1) {
        imprime_natural(num_natural);

        if (num_natural == 0)
            break;
        
        num_natural++; // num_natural = num_natural + 1
    }
    printf("\n --- PAUSA ---\n");
    getchar(); // pausa o programa

    /* int8_t = variável inteira COM SINAL de 1 byte */
    //int8_t num_inteiro = 126;
    num_natural = 126;
    printf("\nNúmero inteiro (com negativos, com sinal)\n");
    while (1) {
        imprime_inteiro(num_natural);
        
        if (num_natural == 0)
            break;

        num_natural++;
    }
    printf("\n"
           "\n ---- FIM ----\n");
    return 0;
}

void imprime_natural(uint8_t num) {
    char bits[] = "0000 0000";
    uint8_t i, n = num;
    for (i=8; n; i--) {
        if (i==4) i--;
        if (i>8) break;
        bits[i] = '0' + n%2;
        n/=2;
    }
    printf("  %s = %d\n", bits, num);
}

void imprime_inteiro(int8_t num) {
    char bits[] = "0000 0000";
    uint8_t i, n = num; // (inteiro) -127 => (natural) 129
    for (i=8; n; i--) {
        if (i==4) i--;
        if (i>8) break;
        bits[i] = '0' + n%2;
        n/=2;
    }
    printf("  %s = %d\n", bits, num);
}
