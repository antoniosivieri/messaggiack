#ifndef _REGISTRO_H_
#define _REGISTRO_H_

// Messaggi da e verso il registro
typedef struct {
    /* TBD */
} messaggio_registro;

// Messaggi verso il server
typedef struct {
    /* TBD */
} messaggio_server;

/* TBD: Definire i tipi di messaggio */


void client(int id_coda_registro_richieste, int id_coda_registro_risposte);
void registro(int id_coda_registro, int id_coda_registro_risposte);
void server(int id_coda_registro, int id_coda_registro_risposte, int id_server);

#endif