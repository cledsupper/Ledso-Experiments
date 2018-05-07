/* livecounter.c - contador simples que executa em segundo plano
 * Autor: Cledson Ferreira
 *
 * Este código está disponível em algum lugar em:
 * https://github.com/cledsupper/ */
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "livecounter.h"

struct _LiveCounter {
    long milis;
    pthread_t task;
    pthread_mutex_t lock;
    bool please_stop;
};

static void *clock_start(void *data) {
    LiveCounter *lcount = (LiveCounter*)data;
    pthread_mutex_lock(&lcount->lock);
    for (; !lcount->please_stop; lcount->milis+=1000)
        sleep(1);
    pthread_mutex_unlock(&lcount->lock);
    return NULL;
}

LiveCounter *newLiveCounter() {
    LiveCounter *lcount = cn_znew(LiveCounter, 1);
    if (!lcount) return lcount;
    pthread_mutex_init(&lcount->lock, NULL);
    setLiveCounter(lcount, 0);
    return lcount;
}

void setLiveCounter(LiveCounter *lcount, long milis) {
    stopLiveCounter(lcount);
    lcount->milis = milis;
    lcount->please_stop = false;
    pthread_create(&lcount->task, NULL, clock_start, lcount);
}

void stopLiveCounter(LiveCounter *lcount) {
    if (!lcount->please_stop) {
        lcount->please_stop = true;
        pthread_join(lcount->task, NULL);
    }
}

void destroyLiveCounter(LiveCounter *lcount) {
    stopLiveCounter(lcount);
    pthread_mutex_destroy(&lcount->lock);
    cn_free(lcount);
}
