#ifndef _HEADER_MSG_H_
#define _HEADER_MSG_H_

#include <sys/types.h>

/* TBD: Definire i valori per i campi-tipo dei messaggi */

typedef struct {
    
    /* TBD: Definire la struttura del messaggio,
            includendo un campo per inserire il PID del mittente
     */

} messaggio_connect;

typedef struct {

    /* TBD: Definire la struttura del messaggio,
            includendo un campo per inserire l'ID della coda di richieste,
            e un campo per inserire l'ID della coda di risposte.
     */

} messaggio_ack;

typedef struct {
    
    /* TBD: Definire la struttura del messaggio,
            includendo un campo per inserire un valore intero.
    */

} messaggio_richiesta;

typedef struct {

    /* TBD: Definire la struttura del messaggio,
            includendo un campo per inserire un valore intero.
    */

} messaggio_risposta;

#endif