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
#include "../include/partita.h"

// Funzioni per Scacchiera
int leggereDimScacchiera(Scacchiera scacchiera) {
    int valoreLetto;

    valoreLetto = scacchiera.dimScacchiera;
    return valoreLetto;
}

int leggereStatoScacchiera(Scacchiera scacchiera, int riga, int colonna) {
    int valoreLetto;
    valoreLetto = scacchiera.caselle[riga][colonna].stato;
    return valoreLetto;
}

void scrivereDimScacchiera(Scacchiera *scacchiera, int valore) {
    scacchiera->dimScacchiera = valore;
}

void scrivereStatoScacchiera(Scacchiera *scacchiera, int riga, int colonna, int valore) {
    scacchiera->caselle[riga][colonna].stato = valore;
}

// Funzioni per Partita
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
    scrivereDimScacchiera(&partita->scacchieraPartita, valore);
}

void scrivereStatoScacchieraPartita(Partita *partita, int valore, int riga, int colonna) {
    scrivereStatoScacchiera(&partita->scacchieraPartita, riga, colonna, valore);
}


void inizializzareScacchieraPartita(Partita *partita, int dim) {
    int riga; // righe della scacchiera
    int colonna; // colonne della scacchiera 

    scrivereDimScacchieraPartita(partita, dim);
         
    partita->scacchieraPartita.caselle = malloc(dim * sizeof(Casella *));
    
    riga = 0;
    while (riga < dim) {
        partita->scacchieraPartita.caselle[riga] = malloc(dim * sizeof(Casella));
        colonna = 0;  
        while (colonna < dim) {
            partita->scacchieraPartita.caselle[riga][colonna].stato = 0; // Inizializza a zero
            colonna = colonna + 1;
        }
        riga = riga + 1;
    }
}

//funzioni per Cella
int leggereStatoCasella(Casella casella){
  int valoreLetto;

  valoreLetto = casella.stato;
  return valoreLetto;
}

void scrivereStatoCasella(Casella *casella, int nuovoStato) {
  casella->stato = nuovoStato;
}



