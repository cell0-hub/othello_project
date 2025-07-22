/*
Autori: Davide Fornelli
        Antoniciello Giuliano

Data di inizio di scrittura del file: 
        04/05/2025

Nome del file:
        Home Page sudoku

Scopo di ogni funzione presente:
- stampareTitoloHomepage: Visualizza il titolo del gioco al centro del terminale.
- stampareMenuHomepage: Stampa le opzioni del menu principale.
- stampareMenuPrincipale: Pulisce lo schermo e mostra sia il titolo che il menu principale del gioco.
- avviareMenuPrincipale: Avvia il menu principale mostrando il contenuto a schermo.
- collezionareInput: Gestisce l’acquisizione dell’input numerico da parte dell’utente nel menu principale.

*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/homepage.h"
#include "../include/funzioniUtilita.h"

#define LARGHEZZA_TERMINALE 80

#define TITOLO_RIGA 10
#define TITOLO_COLONNA 36  
#define OPZIONE_START_RIGA 12
#define OPZIONE_COLONNA 30 
#define PROMPT_RIGA 19
#define PROMPT_COLONNA 28 
#define INPUT_RIGA 20
#define INPUT_COLONNA 35 
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 31

#define NUOVA_PARTITA 1
#define PARTITE_SALVATE 2
#define ESCI 3

#define OPZIONE_MIN 1
#define OPZIONE_MAX 4

#define VERO 1
#define FALSO 0

#define VERDE "\033[32m"
#define RESET "\033[0m"

/********************************************************
* FUNZIONE: stampareMenuPrincipale                      *
*                                                       *
* DESCRIZIONE: Pulisce lo schermo e visualizza il       *
*              titolo della homepage seguito dal menu   *
*              principale.                              *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
********************************************************/
void stampareMenuPrincipale() 
{
  pulireSchermo();

  printf(VERDE);
  printf("\n");
  stampareCentrato("       _   _          _ _          ___ ");
  stampareCentrato("  ___ | |_| |__   ___| | | ___    / _ \\");
  stampareCentrato(" / _ \\| __| '_ \\ / _ \\ | |/ _ \\  / /_\\/");
  stampareCentrato("| (_) | |_| | | |  __/ | | (_) |/ /_\\\\ ");
  stampareCentrato(" \\___/ \\__|_| |_|\\___|_|_|\\___(_)____/ ");
  printf(RESET);

  spostareCursore(TITOLO_RIGA, TITOLO_COLONNA);
  printf("- MENU -");
  spostareCursore(OPZIONE_START_RIGA, OPZIONE_COLONNA);
  printf("[1] Nuova Partita");
  spostareCursore(OPZIONE_START_RIGA + 1, OPZIONE_COLONNA);
  printf("[2] Partite Salvate");
  spostareCursore(OPZIONE_START_RIGA + 2, OPZIONE_COLONNA);
  printf("[3] Esci");
  spostareCursore(PROMPT_RIGA, PROMPT_COLONNA);
  printf("Inserisci una scelta (1 - 3)");
}

/********************************************************
* FUNZIONE: avviareMenuPrincipale                       *
*                                                       *
* DESCRIZIONE: Avvia il menu principale visualizzandolo *
*              e raccogliendo l'input dell'utente.      *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
********************************************************/

void avviareMenuPrincipale(){
  stampareMenuPrincipale();
  collezionareInputHomepage(); 
}

/************************************************************** 
 *  FUNZIONE: collezionareInput()                             *
 *  DESCRIZIONE: colleziona l' input dell' utente             *
 *                                                            *
 *  ARGOMENTI:                                                *
 *  //                                                        *
 *                                                            *
 *  RITORNO: funzione scelta dall' utente avviata             *
 **************************************************************/

void collezionareInputHomepage() {
  int inMenuPrinipale; 
  int input;

  inMenuPrinipale = VERO;
  while(inMenuPrinipale) {
    reimpostareZonaInput(INPUT_RIGA, INPUT_COLONNA);
    
    // non presente nello pseudocodice, perche' si da per scontato
    // che l' input dell' utente sia un numero
    while(scanf("%d", &input) != 1) {  
      pulireBuffer();
      mostrareMessaggioErrore(" Digita un Numero ", ERR_MSG_RIGA, ERR_MSG_COLONNA);
      reimpostareZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }

    pulireBuffer();

    if(input < OPZIONE_MIN || input > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un Numero compreso tra 1 - 4 ", ERR_MSG_RIGA, ERR_MSG_COLONNA - 7);
      reimpostareZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }
    else if (input == NUOVA_PARTITA) {
      inMenuPrinipale = FALSO;
    }
    else if (input == PARTITE_SALVATE) {
      inMenuPrinipale = FALSO;
    }
    else if (input == ESCI) {
      exit(0);
    }
  }
}

