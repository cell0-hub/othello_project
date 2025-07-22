/*
AUTORI: Onofrio de Robertis
        Michele Amato
        Davide Fornelli
        Giuliano Antoniciello
DATA INIZIO: 27/05/2024
DATA MODIFICA: 22/07/2025
*/

#include <stdio.h>
#include "../include/tipiDiDato.h"
#include "../include/partita.h"
#include "../include/funzioniUtilita.h"
#include "../include/caricaPartita.h"
#include "../include/homepage.h"

#define DIM_OTHELLO 8
#define VUOTO 0
#define NERO 1
#define BIANCO 2

#define BLU   "\033[34m"
#define RESET "\033[0m"

#define RIGA_INPUT_RIGA   13
#define RIGA_INPUT_COL    16
#define RIGA_INPUT_VAL    19
#define RIGA_INPUT        28
#define COLONNA_INPUT     67
#define COLONNA_ERRORE    27

void stampareTitoloPartita(){
  stampareCentrato("                           _   _ _                 ");
  stampareCentrato("                          | | (_) |                ");
  stampareCentrato(" ______   _ __   __ _ _ __| |_ _| |_ __ _   ______ ");
  stampareCentrato("|______| | '_ \\ / _` | '__| __| | __/ _` | |______|");
  stampareCentrato("         | |_) | (_| | |  | |_| | || (_| |         ");
  stampareCentrato("         | .__/ \\__,_|_|   \\__|_|\\__\\__,_|         ");
  stampareCentrato("         | |                                       ");
  stampareCentrato("         |_|                                       ");
}

void stampaLineaOrizz(Partita *partita) {
    int indiceColonna;
    int dimensioneScacc;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    printf("   +");
    
    indiceColonna = 0;
    while (indiceColonna < dimensioneScacc) {
        printf("---");
        indiceColonna = indiceColonna + 1;
    }
    printf("-+\n");
}

void stampaIntestColonne(Partita *partita) {
    int indiceColonna;
    int dimensioneScacc;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    printf("    ");
    
    indiceColonna = 0;
    while (indiceColonna < dimensioneScacc) {
        printf("%3d", indiceColonna + 1);
        indiceColonna = indiceColonna + 1;
    }
    printf("\n");
}

void stampaScacchiera(Partita *partita) {
    int indiceRiga;
    int indiceColonna;
    int dimensioneScacc;
    int valoreCorrente;
    char carattereVisual;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    
    stampaIntestColonne(partita);
    stampaLineaOrizz(partita);
    
    indiceRiga = 0;
    while (indiceRiga < dimensioneScacc) {
        printf("%2d |", indiceRiga + 1);
        
        indiceColonna = 0;
        while (indiceColonna < dimensioneScacc) {
            valoreCorrente = leggereStatoCasellaScacchiera(leggereScacchieraPartita(partita), indiceRiga, indiceColonna);
            carattereVisual = (valoreCorrente == NERO) ? 'N' : (valoreCorrente == BIANCO) ? 'B' : '.';
            printf("%3c", carattereVisual);
            indiceColonna = indiceColonna + 1;
        }
        printf(" |\n");
        indiceRiga = indiceRiga + 1;
    }
    stampaLineaOrizz(partita);
}

void disegnaCornice() {
    int contatoreCornice;
    
    spostareCursore(RIGA_INPUT_RIGA - 5, COLONNA_INPUT - 2);
    printf("+------------+\n");
    spostareCursore(RIGA_INPUT_RIGA - 6, COLONNA_INPUT - 2);
    printf("|   Input    |\n");
    spostareCursore(RIGA_INPUT_RIGA - 7, COLONNA_INPUT - 2);
    printf("+------------+\n");
    
    contatoreCornice = -4;
    while (contatoreCornice < 4) {
        spostareCursore(RIGA_INPUT_RIGA + contatoreCornice, COLONNA_INPUT - 2);
        printf("|            |\n");
        contatoreCornice = contatoreCornice + 1;
    }
    spostareCursore(RIGA_INPUT_RIGA + 4, COLONNA_INPUT - 2);
    printf("+------------+\n");
}

void stampaTabellaInput() {
    disegnaCornice();
    spostareCursore(RIGA_INPUT_RIGA - 4, COLONNA_INPUT);
    printf("-Azione-");
    spostareCursore(RIGA_INPUT_RIGA - 1, COLONNA_INPUT + 1);
    printf("-Riga-");
    spostareCursore(RIGA_INPUT_COL - 1, COLONNA_INPUT);
    printf("-Colonna-");
    spostareCursore(25, 17);
    printf("\033[34m azione: (1 giocare / 2 salvare / 3 uscire) \033[0m");
}

void stampaVittoria(int neriTotali, int bianchiTotali) {
    int inputUtente;
    
    pulireSchermo();
    printf("\n\n\n");
    stampareCentrato(" _   _    _    ___ ");
    stampareCentrato("| | | |  / \\  |_ _|");
    stampareCentrato("| |_| | / _ \\  | | ");
    stampareCentrato("|  _  |/ ___ \\ | | ");
    stampareCentrato("|_| |_/_/   \\_\\___|");
    printf("\n\n");
    printf("Nero: %d pedine\n", neriTotali);
    printf("Bianco: %d pedine\n", bianchiTotali);
    
    if (neriTotali > bianchiTotali) {
        stampareCentrato("VINCE IL NERO!");
    } else {
        if (bianchiTotali > neriTotali) {
            stampareCentrato("VINCE IL BIANCO!");
        } else {
            stampareCentrato("PAREGGIO!");
        }
    }
    tornareHomepage(&inputUtente, 20, 30);
}

/* =========================================================
   LOGICA DI GIOCO
========================================================= */

/**
 * DESCRIZIONE: Conta il numero di pedine di un giocatore sulla scacchiera.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   coloreGiocatore: colore del giocatore
 * RITORNO: numero di pedine
 */
int contaPedineGiocatore(Partita *partita, int coloreGiocatore) {
    int indiceRiga;
    int indiceColonna;
    int conteggioTotale;
    int dimensioneScacc;
    int valoreCorrente;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    conteggioTotale = 0;
    
    indiceRiga = 0;
    while (indiceRiga < dimensioneScacc) {
        indiceColonna = 0;
        while (indiceColonna < dimensioneScacc) {
            valoreCorrente = leggereStatoCasellaScacchiera(leggereScacchieraPartita(partita), indiceRiga, indiceColonna);
            if (valoreCorrente == coloreGiocatore) {
                conteggioTotale = conteggioTotale + 1;
            }
            indiceColonna = indiceColonna + 1;
        }
        indiceRiga = indiceRiga + 1;
    }
    return conteggioTotale;
}

/**
 * DESCRIZIONE: Conta quante pedine si possono flippare in una direzione.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   rigaInizio: riga di partenza
 *   colInizio: colonna di partenza
 *   deltaRiga: direzione riga
 *   deltaColonna: direzione colonna
 *   coloreGiocatore: colore del giocatore
 * RITORNO: numero di pedine da flippare
 */
int calcolaPedineFlipp(Partita *partita, int rigaInizio, int colInizio, 
                       int deltaRiga, int deltaColonna, int coloreGiocatore) {
    int coloreAvversario;
    int conteggioFlip;
    int valoreCorrente;
    int dimensioneScacc;
    int rigaCorrente;
    int colCorrente;
    int risultatoFlip;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    coloreAvversario = (coloreGiocatore == NERO) ? BIANCO : NERO;
    conteggioFlip = 0;
    risultatoFlip = 0;
    
    rigaCorrente = rigaInizio + deltaRiga;
    colCorrente = colInizio + deltaColonna;
    
    while (rigaCorrente >= 0 && rigaCorrente < dimensioneScacc && 
           colCorrente >= 0 && colCorrente < dimensioneScacc) {
        valoreCorrente = leggereStatoCasellaScacchiera(leggereScacchieraPartita(partita), rigaCorrente, colCorrente);
        
        if (valoreCorrente == coloreAvversario) {
            conteggioFlip = conteggioFlip + 1;
        } else {
            if (valoreCorrente == coloreGiocatore) {
                risultatoFlip = conteggioFlip;
            }
            rigaCorrente = dimensioneScacc; /* Forza uscita dal ciclo */
        }
        
        if (risultatoFlip == 0 && rigaCorrente < dimensioneScacc) {
            rigaCorrente = rigaCorrente + deltaRiga;
            colCorrente = colCorrente + deltaColonna;
        }
    }
    
    if (risultatoFlip == 0) {
        risultatoFlip = 0;
    }
    
    return risultatoFlip;
}

/**
 * DESCRIZIONE: Controlla se una mossa è valida per il giocatore.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   rigaInput: riga della mossa
 *   colInput: colonna della mossa
 *   coloreGiocatore: colore del giocatore (NERO/BIANCO)
 * RITORNO: 1 se valida, 0 altrimenti
 */
int verificaMossaValida(Partita *partita, int rigaInput, int colInput, int coloreGiocatore) {
    int direzioniRiga[8];
    int direzioniColonna[8];
    int indiceDir;
    int pedineFlippabili;
    int cellaOccupata;
    int mossaValidaTrovata;
    
    direzioniRiga[0] = -1; direzioniRiga[1] = -1; direzioniRiga[2] = -1; direzioniRiga[3] = 0;
    direzioniRiga[4] = 0; direzioniRiga[5] = 1; direzioniRiga[6] = 1; direzioniRiga[7] = 1;
    
    direzioniColonna[0] = -1; direzioniColonna[1] = 0; direzioniColonna[2] = 1; direzioniColonna[3] = -1;
    direzioniColonna[4] = 1; direzioniColonna[5] = -1; direzioniColonna[6] = 0; direzioniColonna[7] = 1;
    
    cellaOccupata = (leggereStatoCasellaScacchiera(leggereScacchieraPartita(partita), rigaInput, colInput) != VUOTO);
    mossaValidaTrovata = 0;
    
    if (cellaOccupata == 0) {
        indiceDir = 0;
        while (indiceDir < 8 && mossaValidaTrovata == 0) {
            pedineFlippabili = calcolaPedineFlipp(partita, rigaInput, colInput, 
                                                  direzioniRiga[indiceDir], direzioniColonna[indiceDir], 
                                                  coloreGiocatore);
            if (pedineFlippabili > 0) {
                mossaValidaTrovata = 1;
            }
            indiceDir = indiceDir + 1;
        }
    }
    return mossaValidaTrovata;
}

/**
 * DESCRIZIONE: Flippa le pedine in tutte le direzioni dopo una mossa valida.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   rigaInput: riga della mossa
 *   colInput: colonna della mossa
 *   coloreGiocatore: colore del giocatore
 * RITORNO: nessuno
 */
void eseguiFlipPedine(Partita *partita, int rigaInput, int colInput, int coloreGiocatore) {
    int direzioniRiga[8];
    int direzioniColonna[8];
    int indiceDir;
    int pedineFlippabili;
    int passoFlip;
    int nuovaRiga;
    int nuovaColonna;
    
    direzioniRiga[0] = -1; direzioniRiga[1] = -1; direzioniRiga[2] = -1; direzioniRiga[3] = 0;
    direzioniRiga[4] = 0; direzioniRiga[5] = 1; direzioniRiga[6] = 1; direzioniRiga[7] = 1;
    
    direzioniColonna[0] = -1; direzioniColonna[1] = 0; direzioniColonna[2] = 1; direzioniColonna[3] = -1;
    direzioniColonna[4] = 1; direzioniColonna[5] = -1; direzioniColonna[6] = 0; direzioniColonna[7] = 1;
    
    indiceDir = 0;
    while (indiceDir < 8) {
        pedineFlippabili = calcolaPedineFlipp(partita, rigaInput, colInput, 
                                              direzioniRiga[indiceDir], direzioniColonna[indiceDir], 
                                              coloreGiocatore);
        passoFlip = 1;
        while (passoFlip <= pedineFlippabili) {
            nuovaRiga = rigaInput + direzioniRiga[indiceDir] * passoFlip;
            nuovaColonna = colInput + direzioniColonna[indiceDir] * passoFlip;
            scrivereStatoCasellaScacchieraPartita(partita, coloreGiocatore, nuovaRiga, nuovaColonna);
            passoFlip = passoFlip + 1;
        }
        indiceDir = indiceDir + 1;
    }
}

/**
 * DESCRIZIONE: Esegue una mossa e aggiorna la scacchiera.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   rigaInput: riga della mossa
 *   colInput: colonna della mossa
 *   coloreGiocatore: colore del giocatore
 * RITORNO: nessuno
 */
void eseguiMossaCompleta(Partita *partita, int rigaInput, int colInput, int coloreGiocatore) {
    scrivereStatoCasellaScacchieraPartita(partita, coloreGiocatore, rigaInput, colInput);
    eseguiFlipPedine(partita, rigaInput, colInput, coloreGiocatore);
}

/**
 * DESCRIZIONE: Controlla se non ci sono mosse possibili per il giocatore.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   coloreGiocatore: colore del giocatore
 * RITORNO: 1 se nessuna mossa possibile, 0 altrimenti
 */
int verificaNessMossa(Partita *partita, int coloreGiocatore) {
    int indiceRiga;
    int indiceColonna;
    int mossaTrovata;
    int dimensioneScacc;
    int risultatoFinale;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    mossaTrovata = 0;
    risultatoFinale = 1;
    
    indiceRiga = 0;
    while (indiceRiga < dimensioneScacc && mossaTrovata == 0) {
        indiceColonna = 0;
        while (indiceColonna < dimensioneScacc && mossaTrovata == 0) {
            if (verificaMossaValida(partita, indiceRiga, indiceColonna, coloreGiocatore) == 1) {
                mossaTrovata = 1;
            }
            indiceColonna = indiceColonna + 1;
        }
        indiceRiga = indiceRiga + 1;
    }
    
    if (mossaTrovata == 1) {
        risultatoFinale = 0;
    }
    
    return risultatoFinale;
}

/* =========================================================
   LOGICA BOT
========================================================= */

/**
 * DESCRIZIONE: Calcola il punteggio di una mossa per il bot.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   rigaInput: riga della mossa
 *   colInput: colonna della mossa
 *   coloreBot: colore del bot
 * RITORNO: punteggio della mossa
 */
int calcolaPunteggioMossa(Partita *partita, int rigaInput, int colInput, int coloreBot) {
    int direzioniRiga[8];
    int direzioniColonna[8];
    int indiceDir;
    int pedineFlippabili;
    int punteggioTotale;
    int bonusAngolo;
    int bonusBordo;
    int dimensioneScacc;
    
    direzioniRiga[0] = -1; direzioniRiga[1] = -1; direzioniRiga[2] = -1; direzioniRiga[3] = 0;
    direzioniRiga[4] = 0; direzioniRiga[5] = 1; direzioniRiga[6] = 1; direzioniRiga[7] = 1;
    
    direzioniColonna[0] = -1; direzioniColonna[1] = 0; direzioniColonna[2] = 1; direzioniColonna[3] = -1;
    direzioniColonna[4] = 1; direzioniColonna[5] = -1; direzioniColonna[6] = 0; direzioniColonna[7] = 1;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    punteggioTotale = 0;
    bonusAngolo = 0;
    bonusBordo = 0;
    
    /* Conta pedine che si possono flippare */
    indiceDir = 0;
    while (indiceDir < 8) {
        pedineFlippabili = calcolaPedineFlipp(partita, rigaInput, colInput, 
                                              direzioniRiga[indiceDir], direzioniColonna[indiceDir], 
                                              coloreBot);
        punteggioTotale = punteggioTotale + pedineFlippabili;
        indiceDir = indiceDir + 1;
    }
    
    /* Bonus per angoli */
    if ((rigaInput == 0 && colInput == 0) ||
        (rigaInput == 0 && colInput == dimensioneScacc - 1) ||
        (rigaInput == dimensioneScacc - 1 && colInput == 0) ||
        (rigaInput == dimensioneScacc - 1 && colInput == dimensioneScacc - 1)) {
        bonusAngolo = 10;
    }
    
    /* Bonus per bordi */
    if (rigaInput == 0 || rigaInput == dimensioneScacc - 1 || 
        colInput == 0 || colInput == dimensioneScacc - 1) {
        bonusBordo = 3;
    }
    
    return punteggioTotale + bonusAngolo + bonusBordo;
}

/**
 * DESCRIZIONE: Trova la migliore mossa disponibile per il bot.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   coloreBot: colore del bot
 *   miglioreRiga: puntatore per salvare la riga della migliore mossa
 *   miglioreCol: puntatore per salvare la colonna della migliore mossa
 * RITORNO: 1 se trova una mossa, 0 altrimenti
 */
int trovaMossaMigliore(Partita *partita, int coloreBot, int *miglioreRiga, int *miglioreCol) {
    int indiceRiga;
    int indiceColonna;
    int dimensioneScacc;
    int punteggioCorrente;
    int punteggioMigliore;
    int mossaTrovata;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    punteggioMigliore = -1;
    mossaTrovata = 0;
    
    *miglioreRiga = 0;
    *miglioreCol = 0;
    
    indiceRiga = 0;
    while (indiceRiga < dimensioneScacc) {
        indiceColonna = 0;
        while (indiceColonna < dimensioneScacc) {
            if (verificaMossaValida(partita, indiceRiga, indiceColonna, coloreBot) == 1) {
                punteggioCorrente = calcolaPunteggioMossa(partita, indiceRiga, indiceColonna, coloreBot);
                if (punteggioCorrente > punteggioMigliore) {
                    punteggioMigliore = punteggioCorrente;
                    *miglioreRiga = indiceRiga;
                    *miglioreCol = indiceColonna;
                    mossaTrovata = 1;
                }
            }
            indiceColonna = indiceColonna + 1;
        }
        indiceRiga = indiceRiga + 1;
    }
    
    return mossaTrovata;
}

/* =========================================================
   FUNZIONI PUBBLICHE
========================================================= */

void avviarePartita(char nomePartita[50], int modalita, int dimensione) {
    Partita partitaCorrente;
    int turnoGiocatore;
    int finePartita;
    int rigaInput;
    int colInput;
    int neriTotali;
    int bianchiTotali;
    int metaDimensione;
    int azioneInput;
    int errore;

    errore = FALSO;
    
    scrivereNomePartita(&partitaCorrente, nomePartita);
    partitaCorrente.modalita = modalita;
    scrivereDimScacchieraPartita(&partitaCorrente, dimensione);
    inizializzareScacchieraPartita(&partitaCorrente, dimensione);
    
    turnoGiocatore = NERO;
    finePartita = 0;
    metaDimensione = dimensione / 2;
    
    scrivereStatoCasellaScacchieraPartita(&partitaCorrente, NERO, metaDimensione - 1, metaDimensione - 1);
    scrivereStatoCasellaScacchieraPartita(&partitaCorrente, BIANCO, metaDimensione - 1, metaDimensione);
    scrivereStatoCasellaScacchieraPartita(&partitaCorrente, BIANCO, metaDimensione, metaDimensione - 1);
    scrivereStatoCasellaScacchieraPartita(&partitaCorrente, NERO, metaDimensione, metaDimensione);
    
    while (finePartita == 0) {
        pulireSchermo();
        if(dimensione != 16){
          stampareTitoloPartita();
        }
        stampaScacchiera(&partitaCorrente);
        stampaTabellaInput();

        if (errore) {
          mostrareMessaggioErrore("mossa non valida", RIGA_ERRORE, COLONNA_ERRORE);
          errore = FALSO;
        }
        
        neriTotali = contaPedineGiocatore(&partitaCorrente, NERO);
        bianchiTotali = contaPedineGiocatore(&partitaCorrente, BIANCO);
        
        spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT);
        printf(">> ");

        
        azioneInput = 0;
        scanf("%d", &azioneInput);
        pulireBuffer();
        
        if (azioneInput == 2) {
            salvarePartita(&partitaCorrente);
        }
        if (azioneInput == 3) {
            avviareMenuPrincipale();
            return;
        }
        
        if (azioneInput == 1) {
            collezionareInput(&rigaInput, RIGA_INPUT_RIGA);
            collezionareInput(&colInput, RIGA_INPUT_COL);
            
            rigaInput = rigaInput - 1;
            colInput = colInput - 1;
            
            if (rigaInput >= 0 && rigaInput < dimensione && colInput >= 0 && colInput < dimensione &&
                verificaMossaValida(&partitaCorrente, rigaInput, colInput, turnoGiocatore) == 1) {
                eseguiMossaCompleta(&partitaCorrente, rigaInput, colInput, turnoGiocatore);
                turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
                
                if (verificaNessMossa(&partitaCorrente, turnoGiocatore) == 1) {
                    turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
                    if (verificaNessMossa(&partitaCorrente, turnoGiocatore) == 1) {
                        finePartita = 1;
                    }
                }
            } else {
                errore = VERO;
            }
        }
    }
    
    neriTotali = contaPedineGiocatore(&partitaCorrente, NERO);
    bianchiTotali = contaPedineGiocatore(&partitaCorrente, BIANCO);
    stampaVittoria(neriTotali, bianchiTotali);
}

void avviarePartitaContinuata(Partita *partita) {
    int turnoGiocatore;
    int rigaInput;
    int colInput;
    int finePartita;
    int neriTotali;
    int bianchiTotali;
    int dimensioneScacc;
    int azioneInput;
    
    dimensioneScacc = leggereDimScacchiera(partita->scacchieraPartita);
    finePartita = 0;
    
    neriTotali = contaPedineGiocatore(partita, NERO);
    bianchiTotali = contaPedineGiocatore(partita, BIANCO);
    turnoGiocatore = (neriTotali > bianchiTotali) ? BIANCO : NERO;
    
    while (finePartita == 0) {
        pulireSchermo();

        if(dimensioneScacc != 16){
          stampareTitoloPartita();
        }

        stampaScacchiera(partita);
        stampaTabellaInput();
        
        spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT);
        printf(">> ");
        
        azioneInput = 0;
        scanf("%d", &azioneInput);
        pulireBuffer();
        
        if (azioneInput == 2) {
            salvarePartita(partita);
        }
        if (azioneInput == 3) {
            avviareMenuPrincipale();
            return;
        }
        
        if (azioneInput == 1) {
            collezionareInput(&rigaInput, RIGA_INPUT_RIGA);
            collezionareInput(&colInput, RIGA_INPUT_COL);
            
            rigaInput = rigaInput - 1;
            colInput = colInput - 1;
            
            if (rigaInput >= 0 && rigaInput < dimensioneScacc && colInput >= 0 && colInput < dimensioneScacc &&
                verificaMossaValida(partita, rigaInput, colInput, turnoGiocatore) == 1) {
                eseguiMossaCompleta(partita, rigaInput, colInput, turnoGiocatore);
                turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
                
                if (verificaNessMossa(partita, turnoGiocatore) == 1) {
                    turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
                    if (verificaNessMossa(partita, turnoGiocatore) == 1) {
                        finePartita = 1;
                    }
                }
            } else {
                mostrareMessaggioErrore("Mossa non valida", RIGA_ERRORE, COLONNA_ERRORE);
            }
        }
    }
    
    neriTotali = contaPedineGiocatore(partita, NERO);
    bianchiTotali = contaPedineGiocatore(partita, BIANCO);
    stampaVittoria(neriTotali, bianchiTotali);
}

/**
 * DESCRIZIONE: Colleziona un input numerico da terminale per una scacchiera, con validazione.
 * ARGOMENTI:
 *   input: puntatore a intero dove salvare il valore inserito
 *   rigaTerminale: riga del terminale dove posizionare il cursore
 * RITORNO: 1 se input valido, 0 altrimenti
 */
int collezionareInput(int *input, int rigaTerminale) {
    int inputValido;
    int risultatoInput;
    
    inputValido = 0;
    risultatoInput = 1;
    
    while (inputValido == 0) {
        reimpostareZonaInput(rigaTerminale, COLONNA_INPUT);
        if (scanf("%d", input) == 1) {
            inputValido = 1;
        } else {
            pulireBuffer();
            mostrareMessaggioErrore("Input non valido", rigaTerminale + 2, COLONNA_INPUT);
        }
    }
    pulireBuffer();
    return risultatoInput;
}

/**
 * DESCRIZIONE: Converte la dimensione simbolica in valore numerico (compatibilità Sudoku).
 * ARGOMENTI:
 *   dimensione: puntatore alla variabile dimensione
 * RITORNO: nessuno
 */
void convertireDimensione(int *dimensione) {
    if (*dimensione == 1) {
        *dimensione = 4;
    } else {
        if (*dimensione == 2) {
            *dimensione = 8;
        } else {
            if (*dimensione == 3) {
                *dimensione = 16;
            }
        }
    }
}
