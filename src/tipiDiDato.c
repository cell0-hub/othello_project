/*
AUTORI: Onofrio de Robertis
        Michele Amato
        DavideFornelli
        Giuliano Antoniciello

DATA INIZIO: 27/05/2024

NOME FILE: tipiDiDato.c

Scopo delle funzioni presenti:
- leggereDimScacchiera: restituisce la dimensione della scacchiera.
- leggereValScacchiera: restituisce il valore in una cella specifica della scacchiera.
- scrivereDimScacchiera: imposta la dimensione della scacchiera.
- scrivereValScacchiera: imposta un valore in una cella specifica della scacchiera.
- leggereDifficoltaImp: restituisce il campo difficoltà di Impostazioni.
- leggereDimScacchieraImp: restituisce il campo dimensione della scacchiera di Impostazioni.
- scrivereDifficoltaImp: imposta il campo difficoltà di Impostazioni.
- scrivereDimensioneImp: imposta il cmapo dimensione della scacchiera di Impostazioni.
- leggereImpPartita: restituisce il campo Impostazioni da una Partita.
- leggereScacchieraPartita: restituisce il campo Scacchiera di Partita.
- leggereNomePartita: restituisce il nome della partita.
- scrivereImpPartita: imposta i campi difficoltà e dimensione del campo impostazioni di Partita.
- scrivereNomePartita: imposta il nome della partita.
- scrivereDimScacchieraPartita: imposta il campo dimensione della scacchiera del campo Scacchiera di Partita.
- scrivereValScacchieraPartita: imposta un valore in una cella della Scacchiera di Partita.
- inizializzareScacchieraPartita: alloca e inizializza a zero la scacchiera di gioco con dimensione scelta.
 */

#include <stdlib.h>
#include <string.h>
#include "../include/tipiDiDato.h"
#include "../include/costanti.h"

//funzioni di accesso per il tipo di dato cella
//
int leggereStatoCella(Cella casella){
  int valoreLetto;
  valoreLetto = casella.stato;
  return valoreLetto;
}

void scrivereStatoCella(Cella *cella, int nuovoStato) {
  cella->stato = nuovoStato;
}

//funzioni di accesso per il tipo di dato scacchiera

int leggereDimScacchiera(Scacchiera scacchiera) {
    int valoreLetto;
    valoreLetto = scacchiera.dimScacchiera;

    return valoreLetto;
}

void scrivereDimScacchiera(Scacchiera *scacchiera, int valore) {
    scacchiera->dimScacchiera = valore;
}

int leggereCellaScacchiera(Scacchiera scacchiera, int riga, int colonna) {
    int valoreLetto;
    valoreLetto = leggereStatoCella(scacchiera.celleScacchiera[riga][colonna]); 
    return valoreLetto;
}

void scrivereCellaScacchiera(Scacchiera *scacchiera, int riga, int colonna, int valore) {
  scrivereStatoCella(&scacchiera->celleScacchiera[riga][colonna], valore);
}

//funzioni di accesso al tipo di dato partita
Impostazioni leggereImpPartita(Partita partita) {
  Impostazioni impostazioniLette;

  impostazioniLette = partita.impPartita;
  return impostazioniLette;
}

//???? scrivereImppartita
int leggereModalitaPartita(Partita partita) {
  int valoreLetto;

  valoreLetto = leggereModalitaImpostazioni(leggereImpPartita(partita));
  return valoreLetto;
}

void scrivereModalitaPartita(Partita *partita, int valore) {
  scrivereModalitaImpostazioni(&(partita->impPartita), valore);
}

Scacchiera leggereScacchieraPartita(Partita *partita) {
    Scacchiera scacchieraLetta;

    scacchieraLetta = partita->scacchieraPartita;
    return scacchieraLetta;
}

char* leggereNomePartita(Partita *partita) {
    char* nomeLetto;

    nomeLetto = partita->nomePartita;
    return nomeLetto;
}

void scrivereNomePartita(Partita *partita, char nome[50]) {
    strcpy(partita->nomePartita, nome);
}

void scrivereDimScacchieraPartita(Partita *partita, int valore) {
  Scacchiera scacchieraPartita;

  //qui utilizziamo scacchieraPartita come appoggio, 
  //perche' abbiamo bisogno di passarlo come puntatore
  scacchieraPartita = leggereScacchieraPartita(partita);
  scrivereDimScacchiera(&scacchieraPartita, valore);
}

void scrivereCellaPartita(Partita *partita, int valore, int riga, int colonna) {
  Scacchiera scacchieraPartita;

  //qui utilizziamo scacchieraPartita come appoggio, 
  //perche' abbiamo bisogno di passarlo come puntatore
  scacchieraPartita = leggereScacchieraPartita(partita);
  scrivereCellaScacchiera(&scacchieraPartita, riga, colonna, valore);
}

int leggereTurnoGiocatore(Partita *partita) {
  int giocatoreCorrente;

  giocatoreCorrente = partita->turnoGiocatore;
  return giocatoreCorrente;
}

void cambiareTurnoGiocatore(Partita *partita) {
  if(partita->turnoGiocatore == NERO) {
    partita->turnoGiocatore = BIANCO;
  } else {
    partita->turnoGiocatore = NERO;
  }
}

void scrivereTurnoGiocatore(Partita *partita, int turno) {
  partita->turnoGiocatore = turno;
}

void inizializzareScacchieraPartita(Partita *partita, int dim) {
    int riga;
    int colonna;
    scrivereDimScacchieraPartita(partita, dim);
    partita->scacchieraPartita.celleScacchiera = malloc(dim * sizeof(Cella *));
    riga = 0;
    while (riga < dim) {
        partita->scacchieraPartita.celleScacchiera[riga] = malloc(dim * sizeof(Cella));
        colonna = 0;  
        while (colonna < dim) {
            scrivereCellaPartita(partita, CELLA_VUOTA, riga, colonna);
            colonna = colonna + 1;
        }
        riga = riga + 1;
    }
}


//funzioni di accesso tipo di dato impostazioni
int leggereModalitaImpostazioni(Impostazioni imp) {
  int valoreLetto;

  valoreLetto = imp.modalitaPartita;
  return valoreLetto;
}

int leggereDimScacchieraImp(Impostazioni imp) {
  int valoreLetto;

  valoreLetto = imp.dimScacchiera;
  return valoreLetto;
}

void scrivereModalitaImpostazioni(Impostazioni *imp, int valore) {
  imp->modalitaPartita = valore;
}

void scrivereDimScacchieraImp(Impostazioni *imp, int valore) {
  imp->dimScacchiera = valore;
}

Impostazioni* inizializzareImpostazioni(int modalita, int dimensione) {
    Impostazioni *imp;
    imp = (Impostazioni*)malloc(sizeof(Impostazioni));
    
    imp->modalitaPartita = modalita;
    imp->dimScacchiera = dimensione;
    
    return imp;
}
