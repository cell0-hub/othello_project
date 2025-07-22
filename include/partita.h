#ifndef PARTITA_H
#define PARTITA_H

#include <stdio.h>
#include "../include/tipiDiDato.h"
 
// Costanti
#define RIGA_INPUT_RIGA 13
#define RIGA_INPUT_COLONNA 16
#define RIGA_INPUT_VALORE 19
#define RIGA_INPUT 28
#define COLONNA_INPUT 67
#define FALSO 0
#define VERO 1
#define RIGA_ERRORE 22
#define COLONNA_ERRORE 27

// Funzioni principali del gioco
void avviarePartita();
void avviarePartitaContinuata(Partita *partita);

// Funzioni di visualizzazione
void mostraSchermo(int dimensione);
void stampareTitoloPartita(void);
void stampareVittoria(void);
void stampareTabellaInput(void);
void disegnareCornice(void);

// Funzioni di gestione scacchiera e stampa
void stampareScacchieraPartita(Partita *partita);
void stampareIntestazioneColonne(int dimensione, int numeroSottoquadrato);
void stampareLineaOrizzontale(int dimensione, int numeroSottoquadrato);
void stampareRigheScacchiera(Scacchiera scacchiera);
void stampareRigaScacchiera(Scacchiera scacchiera, int riga);

// Funzioni di utilità per dimensioni e difficoltà
void convertireDimensione(int *dimensione);
int calcolareSottoquadrato(int dimensione);

// Funzioni di validazione
int collezionareInput(Scacchiera *scacchiera, int *input, int rigaTerminale);

// Funzioni di controllo stato partita
int controllareScacchieraPiena(Scacchiera scacchiera);
int controllareSalvataggio(Partita partita, int *input);

void inizializzarePartitaOthello(Partita *partita);
int mossaValida(Partita *partita, int riga, int colonna, int giocatore);
void eseguiMossa(Partita *partita, int riga, int colonna, int giocatore);
void flipPedine(Partita *partita, int riga, int colonna, int giocatore);
int pedineDaFlippareInDirezione(Partita *p, int r, int c, int dr, int dc, int g);
int nessunaMossaPossibile(Partita *partita, int giocatore);
void stampareScacchieraOthello(Partita *partita);
int contarePedine(Partita *partita, int giocatore);
void stampareVittoriaOthello(int neri, int bianchi);
#endif // PARTITA_H




