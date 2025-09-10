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
#include "../include/impostazioni.h"
#include "../include/caricaPartita.h"
#include "../include/costanti.h"


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


#define OPZIONE_MIN 1
#define OPZIONE_MAX 3 



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
  stampareCentrato("     _   _       _ _       _____ ");
  stampareCentrato(" ___| |_| |_ ___| | |___  |   __|");
  stampareCentrato("| . |  _|   | -_| | | . |_|  |  |");
  stampareCentrato("|___|_| |_|_|___|_|_|___|_|_____|");
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
 *  FUNZIONE: collezionareInputHomepage()                      *
 *  DESCRIZIONE: colleziona l' input dell' utente              *
 *                                                            *
 *  ARGOMENTI:                                                *
 *  //                                                        *
 *                                                            *
 *  RITORNO: funzione scelta dall' utente avviata              *
 **************************************************************/
void collezionareInputHomepage() {
  int inMenuPrincipale; 
  int input;

  inMenuPrincipale = VERO;
  input = 0;
  while(inMenuPrincipale == VERO) {
    reimpostareZonaInput(INPUT_RIGA, INPUT_COLONNA);
    while(scanf("%d", &input) != 1) {  
      pulireBuffer();
      mostrareMessaggioErrore(" Digita un Numero ", ERR_MSG_RIGA, ERR_MSG_COLONNA);
      reimpostareZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }
    pulireBuffer();
    if(input < OPZIONE_MIN || input > OPZIONE_MAX) {
      mostrareMessaggioErrore("Digita un Numero compreso tra 1 - 3 ", ERR_MSG_RIGA, ERR_MSG_COLONNA - 7);
      reimpostareZonaInput(INPUT_RIGA, INPUT_COLONNA);
    }
    else if (input == NUOVA_PARTITA) {
      configurareNuovaPartita();
      inMenuPrincipale = FALSO;
    }
    else if (input == PARTITE_SALVATE) {
      avviareMenuCaricaPartita();
      inMenuPrincipale = FALSO;
    }
    else if (input == ESCI) {
      exit(0);
    }
  }
}

