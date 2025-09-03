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
#include <dirent.h>
#include "../include/tipiDiDato.h"
#include "../include/costanti.h"

//
//funzioni di accesso per il tipo di dato cella
//

/*
 * DESCRIZIONE: leggere il valore del campo statoCella di cella
 * ARGOMENTI: cella, cella di cui leggere il valore del campo, Cella
 * RITORNO: valoreLetto, valore del campo statoCella di cella, Int
 */
int leggereStatoCella(Cella cella){
  int valoreLetto;
  valoreLetto = cella.stato;
  return valoreLetto;
}

/*
 * DESCRIZIONE: scrive il valore del campo statoCella di cella
 * ARGOMENTI: cella, cella di cui scrivere il valore del campo, Cella
 *            valore, nuovo valore del campo statoCella, int
 * RITORNO: cella, cella con il valore del campo statoCella aggiornato, Cella
 */
void scrivereStatoCella(Cella *cella, int valore) {
  cella->stato = valore;
}

//funzioni di accesso per il tipo di dato scacchiera

/*
 * DESCRIZIONE: legge il valore del campo dimScacchiera di scacchiera
 * ARGOMENTI: scacchiera, scacchiera di cui leggere il valore, Scacchiera
 * RITORNO: valoreLetto, valore del campo dimScacchiera di scacchiera, Int
 */
int leggereDimScacchiera(Scacchiera scacchiera) {
    int valoreLetto;
    valoreLetto = scacchiera.dimScacchiera;

    return valoreLetto;
}

/*
 * DESCRIZIONE: scrive il valore del campo dimScacchiera di scacchiera
 * ARGOMENTI: scacchiera, scacchiera di cui modificare 
 *            il valore del campo dimScacchiera, Scacchiera
 *            valore, nuovo valore del campo 
 *            dimScacchira di scacchiera, Int
 * RITORNO: scacchiera, scacchiera aggiornata
 */
void scrivereDimScacchiera(Scacchiera *scacchiera, int valore) {
    scacchiera->dimScacchiera = valore;
}

/*
 * DESCRIZIONE: leggere il valore del campo statoCella di una cella di scacchiera
 * ARGOMENTI: scacchiera, scacchiera da cui leggere, Scacchiera
 *            riga, posizione nelle righe della scacchira della cella da leggere, int
 *            colonna, posizione nelle colonne della scacchira della cella da leggere, int 
 * RITORNO: valoreLetto, valore letto dalla cella, int
 */
int leggereCellaScacchiera(Scacchiera scacchiera, int riga, int colonna) {
    int valoreLetto;
    valoreLetto = leggereStatoCella(scacchiera.celleScacchiera[riga][colonna]); 
    return valoreLetto;
}

/*
 * DESCRIZIONE: scrive il valore del campo statoCella di una cella di scacchiera
 * ARGOMENTI: scacchiera, scacchiera da modificare, Scacchiera
 *            riga, posizione nelle righe della scacchira della cella da modificare, int
 *            colonna, posizione nelle colonne della scacchira della cella da modificare, int 
 *            valore, nuovo valore del campo statoCella della cella, int = [0, 1, 2]
 * RITORNO: scacchiera, scacchiera aggiornata, Scacchiera
 */
void scrivereCellaScacchiera(Scacchiera *scacchiera, int riga, int colonna, int valore) {
  scrivereStatoCella(&scacchiera->celleScacchiera[riga][colonna], valore);
}

//funzioni di accesso al tipo di dato partita
/*
 * DESCRIZIONE: legge il campo impostaziniPartita di partita
 * ARGOMENTI: partita, partita da leggere il campo impostazioniPartita, Partita
 * RITORNO: impostaziniLette, campo impostazioniPartita di partita, Impostazioni
 */
Impostazioni leggereImpPartita(Partita partita) {
  Impostazioni impostazioniLette;

  impostazioniLette = partita.impPartita;
  return impostazioniLette;
}

//???? scrivereImppartita
/*
 * DESCRIZIONE: legge il campo modalitaPartita del campo 
 *              impostazioniPartita di partita
 * ARGOMENTI: partita, partita da cui leggere il valore del campo modalitaPartita, Partita
 * RITORNO: valoreLetto, valore del campo modalitaPartita di partita, int [0, 1, 2]
 */
int leggereModalitaPartita(Partita partita) {
  int valoreLetto;

  valoreLetto = leggereModalitaImpostazioni(leggereImpPartita(partita));
  return valoreLetto;
}

/*
 * DESCRIZIONE: scrive il valore del campo modalitaPartita del campo 
 *              impostazioniPartita di partita
 * ARGOMENTI: partita, partita di cui scrivere il valore del campo modalitaPartita, Partita
 *            valore, nuovo valore del campo modalitaPartita, int [0, 1, 2]
 * RITORNO: partita, partita aggiornata, Partita 
 */
void scrivereModalitaPartita(Partita *partita, int valore) {
  scrivereModalitaImpostazioni(&(partita->impPartita), valore);
}

/*
 * DESCRIZIONE: legge il campo scacchieraPartita di partita
 * ARGOMENTI: partita, partita di cui leggere il campo scacchieraPartita, Partita
 * RITORNO: scacchieraLetta, campo scacchieraPartita di partita, Scacchiera
 */
Scacchiera leggereScacchieraPartita(Partita *partita) {
    Scacchiera scacchieraLetta;

    scacchieraLetta = partita->scacchieraPartita;
    return scacchieraLetta;
}

/*
 * DESCRIZIONE: legge il campo nomePartita di partita 
 * ARGOMENTI: partita, partita di cui leggere il valore del campo nomePartita, Partita
 * RITORNO: nomeLetto, valore del campo nomePartita di Partita, stringa
 */
char* leggereNomePartita(Partita *partita) {
    char* nomeLetto;

    nomeLetto = partita->nomePartita;
    return nomeLetto;
}

/*
 * DESCRIZIONE: scrivere il valore del campo nomePartita di partita 
 * ARGOMENTI: partita, partita di cui modificare il valore del campo nomePartita, Partita
 *            nome, nuovo nome del campo nomePartita di Partita, char []
 * RITORNO: partita, partita aggiornata, Partita
 */
void scrivereNomePartita(Partita *partita, char nome[50]) {
    strcpy(partita->nomePartita, nome);
}

/*
 * DESCRIZIONE: scrive il valore del campo impostazioniPartita di partita
 * ARGOMENTI: partita, partita da aggiornare, Partita
 *            imp, nuove impostazioni di partita, Impostazioni
 * RITORNO: partita, partita aggiornata, Partita
 */
void scrivereImpPartita(Partita *partita, Impostazioni imp) {
  partita->impPartita = imp;
}

/*
 * DESCRIZIONE: scrive il valore del campo dimScacchiera di partita
 * ARGOMENTI: partita, partita di cui modificare i campi dimScacchiera, Partita
 *            valore, nuovo valore del campo dimScacchiera di partita, int
 * RITORNO: partita, partita aggiornata, Partita
 */
void scrivereDimScacchieraPartita(Partita *partita, int valore) {
  partita->impPartita.dimScacchiera = valore;
  partita->scacchieraPartita.dimScacchiera = valore;
}

/*
 * DESCRIZIONE: scrive il valore di un cella della scacchiera di partit
 * ARGOMENTI: partita, partita da aggiornare, Partita
 *            valore, nuovo valore della cella scelta, int [0, 1, 2]
 *            riga, posizione nelle righe della scacchiera di partita della cella da modificare, int
 *            colonna, posizione nelle colonne della scacchiera di partita della cella da modificare, int
 * RITORNO: partita, partita aggiornata, Partita
 */
void scrivereCellaPartita(Partita *partita, int valore, int riga, int colonna) {
  Scacchiera scacchieraPartita;

  //qui utilizziamo scacchieraPartita come appoggio, 
  //perche' abbiamo bisogno di passarlo come puntatore
  scacchieraPartita = leggereScacchieraPartita(partita);
  scrivereCellaScacchiera(&scacchieraPartita, riga, colonna, valore);
}

/*
 * DESCRIZIONE: legge il valore del campo turnoGiocatore di partita
 * ARGOMENTI: partita, partita da cui leggere il valore del campo turnoGiocatore, Partita
 * RITORNO: giocatoreCorrente, valore del campo turnoGiocatore di partita, int [1, 2]
 */
int leggereTurnoGiocatore(Partita *partita) {
  int giocatoreCorrente;

  giocatoreCorrente = partita->turnoGiocatore;
  return giocatoreCorrente;
}

/*
 * DESCRIZIONE: cambia il valore del campo turnoGiocatore di partita
 * ARGOMENTI: partita, partita da aggiornare, Partita
 * RITORNO: partita, partita aggiornata, Partita
 */
void cambiareTurnoGiocatorePartita(Partita *partita) {
  if(partita->turnoGiocatore == NERO) {
    partita->turnoGiocatore = BIANCO;
  } else {
    partita->turnoGiocatore = NERO;
  }
}

/*
 * DESCRIZIONE: scrive il valore del campo turnoGiocatore di partita
 * ARGOMENTI: partita, partita da aggiornare, Partita
 *            turno, nuovo valore del campo turnoGiocatore, int
 * RITORNO: partita, partitaAggiornata, Partita
 */
void scrivereTurnoGiocatorePartita(Partita *partita, int turno) {
  partita->turnoGiocatore = turno;
}

/*
 * DESCRIZIONE: inizializza la scacchiera di partita (imposta tutte le celle = 0)
 * ARGOMENTI: partita, partita di cui inizializzare la scacchiera, Partita 
 *            dim, dimensione della scacchiera di gioco, int
 * RITORNO: partita, partita con il campo scacchieraPartita aggiornato, Partita
 */
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
            scrivereCellaPartita(partita, VUOTO, riga, colonna);
            colonna = colonna + 1;
        }
        riga = riga + 1;
    }
}


//funzioni di accesso tipo di dato impostazioni
/*
 * DESCRIZIONE: legge il valore del campo modalitaPartita di impostazioni
 * ARGOMENTI: imp, impostazioni da cui leggere il valore del campo modalitaPartita, Impostazioni
 * RITORNO: valoreLetto, valore letto dal campo modalitaPartita di impostazioni, int [0, 1, 2] 
 */
int leggereModalitaImpostazioni(Impostazioni imp) {
  int valoreLetto;

  valoreLetto = imp.modalitaPartita;
  return valoreLetto;
}

/*
 * DESCRIZIONE: legge il valore del campo dimScacchiera di impostazioni
 * ARGOMENTI: imp, impostazioni da cui leggere il valore del campo dimScacchiera, Impostazioni
 * RITORNO: valoreLetto, valore letto dal campo dimScacchiera di impostazioni, int [4, 8, 16] 
 */
int leggereDimScacchieraImp(Impostazioni imp) {
  int valoreLetto;

  valoreLetto = imp.dimScacchiera;
  return valoreLetto;
}

/*
 * DESCRIZIONE: scrive il valore del campo modalitaPartita di impostazioni
 * ARGOMENTI: imp, impostazioni di cui modificare il valore del campo modalitaPartita, Impostazioni
 *            valore, nuovo valore del campo modalitaPartita di imopstazioni, int [0,1,2]
 * RITORNO: imp, impostazioni aggiornate, Impostazioni 
 */
void scrivereModalitaImpostazioni(Impostazioni *imp, int valore) {
  imp->modalitaPartita = valore;
}

/*
 * DESCRIZIONE: scrive il valore del campo dimScacchiera di impostazioni
 * ARGOMENTI: imp, impostazioni di cui modificare il valore del campo dimScacchiera, Impostazioni
 *            valore, nuovo valore del campo dimScacchiera di imopstazioni, int [0,1,2]
 * RITORNO: imp, impostazioni aggiornate, Impostazioni 
 */
void scrivereDimScacchieraImp(Impostazioni *imp, int valore) {
  imp->dimScacchiera = valore;
}

/*
 * DESCRIZIONE: inizializza e scrive il valore del campo modalitaPartita e dimScacchiera di impostazioni 
 * ARGOMENTI: modalita, campo modalitaPartita di imp, int [0,1,2]
 *            dimensione, campo dimScacchiera di imp, int [4,8,16]
 * RITORNO: imp, impostazioni inizializzate, Impostazioni
 */
Impostazioni* inizializzareImpostazioni(int modalita, int dimensione) {
    Impostazioni *imp;
    imp = (Impostazioni*)malloc(sizeof(Impostazioni));
    
    imp->modalitaPartita = modalita;
    imp->dimScacchiera = dimensione;
    
    return imp;
}

//funzioni di accesso cartella
/**
 * DESCRIZIONE: Legge la voce successiva in una cartella.
 * ARGOMENTI: cartella, cartella da cui leggere i file, cartella
 * RITORNO: voceLetta, file letto, FILE, char []
 */
struct dirent* leggereProssimaVoce(DIR* cartella) {
    struct dirent* voceLetta;
    voceLetta = readdir(cartella);
    return voceLetta;
}

/**
 * DESCRIZIONE: Ottiene il nome di un file/voce.
 * ARGOMENTI: voce, voce letta dalla cartella, FILE 
 * RITORNO: nome della voce letta dal file, char []
 */
const char* ottenereNomeVoce(struct dirent* voce) {
    const char* nomeVoce;
    nomeVoce = voce->d_name;
    return nomeVoce;
}

// nel codice utilizziamo il tipo di dato file e il tipo di dato cartella con le funzioni
// standard di c
// non utilizziamo quelle nostre perche' problematiche...
// qui commentato c'e comunuque il codice dei tipi di dato + funzioni di accesso
//
//typedef struct {
//    char nomeFile[100];        
//   unsigned int posizione;    
//   char caratteri[MAX_CARATTERI];  
//} File;

//const char* leggereNomeFile(File file) {
//   return file.nomeFile;
//}

//unsigned int posLeggereFile(File file) {
//   return file.posizione;
//}

//void incPosizioneFile(File* file) {
//   file->posizione = posizione + 1;
//}

//char leggereCarattereFile(File* file) {
//    char valoreLetto = file->caratteri[file->posizione];
//    incPosizioneFile(file);
//    return valoreLetto;
//}

//void scrivereNomeFile(File* file, const char* nuovoNome) {
//    strncpy(file->nomeFile, nuovoNome, sizeof(file->nomeFile) - 1);
//    file->nomeFile[sizeof(file->nomeFile) - 1] = '\0'; 
//}

//void scrivereCarattereFile(File* file, char nuovoValore, unsigned int pos) {
//    if (pos < MAX_CARATTERI) {
//        file->caratteri[pos] = nuovoValore;
//        incPosizioneFile(file);
//    }
//}
//
// typedef struct {
//   File voci[MAX_VOCI]; 
//   unsigned int posizione; 
// Cartella;}
//
// File leggereProssimaVoce(Cartella* cartella) {
// File voceLetta = cartella->voci[cartella->posizione];
//    incPosizioneCartella(cartella);
//    return voceLetta;
//}
//
//char* ottenereNomeFile(File voce) {
//   return voce.nomeFile;
//}
//
//void incPosizioneCartella(Cartella* cartella) {
//   cartella->posizione += 1;
//}

//void scrivereVoce(Cartella* cartella, File voce) {
//   cartella->voci[cartella->posizione] = voce;
//   incPosizioneCartella(cartella);
//}
