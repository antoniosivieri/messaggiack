#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include "registro.h"

void client(int id_coda_registro_richieste, int id_coda_registro_risposte) {

    printf("Client: Avvio...\n");

    srand(getpid());

    int id_server = rand() % 2;

    printf("Client: Invio messaggio QUERY (id_server=%d)\n", id_server);

    /* TBD */



    printf("Client: Attesa messaggio RESULT...\n");

    /* TBD */

    int id_coda_server = /* TBD */

    printf("Client: Ricevuto messaggio RESULT (id_coda=%d)\n", id_coda_server);



    for(int i = 0; i<3; i++) {

        int valore = rand() % 11;

        printf("Client: Invio messaggio SERVICE (id_server=%d, id_coda=%d, valore=%d)\n", id_server, id_coda_server, valore);

        /* TBD */

        sleep(1);
    }

    printf("Client: Uscita\n");
}
