/*
AUTORI: Davide Fornelli
        Giuliano Antoniciello

DATA INIZIO: 27/05/2025

NOME FILE: tipiDiDato.c

Scopo delle funzioni presenti:
- stampareMenuDifficolta: Pulisce lo schermo e mostra a video il titolo e il menu delle impostazioni.
  e il nome della partita e infine avvia la partita con i parametri raccolti.
- stampareTitoloImpostazioni: Stampa il titolo per la sezione "Impostazioni".
- stampareMenuImpostazioni: Stampa le opzioni del menu delle impostazioni, incluse:
- dimensione della griglia: piccola, media, grande
- spazio per l' inserimento del nome della partita
- collezionareDimensione: Richiede all'utente un valore numerico corrispondente alla dimensione della griglia di gioco.
- collezionaNomeGioco: Richiede all'utente il nome da assegnare alla nuova partita.
 */

#include "../include/funzioniUtilita.h"
#include "../include/impostazioni.h"
#include "../include/partita.h"
#include "../include/costanti.h"

#include <stdio.h>

#define OPZIONE_START_RIGA 11
#define OPZIONE_COLONNA 16
#define INPUT_RIGA_DIFFICOLTA 14
#define INPUT_RIGA_DIMENSIONE 23
#define INPUT_COLONNA 17
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 12
#define INPUT_RIGA_NOME 11 
#define NOME_MAX 50
#define VERO 1
#define FALSO 0

#define OPZIONE_MIN 1
#define OPZIONE_MAX 3

/**
 * DESCRIZIONE: Pulisce lo schermo e stampa il titolo e il menu delle impostazioni di difficoltà e dimensione.
 * ARGOMENTI: nessuno
 * RITORNO: nessuno
 */
void stampareMenuImpostazioni() {
  pulireSchermo();
  printf(CIANO);
  printf("\n");
  stampareCentrato("        _                   _           _         _        ");
  stampareCentrato(" ___   |_|_____ ___ ___ ___| |_ ___ ___|_|___ ___|_|   ___ ");
  stampareCentrato("|___|  | |     | . | . |_ -|  _| .'|- _| | . |   | |  |___|");
  stampareCentrato("       |_|_|_|_|  _|___|___|_| |__,|___|_|___|_|_|_|       ");
  stampareCentrato("               |_|                                         ");
  printf(RESET);
  spostareCursore(OPZIONE_START_RIGA - 2, OPZIONE_COLONNA - 7);
  printf("-Scegliere la Modalita-");

  spostareCursore(OPZIONE_START_RIGA, OPZIONE_COLONNA - 3);
  printf("[1] vs amico");
  
  spostareCursore(OPZIONE_START_RIGA + 1, OPZIONE_COLONNA - 3);
  printf("[2] NERO vs bot ");
  
  spostareCursore(OPZIONE_START_RIGA + 2, OPZIONE_COLONNA - 3);
  printf("[3] BIANCO vs bot ");

  spostareCursore(OPZIONE_START_RIGA + 6, OPZIONE_COLONNA - 7);
  printf("-Scegliere la Dimensione-");

  spostareCursore(OPZIONE_START_RIGA + 8, OPZIONE_COLONNA);
  printf("[1] piccola");
  
  spostareCursore(OPZIONE_START_RIGA + 9, OPZIONE_COLONNA);
  printf("[2] media");
  
  spostareCursore(OPZIONE_START_RIGA + 10, OPZIONE_COLONNA);
  printf("[3] grande");

  spostareCursore(OPZIONE_START_RIGA - 2 , OPZIONE_COLONNA + 35);
  printf("-Scegliere il Nome-");
}

/**
 * DESCRIZIONE: Avvia il processo per iniziare una nuova partita. Mostra il menu di scelta della difficoltà, raccoglie i parametri necessari (modalità, dimensione, nome partita) e avvia il gioco usando la funzione unificata.
 * ARGOMENTI: nessuno
 * RITORNO: nessuno
 */
void configurareNuovaPartita() {
  char nomePartita[NOME_MAX];
  int modalita;
  int dimensione;
  int modalitaBot;
  int coloreGiocatore;
  Impostazioni *impostazioniPartita;

  stampareMenuImpostazioni();

  modalita = collezionareModalita();
  printf("%d", modalita);
  dimensione = collezionareDimensione();
  printf("%d", dimensione);
  collezionareNomePartita(nomePartita);

  dimensione = convertireDimensione(dimensione);
  impostazioniPartita = inizializzareImpostazioni(modalita, dimensione);
  printf("%d", impostazioniPartita->modalitaPartita);
  printf("%d", impostazioniPartita->dimScacchiera);
  getchar();

  if (modalita == 1) {
    modalitaBot = FALSO;
    coloreGiocatore = 0; // Non usato in modalità PvP
  } else {
    modalitaBot = VERO;
    if (modalita == 2) {
      coloreGiocatore = NERO; // Giocatore umano è NERO
    } else {
      coloreGiocatore = BIANCO; // Giocatore umano è BIANCO
    }
  }
  avviarePartitaUnificata(nomePartita, impostazioniPartita, NULL, modalitaBot, coloreGiocatore);
}

/**
 * DESCRIZIONE: Permette all'utente di inserire un valore numerico per la modalità di gioco. Controlla che l'input sia numerico e compreso tra OPZIONE_MIN e OPZIONE_MAX.
 * ARGOMENTI: nessuno
 * RITORNO: valore della modalità selezionata
 */
int collezionareModalita() {
  int inputModalita;
  int inMenuModalita;

  inputModalita = 0;
  inMenuModalita = VERO;

  while (inMenuModalita == VERO) {
    reimpostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    while (scanf("%d", &inputModalita) != 1) {
      pulireBuffer();
      reimpostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA - 6, ERR_MSG_COLONNA);
      reimpostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    }
    pulireBuffer();
    if (inputModalita >= OPZIONE_MIN && inputModalita <= OPZIONE_MAX) {
      inMenuModalita = FALSO;  
    } else {
      mostrareMessaggioErrore("Digita un numero tra (1 - 3)", ERR_MSG_RIGA - 6, ERR_MSG_COLONNA - 5);
      reimpostareZonaInput(INPUT_RIGA_DIFFICOLTA, INPUT_COLONNA);
    }
  }
  return inputModalita;
}

/**
 * DESCRIZIONE: Permette all'utente di inserire un valore numerico per la dimensione della griglia. Valida l'input assicurandosi che rientri nell'intervallo OPZIONE_MIN - OPZIONE_MAX.
 * ARGOMENTI: nessuno
 * RITORNO: valore della dimensione selezionata
 */
int collezionareDimensione() {
  int inMenuDimensione;
  int inputDimensione;

  inMenuDimensione = VERO;
  inputDimensione = 0;
  
  while (inMenuDimensione == VERO) {
    reimpostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    while (scanf("%d", &inputDimensione) != 1) {
      pulireBuffer();
      reimpostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
      mostrareMessaggioErrore("Digita un Numero", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA);
      reimpostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    }
    pulireBuffer();
    if (inputDimensione >= OPZIONE_MIN && inputDimensione <= OPZIONE_MAX) {
      inMenuDimensione = FALSO;  
    } else {
      mostrareMessaggioErrore("Digita un numero tra (1 - 3)", ERR_MSG_RIGA + 2, ERR_MSG_COLONNA - 5);
      reimpostareZonaInput(INPUT_RIGA_DIMENSIONE, INPUT_COLONNA);
    }
  }
  return inputDimensione;
}

/**
 * DESCRIZIONE: Permette all'utente di inserire un nome per la partita.
 * ARGOMENTI: inputNomePartita: buffer dove salvare il nome della partita
 * RITORNO: nessuno
 */
void collezionareNomePartita(char *inputNomePartita) {
  int lunghezzaNome;
  int inputValido;

  lunghezzaNome = 0;
  inputValido = FALSO;
  
  while (inputValido == FALSO) {
    reimpostareZonaInput(INPUT_RIGA_NOME, INPUT_COLONNA + 35);
    fgets(inputNomePartita, NOME_MAX, stdin);
    lunghezzaNome = lunghezza(inputNomePartita);
    
    if (inputNomePartita[lunghezzaNome - 1] == '\n' && lunghezzaNome < NOME_MAX) { 
      inputNomePartita[lunghezzaNome - 1] = '\0'; 
      inputValido = VERO;
    } else {
      pulireBuffer();
    }
  }
}
