#ifndef TIPIDIDATO_H
#define TIPIDIDATO_H

// Definizione della struttura Casella
typedef struct {
  int stato;
} Casella;

// Definizione della struttura Scacchiera
typedef struct {
    Casella **caselle;
    int dimScacchiera;
} Scacchiera;

// Definizione della struttura Partita
typedef struct {
    Scacchiera scacchieraPartita;
    char nomePartita[50];
    int modalita;
} Partita;

// Dichiarazioni delle funzioni per Scacchiera
int leggereDimScacchiera(Scacchiera scacchiera);
int leggereStatoCasellaScacchiera(Scacchiera scacchiera, int riga, int colonna);
void scrivereDimScacchiera(Scacchiera *scacchiera, int valore);
void scrivereStatoCasellaScacchiera(Scacchiera *scacchiera, int riga, int colonna, int valore);


// Dichiarazioni delle funzioni per Partita
Scacchiera leggereScacchieraPartita(Partita *partita);
char* leggereNomePartita(Partita *partita);
void scrivereNomePartita(Partita *partita, char nome[50]);
void scrivereDimScacchieraPartita(Partita *partita, int valore);
void scrivereStatoCasellaScacchieraPartita(Partita *partita, int valore, int riga, int colonna);
void inizializzareScacchieraPartita(Partita *partita, int dimensione);
void scrivereModalitaPartita(Partita *partita, int nuovaModalita);

#endif

