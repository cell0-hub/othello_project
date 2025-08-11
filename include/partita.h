#ifndef PARTITA_H
#define PARTITA_H

#include <stdio.h>
#include "../include/tipiDiDato.h"
 
// Costanti
#define RIGA_INPUT_COLONNA 16
#define RIGA_INPUT_VALORE 19
#define RIGA_INPUT 28
#define COLONNA_INPUT 67
#define FALSO 0
#define VERO 1
#define RIGA_ERRORE 24
#define COLONNA_ERRORE 27

// Funzioni principali del gioco
void avviarePartita(char nomePartita[50], Impostazioni *impostazioniPartita);
void avviarePartitaContinuata(Partita *partita);
void avviarePartitaBot(char nomePartita[50], Impostazioni *impostazioniPartita, int coloreGiocatore);
void avviarePartitaContinuataBot(Partita *partita, int coloreGiocatore);
  

// Funzioni di visualizzazione
void mostraSchermo(int dimensione);
void stampareTitoloPartita();
void stampareVittoria();
void stampareTabellaInput();
void disegnareCornice();

// Funzioni di gestione scacchiera e stampa
void stampareScacchieraPartita(Partita *partita);
void stampareIntestazioneColonne(int dimensione, int numeroSottoquadrato);
void stampareLineaOrizzontale(Partita *partita);
void stampareRigheScacchiera(Scacchiera scacchiera);
void stampareRigaScacchiera(Scacchiera scacchiera, int riga);

// Funzioni di utilità per dimensioni e difficoltà
int convertireDimensione(int dimensione);

// Funzioni di validazione
int collezionareCoordinata(int rigaTerminale);
int collezionareAzione();

// Funzioni di controllo stato partita
int controllareScacchieraPiena(Scacchiera scacchiera);
int controllareSalvataggio(Partita partita, int *input);

void inizializzarePartitaOthello(Partita *partita);
int mossaValida(Partita *partita, int riga, int colonna, int giocatore);
void eseguireMossa(Partita *partita, int riga, int colonna, int giocatore);
void flipPedine(Partita *partita, int riga, int colonna, int giocatore);
int pedineDaFlippareInDirezione(Partita *p, int r, int c, int dr, int dc, int g);
int nessunaMossaPossibile(Partita *partita, int giocatore);
void stampareScacchieraOthello(Partita *partita);
int contarePedine(Partita *partita, int giocatore);
void stampareConteggioPedine(Partita *partita, int turnoCorrente);
void stampareVittoria(int neriTotali, int bianchiTotali);


#endif // PARTITA_H


