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

/**
 * DESCRIZIONE: Restituisce la dimensione della scacchiera.
 * ARGOMENTI: scacchiera: struttura Scacchiera
 * RITORNO: dimensione della scacchiera
 */
int leggereDimScacchiera(Scacchiera scacchiera) {
    int valoreLetto;
    valoreLetto = scacchiera.dimScacchiera;
    return valoreLetto;
}

/**
 * DESCRIZIONE: Restituisce il valore in una cella specifica della scacchiera.
 * ARGOMENTI: scacchiera: struttura Scacchiera, riga: riga, colonna: colonna
 * RITORNO: valore della cella
 */
int leggereStatoCasellaScacchiera(Scacchiera scacchiera, int riga, int colonna) {
    int valoreLetto;
    valoreLetto = scacchiera.caselle[riga][colonna].stato;
    return valoreLetto;
}

/**
 * DESCRIZIONE: Imposta la dimensione della scacchiera.
 * ARGOMENTI: scacchiera: puntatore a Scacchiera, valore: dimensione
 * RITORNO: nessuno
 */
void scrivereDimScacchiera(Scacchiera *scacchiera, int valore) {
    scacchiera->dimScacchiera = valore;
}

/**
 * DESCRIZIONE: Imposta un valore in una cella specifica della scacchiera.
 * ARGOMENTI: scacchiera: puntatore a Scacchiera, riga: riga, colonna: colonna, valore: valore da scrivere
 * RITORNO: nessuno
 */
void scrivereStatoCasellaScacchiera(Scacchiera *scacchiera, int riga, int colonna, int valore) {
    scacchiera->caselle[riga][colonna].stato = valore;
}

/**
 * DESCRIZIONE: Restituisce la scacchiera dalla struttura Partita.
 * ARGOMENTI: partita: puntatore a Partita
 * RITORNO: struttura Scacchiera
 */
Scacchiera leggereScacchieraPartita(Partita *partita) {
    Scacchiera scacchieraLetta;
    scacchieraLetta = partita->scacchieraPartita;
    return scacchieraLetta;
}

/**
 * DESCRIZIONE: Restituisce il nome della partita.
 * ARGOMENTI: partita: puntatore a Partita
 * RITORNO: puntatore a stringa nome
 */
char* leggereNomePartita(Partita *partita) {
    char* nomeLetto;
    nomeLetto = partita->nomePartita;
    return nomeLetto;
}

/**
 * DESCRIZIONE: Imposta il nome della partita.
 * ARGOMENTI: partita: puntatore a Partita, nome: stringa nome
 * RITORNO: nessuno
 */
void scrivereNomePartita(Partita *partita, char nome[50]) {
    strcpy(partita->nomePartita, nome);
}

void scrivereModalitaPartita(Partita *partita, int nuovaModalita) {
  partita->modalita = nuovaModalita;
}

/**
 * DESCRIZIONE: Imposta la dimensione della scacchiera nella struttura Partita.
 * ARGOMENTI: partita: puntatore a Partita, valore: dimensione
 * RITORNO: nessuno
 */
void scrivereDimScacchieraPartita(Partita *partita, int valore) {
    scrivereDimScacchiera(&partita->scacchieraPartita, valore);
}

/**
 * DESCRIZIONE: Imposta un valore in una cella della scacchiera della struttura Partita.
 * ARGOMENTI: partita: puntatore a Partita, valore: valore da scrivere, riga: riga, colonna: colonna
 * RITORNO: nessuno
 */
void scrivereStatoCasellaPartita(Partita *partita, int valore, int riga, int colonna) {
    scrivereStatoCasellaScacchiera(&partita->scacchieraPartita, riga, colonna, valore);
}

/**
 * DESCRIZIONE: Alloca e inizializza a zero la scacchiera di gioco con dimensione scelta.
 * ARGOMENTI: partita: puntatore a Partita, dim: dimensione
 * RITORNO: nessuno
 */
void inizializzareScacchieraPartita(Partita *partita, int dim) {
    int riga;
    int colonna;
    scrivereDimScacchieraPartita(partita, dim);
    partita->scacchieraPartita.caselle = malloc(dim * sizeof(Casella *));
    riga = 0;
    while (riga < dim) {
        partita->scacchieraPartita.caselle[riga] = malloc(dim * sizeof(Casella));
        colonna = 0;  
        while (colonna < dim) {
            partita->scacchieraPartita.caselle[riga][colonna].stato = 0;
            colonna = colonna + 1;
        }
        riga = riga + 1;
    }
}

/**
 * DESCRIZIONE: Restituisce lo stato di una casella.
 * ARGOMENTI: casella: struttura Casella
 * RITORNO: stato della casella
 */
int leggereStatoCasella(Casella casella){
  int valoreLetto;
  valoreLetto = casella.stato;
  return valoreLetto;
}

/**
 * DESCRIZIONE: Imposta lo stato di una casella.
 * ARGOMENTI: casella: puntatore a Casella, nuovoStato: valore da assegnare
 * RITORNO: nessuno
 */
void scrivereStatoCasella(Casella *casella, int nuovoStato) {
  casella->stato = nuovoStato;
}
