#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "registro.h"

void registro(int id_coda_registro_richieste, int id_coda_registro_risposte) {
    
    printf("Registro: Avvio...\n");

    int id_code_server[2];
    id_code_server[0] = 0;
    id_code_server[1] = 0;

    while(1) {

        printf("Registro: In attesa di messaggi...\n");

         /* TBD: Completare la ricezione e gestione dei messaggi */
    }
}
