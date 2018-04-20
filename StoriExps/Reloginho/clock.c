/* clock.c - contador simples que executa em segundo plano
 * Autor: Cledson Ferreira
 *
 * Este código está disponível em algum lugar em:
 * https://github.com/cledsupper/ */
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "clock.h"

struct _Clock {
    long milis;
    pthread_t task;
    pthread_mutex_t lock;
    bool please_stop;
};

static void *clock_start(void *data) {
    Clock *clk = (Clock*)data;
    pthread_mutex_lock(&clk->lock);
    for (; !clk->please_stop; clk->milis+=1000)
        sleep(1);
    pthread_mutex_unlock(&clk->lock);
    return NULL;
}

Clock *newClock() {
    Clock *clk = cn_znew(Clock, 1);
    if (!clk) return clk;
    pthread_mutex_init(&clk->lock, NULL);
    setClock(clk, 0);
    return clk;
}

void setClock(Clock *clk, long milis) {
    stopClock(clk);
    clk->milis = milis;
    clk->please_stop = false;
    pthread_create(&clk->task, NULL, clock_start, clk);
}

void stopClock(Clock *clk) {
    if (!clk->please_stop) {
        clk->please_stop = true;
        pthread_join(clk->task, NULL);
    }
}

void destroyClock(Clock *clk) {
    stopClock(clk);
    pthread_mutex_destroy(&clk->lock);
    cn_free(clk);
}
