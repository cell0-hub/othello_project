/*
AUTORI: Davide Fornelli

DATA INIZIO: 27/05/2025

NOME FILE: interfaccia_util.c

Scopo delle funzioni presenti:
stampaASinistra() -> funzione utilizzata per centrare a sinistra sul terminale;
stampaCentrato() -> funzione utilizzata per centrare sul terminale il menù di partenza;
mostraMenu() -> funzione utilizzata per stampare a video il menù di partenza;
collezionaInput() -> funzione utilizzata per collezionare l' input dell utente;
spostareCursore() -> funzione utilizzata per spostare la posizione del cursore nel terminale;
*/

#include <stdio.h>
#include "../include/homepage.h"
#include "../include/costanti.h"

#define LARGHEZZA_TERMINALE 80
#define ALTEZZA_TERMINALE 25

void spostareCursore(int x, int y)
{
  printf("\033[%d;%dH", x, y);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *  FUNZIONE: stampaCentrato(const char *testo)             *
 *  DESCRIZIONE: Allinea la stringa "testo"sul terminale    *
 *                                                          *
 *  ARGOMENTI:                                              *
 *  const char *testo: stringa da allineare                 *
 *                                                          *
 *  RITORNO: Terminale aggiornato                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
void stampareCentrato(const char *testo) 
{
  int spaziDaInserire; 
  int dimStringa; 
  int spazi; 

  dimStringa = lunghezza(testo);
  spazi = (LARGHEZZA_TERMINALE - dimStringa) / 2;
  if (spazi < 0)
  {
    spazi = 0;
  }

  spaziDaInserire = 0;
  while(spaziDaInserire < spazi)
  {
    printf(" ");
    spaziDaInserire = spaziDaInserire + 1;
  }
  printf("%s\n", testo);
}


/*******************************************************
reimpostareZonaInput                                   *
*                                                      *
* DESCRIZIONE: Ripulisce e reimposta la zona di input  *
*              nella posizione specificata sullo       *
*              schermo. Mostra il prompt ">> " e       *
*              cancella eventuali caratteri residui.   *
*                                                      *
* ARGOMENTI:                                           *
* posRiga: riga dello schermo dove posizionare il      *
*          cursore per l'input                         *
* posColonna: colonna dello schermo dove posizionare   *
*              il cursore per l'input                  *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void reimpostareZonaInput(int posRiga, int posColonna){
    spostareCursore(posRiga, posColonna);
    printf(">> ");
    printf("%-8s", "");
    spostareCursore(posRiga, posColonna + 3);
}

void pulireBuffer(){
      while(getchar() != '\n'); // pulisce il buffer
}


/*******************************************************
* FUNZIONE: mostrareMessaggioErrore                    *
*                                                      *
* DESCRIZIONE: Mostra un messaggio di errore colorato  *
*              in rosso in una posizione specifica     *
*              dello schermo. Cancella prima la riga   *
*              per evitare sovrapposizioni di testo.   *
*                                                      *
* ARGOMENTI:                                           *
* testo: stringa del messaggio da visualizzare         *
* posRiga: riga in cui mostrare il messaggio           *
* posColonna: colonna in cui mostrare il messaggio     *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void mostrareMessaggioErrore(const char *testo, int posRiga, int posColonna) {
      spostareCursore(posRiga, 0);
      printf("%-80s", "");
      spostareCursore(posRiga, posColonna);
      printf("%s %s %s",COLOR_RED, testo, COLOR_RESET);
}


/*******************************************************
* FUNZIONE: tornareHomepage                            *
*                                                      *
* DESCRIZIONE: Mostra un'opzione per tornare alla      *
*              homepage del menu principale. Attende   *
*              l'inserimento del valore "0" da parte   *
*              dell'utente, verificando che l'input    *
*              sia corretto. In caso di input errato,  *
*              mostra un messaggio d'errore e richiede *
*              nuovamente l'inserimento.               *
*                                                      *
* ARGOMENTI:                                           *
* input: puntatore a intero in cui viene memorizzato   *
*        il valore inserito dall'utente                *
* posRiga: riga in cui visualizzare il prompt          *
* posColonna: colonna in cui visualizzare il prompt    *
*                                                      *
* RITORNO: Terminale aggiornato                        *
*******************************************************/
void tornareHomepage(int *input, int posRiga, int posColonna){
  int inMenuCorrente;

  inMenuCorrente = VERO;
  spostareCursore(posRiga - 1, posColonna);
  printf("[0] torna alla homepage");
  while(inMenuCorrente) {
    reimpostareZonaInput(posRiga, posColonna + 8);

    while(scanf("%d", input) != 1) {
        mostrareMessaggioErrore("input non valido", posRiga + 2, posColonna + 3);
        reimpostareZonaInput(posRiga, posColonna + 8);
        pulireBuffer();
    }
    if(*input != 0){
        mostrareMessaggioErrore("input non valido", posRiga + 2, posColonna + 3);
        reimpostareZonaInput(posRiga, posColonna + 8);
        pulireBuffer();
    }
    else if (*input == 0) {
      avviareMenuPrincipale();
      inMenuCorrente = FALSO;
    }
  }
}

void pulireSchermo() {
    printf("\033[2J");    
    printf("\033[H");     
    fflush(stdout);
}

int lunghezza(const char stringa[]) {
    int lunghezza = 0;
    while (stringa[lunghezza] != '\0') {
        lunghezza = lunghezza + 1;
    }
    return lunghezza;
}

void concatenareDueStringhe(const char stringa1[], const char stringa2[], char stringaFinale[]) {
    int i = 0;
    while (i < lunghezza(stringa1)) {
        stringaFinale[i] = stringa1[i];
        i = i + 1;
    }

    int j = 0;
    while (j < lunghezza(stringa2)) {
        stringaFinale[i + j] = stringa2[j];
        j = j + 1;
    }

    stringaFinale[i + j] = '\0'; // Carattere di fine stringa
}

int confrontarePrefisso(const char *stringa1, const char *prefisso) {
    int lunghezzaPrefisso;
    int cursStringa;
    int esito; 

    lunghezzaPrefisso = lunghezza(prefisso);
    esito = VERO;

    cursStringa = 0;
    while (cursStringa < lunghezzaPrefisso) {
        if (stringa1[cursStringa] != prefisso[cursStringa]) {
            esito = FALSO;
        }
        cursStringa = cursStringa + 1;
    }
    return esito;
}

int modulo(int dividendo, int divisore) {
    int resto = 0;
    if(divisore == 0){
      resto = -1;
    } else {
      while (dividendo >= divisore) {
        dividendo = dividendo - divisore;
      }
      if (dividendo < 0) {
        resto = -dividendo;
      } else {
        resto = dividendo;
      }
    }
    return resto;
}

void copiareDueStringhe(char* stringa1, const char* stringa2) {
  int cursStringa;

  cursStringa = 0;
  while (cursStringa < lunghezza(stringa2)) {
    stringa1[cursStringa] = stringa2[cursStringa];
    cursStringa = cursStringa + 1;
  }
}

