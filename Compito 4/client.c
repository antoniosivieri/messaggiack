#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "header_msg.h"

int main() {

    srand(getpid());


    /* TBD: Ottenere le due code di messaggi "connect" ed "ack"
            (le stesse create nel programma "start")
     */

    int id_connect = /* TBD */;

    int id_ack = /* TBD */;




    /* TBD: Inviare un messaggio di "connect" */

    /* TBD: Attendere la ricezione di un messaggio "ack" */

    printf("[CLIENT %d] Connesso\n", getpid());

    int id_coda_richieste = /* TBD */;

    int id_coda_risposte = /* TBD */;



    for(int i=0; i<3; i++) {

        printf("[CLIENT %d] Invio richiesta produzione\n", getpid());

        int valore = rand() % 10;

        /* TBD: Inviare un messaggio di richiesta di tipo "PRODUZIONE", con il valore */



        /* TBD: Attendere un messaggio di risposta di tipo "PRODUZIONE" */

        printf("[CLIENT %d] Valore prodotto: %d\n", getpid(), valore);

    }


    for(int i=0; i<3; i++) {

        printf("[CLIENT %d] Invio richiesta consumazione\n", getpid());

        /* TBD: Inviare un messaggio di richiesta di tipo "CONSUMAZIONE", con nessun valore */



        /* TBD: Attendere un messaggio di risposta di tipo "CONSUMAZIONE", ed estrapolare il valore */

        int valore = /* TBD */;

        printf("[CLIENT %d] Valore consumato: %d\n", getpid(), valore);

    }


    /* TBD: Rimuovere le due code di richieste e risposte dedicate alla connessione */

}