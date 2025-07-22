/*
AUTORI: Giuliano Antoniciello 
        Davide Fornelli
        Onofrio de Robertis

DATA INIZIO: 28/05/2025

NOME FILE: partita.c

Scopo delle funzioni presenti:
- avviarePartita: gestisce l'intero ciclo di gioco, dall'inizializzazione alla vittoria.
- mostraSchermo: stampa la schermata iniziale della partita in base alla dimensione.
- stampareTitoloPartita: stampa il titolo della partita.
- stampareVittoria: mostra il messaggio finale di vittoria.
- stampareTabellaInput: disegna la tabella per l'inserimento di riga, colonna e valore.
- disegnareCornice: stampa la cornice decorativa per l'input utente.
- convertireDimensione: converte un input numerico in dimensione reale della scacchiera (4, 9, 16).
- rimuovereNumeri: rimuove celle dalla scacchiera in base alla difficoltà scelta.
- calcolareCelleDaRimuovere: calcola la percentuale di celle da rimuovere in base alla difficoltà.
- verificareRiga: controlla se un numero è già presente nella riga.
- verificareColonna: controlla se un numero è già presente nella colonna.
- verificareSottoquadrato: controlla se un numero è già presente nel quadrato interno.
- riempireScacchiera: riempie ricorsivamente la scacchiera con una soluzione valida.
- trovareCellaVuota: trova una cella ancora vuota nella scacchiera.
- generareSudoku: genera una scacchiera completa e ne rimuove celle in base alla difficoltà.
- stampareScacchieraPartita: gestisce la stampa completa della scacchiera di gioco.
- calcolareSottoquadrato: calcola la dimensione del sotto-quadrato in base alla dimensione totale.
- stampareIntestazioneColonne: stampa l'intestazione delle colonne numerate.
- stampareLineaOrizzontale: stampa una riga di separazione tra righe della scacchiera.
- stampareRigheScacchiera: stampa tutte le righe della scacchiera.
- stampareRigaScacchiera: stampa una singola riga della scacchiera.
- collezionareInput: raccoglie input utente con controlli di validità e messaggi d'errore.
- controllareScacchieraPiena: verifica se tutte le celle della scacchiera sono state riempite.
- salvarePartitaCorrente: salva lo stato attuale della partita su file.
- salvarePartita: scrive su file tutti i dati della partita.
- caricaPartita: carica una partita precedentemente salvata da file.
- caricaValoriScacchiera: legge e carica i valori della scacchiera da file.
- avviarePartitaContinuata: permette di continuare una partita precedentemente salvata.
                    su riga, colonna e sottoquadrato(verificareRiga, verificareColonna, verificareSottoquadrato), per avere un codice più leggibile e modulare

Nel giorno 18/06/25, Giuliano Antoniciello ha inserito la funziona: calcolareSottoquadrato() per calcolare dinamicamente la dimensione del quadrante in base alla dimensione della scacchiera.
                    In questo modo il codice è più dinamico e flessibile.

Nel giorno 20/06/25, Giuliano Antoniciello ha inserito le funzioni per il salvataggio e caricamento partita (salvarePartita, caricaPartita), per permettere di interrompere e riprendere 
                    una partita in momenti successivi

Nel giorno 20/06/25, Michele Amato ha inserito la funzione: stampareScacchieraPartita() per aumentare la leggibilità della scacchiera sul terminale

Nel giorno 21/06/25, Giuliano Antoniciello e Davide Fornelli hanno aggiornato le funzioni: collezionareInput(), riempireScacchiera() e mostraSchermo() per rendere il codice più compatto
                    e metterlo al sicuro da eventuali arresti anomali
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/funzioniUtilita.h"
#include "../include/tipiDiDato.h"
#include "../include/partita.h"

#include "../include/homepage.h"

#define RIGA_INPUT_RIGA 13
#define RIGA_INPUT_COLONNA 16
#define RIGA_INPUT_VALORE 19
#define RIGA_INPUT 28
#define COLONNA_INPUT 67
#define CELLA_VUOTA 0
#define FALSO 0
#define VERO 1
#define DIFFICOLTA_FACILE 1
#define DIFFICOLTA_MEDIA 2
#define DIFFICOLTA_DIFFICILE 3
#define RIGA_ERRORE 22
#define COLONNA_ERRORE 27
#define SALVA_PARTITA 2
#define GIOCA 1
#define TORNA_MENU 3
#define RIGA_INIZIO_CORNICE -4
#define PICCOLA 1
#define MEDIA 2
#define GRANDE 3

#define BLU "\033[34m"
#define RESET "\033[0m"

/*******************************************************
* FUNZIONE: avviarePartita                             *
*                                                      *
* DESCRIZIONE: Avvia una nuova partita di Sudoku,      *
*              gestendo la logica di gioco fino alla   *
*              sua conclusione.                        *
*                                                      *
* ARGOMENTI:                                           *
* inputNome: nome della partita (stringa)              *
* inputDifficolta: livello di difficoltà               *
* inputDimensione: dimensione della scacchiera            *
*                                                      *
* RITORNO: permette all'utente di giocare al Sudoku    *
*******************************************************/
void avviarePartita(const char *inputNome) {
    int scacchieraPiena;
    int valido;
    int errore;
    Scacchiera scacchiera; 
    Partita partita;
    int valDaInserire, riga, colonna;
    int sceltaAzione;
    int dimensione;
    int difficolta;

    scacchieraPiena = FALSO;
    valido = FALSO;
    errore = FALSO;

    inizializzareScacchieraPartita(&partita, dimensione);
    scrivereNomePartita(&partita, (char *)inputNome);

    convertireDimensione(&dimensione);
    while (scacchieraPiena == FALSO) {
        mostraSchermo(dimensione);
        stampareScacchieraPartita(&partita);
        stampareTabellaInput();

        if (errore == VERO) {
            mostrareMessaggioErrore("Inserisci valori corretti", RIGA_ERRORE + 2, COLONNA_ERRORE);
            errore = FALSO;
        }

        spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT );
        printf(">> ");
        scanf("%d", &sceltaAzione);
        pulireBuffer();

        if (sceltaAzione == GIOCA) {
            scacchiera = leggereScacchieraPartita(&partita);
            collezionareInput(&scacchiera, &riga, RIGA_INPUT_RIGA);
            collezionareInput(&scacchiera, &colonna, RIGA_INPUT_COLONNA);
            collezionareInput(&scacchiera, &valDaInserire, RIGA_INPUT_VALORE);

                errore = VERO;
            } else {
                if (valido == VERO) {
                    scacchieraPiena = controllareScacchieraPiena(leggereScacchieraPartita(&partita));
                } else {
                    errore = VERO;
                }
            }
        } if (sceltaAzione == SALVA_PARTITA) {
        } else if (sceltaAzione == TORNA_MENU) {
            avviareMenuPrincipale();
        } else {
          errore = VERO;
        } 
    }
    stampareVittoria();
}


/*******************************************************
* FUNZIONE: mostraSchermo                              *
*                                                      *
* DESCRIZIONE: Pulisce lo schermo e, se la dimensione  *
*              non è 16, stampa anche il titolo del    *
*              gioco.                                  *
*                                                      *
* ARGOMENTI:                                           *
* dimensione: dimensione della scacchiera di gioco        *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void mostraSchermo(int dimensione) {
    if (dimensione != 16) {
        stampareTitoloPartita();
    } else {
        pulireSchermo();
        printf("\n");
    }
}


/*******************************************************
* FUNZIONE: stampareTitoloPartita                      *
*                                                      *
* DESCRIZIONE: Pulisce lo schermo e stampa il titolo   *
*              artistico del gioco in formato ASCII,   *
*              centrato e colorato.                    *
*                                                      *
* ARGOMENTI: Nessuno                                   *
*                                                      *
* RITORNO: Titolo stampato al centro del terminale     *
*******************************************************/
void stampareTitoloPartita() {
    printf(BLU);
    pulireSchermo();
    printf("\n");
    stampareCentrato("                    _   _ _              ");
    stampareCentrato(" ___    ___ ___ ___| |_|_| |_ ___    ___ ");
    stampareCentrato("|___|  | . | .'|  _|  _| |  _| .'|  |___|");
    stampareCentrato("       |  _|__,|_| |_| |_|_| |__,|       ");
    stampareCentrato("       |_|                               ");
    printf("\n");
    printf(RESET);
}


/*********************************************************
* FUNZIONE: stampareVittoria                             *
*                                                        *
* DESCRIZIONE: Pulisce lo schermo e stampa a video un    *
*              messaggio di vittoria.                    *
*                                                        *
* ARGOMENTI: Nessuno                                     *
*                                                        *
* RITORNO: Terminale aggiornato con la stampa del titolo *
*********************************************************/
void stampareVittoria() {
    int input;
    pulireSchermo();
    printf("\n\n\n");

    stampareCentrato(" _   _    _    ___ ");
    stampareCentrato("| | | |  / \\  |_ _|");
    stampareCentrato("| |_| | / _ \\  | | ");
    stampareCentrato("|  _  |/ ___ \\ | | ");
    stampareCentrato("|_| |_/_/   \\_\\___|");
    printf("\n\n");

    stampareCentrato("__     _____ _   _ _____ ___  ");
    stampareCentrato("\\ \\   / /_ _| \\ | |_   _/ _ \\ ");
    stampareCentrato(" \\ \\ / / | ||  \\| | | || | | |");
    stampareCentrato("  \\ V /  | || |\\  | | || |_| |");
    stampareCentrato("   \\_/  |___|_| \\_| |_| \\___/ ");
    tornareHomepage(&input, RIGA_INPUT - 10, 30);
}


/*******************************************************
* FUNZIONE: stampareTabellaInput                       *
*                                                      *
* DESCRIZIONE: Disegna la cornice e stampa la tabella  *
*              con le etichette per l'inserimento di   *
*              riga, colonna e valore. Mostra anche le *
*              istruzioni per salvare o tornare alla   *
*              homepage.                               *
*                                                      *
* ARGOMENTI: Nessuno                                   *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void stampareTabellaInput() {
    disegnareCornice();
    
    spostareCursore(RIGA_INPUT_RIGA - 4, COLONNA_INPUT);
    printf("-Azione-");
    spostareCursore(RIGA_INPUT_RIGA - 1, COLONNA_INPUT + 1);
    printf("-Riga-");
    spostareCursore(RIGA_INPUT_COLONNA - 1, COLONNA_INPUT);
    printf("-Colonna-");
    spostareCursore(25, 17);
    printf("\033[34m azione: (1 giocare / 2 salvare / 3 uscire) \033[0m");
}


/*******************************************************
* FUNZIONE: disegnareCornice                           *
*                                                      *
* DESCRIZIONE: Disegna a schermo una cornice grafica   *
*              per l'input, con intestazione e         *
*              spazio per riga, colonna e valore.      *
*                                                      *
* ARGOMENTI: Nessuno                                   *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void disegnareCornice() {
    int i; 
    
    spostareCursore(RIGA_INPUT_RIGA - 5, COLONNA_INPUT - 2);
    printf("+------------+\n");
    spostareCursore(RIGA_INPUT_RIGA - 6, COLONNA_INPUT - 2);
    printf("|   Input    |\n");
    spostareCursore(RIGA_INPUT_RIGA - 7, COLONNA_INPUT - 2);
    printf("+------------+\n");
    
    i = RIGA_INIZIO_CORNICE;
    while (i < 5) {
        spostareCursore(RIGA_INPUT_RIGA + i, COLONNA_INPUT - 2);
        printf("|            |\n");
        i = i + 1;
    }
    
    spostareCursore(RIGA_INPUT_RIGA + 7, COLONNA_INPUT - 2);
    printf("+------------+\n");
}


/*******************************************************
* FUNZIONE: convertireDimensione                       *
*                                                      *
* DESCRIZIONE: Converte un valore numerico associato   *
*              a una scelta dell'utente (1, 2 o 3)     *
*              nella dimensione effettiva della scacchiera*
*              (4, 9 o 16).                            *
*                                                      *
* ARGOMENTI:                                           *
* dimensione: puntatore alla dimensione scelta         *
*                                                      *
* RITORNO: valore di dimensione aggiornato             *
*******************************************************/
void convertireDimensione(int *dimensione) {
    if (*dimensione == PICCOLA) {
        *dimensione = 4;
    } else {
        if (*dimensione == MEDIA) {
            *dimensione = 9;
        } else {
            if (*dimensione == GRANDE) {
                *dimensione = 16;
            }
        }
    }
}


/*******************************************************
* FUNZIONE: stampareScacchieraPartita                      *
*                                                       *
* DESCRIZIONE: Stampa a video la scacchiera Sudoku         *
*              corrente della partita, includendo       *
*              intestazioni di colonna e linee          *
*              orizzontali per una migliore leggibilità *
*                                                       *
* ARGOMENTI:                                            *
* partita: puntatore alla struttura della partita       *
*                                                       *
* RITORNO: Terminale aggiornato                         *
*                                                       *
********************************************************/
void stampareScacchieraPartita(Partita *partita) {
    Scacchiera scacchiera; 
    int dimensione; 
    int numeroSottoquadrato;

    scacchiera = leggereScacchieraPartita(partita);
    dimensione = leggereDimScacchiera(scacchiera);
    numeroSottoquadrato = calcolareSottoquadrato(dimensione);

    stampareIntestazioneColonne(dimensione, numeroSottoquadrato);
    stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
    stampareRigheScacchiera(scacchiera);
    stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
}


/********************************************************
* FUNZIONE: calcolareSottoquadrato                       *
*                                                        *
* DESCRIZIONE: Calcola la dimensione del sottoquadrato   *
*              (blocco) di una scacchiera Sudoku            *
*              in base alla dimensione totale della      *
*              scacchiera.                                  *
*                                                        *
* ARGOMENTI:                                             *
* dimensione: dimensione della scacchiera Sudoku            *
*                                                        *
* RITORNO:                                               *
* Intero che rappresenta la dimensione del sottoquadrato *
* (ad esempio, 3 per una scacchiera 9x9, 4 per 16x16)       *
*********************************************************/
int calcolareSottoquadrato(int dimensione) {
    int risultato;

    risultato = 2;
    if (dimensione == 9) {
        risultato = 3;
    } else {
        if (dimensione == 16) {
            risultato = 4;
        }
    }
    return risultato;
}


/*******************************************************
* FUNZIONE: stampareIntestazioneColonne                 *
*                                                       *
* DESCRIZIONE: Stampa l'intestazione delle colonne      *
*              numerate della scacchiera Sudoku,           *
*              formattando gli spazi in base alla       *
*              dimensione e alla dimensione del         *
*              sottoquadrato per una migliore           *
*              leggibilità.                             *
*                                                       *
* ARGOMENTI:                                            *
* dimensione: numero totale di colonne della scacchiera    *
* numeroSottoquadrato: dimensione del sottoquadrato     *
*                                                       *
* RITORNO: Terminale aggiornato                         *
********************************************************/
void stampareIntestazioneColonne(int dimensione, int numeroSottoquadrato) {
    int j;

    j = 0;
    printf("    ");
    while (j < dimensione) {
        if (dimensione == 16 && j + 1 < 10) {
            printf("  %d", j + 1);
        } else {
            printf("%3d", j + 1);
        }
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf("  ");
        }
        j = j + 1;
    }
    printf("\n");
}


/*******************************************************
* FUNZIONE: stampareLineaOrizzontale                   *
*                                                      *
* DESCRIZIONE: Stampa una linea orizzontale            *
*              formattata per separare i sottoquadrati *
*              nella scacchiera Sudoku durante la stampa. *
*                                                      *
* ARGOMENTI:                                           *
* dimensione: dimensione della scacchiera                 *
* numeroSottoquadrato: dimensione del sottoquadrato    *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void stampareLineaOrizzontale(int dimensione, int numeroSottoquadrato) {
    int j;
    j = 0;
    printf("   +");
    while (j < dimensione) {
        printf("---");
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf("-+");
        }
        j = j + 1;
    }
    printf("-+\n");
}


/*******************************************************
* FUNZIONE: stampareRigheScacchiera                       *
*                                                      *
* DESCRIZIONE: Stampa tutte le righe della scacchiera     *
*              Sudoku, separando i sottoquadrati con   *
*              linee orizzontali per una migliore      *
*              leggibilità.                            *
*                                                      *
* ARGOMENTI:                                           *
* scacchiera: struttura della scacchiera Sudoku              *
* dimensione: dimensione della scacchiera                 *
* numeroSottoquadrato: dimensione del sottoquadrato    *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void stampareRigheScacchiera(Scacchiera scacchiera) {
    int i;
    int dimensione;
    int numeroSottoquadrato;

    dimensione = leggereDimScacchiera(scacchiera);
    numeroSottoquadrato = calcolareSottoquadrato(dimensione);

    i = 0;
    while (i < dimensione) {
        stampareRigaScacchiera(scacchiera, i);
        
        if ((i + 1) % numeroSottoquadrato == 0 && i != dimensione - 1) {
            stampareLineaOrizzontale(dimensione, numeroSottoquadrato);
        }
        i = i + 1;
    }
}


/*******************************************************
* FUNZIONE: stampareRigaScacchiera                        *
*                                                      *
* DESCRIZIONE: Stampa una singola riga della scacchiera   *
*              Sudoku, visualizzando i numeri o un     *
*              punto ('.') per celle vuote, con        *
*              separatori per i sottoquadrati.         *
*                                                      *
* ARGOMENTI:                                           *
* scacchiera: struttura della scacchiera Sudoku              *
* dimensione: dimensione della scacchiera                 *
* numeroSottoquadrato: dimensione del sottoquadrato    *
* riga: indice della riga da stampare                  *
*                                                      *
*******************************************************/
void stampareRigaScacchiera(Scacchiera scacchiera, int riga) {
    int j; 
    int valore;
    int dimensione;
    int numeroSottoquadrato;

    dimensione = leggereDimScacchiera(scacchiera);
    numeroSottoquadrato = calcolareSottoquadrato(dimensione);


    
    j = 0;
    if (dimensione == 16) {
        printf("%2d |", riga + 1);
    } else {
        printf("%2d |", riga + 1);
    }
    
    while (j < dimensione) {
        if (valore == 0) {
            printf("  .");
        } else {
            printf("%3d", valore);
        }
        
        if ((j + 1) % numeroSottoquadrato == 0 && j != dimensione - 1) {
            printf(" |");
        }
        j = j + 1;
    }
    printf(" |\n");
}


/********************************************************
* FUNZIONE: collezionareInput                           *
*                                                       *
* DESCRIZIONE: Gestisce la raccolta sicura di un        *
*              input numerico da tastiera, effettuando  *
*              controlli di validità e fornendo         *
*              messaggi di errore fino a ottenere un    *
*              valore corretto o l'uscita al menu       *
*              principale.                              *
*                                                       *
* ARGOMENTI:                                            *
* partita: puntatore alla struttura della partita       *
* scacchiera: puntatore alla struttura della scacchiera       *
* inputRiga: puntatore a intero dove memorizzare        *
*           l'input acquisito                           *
* posRiga: posizione verticale dello spazio di input    *
*          nella UI (per la gestione dei messaggi)      *
*                                                       *
* RITORNO:                                              *
* Valore intero inserito dall'utente, se valido, o      *
* attivazione del menu principale in caso di input      *
* speciale (32).                                        *
********************************************************/
int collezionareInput(Scacchiera *scacchiera, int *input, int rigaTerminale) {
    int valida;
    int inputOk;

    valida = FALSO;
    while (valida == FALSO) {
        reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
        inputOk = FALSO;

        // questa parte non e' inclusa nello pseudocodice perche' 
        // diamo per supposto che input sia un numero
        while (inputOk == FALSO) {
            if (scanf("%d", input) == 1) {
                inputOk = VERO;
            } else {
                pulireBuffer();
                reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
                mostrareMessaggioErrore("Digita un Numero", RIGA_ERRORE + 2, COLONNA_ERRORE);
                reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
            }
        }

        pulireBuffer();

        if (*input < 1 || *input > leggereDimScacchiera(*scacchiera)) {
            mostrareMessaggioErrore("Numero fuori intervallo", RIGA_ERRORE + 2, COLONNA_ERRORE);
            reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
        } else {
            valida = VERO;
        }
    }
    return *input;
}

/*******************************************************
* FUNZIONE: controllareScacchieraPiena                    *
*                                                      *
* DESCRIZIONE: Verifica se la scacchiera Sudoku è         *
*              completamente riempita, cioè se non ci  *
*              sono celle vuote (valore 0).            *
*                                                      *
* ARGOMENTI:                                           *
* scacchiera: struttura della scacchiera Sudoku              *
*                                                      *
* RITORNO:                                             *
* VERO se la scacchiera è piena,                          *
* FALSO se esiste almeno una cella vuota               *
*******************************************************/
int controllareScacchieraPiena(Scacchiera scacchiera) {
    int dimensione;
    int cursRiga;
    int cursColonna; 
    int esito;

    esito = VERO;
    dimensione = leggereDimScacchiera(scacchiera);

    cursRiga = 0;
    while (cursRiga < dimensione && esito == VERO) {
        cursColonna = 0;
        while (cursColonna < dimensione && esito == VERO) {
            if (leggereStatoScacchiera(scacchiera, cursRiga, cursColonna) == 0) {
                esito = FALSO;
            } else {
                cursColonna = cursColonna + 1;
            }
        }
        if (esito == VERO) {
            cursRiga = cursRiga + 1;
        }
    }
    return esito;
}



/*************************************************************
* FUNZIONE: avviarePartitaContinuata                          *
*                                                             *
* DESCRIZIONE: Gestisce il ciclo di gioco di una              *
*              partita Sudoku già iniziata,                   *
*              permettendo all'utente di inserire             *
*              valori, salvare la partita e controllare       *
*              la validità delle mosse fino al completamento. *
*                                                             *
* ARGOMENTI:                                                  *
* partita: puntatore alla struttura della partita             *
*                                                             *
* RITORNO: permette all'utente di giocare                     *
*************************************************************/
void avviarePartitaContinuata(Partita *partita) {
    Scacchiera scacchiera;
    int dimensione;
    int valore, riga, colonna;
    int scacchieraPiena;
    int valido;
    int errore;
    int sceltaAzione;

    dimensione = leggereDimScacchiera(leggereScacchieraPartita(partita));
    scacchieraPiena = FALSO;
    valido = FALSO;
    errore = FALSO;

    while (scacchieraPiena == FALSO) {
        mostraSchermo(dimensione);
        stampareScacchieraPartita(partita);
        stampareTabellaInput();

        if (errore == VERO) {
            mostrareMessaggioErrore("Inserisci valori corretti", RIGA_ERRORE + 2, COLONNA_ERRORE);
            errore = FALSO;
        }

        spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT );
        printf(">> ");
        scanf("%d", &sceltaAzione);
        pulireBuffer();

        if (sceltaAzione == 1) {
            scacchiera = leggereScacchieraPartita(partita);
            collezionareInput(&scacchiera, &riga, RIGA_INPUT_RIGA);
            collezionareInput(&scacchiera, &colonna, RIGA_INPUT_COLONNA);
            collezionareInput(&scacchiera, &valore, RIGA_INPUT_VALORE);

            if (valido == VERO) {
                scacchieraPiena = controllareScacchieraPiena(leggereScacchieraPartita(partita));
            } else {
                errore = VERO;
            }
        } else if (sceltaAzione == 2) {
          return;
        } else if (sceltaAzione == 3) {
            avviareMenuPrincipale();
        } else {
          errore = VERO;
        }
    }
    stampareVittoria();
}

