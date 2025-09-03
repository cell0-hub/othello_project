#ifndef TIPIDIDATO_H
#define TIPIDIDATO_H

#include <dirent.h>
// Definizione della struttura Cella
typedef struct {
  int stato;
} Cella;

// Definizione della struttura Scacchiera
typedef struct {
    int dimScacchiera;
    Cella **celleScacchiera;
} Scacchiera;

typedef struct {
  int modalitaPartita;
  int dimScacchiera;
} Impostazioni;

// Definizione della struttura Partita
typedef struct {
    Scacchiera scacchieraPartita;
    char nomePartita[50];
    Impostazioni impPartita;
    int turnoGiocatore;
} Partita;

// Dichiarazioni delle funzioni per Scacchiera
int leggereDimScacchiera(Scacchiera scacchiera);
int leggereCellaScacchiera(Scacchiera scacchiera, int riga, int colonna);
void scrivereDimScacchiera(Scacchiera *scacchiera, int valore);
void scrivereCellaScacchiera(Scacchiera *scacchiera, int riga, int colonna, int valore);

// Dichiarazioni delle funzioni per Partita
Scacchiera leggereScacchieraPartita(Partita *partita);
char* leggereNomePartita(Partita *partita);
void scrivereNomePartita(Partita *partita, char nome[50]);
void scrivereDimScacchieraPartita(Partita *partita, int valore);
void scrivereCellaPartita(Partita *partita, int valore, int riga, int colonna);
void inizializzareScacchieraPartita(Partita *partita, int dimensione);
Impostazioni leggereImpPartita(Partita partita);
int leggereModalitaPartita(Partita partita);
void scrivereModalitaPartita(Partita *partita, int valore);
void cambiareTurnoGiocatorePartita(Partita *partita);
int leggereTurnoGiocatore(Partita *partita);
void scrivereTurnoGiocatorePartita(Partita *partita, int turno);
void scrivereImpPartita(Partita *partita, Impostazioni imp);

//Funzioni di accesso tipo di dato impostazioni
int leggereModalitaImpostazioni(Impostazioni imp);
int leggereDimScacchieraImp(Impostazioni imp);
void scrivereModalitaImpostazioni(Impostazioni *imp, int valore);
void scrivereDimScacchieraImp(Impostazioni *imp, int valore);
Impostazioni* inizializzareImpostazioni(int modalita, int dimensione);

int leggereStatoCella(Cella cella);
void scrivereStatoCella(Cella *cella, int nuovoStato);

struct dirent* leggereProssimaVoce(DIR* cartella);
const char* ottenereNomeVoce(struct dirent* voce); 
#endif

