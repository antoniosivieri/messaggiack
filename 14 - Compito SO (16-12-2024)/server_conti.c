#include <stdio.h>
#include <stdlib.h>

#include "server_conti.h"

void server(int coda_richieste, int coda_risposte/* TBD: Completare il passaggio dei parametri */) {

    printf("Avvio processo server\n");

    int conti[NUM_CONTI] = {30, 30, 30};

    while(1) {

        printf("[SERVER] in attesa di richieste\n");

        /* TBD: ricevere un messaggio dalla coda delle richieste */
        richiesta msg;
        risposta msg_ris;
        int ret;

        ret = msgrcv(coda_richieste,&msg,sizeof(msg)-sizeof(long),0,0);

        if (ret < 0) {
            perror("Errore rcv");
            exit(1);
        }


        if(msg.type==TERMINAZIONE/* TBD: Verificare se la richiesta è di tipo TERMINAZIONE */) {

            printf("Server terminato\n");
            exit(0);
        }
        else if(msg.type==LETTURA_CONTO/* TBD: Verificare se la richiesta è di tipo LETTURA_CONTO */) {

            printf("[SERVER] Ricevuto richiesta di LETTURA_CONTO\n");

            int conto = msg.conto;/* TBD: l'identificativo del conto, ricevuto nel messaggio di richiesta */

            int saldo = conti[conto];
            int esito = SUCCESSO_OPERAZIONE;

            /* TBD: Mandare un messaggio di risposta con il saldo del conto. */
            msg_ris.saldo = saldo;
            msg_ris.esito = esito;
            msg_ris.type = msg.pid;

            ret = msgsnd(coda_risposte,&msg_ris,sizeof(msg_ris)-sizeof(long),0);

        }
        else if(msg.type==PRELIEVO_CONTO/* TBD: Verificare se la richiesta è di tipo PRELIEVO_CONTO */) {
            
            printf("[SERVER] Ricevuto richiesta di PRELIEVO_CONTO\n");

            int conto = msg.conto;/* TBD: l'identificativo del conto, ricevuto nel messaggio di richiesta */
            int importo = msg.importo;/* TBD: l'importo da prelevare, ricevuto nel messaggio di richiesta */

            int esito;
            
            if(conti[conto] >= importo) {

                conti[conto] -= importo;
                esito = SUCCESSO_OPERAZIONE;
            }
            else {
                esito = INSUCCESSO_OPERAZIONE;
            }

            /* TBD: Inviare un messaggio di risposta al client, includendo l'esito dell'operazione */
            msg_ris.type = msg.pid;
            msg_ris.esito = esito;

            ret = msgsnd(coda_risposte,&msg_ris,sizeof(msg_ris)-sizeof(long),0);

            if (ret < 0) {
                perror("Errore snd");
                exit(1);
            }
    
        }
        else if(msg.type==VERSAMENTO_CONTO/* TBD: Verificare se la richiesta è di tipo VERSAMENTO_CONTO */) {
            
            printf("[SERVER] Ricevuto richiesta di VERSAMENTO_CONTO\n");

            int conto = msg.conto;/* TBD: l'identificativo del conto, ricevuto nel messaggio di richiesta */
            int importo = msg.importo;/* TBD: l'importo da prelevare, ricevuto nel messaggio di richiesta */

            int esito = SUCCESSO_OPERAZIONE;

            conti[conto] += importo;
  
            /* TBD: Inviare un messaggio di risposta al client, includendo l'esito dell'operazione */
            msg_ris.type = msg.pid;
            msg_ris.esito = esito;

            ret = msgsnd(coda_risposte,&msg_ris,sizeof(msg_ris)-sizeof(long),0);

            if (ret < 0) {
                perror("Errore snd");
                exit(1);
            }

        }
        else {
            printf("[SERVER] Ricevuto richiesta di tipo sconosciuto\n");
        }

    }
}