/*
AUTORI: Onofrio de Robertis
        Michele Amato
        Davide Fornelli
        Giuliano Antoniciello

DATA INIZIO: 27/05/2024
DATA MODIFICA: 22/07/2025

NOME FILE: partita.c (versione Othello)

MODIFICHE:
- Adattato per gioco Othello
- Griglia 8x8
- Logica di flip pedine
- Controllo mosse valide
- Turni giocatore 1 (nero) e 2 (bianco)
*/

#include <stdio.h>
#include "../include/tipiDiDato.h"
#include "../include/partita.h"
#include "../include/funzioniUtilita.h"
#include "../include/caricaPartita.h"

#define DIM_OTHELLO 8
#define VUOTO 0
#define NERO 1
#define BIANCO 2

#define PICCOLA 1
#define MEDIA 2
#define GRANDE 3

/**
 * DESCRIZIONE: Avvia una nuova partita Othello.
 * ARGOMENTI:
 *   nomePartita: nome della partita
 *   modalita: modalità di gioco
 *   dimensione: dimensione della scacchiera
 * RITORNO: nessuno
 */
void avviarePartita(char nomePartita[50], int modalita, int dimensione) {
    Partita partita;
    int turno;
    int riga;
    int colonna;
    int fine;
    int numeroNeri;
    int numeroBianchi;
    int meta;
    char sceltaSalvataggio;

    turno = NERO;
    fine = 0;
    numeroNeri = 0;
    numeroBianchi = 0;
    riga = 0;
    colonna = 0;
    sceltaSalvataggio = 'n';
    meta = 0;

    scrivereNomePartita(&partita, (char *)nomePartita);
    partita.modalita = modalita;
    scrivereDimScacchieraPartita(&partita, dimensione);
    inizializzareScacchieraPartita(&partita, dimensione);

    if (dimensione >= 4 && modulo(dimensione, 2) == 0) {
        meta = dimensione / 2;
        scrivereStatoScacchieraPartita(&partita, NERO, meta - 1, meta - 1);
        scrivereStatoScacchieraPartita(&partita, BIANCO, meta - 1, meta);
        scrivereStatoScacchieraPartita(&partita, BIANCO, meta, meta - 1);
        scrivereStatoScacchieraPartita(&partita, NERO, meta, meta);
    }

    pulireBuffer();

    while (fine == 0) {
        pulireSchermo();
        stampareScacchieraOthello(&partita);

        numeroNeri = contarePedine(&partita, NERO);
        numeroBianchi = contarePedine(&partita, BIANCO);
        printf("\nTurno: %s   Nero: %d   Bianco: %d\n",
               (turno == NERO ? "Nero" : "Bianco"), numeroNeri, numeroBianchi);

        printf("Vuoi salvare la partita? (s/n): ");
        scanf(" %c", &sceltaSalvataggio);
        pulireBuffer();
        if (sceltaSalvataggio == 's' || sceltaSalvataggio == 'S') {
            salvarePartita(&partita);
            printf("Partita salvata! Premi invio per continuare...");
            getchar();
        }

        if (nessunaMossaPossibile(&partita, turno) == 1) {
            printf("Nessuna mossa disponibile per %s.\n",
                   (turno == NERO ? "Nero" : "Bianco"));
            if (turno == NERO) {
                turno = turno + 1;
            } else {
                turno = turno - 1;
            }
            if (nessunaMossaPossibile(&partita, turno) == 1) {
                fine = 1;
            }
            continue;
        }

        printf("Inserisci riga e colonna (1-%d, es. 4 5): ", dimensione);
        scanf("%d %d", &riga, &colonna);
        pulireBuffer();

        if (riga < 1 || riga > dimensione || colonna < 1 || colonna > dimensione) {
            printf("Valori fuori range.\n");
            continue;
        }

        riga = riga - 1;
        colonna = colonna - 1;

        if (mossaValida(&partita, riga, colonna, turno) == 0) {
            printf("Mossa non valida.\n");
            continue;
        }

        eseguiMossa(&partita, riga, colonna, turno);
        if (turno == NERO) {
            turno = turno + 1;
        } else {
            turno = turno - 1;
        }
    }

    stampareVittoriaOthello(numeroNeri, numeroBianchi);
}

/**
 * DESCRIZIONE: Avvia una partita Othello continuata da uno stato salvato.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita già caricata
 * RITORNO: nessuno
 */
void avviarePartitaContinuata(Partita *partita) {
    int turno;
    int dimensione;
    int riga;
    int colonna;
    int fine;
    int numeroNeri;
    int numeroBianchi;
    char sceltaSalvataggio;

    turno = NERO;
    dimensione = leggereDimScacchiera(partita->scacchieraPartita);
    riga = 0;
    colonna = 0;
    fine = 0;
    numeroNeri = 0;
    numeroBianchi = 0;
    sceltaSalvataggio = 'n';

    numeroNeri = contarePedine(partita, NERO);
    numeroBianchi = contarePedine(partita, BIANCO);
    if (numeroNeri > numeroBianchi) {
        turno = BIANCO;
    } else {
        turno = NERO;
    }

    pulireBuffer();
    while (fine == 0) {
        pulireSchermo();
        stampareScacchieraOthello(partita);
        numeroNeri = contarePedine(partita, NERO);
        numeroBianchi = contarePedine(partita, BIANCO);
        printf("\nTurno: %s   Nero: %d   Bianco: %d\n",
               (turno == NERO ? "Nero" : "Bianco"), numeroNeri, numeroBianchi);
        printf("Vuoi salvare la partita? (s/n): ");
        scanf(" %c", &sceltaSalvataggio);
        pulireBuffer();
        if (sceltaSalvataggio == 's' || sceltaSalvataggio == 'S') {
            salvarePartita(partita);
            printf("Partita salvata! Premi invio per continuare...");
            getchar();
        }
        if (nessunaMossaPossibile(partita, turno) == 1) {
            printf("Nessuna mossa disponibile per %s.\n",
                   (turno == NERO ? "Nero" : "Bianco"));
            if (turno == NERO) {
                turno = turno + 1;
            } else {
                turno = turno - 1;
            }
            if (nessunaMossaPossibile(partita, turno) == 1) {
                fine = 1;
            }
            continue;
        }
        printf("Inserisci riga e colonna (1-%d, es. 4 5): ", dimensione);
        scanf("%d %d", &riga, &colonna);
        pulireBuffer();
        if (riga < 1 || riga > dimensione || colonna < 1 || colonna > dimensione) {
            printf("Valori fuori range.\n");
            continue;
        }
        riga = riga - 1;
        colonna = colonna - 1;
        if (mossaValida(partita, riga, colonna, turno) == 0) {
            printf("Mossa non valida.\n");
            continue;
        }
        eseguiMossa(partita, riga, colonna, turno);
        if (turno == NERO) {
            turno = turno + 1;
        } else {
            turno = turno - 1;
        }
    }
    stampareVittoriaOthello(numeroNeri, numeroBianchi);
}

// === INIZIALIZZAZIONE ===
/**
 * DESCRIZIONE: Inizializza una partita Othello con la posizione iniziale standard.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita da inizializzare
 * RITORNO: nessuno
 */
void inizializzarePartitaOthello(Partita *partita) {
    int dimensione;
    dimensione = DIM_OTHELLO;
    scrivereDimScacchieraPartita(partita, dimensione);
    inizializzareScacchieraPartita(partita, dimensione);
    scrivereStatoScacchieraPartita(partita, NERO, 3, 3);
    scrivereStatoScacchieraPartita(partita, BIANCO, 3, 4);
    scrivereStatoScacchieraPartita(partita, BIANCO, 4, 3);
    scrivereStatoScacchieraPartita(partita, NERO, 4, 4);
}

// === CONTROLLO VALIDITÀ MOSSA ===
/**
 * DESCRIZIONE: Controlla se una mossa è valida per il giocatore (più leggibile e robusta).
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   riga: riga della mossa
 *   colonna: colonna della mossa
 *   giocatore: colore del giocatore (NERO/BIANCO)
 * RITORNO: 1 se valida, 0 altrimenti
 */
int mossaValida(Partita *partita, int riga, int colonna, int giocatore) {
    int direzioniRiga[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int direzioniColonna[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int indiceDirezione;
    int pedineFlippabili;
    int cellaOccupata;
    int mossaValidaTrovata;

    cellaOccupata = (leggereStatoScacchiera(leggereScacchieraPartita(partita), riga, colonna) != VUOTO);
    mossaValidaTrovata = 0;
    indiceDirezione = 0;
    if (cellaOccupata == 0) {
        while (indiceDirezione < 8) {
            pedineFlippabili = pedineDaFlippareInDirezione(partita, riga, colonna, direzioniRiga[indiceDirezione], direzioniColonna[indiceDirezione], giocatore);
            if (pedineFlippabili > 0) {
                mossaValidaTrovata = 1;
            }
            indiceDirezione = indiceDirezione + 1;
        }
    }
    return mossaValidaTrovata;
}

// === ESECUZIONE MOSSA ===
/**
 * DESCRIZIONE: Esegue una mossa e aggiorna la scacchiera.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   riga: riga della mossa
 *   colonna: colonna della mossa
 *   giocatore: colore del giocatore
 * RITORNO: nessuno
 */
void eseguiMossa(Partita *partita, int riga, int colonna, int giocatore) {
    scrivereStatoScacchieraPartita(partita, giocatore, riga, colonna);
    flipPedine(partita, riga, colonna, giocatore);
}

// === FLIP PEDINE ===
/**
 * DESCRIZIONE: Flippa le pedine in tutte le direzioni dopo una mossa valida (più leggibile e robusta).
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   riga: riga della mossa
 *   colonna: colonna della mossa
 *   giocatore: colore del giocatore
 * RITORNO: nessuno
 */
void flipPedine(Partita *partita, int riga, int colonna, int giocatore) {
    int direzioniRiga[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int direzioniColonna[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int indiceDirezione;
    int pedineDaFlippare;
    int passo;
    int nuovaRiga;
    int nuovaColonna;

    indiceDirezione = 0;
    while (indiceDirezione < 8) {
        pedineDaFlippare = pedineDaFlippareInDirezione(partita, riga, colonna, direzioniRiga[indiceDirezione], direzioniColonna[indiceDirezione], giocatore);
        passo = 1;
        while (passo <= pedineDaFlippare) {
            nuovaRiga = riga + direzioniRiga[indiceDirezione] * passo;
            nuovaColonna = colonna + direzioniColonna[indiceDirezione] * passo;
            scrivereStatoScacchieraPartita(partita, giocatore, nuovaRiga, nuovaColonna);
            passo = passo + 1;
        }
        indiceDirezione = indiceDirezione + 1;
    }
}

// === CONTA PEDINE DA FLIPPARE IN UNA DIREZIONE ===
/**
 * DESCRIZIONE: Conta quante pedine si possono flippare in una direzione.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   riga: riga di partenza
 *   colonna: colonna di partenza
 *   dr: direzione riga
 *   dc: direzione colonna
 *   giocatore: colore del giocatore
 * RITORNO: numero di pedine da flippare
 */
int pedineDaFlippareInDirezione(Partita *partita, int riga, int colonna, int dr, int dc, int giocatore) {
    int dimensione;
    int avversario;
    int conteggio;
    int valore;
    int esito;

    dimensione = leggereDimScacchiera(partita->scacchieraPartita);
    avversario = NERO;
    if (giocatore == NERO) {
        avversario = BIANCO;
    }
    conteggio = 0;
    riga = riga + dr;
    colonna = colonna + dc;
    esito = 0;
    while (riga >= 0 && riga < dimensione && colonna >= 0 && colonna < dimensione && esito == 0) {
        valore = leggereStatoScacchiera(leggereScacchieraPartita(partita), riga, colonna);
        if (valore == avversario) {
            conteggio = conteggio + 1;
        } else if (valore == giocatore) {
            esito = 1;
        } else {
            esito = 2;
        }
        riga = riga + dr;
        colonna = colonna + dc;
    }
    if (esito == 1) {
        return conteggio;
    } else {
        return 0;
    }
}

// === CONTROLLO FINE PARTITA ===
/**
 * DESCRIZIONE: Controlla se non ci sono mosse possibili per il giocatore.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   giocatore: colore del giocatore
 * RITORNO: 1 se nessuna mossa possibile, 0 altrimenti
 */
int nessunaMossaPossibile(Partita *partita, int giocatore) {
    int dimensione;
    int riga;
    int colonna;
    int trovato;
    int esito;

    dimensione = leggereDimScacchiera(partita->scacchieraPartita);
    riga = 0;
    trovato = 0;
    esito = 1;
    while (riga < dimensione) {
        colonna = 0;
        while (colonna < dimensione) {
            if (mossaValida(partita, riga, colonna, giocatore) == 1) {
                trovato = 1;
            }
            colonna = colonna + 1;
        }
        riga = riga + 1;
    }
    if (trovato == 1) {
        esito = 0;
    }
    return esito;
}

// === STAMPA SCACCHIERA ===
/**
 * DESCRIZIONE: Stampa la scacchiera Othello a schermo.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 * RITORNO: nessuno
 */
void stampareScacchieraOthello(Partita *partita) {
    int dimensione;
    int colonna;
    int riga;
    int valore;
    char simbolo;

    dimensione = leggereDimScacchiera(partita->scacchieraPartita);
    printf("\n    ");
    colonna = 0;
    while (colonna < dimensione) {
        printf(" %d ", colonna + 1);
        colonna = colonna + 1;
    }
    printf("\n   +");
    colonna = 0;
    while (colonna < dimensione) {
        printf("---+");
        colonna = colonna + 1;
    }
    printf("\n");
    riga = 0;
    while (riga < dimensione) {
        printf(" %d |", riga + 1);
        colonna = 0;
        while (colonna < dimensione) {
            valore = leggereStatoScacchiera(leggereScacchieraPartita(partita), riga, colonna);
            simbolo = '.';
            if (valore == NERO) {
                simbolo = 'N';
            } else if (valore == BIANCO) {
                simbolo = 'B';
            }
            printf(" %c |", simbolo);
            colonna = colonna + 1;
        }
        printf("\n   +");
        colonna = 0;
        while (colonna < dimensione) {
            printf("---+");
            colonna = colonna + 1;
        }
        printf("\n");
        riga = riga + 1;
    }
}

// === CONTA PEDINE ===
/**
 * DESCRIZIONE: Conta il numero di pedine di un giocatore sulla scacchiera.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   giocatore: colore del giocatore
 * RITORNO: numero di pedine
 */
int contarePedine(Partita *partita, int giocatore) {
    int dimensione;
    int riga;
    int colonna;
    int conteggio;

    dimensione = leggereDimScacchiera(partita->scacchieraPartita);
    riga = 0;
    conteggio = 0;
    while (riga < dimensione) {
        colonna = 0;
        while (colonna < dimensione) {
            if (leggereStatoScacchiera(leggereScacchieraPartita(partita), riga, colonna) == giocatore) {
                conteggio = conteggio + 1;
            }
            colonna = colonna + 1;
        }
        riga = riga + 1;
    }
    return conteggio;
}

// === STAMPA VITTORIA ===
/**
 * DESCRIZIONE: Stampa il risultato della partita Othello.
 * ARGOMENTI:
 *   neri: numero di pedine nere
 *   bianchi: numero di pedine bianche
 * RITORNO: nessuno
 */
void stampareVittoriaOthello(int neri, int bianchi) {
    int input;
    pulireSchermo();
    printf("\n\n");
    stampareCentrato("Partita terminata!");
    printf("\n");
    printf("Nero: %d pedine\n", neri);
    printf("Bianco: %d pedine\n", bianchi);
    if (neri > bianchi) {
        stampareCentrato("Vince il NERO!");
    } else if (bianchi > neri) {
        stampareCentrato("Vince il BIANCO!");
    } else {
        stampareCentrato("PAREGGIO!");
    }
    input = 0;
    tornareHomepage(&input, 20, 30);
}

/**
 * DESCRIZIONE: Converte la dimensione simbolica in valore numerico.
 * ARGOMENTI:
 *   dimensione: puntatore alla variabile dimensione
 * RITORNO: nessuno
 */
void convertireDimensione(int *dimensione) {
    if (*dimensione == PICCOLA) {
        *dimensione = 4;
    } else if (*dimensione == MEDIA) {
        *dimensione = 8;
    } else if (*dimensione == GRANDE) {
        *dimensione = 16;
    }
}
