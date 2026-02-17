#include "header_monitor.h"

void init_monitorpc(MonitorPC *p) {

    /* TBD: Inizializzare le variabili testa/coda per il vettore circolare */

    /* TBD: Inizializzare le variabili per la sincronizzazione */
}

void remove_monitorpc(MonitorPC *p) {

    /* TBD: De-inizializzare le variabili per la sincronizzazione */

}

void produci(MonitorPC *p, int val) {

    /* TBD: Completare il metodo con la sincronizzazione
            e con la gestione della coda circolare
     */

    p->buffer[/* TBD */] = val;

}

int consuma(MonitorPC *p) {

    int val;

    /* TBD: Completare il metodo con la sincronizzazione
            e con la gestione della coda circolare
     */

    val = p->buffer[/* TBD */];


    return val;
}
