/* counter.c - contador simples que executa em segundo plano
 * Autor: Cledson Ferreira
 *
 * Este código está disponível em algum lugar em:
 * https://github.com/cledsupper/ */

#include "counter.h"

counter_t counter_start(counter_t *pcounter) {
    counter_t counter = time(0);
    if (pcounter)
        *pcounter = counter;
    return counter;
}

counter_t counter_set(counter_t *pcounter, time_t secs) {
    counter_t counter = time(0) - secs;
    if (pcounter)
        *pcounter = counter;
    return counter;    
}

time_t counter_get_time(counter_t counter) {
    return time(0) - counter;
}
