#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "registro.h"

void server(int id_coda_registro_richieste, int id_coda_registro_risposte, int id_server) {
    
    printf("Registro: Server...\n");

    int risorsa = 0;

    int id_coda_server = /* TBD */

    printf("Server: Invio messaggio BIND (id_server=%d, id_coda=%d)\n", id_server, id_coda_server);

    /* TBD */


    while(1) {

        printf("Server: In attesa di messaggi...\n");

        /* TBD: Completare la ricezione e gestione dei messaggi */

    }
}
