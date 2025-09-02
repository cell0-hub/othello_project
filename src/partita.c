/*
AUTORI: Onofrio de Robertis
        Michele Amato
        Davide Fornelli
        Giuliano Antoniciello
*/

#include <stdio.h>
#include "../include/tipiDiDato.h"
#include "../include/partita.h"
#include "../include/funzioniUtilita.h"
#include "../include/caricaPartita.h"
#include "../include/homepage.h"
#include "../include/costanti.h"

#define RIGA_INPUT_RIGA   15
#define RIGA_INPUT_COL    16
#define RIGA_INPUT_VAL    19
#define RIGA_INPUT        28
#define COLONNA_INPUT     67
#define COLONNA_ERRORE    27


/**
 * DESCRIZIONE: Conta il numero di pedine di un giocatore sulla scacchiera.
 * ARGOMENTI:
 *   partita: partita di gioco
 *   coloreGiocatore: colore del giocatore di cui si 
 *                    vogliono contare il numero di pedine
 * RITORNO: conteggioTotale: numero di pedine contate
 */

int contarePedineGiocatore(Partita *partita, int coloreGiocatore) {
  int indiceRiga;
  int indiceColonna;
  int conteggioTotale;
  int dimensione;
  int valoreCorrente;

  dimensione = leggereDimScacchieraImp(leggereImpPartita(*partita));
  conteggioTotale = 0;

  indiceRiga = 0;
  while (indiceRiga < dimensione) {
    indiceColonna = 0;
    while (indiceColonna < dimensione) {
      valoreCorrente = leggereCellaScacchiera(leggereScacchieraPartita(partita), indiceRiga, indiceColonna);
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
 * DESCRIZIONE: Conta quante pedine si possono capovolgere in una direzione.
 * ARGOMENTI:
 *   partita: partita di gioco, Partita 
 *   rigaInizio: riga di partenza
 *   colInizio: colonna di partenza
 *   deltaRiga: direzione riga
 *   deltaColonna: direzione colonna
 *   coloreGiocatore: colore del giocatore
 * RITORNO: pedineDaCapovolgere: numero di pedine da capovolegere
 */
int calcolarePedineDaCapovolgere(Partita *partita, int rigaInizio, int colInizio, 
                                 int deltaRiga, int deltaColonna) {
  int coloreGiocatore; 
  int coloreAvversario;
  int contatorePedine;
  int valoreCorrente;
  int dimensioneScacc;
  int rigaCorrente;
  int colCorrente;
  int pedineDaCapovolgere;

  coloreGiocatore = leggereTurnoGiocatore(partita);
  dimensioneScacc = leggereDimScacchieraImp(leggereImpPartita(*partita));

  if (coloreGiocatore == NERO) {
    coloreAvversario = BIANCO;
  } else {
    coloreAvversario = NERO;
  }

  contatorePedine = 0;
  pedineDaCapovolgere = 0;

  rigaCorrente = rigaInizio + deltaRiga;
  colCorrente = colInizio + deltaColonna;

  while (rigaCorrente >= 0 && rigaCorrente < dimensioneScacc && 
    colCorrente >= 0 && colCorrente < dimensioneScacc) {
    valoreCorrente = leggereCellaScacchiera(leggereScacchieraPartita(partita), rigaCorrente, colCorrente);

    if (valoreCorrente == coloreAvversario) {
      contatorePedine = contatorePedine + 1;
    } else {
      if (valoreCorrente == coloreGiocatore) {
        pedineDaCapovolgere = contatorePedine;
      }
      rigaCorrente = dimensioneScacc + 1; /* Forza uscita dal ciclo */
    }

    if (pedineDaCapovolgere == 0 && rigaCorrente < dimensioneScacc && colCorrente < dimensioneScacc) {
      rigaCorrente = rigaCorrente + deltaRiga;
      colCorrente = colCorrente + deltaColonna;
    }
  }

  return pedineDaCapovolgere;
}

/**
 * DESCRIZIONE: Controlla se una mossa è valida per il giocatore.
 * ARGOMENTI:
 *   partita: partita di gioco 
 *   rigaInput: riga della mossa
 *   colInput: colonna della mossa
 *   coloreGiocatore: colore del giocatore (NERO/BIANCO)
 * RITORNO: 1 se valida, 0 altrimenti
 */
int verificareMossaValida(Partita *partita, int rigaInput, int colInput) {
  int direzioni[8][2] = {{NORD, OVEST}, {NORD, CENTRO}, {NORD, EST},
    {CENTRO, OVEST},               {CENTRO, EST}, 
    {SUD, OVEST},   {SUD, CENTRO}, {SUD, EST}};
  int indiceDir = 0;
  int risultato = FALSO;

  // Verifica se la cella è vuota
  if (leggereCellaScacchiera(leggereScacchieraPartita(partita), rigaInput, colInput) == VUOTO) {
    while (indiceDir < NUMERO_DIREZIONI && risultato == FALSO) {
      if (calcolarePedineDaCapovolgere(partita, rigaInput, colInput, 
                                       direzioni[indiceDir][VERT], direzioni[indiceDir][ORR]) > 0) {
        risultato = VERO;
      }
      indiceDir = indiceDir + 1;
    }
  }

  return risultato;
}

/**
 * DESCRIZIONE: capovolge le pedine in tutte le direzioni valide
 *              dopo una mossa valida.
 * ARGOMENTI:
 *   partita: partita di gioco, Partita 
 *   rigaInput: riga della mossa
 *   colInput: colonna della mossa
 *   coloreGiocatore: colore del giocatore
 * RITORNO: partita: partita con le pedine capovolte
 */

void capovolgerePedine(Partita *partita, int rigaInput, int colInput, int coloreGiocatore) {
  int direzioni[8][2] = {{NORD, OVEST}, {NORD, CENTRO}, {NORD, EST},
    {CENTRO, OVEST},               {CENTRO, EST}, 
    {SUD, OVEST},   {SUD, CENTRO}, {SUD, EST}};
  int indiceDir = 0;
  int pedineDaCapovolgere;
  int contatorePedine;
  int nuovaRiga;
  int nuovaColonna;

  while (indiceDir < NUMERO_DIREZIONI) {
    pedineDaCapovolgere = calcolarePedineDaCapovolgere(partita, rigaInput, colInput, 
                                                    direzioni[indiceDir][VERT], direzioni[indiceDir][ORR]);
    contatorePedine = 1;
    while (contatorePedine <= pedineDaCapovolgere) {
      nuovaRiga = rigaInput + direzioni[indiceDir][0] * contatorePedine;
      nuovaColonna = colInput + direzioni[indiceDir][1] * contatorePedine;
      scrivereCellaPartita(partita, coloreGiocatore, nuovaRiga, nuovaColonna);
      contatorePedine = contatorePedine + 1;
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
 * RITORNO: partita, partita con la mossa completa effettuta
 */
void eseguireMossaCompleta(Partita *partita, int rigaInput, int colInput, int coloreGiocatore) {
  scrivereCellaPartita(partita, coloreGiocatore, rigaInput, colInput);
  capovolgerePedine(partita, rigaInput, colInput, coloreGiocatore);
}

/**
 * DESCRIZIONE: Controlla se non ci sono mosse possibili per il giocatore.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   coloreGiocatore: colore del giocatore
 * RITORNO: 1 se nessuna mossa possibile, 0 altrimenti
 */
int verificareNessunaMossa(Partita *partita) {
  int indiceRiga;
  int indiceColonna;
  int mossaTrovata;
  int dimensioneScacc;
  int risultatoFinale;

  dimensioneScacc = leggereDimScacchieraImp(leggereImpPartita(*partita));
  mossaTrovata = FALSO;
  risultatoFinale = VERO;

  indiceRiga = 0;
  while (indiceRiga < dimensioneScacc && mossaTrovata == FALSO) {
    indiceColonna = 0;
    while (indiceColonna < dimensioneScacc && mossaTrovata == FALSO) {
      if (verificareMossaValida(partita, indiceRiga, indiceColonna) == VERO) {
        mossaTrovata = 1;
      }
      indiceColonna = indiceColonna + 1;
    }
    indiceRiga = indiceRiga + 1;
  }

  if (mossaTrovata == VERO) {
    risultatoFinale = FALSO;
  }

  return risultatoFinale;
}

/*
 * DESCRIZIONE: inizializza la partita, 
 *              se esiste una partita da caricare la carica, 
 *              altrimenti riempie la scacchiera seguendo
 *              le regole di othello
 * ARGOMENTI: nomePartita: nome della partita da inizializzare
 *            impostazioniPartita: impostazioni della partita da inizializzare
 *            partitaEsistente: partita esistente da caricare. NULL se non esiste
 *            partitaAttiva: partita inizializzata
 * RITORNO: partitaAttiva: partita inizializzata
 */
void inizializzarePartita(char nomePartita[50], Impostazioni *impostazioniPartita,
                                Partita *partitaEsistente, Partita *partitaAttiva) {
    int metaDimensione;
    int dimensione;
    if (partitaEsistente == NULL) {
        dimensione = leggereDimScacchieraImp(*impostazioniPartita);

        inizializzareScacchieraPartita(partitaAttiva, dimensione);
        scrivereNomePartita(partitaAttiva, nomePartita);
        scrivereModalitaPartita(partitaAttiva, leggereModalitaImpostazioni(*impostazioniPartita));
        scrivereTurnoGiocatore(partitaAttiva, NERO);
        scrivereDimScacchieraPartita(partitaAttiva, dimensione);

        metaDimensione = dimensione / 2;
        scrivereCellaPartita(partitaAttiva, NERO, metaDimensione - 1, metaDimensione - 1);
        scrivereCellaPartita(partitaAttiva, BIANCO, metaDimensione - 1, metaDimensione);
        scrivereCellaPartita(partitaAttiva, BIANCO, metaDimensione, metaDimensione - 1);
        scrivereCellaPartita(partitaAttiva, NERO, metaDimensione, metaDimensione);
    } else {
        *partitaAttiva = *partitaEsistente;
    }
}

/*
 * DESCRIZIONE: controlla se ci sono mosse possibili per i giocatori
 * ARGOMENTI: partitaAttiva: partita di gioco
 * RITORNO: esito: VERO se non ci sono mosse possibili, 
 *          FALSO se ci sono mosse possibili
 */
int controllareFinePartita(Partita *partitaAttiva) {
    int esitoFinale;
    int primoEsito;

    esitoFinale = FALSO;
    primoEsito = FALSO;

    if (verificareNessunaMossa(partitaAttiva)) {
        cambiareTurnoGiocatore(partitaAttiva);
        primoEsito = VERO;
    }

    if(primoEsito == VERO) {
        if (verificareNessunaMossa(partitaAttiva)) {
            esitoFinale = VERO;
        }
    }
    return esitoFinale;
}

/*
 * DESCRIZIONE: gestisce l' input dell utente per quanto riguarda le mosse della partita
 * ARGOMENTI: partitaAttiva: partita di gioco
 *            errore: indica se c'e un errore nell' input dell utente
 * RITORNO: mossa del giocatore effettuta
 */
void gestireTurnoGiocatore(Partita *partitaAttiva, int *errore) {
    int azioneInput, rigaInput, colInput, dimensione;

    dimensione = leggereDimScacchieraImp(leggereImpPartita(*partitaAttiva));
    spostareCursore(RIGA_INPUT - 16, COLONNA_INPUT);
    printf(">> ");
    scanf("%d", &azioneInput);
    pulireBuffer();

    if (azioneInput == SALVA) {
        salvarePartita(partitaAttiva);
    } else if (azioneInput == ESCI) {
        avviareMenuPrincipale();
    } else if (azioneInput == GIOCA) {
        reimpostareZonaInput(RIGA_INPUT_RIGA, COLONNA_INPUT);
        scanf("%d", &rigaInput);
        reimpostareZonaInput(RIGA_INPUT_RIGA + 3, COLONNA_INPUT);
        scanf("%d", &colInput);

        rigaInput--; colInput--;

        if (rigaInput >= 0 && rigaInput < dimensione &&
            colInput >= 0 && colInput < dimensione &&
            verificareMossaValida(partitaAttiva, rigaInput, colInput)) {

            eseguireMossaCompleta(partitaAttiva, rigaInput, colInput, leggereTurnoGiocatore(partitaAttiva));
            cambiareTurnoGiocatore(partitaAttiva);
        } else {
            *errore = VERO;
        }
    }
}

/*
 * DESCRIZIONE: gestisce il turno del bot. trova la prima mossa valida e la esegue
 * ARGOMENTI: partitaAttiva: partita di gioco, Partita
 * RITORNO: partitaAttiva: partita aggiornata con la mossa del bot, Partita
 */
void gestireTurnoBot(Partita *partitaAttiva) {
    int mossaBotValida, rigaBot, colBot, dimensione;
    dimensione = leggereDimScacchieraImp(leggereImpPartita(*partitaAttiva));
    printf("\nPremi INVIO per continuare");
    getchar();
    mossaBotValida = trovareMossaBot(partitaAttiva);
    if (mossaBotValida != 0) {
        rigaBot = mossaBotValida / dimensione;
        colBot = mossaBotValida % dimensione;
        eseguireMossaCompleta(partitaAttiva, rigaBot, colBot, leggereTurnoGiocatore(partitaAttiva));
        cambiareTurnoGiocatore(partitaAttiva);
    } else {
        cambiareTurnoGiocatore(partitaAttiva);
    }
}

/*
 * DESCRIZIONE: avvia un menu interattivo in cui l' utente puo giocare
 *              una partita di othello
 * ARGOMENTI: nomePartita: nome della partita scelto dall' utente
 *            impostazioniPartita: impostazioni della partita di gioco
 *            partitaEsistente: partita da caricare (= NULL se non esiste)
 *            modalitaBot: indica se la partita viene giocata contro un bot o meno
 *            coloreGiocatore: indica il colore delle pedine dell' utente nella partita corrente 
 * RITORNO: menu interattivo stampato a schermo 
 */
void avviarePartita(char nomePartita[50], Impostazioni *impostazioniPartita,
                    Partita *partitaEsistente, int modalitaBot, int coloreGiocatore) {
    Partita partitaAttiva;
    int finePartita = FALSO, errore = FALSO;
    int dimensione;

    inizializzarePartita(nomePartita, impostazioniPartita, partitaEsistente, &partitaAttiva);
    dimensione = leggereDimScacchieraImp(leggereImpPartita(partitaAttiva));

    while (!finePartita) {
        pulireSchermo();
        if (dimensione != 16) stampareTitoloPartita();
        stampareScacchiera(&partitaAttiva);
        stampareTabellaInput();
        stampareConteggioPedine(&partitaAttiva, leggereTurnoGiocatore(&partitaAttiva));

        if (errore) {
            mostrareMessaggioErrore("mossa non valida", RIGA_ERRORE, COLONNA_ERRORE);
            errore = FALSO;
        }

        if (!modalitaBot || leggereTurnoGiocatore(&partitaAttiva) == coloreGiocatore) {
            gestireTurnoGiocatore(&partitaAttiva,  &errore);
        } else {
            gestireTurnoBot(&partitaAttiva);
        }

        if (!errore) {
            if (controllareFinePartita(&partitaAttiva)) finePartita = VERO;
        }
    }

    stampareVittoria(
        contarePedineGiocatore(&partitaAttiva, NERO),
        contarePedineGiocatore(&partitaAttiva, BIANCO)
    );
}


/**
 * DESCRIZIONE: Converte la dimensione simbolica in valore numerico
 * ARGOMENTI:
 *   dimensione: dimensione da convertire
 * RITORNO: dimensione: dimensione convertita
 */
int convertireDimensione(int dimensione) {
  if (dimensione == PICCOLA) {
    dimensione = 4;
  } else if (dimensione == MEDIA) {
    dimensione = 8;
  } else if (dimensione == GRANDE) {
    dimensione = 16;
  }
  return dimensione;
}

/**
 * DESCRIZIONE: Stampa il conteggio delle pedine e il turno corrente
 * ARGOMENTI:
 *   partita: partita di gioco corrente
 *   turnoCorrente: colore delle pedine del giocatore corrente 
 * RITORNO: conteggio delle pedine e turno corrente stampato a schermo
 */
void stampareConteggioPedine(Partita *partita, int turnoCorrente) {
  int neriTotali = contarePedineGiocatore(partita, NERO);
  int bianchiTotali = contarePedineGiocatore(partita, BIANCO);
  char* nomeGiocatoreCorrente = (turnoCorrente == NERO) ? "NERO" : "BIANCO";
  
  spostareCursore(RIGA_ERRORE - 1, COLONNA_ERRORE - 8);
  printf(" Nere:  %2d    ", neriTotali);
  printf(" Bianche: %2d  ", bianchiTotali);
  printf(" Turno: %s     ", nomeGiocatoreCorrente);
}

/**
 * DESCRIZIONE: Trova la prima mossa valida per il bot
 * ARGOMENTI:
 *   partita: partita di gioco corrente, Partita
 * RITORNO: risultato: coordinate della mossa del bot, intero
 */
int trovareMossaBot(Partita *partita) {
  int dimensioneScacc;
  int indiceRiga;
  int indiceColonna;
  int risultato;
  int mossaTrovata;
  
  dimensioneScacc = leggereDimScacchieraImp(leggereImpPartita(*partita));
  risultato = 0;
  mossaTrovata = FALSO;
  indiceRiga = 0;
  
  while (indiceRiga < dimensioneScacc && !mossaTrovata) {
    indiceColonna = 0;
    while (indiceColonna < dimensioneScacc && !mossaTrovata) {
      if (verificareMossaValida(partita, indiceRiga, indiceColonna)) {
        risultato = indiceRiga * dimensioneScacc + indiceColonna;
        mossaTrovata = VERO;
      }
      indiceColonna = indiceColonna + 1;
    }
    indiceRiga = indiceRiga + 1;
  }
  
  return risultato;
}

/**
 * DESCRIZIONE: stampa il titolo della partita
 * ARGOMENTI: nessuno
 * RITORNO: titolo della partita stampato a schermo
 */
void stampareTitoloPartita(){
  pulireSchermo();
  stampareCentrato("             _   _ _       ");
  stampareCentrato(" ___ ___ ___| |_|_| |_ ___ ");
  stampareCentrato("| . | .'|  _|  _| |  _| .'|");
  stampareCentrato("|  _|__,|_| |_| |_|_| |__,|");
  stampareCentrato("|_|                        ");
  printf("\n\n");
}

/**
 * DESCRIZIONE: stampa la linea orrizonatale della scacchiera 
 * ARGOMENTI: nessuno
 * RITORNO: linea orrizonatale stampata a schermo 
 */
void stampareLineaOrizzontale(Partita *partita) {
  int indiceColonna;
  int dimensione;

  dimensione = leggereDimScacchieraImp(leggereImpPartita(*partita));
  printf("   +");

  indiceColonna = 0;
  while (indiceColonna < dimensione) {
    printf("---");
    indiceColonna = indiceColonna + 1;
  }
  printf("-+\n");
}

/**
 * DESCRIZIONE: stampa le coordinate prima delle colonne 
 * ARGOMENTI: partita di gioco (serve per la dimensione della scacchiera)
 * RITORNO: coordinate prima delle colonne stampate a schermo
 */
void stampareIntestColonne(Partita *partita) {
  int indiceColonna;
  int dimensione;

  dimensione = leggereDimScacchieraImp(leggereImpPartita(*partita));
  printf("    ");

  indiceColonna = 0;
  while (indiceColonna < dimensione) {
    printf("%3d", indiceColonna + 1);
    indiceColonna = indiceColonna + 1;
  }
  printf("\n");
}

/**
 * DESCRIZIONE: stampa la scacchiera di gioco 
 * ARGOMENTI: partita: partita di gioco, Partita
 * RITORNO: scacchiera di gioco stampata a schermo 
 */
void stampareScacchiera(Partita *partita) {
  int indiceRiga;
  int indiceColonna;
  int dimensione;
  int valoreCorrente;
  char carattereVisualizzato;

  dimensione = leggereDimScacchieraImp(leggereImpPartita(*partita));

  stampareIntestColonne(partita);
  stampareLineaOrizzontale(partita);

  indiceRiga = 0;
  while (indiceRiga < dimensione) {
    printf("%2d |", indiceRiga + 1);

    indiceColonna = 0;
    while (indiceColonna < dimensione) {
      valoreCorrente = leggereCellaScacchiera(leggereScacchieraPartita(partita), indiceRiga, indiceColonna);
      if(valoreCorrente == NERO){
        carattereVisualizzato = 'N';
      } else if (valoreCorrente == BIANCO) {
        carattereVisualizzato = 'B';
      } else {
        carattereVisualizzato = '.';
      }
      printf("%3c", carattereVisualizzato);
      indiceColonna = indiceColonna + 1;
    }
    printf(" |\n");
    indiceRiga = indiceRiga + 1;
  }
  stampareLineaOrizzontale(partita);
}



/**
 * DESCRIZIONE: stampa la cornice della zona
 *              dove l' utente inserisce gli input 
 * ARGOMENTI: nessuno 
 * RITORNO: cornice della zona dove 
 *          l' utente inserisce gli input stampata a schermo
 */
void disegnareCornice() {
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

/**
 * DESCRIZIONE: stampa la zona dove l' utente inserisce gli input 
 * ARGOMENTI: nessuno 
 * RITORNO: zona dove l' utente inserisce gli input stampata a schermo
 */
void stampareTabellaInput() {
  disegnareCornice();
  spostareCursore(RIGA_INPUT_RIGA - 4, COLONNA_INPUT);
  printf("-Azione-");
  spostareCursore(RIGA_INPUT_RIGA - 1, COLONNA_INPUT + 1);
  printf("-Riga-");
  spostareCursore(RIGA_INPUT_RIGA + 2, COLONNA_INPUT);
  printf("-Colonna-");
  spostareCursore(25, 17);
  printf("\033[34m azione: (1 giocare / 2 salvare / 3 uscire) \033[0m");
}

/*
 * DESCRIZIONE: stampa la schermata di vittoria
 * ARGOMENTI: neriTotali: numero di pedine del giocatore nero
 *            bianchiTotali: numero di pedine del giocatore bianchi
 * RITORNO: schermata di vittoria stampata a schermo
 */
void stampareVittoria(int neriTotali, int bianchiTotali) {
  int inputUtente;

  pulireSchermo();
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
