#ifndef _HEADER_
#define _HEADER_

#include <sys/ipc.h>
#include <sys/msg.h>

#define NUM_CONTI 3

/* usare la macro #define per definire 4 tipi di richiesta:

   LETTURA_CONTO
   PRELIEVO_CONTO
   VERSAMENTO_CONTO
   TERMINAZIONE

*/
#define LETTURA_CONTO 4
#define PRELIEVO_CONTO 5
#define VERSAMENTO_CONTO 6
#define TERMINAZIONE 7

#define SUCCESSO_OPERAZIONE 1
#define INSUCCESSO_OPERAZIONE 0

typedef struct {

    /* TBD: Definire la struttura del messaggio di richiesta, includendo:

        - il tipo di richiesta (può assumere i valori LETTURA_CONTO, PRELIEVO_CONTO, VERSAMENTO_CONTO, TERMINAZIONE)

        - il conto su cui operare (valore intero, tra 0 e 2)

        - l'importo da prelevare o versare (valore intero positivo),
          nel caso di operazioni di LETTURA_CONTO questo valore può essere lasciato a 0

        - il PID del processo client che invia la richiesta
     */
    long type;
    int conto;
    unsigned int importo;
    int pid;

} richiesta;

typedef struct {

    /* TBD: Definire la struttura del messaggio di risposta, includendo:

       - il tipo di richiesta (dovrà contenere il PID del client a cui è destinata la risposta)

       - l'esito della richiesta (valore intero, può assumere i valori SUCCESSO_OPERAZIONE oppure INSUCCESSO_OPERAZIONE)

       - il saldo del conto (valore intero positivo),
         nel caso di operazioni di PRELIEVO oppure VERSAMENTO questo valore può essere lasciato a 0

     */
    long type;
    int esito;
    int saldo;

} risposta;

void server(int coda_richieste, int coda_risposte/* TBD: Completare il passaggio dei parametri */);

#endif