/* livecounter.h - contador estático simples (o oposto do LiveCounter)
 * Autor: Cledson Ferreira
 *
 * Este código está disponível em algum lugar em:
 * https://github.com/cledsupper/ */
#ifndef __COUNTER_H__
#define __COUNTER_H__

#include <time.h>

#define cn_new(TYPE, SIZE)  (TYPE*) malloc(sizeof(TYPE)*(SIZE))
#define cn_znew(TYPE, SIZE) (TYPE*) calloc(sizeof(TYPE), (SIZE))
#define cn_resize(POINTER, TYPE, SIZE)\
    (TYPE*) realloc(POINTER, sizeof(TYPE)*(SIZE))
#define cn_free(POINTER)    free(POINTER)

typedef time_t counter_t;

/* Retorna um "novo" contador */
counter_t counter_start();

/* Reinicia o contador com <secs> segundos */
counter_t counter_set(counter_t *counter, time_t secs);

/* Retorna variação de tempo */
time_t counter_get_time(counter_t counter);

#endif /* __COUNTER_H__ */
