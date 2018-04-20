/* clock.h - contador simples que executa em segundo plano
 * Autor: Cledson Ferreira
 *
 * Este código está disponível em algum lugar em:
 * https://github.com/cledsupper/ */
#ifndef __CLOCK_H__
#define __CLOCK_H__

#define cn_new(TYPE, SIZE)  (TYPE*) malloc(sizeof(TYPE)*(SIZE))
#define cn_znew(TYPE, SIZE) (TYPE*) calloc(sizeof(TYPE), (SIZE))
#define cn_resize(POINTER, TYPE, SIZE)\
    (TYPE*) realloc(POINTER, sizeof(TYPE)*(SIZE))
#define cn_free(POINTER)    free(POINTER)

/* Apenas as funões essenciais do contador
 * E é, eu coloquei o nome Clock no contador pq
 * minha ideia inicialmente era ser um display
 * de relógio, mas isso exige mais trabalho, e
 * a princípio eu quero saber se as bases
 * do trocinho funcionam :? */

typedef struct _Clock Clock;

Clock *newClock();

void setClock(Clock *clk, long milis);

void stopClock(Clock *clk);

void destroyClock(Clock *clk);

#endif /* __CLOCK_H__ */
