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

#define DIM_OTHELLO 8
#define VUOTO 0
#define CELLA_VUOTA 0

#define NERO 1
#define BIANCO 2

#define BLU   "\033[34m"
#define RESET "\033[0m"

#define RIGA_INPUT_RIGA   15
#define RIGA_INPUT_COL    16
#define RIGA_INPUT_VAL    19
#define RIGA_INPUT        28
#define COLONNA_INPUT     67
#define COLONNA_ERRORE    27

#define NORD -1
#define OVEST -1
#define SUD 1
#define EST 1
#define CENTRO 0

void stampareTitoloPartita(){
  pulireSchermo();
  stampareCentrato("             _   _ _       ");
  stampareCentrato(" ___ ___ ___| |_|_| |_ ___ ");
  stampareCentrato("| . | .'|  _|  _| |  _| .'|");
  stampareCentrato("|  _|__,|_| |_| |_|_| |__,|");
  stampareCentrato("|_|                        ");
  printf("\n\n");
}

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

/**
 * DESCRIZIONE: Conta il numero di pedine di un giocatore sulla scacchiera.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   coloreGiocatore: colore del giocatore
 * RITORNO: numero di pedine
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
int calcolarePedineDaCapovolgere(Partita *partita, int rigaInizio, int colInizio, 
                                 int deltaRiga, int deltaColonna, int coloreGiocatore) {
  int coloreAvversario;
  int contatorePedine;
  int valoreCorrente;
  int dimensioneScacc;
  int rigaCorrente;
  int colCorrente;
  int pedineDaCapovolgere;

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
      rigaCorrente = dimensioneScacc; /* Forza uscita dal ciclo */
    }

    if (pedineDaCapovolgere == 0 && rigaCorrente < dimensioneScacc) {
      rigaCorrente = rigaCorrente + deltaRiga;
      colCorrente = colCorrente + deltaColonna;
    }
  }
  if (pedineDaCapovolgere == 0) {
    pedineDaCapovolgere = 0;
  }

  return pedineDaCapovolgere;
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
int verificareMossaValida(Partita *partita, int rigaInput, int colInput, int coloreGiocatore) {
  int direzioni[8][2] = {{NORD, OVEST}, {NORD, CENTRO}, {NORD, EST},
    {CENTRO, OVEST},               {CENTRO, EST}, 
    {SUD, OVEST},   {SUD, CENTRO}, {SUD, EST}};
  int indiceDir = 0;
  int risultato = FALSO;

  // Verifica se la cella è vuota
  if (leggereCellaScacchiera(leggereScacchieraPartita(partita), rigaInput, colInput) == VUOTO) {
    while (indiceDir < 8 && risultato == 0) {
      if (calcolarePedineDaCapovolgere(partita, rigaInput, colInput, 
                                       direzioni[indiceDir][0], direzioni[indiceDir][1], 
                                       coloreGiocatore) > 0) {
        risultato = VERO;
      }
      indiceDir = indiceDir + 1;
    }
  }

  return risultato;
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
void capovolgerePedine(Partita *partita, int rigaInput, int colInput, int coloreGiocatore) {
  int direzioni[8][2] = {{NORD, OVEST}, {NORD, CENTRO}, {NORD, EST},
    {CENTRO, OVEST},               {CENTRO, EST}, 
    {SUD, OVEST},   {SUD, CENTRO}, {SUD, EST}};
  int indiceDir = 0;
  int pedineFlippabili;
  int passoFlip;
  int nuovaRiga;
  int nuovaColonna;

  while (indiceDir < 8) {
    pedineFlippabili = calcolarePedineDaCapovolgere(partita, rigaInput, colInput, 
                                                    direzioni[indiceDir][0], direzioni[indiceDir][1], 
                                                    coloreGiocatore);
    passoFlip = 1;
    while (passoFlip <= pedineFlippabili) {
      nuovaRiga = rigaInput + direzioni[indiceDir][0] * passoFlip;
      nuovaColonna = colInput + direzioni[indiceDir][1] * passoFlip;
      scrivereCellaPartita(partita, coloreGiocatore, nuovaRiga, nuovaColonna);
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
int verificareNessunaMossa(Partita *partita, int coloreGiocatore) {
  int indiceRiga;
  int indiceColonna;
  int mossaTrovata;
  int dimensioneScacc;
  int risultatoFinale;

  dimensioneScacc = leggereDimScacchieraImp(leggereImpPartita(*partita));
  mossaTrovata = 0;
  risultatoFinale = 1;

  indiceRiga = 0;
  while (indiceRiga < dimensioneScacc && mossaTrovata == 0) {
    indiceColonna = 0;
    while (indiceColonna < dimensioneScacc && mossaTrovata == 0) {
      if (verificareMossaValida(partita, indiceRiga, indiceColonna, coloreGiocatore) == 1) {
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

/**
 * DESCRIZIONE: Controlla se non ci sono mosse possibili per il giocatore.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   coloreGiocatore: colore del giocatore
 * RITORNO: 1 se nessuna mossa possibile, 0 altrimenti
 */
void avviarePartita(char nomePartita[50], Impostazioni *impostazioniPartita) {
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
  int modalita;
  int dimensione;

  errore = FALSO;

  modalita = leggereModalitaImpostazioni(*impostazioniPartita);
  dimensione = leggereDimScacchieraImp(*impostazioniPartita);

  scrivereNomePartita(&partitaCorrente, nomePartita);
  scrivereModalitaPartita(&partitaCorrente, modalita); 
  scrivereDimScacchieraPartita(&partitaCorrente, dimensione);
  inizializzareScacchieraPartita(&partitaCorrente, dimensione);

  turnoGiocatore = NERO;
  finePartita = 0;
  metaDimensione = dimensione / 2;

  scrivereCellaPartita(&partitaCorrente, NERO, metaDimensione - 1, metaDimensione - 1);
  scrivereCellaPartita(&partitaCorrente, BIANCO, metaDimensione - 1, metaDimensione);
  scrivereCellaPartita(&partitaCorrente, BIANCO, metaDimensione, metaDimensione - 1);
  scrivereCellaPartita(&partitaCorrente, NERO, metaDimensione, metaDimensione);

  while (finePartita == 0) {
    pulireSchermo();
    if(dimensione != 16){
      stampareTitoloPartita();
    }
    stampareConteggioPedine(&partitaCorrente, turnoGiocatore);
    stampareScacchiera(&partitaCorrente);
    stampareTabellaInput();

    if (errore) {
      mostrareMessaggioErrore("mossa non valida", RIGA_ERRORE, COLONNA_ERRORE);
      errore = FALSO;
    }

    neriTotali = contarePedineGiocatore(&partitaCorrente, NERO);
    bianchiTotali = contarePedineGiocatore(&partitaCorrente, BIANCO);

    spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT);
    printf(">> ");


    azioneInput = 0;
    scanf("%d", &azioneInput);
    pulireBuffer();

    if (azioneInput == 2) {
      salvarePartita(&partitaCorrente, turnoGiocatore);
    }
    if (azioneInput == 3) {
      avviareMenuPrincipale();
      return;
    }

    if (azioneInput == 1) {
      collezionareInput(&rigaInput, RIGA_INPUT_RIGA);
      collezionareInput(&colInput, RIGA_INPUT_COL + 2);

      rigaInput = rigaInput - 1;
      colInput = colInput - 1;

      if (rigaInput >= 0 && rigaInput < dimensione && colInput >= 0 && colInput < dimensione &&
        verificareMossaValida(&partitaCorrente, rigaInput, colInput, turnoGiocatore) == 1) {
        eseguireMossaCompleta(&partitaCorrente, rigaInput, colInput, turnoGiocatore);
        turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;

        if (verificareNessunaMossa(&partitaCorrente, turnoGiocatore) == 1) {
          turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
          if (verificareNessunaMossa(&partitaCorrente, turnoGiocatore) == 1) {
            finePartita = 1;
          }
        }
      } else {
        errore = VERO;
      }
    }
  }

  neriTotali = contarePedineGiocatore(&partitaCorrente, NERO);
  bianchiTotali = contarePedineGiocatore(&partitaCorrente, BIANCO);
  stampareVittoria(neriTotali, bianchiTotali);
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

  dimensioneScacc = leggereDimScacchieraImp(leggereImpPartita(*partita));
  finePartita = 0;

  neriTotali = contarePedineGiocatore(partita, NERO);
  bianchiTotali = contarePedineGiocatore(partita, BIANCO);
  turnoGiocatore = (neriTotali > bianchiTotali) ? BIANCO : NERO;

  while (finePartita == 0) {
    pulireSchermo();

    if(dimensioneScacc != 16){
      stampareTitoloPartita();
    }

    stampareScacchiera(partita);
    stampareTabellaInput();

    spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT);
    printf(">> ");

    azioneInput = 0;
    scanf("%d", &azioneInput);
    pulireBuffer();

    if (azioneInput == 2) {
      salvarePartita(partita, turnoGiocatore);
    }
    if (azioneInput == 3) {
      avviareMenuPrincipale();
      return;
    }

    if (azioneInput == 1) {
      collezionareInput(&rigaInput, RIGA_INPUT_RIGA + 2);
      collezionareInput(&colInput, RIGA_INPUT_COL);

      rigaInput = rigaInput - 1;
      colInput = colInput - 1;

      if (rigaInput >= 0 && rigaInput < dimensioneScacc && colInput >= 0 && colInput < dimensioneScacc &&
        verificareMossaValida(partita, rigaInput, colInput, turnoGiocatore) == 1) {
        eseguireMossaCompleta(partita, rigaInput, colInput, turnoGiocatore);
        turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;

        if (verificareNessunaMossa(partita, turnoGiocatore) == 1) {
          turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
          if (verificareNessunaMossa(partita, turnoGiocatore) == 1) {
            finePartita = 1;
          }
        }
      } else {
        mostrareMessaggioErrore("Mossa non valida", RIGA_ERRORE, COLONNA_ERRORE);
      }
    }
  }

  neriTotali = contarePedineGiocatore(partita, NERO);
  bianchiTotali = contarePedineGiocatore(partita, BIANCO);
  stampareVittoria(neriTotali, bianchiTotali);
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
int convertireDimensione(int dimensione) {
  if (dimensione == 1) {
    dimensione = 4;
  } else {
    if (dimensione == 2) {
      dimensione = 8;
    } else {
      if (dimensione == 3) {
        dimensione = 16;
      }
    }
  }
  return dimensione;
}

void stampareConteggioPedine(Partita *partita, int turnoCorrente) {
  int neriTotali = contarePedineGiocatore(partita, NERO);
  int bianchiTotali = contarePedineGiocatore(partita, BIANCO);
  char* nomeGiocatoreCorrente = (turnoCorrente == NERO) ? "NERO" : "BIANCO";

  // Posiziona il conteggio in alto a destra
  spostareCursore(RIGA_ERRORE-1, COLONNA_ERRORE-8);
  printf(" Nere:  %2d    ", neriTotali);
  printf(" Bianche: %2d  ", bianchiTotali);
  printf(" Turno: %s     ", nomeGiocatoreCorrente);
}

/**
 * DESCRIZIONE: Trova la prima mossa valida per il bot.
 * ARGOMENTI:
 *   partita: puntatore alla struttura Partita
 *   coloreBot: colore del bot (NERO/BIANCO)
 *   rigaBot: puntatore dove salvare la riga della mossa
 *   colBot: puntatore dove salvare la colonna della mossa
 * RITORNO: 1 se trova una mossa, 0 altrimenti
 */
int trovareMossaBot(Partita *partita, int coloreBot, int *rigaBot, int *colBot) {
  int dimensioneScacc;
  int indiceRiga;
  int indiceColonna;
  int mossaTrovata;

  dimensioneScacc = leggereDimScacchieraImp(leggereImpPartita(*partita));
  mossaTrovata = 0;

  indiceRiga = 0;
  while (indiceRiga < dimensioneScacc && mossaTrovata == 0) {
    indiceColonna = 0;
    while (indiceColonna < dimensioneScacc && mossaTrovata == 0) {
      if (verificareMossaValida(partita, indiceRiga, indiceColonna, coloreBot) == 1) {
        *rigaBot = indiceRiga;
        *colBot = indiceColonna;
        mossaTrovata = 1;
      }
      indiceColonna = indiceColonna + 1;
    }
    indiceRiga = indiceRiga + 1;
  }

  return mossaTrovata;
}

void avviarePartitaBot(char nomePartita[50], Impostazioni *impostazioniPartita, int coloreGiocatore) {
  Partita partitaCorrente;
  int turnoGiocatore;
  int finePartita;
  int rigaInput;
  int colInput;
  int rigaBot;
  int colBot;
  int neriTotali;
  int bianchiTotali;
  int metaDimensione;
  int azioneInput;
  int errore;
  int coloreBot;
  int modalita;
  int dimensione;

  errore = FALSO;
  if(coloreGiocatore == NERO) {
    coloreBot = BIANCO;
  } else {
    coloreBot = NERO;
  }

  modalita = leggereModalitaImpostazioni(*impostazioniPartita);
  dimensione = leggereDimScacchieraImp(*impostazioniPartita);


  scrivereNomePartita(&partitaCorrente, nomePartita);
  scrivereModalitaPartita(&partitaCorrente, modalita);
  scrivereDimScacchieraPartita(&partitaCorrente, dimensione);
  inizializzareScacchieraPartita(&partitaCorrente, dimensione);


  turnoGiocatore = NERO;
  finePartita = FALSO;
  metaDimensione = dimensione / 2;

  // Inizializzazione standard Othello
  scrivereCellaPartita(&partitaCorrente, NERO, metaDimensione - 1, metaDimensione - 1);
  scrivereCellaPartita(&partitaCorrente, BIANCO, metaDimensione - 1, metaDimensione);
  scrivereCellaPartita(&partitaCorrente, BIANCO, metaDimensione, metaDimensione - 1);
  scrivereCellaPartita(&partitaCorrente, NERO, metaDimensione, metaDimensione);

  while (finePartita == FALSO) {
    pulireSchermo();
    if(dimensione != 16){
      stampareTitoloPartita();
    }
    stampareScacchiera(&partitaCorrente);
    stampareConteggioPedine(&partitaCorrente, turnoGiocatore);
    stampareTabellaInput();

    if (errore) {
      mostrareMessaggioErrore("mossa non valida", RIGA_ERRORE, COLONNA_ERRORE);
      errore = FALSO;
    }

    neriTotali = contarePedineGiocatore(&partitaCorrente, NERO);
    bianchiTotali = contarePedineGiocatore(&partitaCorrente, BIANCO);

    // Turno del giocatore umano
    if (turnoGiocatore == coloreGiocatore) {
      spostareCursore(RIGA_INPUT - 16, COLONNA_INPUT);
      printf(">> ");

      azioneInput = 0;
      scanf("%d", &azioneInput);
      pulireBuffer();

      if (azioneInput == 2) {
        salvarePartita(&partitaCorrente, turnoGiocatore);
      }
      if (azioneInput == 3) {
        avviareMenuPrincipale();
        return;
      }

      if (azioneInput == 1) {
        collezionareInput(&rigaInput, RIGA_INPUT_RIGA);
        collezionareInput(&colInput, RIGA_INPUT_COL + 2);

        rigaInput = rigaInput - 1;
        colInput = colInput - 1;

        if (rigaInput >= 0 && rigaInput < dimensione && colInput >= 0 && colInput < dimensione &&
          verificareMossaValida(&partitaCorrente, rigaInput, colInput, turnoGiocatore) == 1) {
          eseguireMossaCompleta(&partitaCorrente, rigaInput, colInput, turnoGiocatore);
          turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;

          if (verificareNessunaMossa(&partitaCorrente, turnoGiocatore) == 1) {
            turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
            if (verificareNessunaMossa(&partitaCorrente, turnoGiocatore) == 1) {
              finePartita = VERO;
            }
          }
        } else {
          errore = VERO;
        }
      }
    } else {
      // turno del bot 
      getchar();
      if (trovareMossaBot(&partitaCorrente, coloreBot, &rigaBot, &colBot) == 1) {
        eseguireMossaCompleta(&partitaCorrente, rigaBot, colBot, turnoGiocatore);
        turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;

        if (verificareNessunaMossa(&partitaCorrente, turnoGiocatore) == 1) {
          turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
          if (verificareNessunaMossa(&partitaCorrente, turnoGiocatore) == 1) {
            finePartita = 1;
          }
        }
      } else {
        // Il bot non può muovere, passa il turno
        turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
        if (verificareNessunaMossa(&partitaCorrente, turnoGiocatore) == 1) {
          finePartita = 1;
        }
      }
    }
  }
  neriTotali = contarePedineGiocatore(&partitaCorrente, NERO);
  bianchiTotali = contarePedineGiocatore(&partitaCorrente, BIANCO);
  stampareVittoria(neriTotali, bianchiTotali);
}

void avviarePartitaContinuataBot(Partita *partita, int coloreGiocatore) {
  int turnoGiocatore;
  int rigaInput;
  int colInput;
  int rigaBot;
  int colBot;
  int finePartita;
  int neriTotali;
  int bianchiTotali;
  int dimensioneScacc;
  int azioneInput;
  int coloreBot;
  int errore;

  errore = FALSO;
  coloreBot = (coloreGiocatore == NERO) ? BIANCO : NERO;
  dimensioneScacc = leggereDimScacchieraImp(leggereImpPartita(*partita));
  finePartita = 0;

  neriTotali = contarePedineGiocatore(partita, NERO);
  bianchiTotali = contarePedineGiocatore(partita, BIANCO);
  turnoGiocatore = (neriTotali > bianchiTotali) ? BIANCO : NERO;

  while (finePartita == 0) {
    pulireSchermo();

    if(dimensioneScacc != 16){
      stampareTitoloPartita();
    }

    stampareScacchiera(partita);
    stampareTabellaInput();
    stampareConteggioPedine(partita, turnoGiocatore);

    if (errore) {
      mostrareMessaggioErrore("mossa non valida", RIGA_ERRORE, COLONNA_ERRORE);
      errore = FALSO;
    }

    // Turno del giocatore umano
    if (turnoGiocatore == coloreGiocatore) {
      spostareCursore(RIGA_INPUT - 18, COLONNA_INPUT);
      printf(">> ");

      azioneInput = 0;
      scanf("%d", &azioneInput);
      pulireBuffer();

      if (azioneInput == 2) {
        salvarePartita(partita, turnoGiocatore);
      }
      if (azioneInput == 3) {
        avviareMenuPrincipale();
        return;
      }

      if (azioneInput == 1) {
        collezionareInput(&rigaInput, RIGA_INPUT_RIGA + 2);
        collezionareInput(&colInput, RIGA_INPUT_COL);

        rigaInput = rigaInput - 1;
        colInput = colInput - 1;

        if (rigaInput >= 0 && rigaInput < dimensioneScacc && colInput >= 0 && colInput < dimensioneScacc &&
          verificareMossaValida(partita, rigaInput, colInput, turnoGiocatore) == 1) {
          eseguireMossaCompleta(partita, rigaInput, colInput, turnoGiocatore);
          turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;

          if (verificareNessunaMossa(partita, turnoGiocatore) == 1) {
            turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
            if (verificareNessunaMossa(partita, turnoGiocatore) == 1) {
              finePartita = 1;
            }
          }
        } else {
          errore = VERO;
        }
      }
    } else {
      // Turno del bot
      getchar();

      if (trovareMossaBot(partita, coloreBot, &rigaBot, &colBot) == 1) {
        eseguireMossaCompleta(partita, rigaBot, colBot, turnoGiocatore);
        turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;

        if (verificareNessunaMossa(partita, turnoGiocatore) == 1) {
          turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
          if (verificareNessunaMossa(partita, turnoGiocatore) == 1) {
            finePartita = 1;
          }
        }
      } else {
        // Il bot non può muovere, passa il turno
        turnoGiocatore = (turnoGiocatore == NERO) ? BIANCO : NERO;
        if (verificareNessunaMossa(partita, turnoGiocatore) == 1) {
          finePartita = 1;
        }
      }
    }
  }

  neriTotali = contarePedineGiocatore(partita, NERO);
  bianchiTotali = contarePedineGiocatore(partita, BIANCO);
  stampareVittoria(neriTotali, bianchiTotali);
}
