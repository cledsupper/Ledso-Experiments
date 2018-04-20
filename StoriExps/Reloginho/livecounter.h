/* livecounter.h - contador simples que executa em segundo plano
 * Autor: Cledson Ferreira
 *
 * Este código está disponível em algum lugar em:
 * https://github.com/cledsupper/ */
#ifndef __LIVECOUNTER_H__
#define __LIVECOUNTER_H__

#define cn_new(TYPE, SIZE)  (TYPE*) malloc(sizeof(TYPE)*(SIZE))
#define cn_znew(TYPE, SIZE) (TYPE*) calloc(sizeof(TYPE), (SIZE))
#define cn_resize(POINTER, TYPE, SIZE)\
    (TYPE*) realloc(POINTER, sizeof(TYPE)*(SIZE))
#define cn_free(POINTER)    free(POINTER)

/* Apenas as funões essenciais do contador
 * E é, eu coloquei o nome LiveCounter no contador pq
 * minha ideia inicialmente era ser um display
 * de relógio, mas isso exige mais trabalho, e
 * a princípio eu quero saber se as bases
 * do trocinho funcionam :? */

typedef struct _LiveCounter LiveCounter;

LiveCounter *newLiveCounter();

void setLiveCounter(LiveCounter *lcounter, long milis);

void stopLiveCounter(LiveCounter *lcounter);

void destroyLiveCounter(LiveCounter *lcounter);

#endif /* __LIVECOUNTER_H__ */
