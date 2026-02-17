#ifndef _HEADER_MONITOR_H_
#define _HEADER_MONITOR_H_

#include <pthread.h>

#define DIM 5

typedef struct {

    int buffer[DIM];

    /* TBD: Aggiungere le variabili testa/coda per il vettore circolare */

    /* TBD: Aggiungere le variabili per la sincronizzazione */

} MonitorPC;

void init_monitorpc(MonitorPC *p);
void remove_monitorpc(MonitorPC *p);
void produci(MonitorPC *p, int val);
int consuma(MonitorPC *p);

#endif