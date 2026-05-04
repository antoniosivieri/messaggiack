#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

#include "registro.h"

int main() {


    /* TBD: Creare le code di messaggi, e avviare i processi server e registro,
     *      facendogli chiamare le funzioni server() e registro().
     */


    /* NOTA: I client sono avviati con un ritardo, per dare il tempo
             ai server di registrarsi sul processo registro.
     */

    sleep(2);

    /* TBD: Avviare i processi client, facendogli chiamare la funzione client() */

    /* TBD: Far terminare il programma come indicato nella traccia */
}