#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "server_conti.h"

#define NUM_THREADS 3

void client1(int coda_richieste, int coda_risposte/* TBD: Completare il passaggio dei parametri */);
void client2(int coda_richieste, int coda_risposte/* TBD: Completare il passaggio dei parametri */);
void client3(int coda_richieste, int coda_risposte/* TBD: Completare il passaggio dei parametri */);

int main() {

    int coda_richieste = msgget(IPC_PRIVATE,IPC_CREAT|0644);/* TBD: Creare una coda per i messaggi di richiesta */

    int coda_risposte = msgget(IPC_PRIVATE,IPC_CREAT|0644);/* TBD: Creare una coda per i messaggi di risposta */


    /* TBD: Creare un processo figlio,
            e fargli eseguire la funzione server(),
            passandogli gli identificativi delle code
     */
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        server(coda_richieste,coda_risposte);
        exit(0);
    } else if (pid < 0) {
        perror("Errore");
        exit(1);
    }

    /* TBD: Creare un processo figlio,
            e fargli eseguire la funzione client1(),
            passandogli gli identificativi delle code
     */
    pid = fork();
    if (pid == 0) {
        client1(coda_richieste,coda_risposte);
        exit(0);
    } else if (pid < 0) {
        perror("Errore");
        exit(1);
    }

    /* TBD: Creare un processo figlio,
            e fargli eseguire la funzione client2(),
            passandogli gli identificativi delle code
     */
    pid = fork();
    if (pid == 0) {
        client2(coda_richieste,coda_risposte);
        exit(0);
    } else if (pid < 0) {
        perror("Errore");
        exit(1);
    }

    /* TBD: Creare un processo figlio,
            e fargli eseguire la funzione client3(),
            passandogli gli identificativi delle code
     */
    pid = fork();
    if (pid == 0) {
        client3(coda_richieste,coda_risposte);
        exit(0);
    } else if (pid < 0) {
        perror("Errore");
        exit(1);
    }



    /* TBD: Attendere la terminazione dei 3 processi client */
    for (int i=0; i<3; i++) {
        wait(NULL);
    }

    int ret;

    /* TBD: Inviare al server un messaggio di TERMINAZIONE.
            È consentito porre a 0 tutti i campi del messaggio eccetto
            il campo del tipo di messaggio.
     */
    richiesta termina;
    termina.conto=0;
    termina.importo=0;
    termina.pid=0;
    termina.type=TERMINAZIONE;

    ret = msgsnd(coda_richieste,&termina,sizeof(termina)-sizeof(long),0);

    if (ret < 0) {
        perror("Errore snd");
        exit(1);
    }

    /* TBD: Attendere la terminazione del processo server */
    wait(NULL);
    
    /* TBD: Rimozione delle code di messaggi */
    msgctl(coda_richieste,IPC_RMID,0);
    msgctl(coda_risposte,IPC_RMID,0);


    return 0;
}


void client1(int coda_richieste, int coda_risposte/* TBD: Completare il passaggio dei parametri */) {

    printf("Avvio processo client1\n");

    /* TBD: Inviare un messaggio di richiesta di tipo LETTURA_CONTO,
            indicando il conto 0,
            ed il PID del processo client
     */
    int ret;

    richiesta msg;
    msg.type=LETTURA_CONTO;
    msg.pid = getpid();
    msg.conto = 0;
    msg.importo = 0; //lettura

    ret = msgsnd(coda_richieste,&msg,sizeof(msg)-sizeof(long),0);

    if (ret < 0) {
        perror("Errore snd");
        exit(1);
    }


    /* TBD: Ricevere un messaggio di risposta, mediante ricezione selettiva basata su PID */
    risposta ris;

    ret = msgrcv(coda_risposte,&ris,sizeof(ris)-sizeof(long),getpid(),0);

    if (ret < 0) {
        perror("Errore rcv");
        exit(1);
    }

    int saldo = ris.saldo;/* TBD: Estrarre il valore del saldo dal messaggio */;

    printf("[CLIENT 1] Saldo conto: %d\n", saldo);



    int totale_prelevato = 0;

    while(totale_prelevato < 50) {

        printf("[CLIENT 1] Richiesta di prelievo di 10\n");

        /* TBD: Inviare un messaggio di richiesta di tipo PRELIEVO_CONTO,
                indicando il conto 0,
                il PID del processo client,
                e un importo pari a 10
         */
        richiesta prel;
        prel.type = PRELIEVO_CONTO;
        prel.pid = getpid();
        prel.conto = 0;
        prel.importo = 10;

        ret = msgsnd(coda_richieste,&prel,sizeof(prel)-sizeof(long),0);

        if (ret < 0) {
            perror("Errore snd");
            exit(1);
        }


        /* TBD: Ricevere un messaggio di risposta, mediante ricezione selettiva basata su PID */
        risposta ris_prel;

        ret = msgrcv(coda_risposte,&ris_prel,sizeof(ris_prel)-sizeof(long),getpid(),0);

        if (ret < 0) {
            perror("Errore rcv");
            exit(1);
        }

        int esito = ris_prel.esito;/* TBD: Estrarre dal messaggio l'esito della operazione*/

        if(esito == INSUCCESSO_OPERAZIONE) {
            printf("[CLIENT 1] Prelievo fallito, verrà ritentato\n");
        }
        else {

            totale_prelevato += 10;

            printf("[CLIENT 1] Prelievo effettuato, totale prelevato = %d\n", totale_prelevato);
        }


        sleep(1);
    }

    printf("Termine processo client1\n");

}

void client2(int coda_richieste, int coda_risposte/* TBD: Completare il passaggio dei parametri */) {

    printf("Avvio processo client2\n");

    /* TBD: Inviare un messaggio di richiesta di tipo LETTURA_CONTO,
            indicando il conto 1,
            ed il PID del processo client
     */
    richiesta ric;
    ric.type = LETTURA_CONTO;
    ric.conto = 1;
    ric.pid = getpid();
    ric.importo = 0;

    int ret;

    ret = msgsnd(coda_richieste,&ric,sizeof(ric)-sizeof(long),0);

    if (ret < 0) {
        perror("Errore snd");
        exit(1);
    }




    /* TBD: Ricevere un messaggio di risposta, mediante ricezione selettiva basata su PID */
    risposta ris;

    ret = msgrcv(coda_risposte,&ris,sizeof(ris)-sizeof(long),getpid(),0);

    if (ret < 0) {
        perror("Errore rcv");
        exit(1);
    }

    int saldo = ris.saldo/* TBD: Estrarre il valore del saldo dal messaggio */;

    printf("[CLIENT 2] Saldo conto: %d\n", saldo);



    int totale_prelevato = 0;

    while(totale_prelevato < 50) {

        printf("[CLIENT 2] Richiesta di prelievo di 10\n");

        /* TBD: Inviare un messaggio di richiesta di tipo PRELIEVO_CONTO,
                indicando il conto 1,
                il PID del processo client,
                e un importo pari a 10
         */
        richiesta ric_prel;
        ric_prel.type = PRELIEVO_CONTO;
        ric_prel.conto = 1;
        ric_prel.pid = getpid();
        ric.importo = 10;

        ret  = msgsnd(coda_richieste,&ric_prel,sizeof(ric_prel)-sizeof(long),0);

        if (ret < 0) {
            perror("Errore snd");
            exit(1);
        }


        /* TBD: Ricevere un messaggio di risposta, mediante ricezione selettiva basata su PID */
        risposta ris_prel;

        ret = msgrcv(coda_risposte,&ris_prel,sizeof(ris_prel)-sizeof(long),getpid(),0);

        if (ret < 0) {
            perror("Errore rcv");
            exit(1);
        }

        int esito = ris_prel.esito;/* TBD: Estrarre dal messaggio l'esito della operazione*/

        if(esito == INSUCCESSO_OPERAZIONE) {
            printf("[CLIENT 2] Prelievo fallito, verrà ritentato\n");
        }
        else {

            totale_prelevato += 10;

            printf("[CLIENT 2] Prelievo effettuato, totale prelevato = %d\n", totale_prelevato);
        }


        sleep(1);
    }

    printf("Termine processo client2\n");

}

void client3(int coda_richieste, int coda_risposte/* TBD: Completare il passaggio dei parametri */) {

    printf("Avvio processo client3\n");

    sleep(5);

    printf("[CLIENT 3] Versamento su conto 0\n");

    /* TBD: Inviare un messaggio di tipo VERSAMENTO_CONTO, indicando
            il PID del processo client3,
            il conto 0,
            e un importo di 20
     */
    richiesta ric_vers;
    ric_vers.type = VERSAMENTO_CONTO;
    ric_vers.pid = getpid();
    ric_vers.importo = 20;
    ric_vers.conto = 0;

    int ret;
    ret = msgsnd(coda_richieste,&ric_vers,sizeof(ric_vers)-sizeof(long),0);

    if (ret < 0) {
        perror("Errore snd");
        exit(1);
    }

    /* TBD: Ricevere un messaggio di risposta, mediante ricezione selettiva basata su PID */
    risposta ris_vers;

    ret = msgrcv(coda_risposte,&ris_vers,sizeof(ris_vers)-sizeof(long),getpid(),0);

    if (ret < 0) {
        perror("Errore rcv");
        exit(1);
    }

    printf("[CLIENT 3] Versamento effettuato\n");

    sleep(1);


    printf("[CLIENT 3] Versamento su conto 1\n");

    /* TBD: Inviare un messaggio di tipo VERSAMENTO_CONTO, indicando
            il PID del processo client3,
            il conto 1,
            e un importo di 20
     */
    richiesta ric_vers2;
    ric_vers2.type = VERSAMENTO_CONTO;
    ric_vers2.pid = getpid();
    ric_vers2.conto = 1;
    ric_vers2.importo = 20;

    ret = msgsnd(coda_richieste,&ric_vers2,sizeof(ric_vers2)-sizeof(long),0);

    if (ret < 0) {
        perror("Errore snd");
        exit(1);
    }

    /* TBD: Ricevere un messaggio di risposta, mediante ricezione selettiva basata su PID */
    risposta ris_vers2;

    ret = msgrcv(coda_risposte,&ris_vers2,sizeof(ris_vers2)-sizeof(long),getpid(),0);

    if (ret < 0) {
        perror("Errore rcv");
        exit(1);
    }

    printf("[CLIENT 3] Versamento effettuato\n");

    printf("Termine processo client3\n");

}

