/*
AUTORI: Davide Fornelli
        Antoniciello Giuliano

DATA INIZIO: 04/05/2025

NOME FILE: Carica/Salva Othello

Scopo di ogni funzione presente:
- raccogliereNomiPartiteSalvate: legge dalla cartella database i file che rappresentano le partite salvate dall'utente. Restituisce il numero totale di partite trovate.
- liberareNomiPartite: libera la memoria utilizzata per contenere i nomi delle partite.
- estrapolareNomeDaFile: estrae il nome "umano" da un file partita.
- caricarePartita: carica una partita Othello da file.
- salvarePartita: salva una partita Othello su file.
- stampareTitoloCaricaPartita: stampa il titolo artistico per il caricamento partite.
*/

#include "../include/funzioniUtilita.h"
#include "../include/homepage.h"
#include "../include/partita.h"
#include "../include/costanti.h"
#include "../include/tipiDiDato.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITE 13
#define RIGA 11
#define COLONNA 40
#define TITOLO_RIGA 9
#define TITOLO_COLONNA 0
#define OPZIONE_START_RIGA 12
#define OPZIONE_COLONNA 28
#define PROMPT_RIGA 19
#define PROMPT_COLONNA 28
#define INPUT_RIGA 20
#define INPUT_COLONNA 35
#define ERR_MSG_RIGA 22
#define ERR_MSG_COLONNA 31
#define ARANCIONE "\033[38;5;208m"
#define RESET "\033[0m"

/**
 * DESCRIZIONE: Legge la prossima voce in una cartella.
 * ARGOMENTI: cartella: puntatore a DIR
 * RITORNO: puntatore a struct dirent
 */
struct dirent* leggereProssimaVoce(DIR* cartella) {
  struct dirent* voce;
  voce = readdir(cartella);
  return voce;
}

/**
 * DESCRIZIONE: Ottiene il nome di un file/voce.
 * ARGOMENTI: voce: puntatore a struct dirent
 * RITORNO: nome del file
 */
const char* ottenereNomeFile(struct dirent* voce) {
  const char* nome;
  nome = voce->d_name;
  return nome;
}

/**
 * DESCRIZIONE: Raccoglie i nomi delle partite salvate (file che iniziano con "partita_").
 * ARGOMENTI: nomiPartite: array di stringhe da riempire
 * RITORNO: nessuno
 */
void raccogliereNomiPartiteSalvate(char *nomiPartite[]) {
  DIR *cartella;
  struct dirent *voce;
  int conteggio;
  const char *nomeFile;

  cartella = opendir("database");
  conteggio = 0;
  if (!cartella) {
    return;
  }
  voce = leggereProssimaVoce(cartella);
  while (voce != NULL && conteggio < MAX_PARTITE) {
    nomeFile = ottenereNomeFile(voce);
    if (confrontarePrefisso(nomeFile, "partita_") == VERO) {
      nomiPartite[conteggio] = malloc(lunghezza(nomeFile) + 1);
      strcpy(nomiPartite[conteggio], nomeFile);
      conteggio = conteggio + 1;
    }
    voce = leggereProssimaVoce(cartella);
  }
  closedir(cartella);
}

/**
 * DESCRIZIONE: Libera la memoria dei nomi delle partite.
 * ARGOMENTI: nomiPartite: array di stringhe, numero: quanti elementi liberare
 * RITORNO: nessuno
 */
void liberareNomiPartite(char *nomiPartite[], int numero) {
  int indice;
  indice = 0;
  while (indice < numero) {
    free(nomiPartite[indice]);
    indice = indice + 1;
  }
}

/**
 * DESCRIZIONE: Conta il numero di partite salvate.
 * ARGOMENTI: nessuno
 * RITORNO: numero di partite trovate
 */
int contareNumeroPartiteSalvate() {
  DIR *cartella;
  struct dirent *voce;
  int conteggio;
  const char *nomeFile;

  cartella = opendir("database");
  conteggio = 0;
  if (!cartella) {
    return 0;
  }
  voce = leggereProssimaVoce(cartella);
  while (voce != NULL && conteggio < MAX_PARTITE) {
    nomeFile = ottenereNomeFile(voce);
    if (confrontarePrefisso(nomeFile, "partita_") == VERO) {
      conteggio = conteggio + 1;
    }
    voce = leggereProssimaVoce(cartella);
  }
  closedir(cartella);
  return conteggio;
}

/********************************************************
* FUNZIONE: stampareTitoloCaricaPartita                 *
*                                                       *
* DESCRIZIONE: Mostra a schermo un titolo artistico     *
*              colorato per la schermata di caricamento *
*              delle partite salvate.                   *
*                                                       *
* ARGOMENTI: Nessuno                                    *
*                                                       *
* RITORNO: Terminale aggiornato                         *
********************************************************/
void stampareTitoloCaricaPartita() {
  printf(ARANCIONE);
  stampareCentrato("     _____ _____ _____ _____ _____ _____     ");
  stampareCentrato("    |     |  _  | __  |     |     |  _  |    ");
  stampareCentrato("    |   --|     |    -|-   -|   --|     |    ");
  stampareCentrato("    |_____|__|__|__|__|_____|_____|__|__|    ");
  stampareCentrato("   _____ _____ _____ _____ _____ _____ _____ ");
  stampareCentrato("  |  _  |  _  | __  |_   _|     |_   _|  _  |");
  stampareCentrato("  |   __|     |    -| | | |-   -| | | |     |");
  stampareCentrato("  |__|  |__|__|__|__| |_| |_____| |_| |__|__|");
  stampareCentrato("                                             ");
  printf(RESET);
}

/**
 * DESCRIZIONE: Estrae il nome "umano" da un file partita (toglie prefisso e suffisso).
 * ARGOMENTI: nomeFile: nome file, nome: buffer di output
 * RITORNO: nessuno
 */
void estrapolareNomeDaFile(const char *nomeFile, char *nome) {
  int cursoreNome;
  int cursoreNomeFile;
  cursoreNome = 0;
  cursoreNomeFile = 8;
  while(nomeFile[cursoreNomeFile] != '.' && nomeFile[cursoreNomeFile] != '\0') {
    nome[cursoreNome] = nomeFile[cursoreNomeFile];
    cursoreNome = cursoreNome + 1;
    cursoreNomeFile = cursoreNomeFile + 1;
  }
  nome[cursoreNome] = '\0';
}

/**
 * DESCRIZIONE: Salva una partita Othello completa su file: 
 *              dimensione, modalità, turno corrente, poi matrice scacchiera.
 * ARGOMENTI: partita: puntatore a Partita, turnoCorrente: colore giocatore corrente
 * RITORNO: nessuno
 */
void salvarePartita(Partita *partita) {
  FILE *file;
  char percorso[100];
  int dimensione;
  int riga;
  int colonna;
  int valore;
  int turnoCorrente;

  dimensione = leggereDimScacchieraImp(leggereImpPartita(*partita));
  turnoCorrente = leggereTurnoGiocatore(partita);
  snprintf(percorso, sizeof(percorso), "database/partita_%s.txt", leggereNomePartita(partita));
  file = fopen(percorso, "w");

  // Salva le informazioni della partita
  fprintf(file, "%d\n", dimensione);           // Prima riga: dimensione
  fprintf(file, "%d\n", leggereModalitaImpostazioni(leggereImpPartita(*partita)));    // Seconda riga: modalità (1=vs umano, 2=vs bot)
  fprintf(file, "%d\n", turnoCorrente);        // Terza riga: turno corrente (1=NERO, 2=BIANCO)

  // Salva la scacchiera
  riga = 0;
  while (riga < dimensione) {
    colonna = 0;
    while (colonna < dimensione) {
      valore = leggereCellaScacchiera(leggereScacchieraPartita(partita), riga, colonna);
      fprintf(file, "%d ", valore);
      colonna = colonna + 1;
    }
    fprintf(file, "\n");
    riga = riga + 1;
  }
  fclose(file);
}

/**
 * DESCRIZIONE: Carica una partita Othello completa da file: 
 *              dimensione, modalità, turno corrente, poi matrice scacchiera.
 * ARGOMENTI: partita: puntatore a Partita, percorso: path del file, 
 *            turnoCorrente: puntatore per salvare il turno caricato
 * RITORNO: nessuno
 */
void caricarePartita(Partita *partita, const char *percorso) {
  FILE *file;
  int dimensione;
  int modalita;
  int riga;
  int colonna;
  int valore;
  int turnoCorrente;
  Impostazioni *impPartita;

  file = fopen(percorso, "r");

  // Carica le informazioni della partita
  fscanf(file, "%d", &dimensione);        // Prima riga: dimensione
  fscanf(file, "%d", &modalita);          // Seconda riga: modalità
  fscanf(file, "%d", &turnoCorrente);      // Terza riga: turno corrente

  // Inizializza la partita
  impPartita = inizializzareImpostazioni(modalita, dimensione);
  scrivereTurnoGiocatore(partita, turnoCorrente);
  partita->impPartita = *impPartita;
  printf("modalita: %d", partita->impPartita.modalitaPartita);
  printf("dimensione: %d", partita->impPartita.dimScacchiera);
  inizializzareScacchieraPartita(partita, dimensione);

  // Carica la scacchiera
  riga = 0;
  while (riga < dimensione) {
    colonna = 0;
    while (colonna < dimensione) {
      fscanf(file, "%d", &valore);
      scrivereCellaPartita(partita, valore, riga, colonna);
      colonna = colonna + 1;
    }
    riga = riga + 1;
  }
  fclose(file);
}

void avviareMenuCaricaPartita() {
  char *nomiPartite[100];
  int numeroPartite;
  int input;
  int tornaHP;
  int cursorePartite;
  char nomeVisualizzato[128];
  char percorso[256];
  Partita partita;
  char nome[128];
  int turnoCaricato;

  pulireSchermo();
  stampareTitoloCaricaPartita();
  raccogliereNomiPartiteSalvate(nomiPartite);
  numeroPartite = contareNumeroPartiteSalvate();
  if (numeroPartite == 0) {
    stampareCentrato("Nessuna partita salvata.");
    liberareNomiPartite(nomiPartite, numeroPartite);
    tornareHomepage(&tornaHP, RIGA_ERRORE, COLONNA - 10);
  }
  printf("  [0] Torna al menu principale\n");
  cursorePartite = 0;
  while (cursorePartite < numeroPartite) {
    estrapolareNomeDaFile(nomiPartite[cursorePartite], nomeVisualizzato);
    printf("  [%d] %s\n", cursorePartite + 1, nomeVisualizzato);
    cursorePartite = cursorePartite + 1;
  }

  printf("\n Scegli una partita: ");
  scanf("%d", &input);
  pulireBuffer();

  if (input == 0) {
    liberareNomiPartite(nomiPartite, numeroPartite);
    avviareMenuPrincipale(); 
    return;
  } else if (input > 0 && input <= numeroPartite) {
    snprintf(percorso, sizeof(percorso), "database/%s", nomiPartite[input-1]);
    caricarePartita(&partita, percorso);
    estrapolareNomeDaFile(nomiPartite[input-1], nome);
    scrivereNomePartita(&partita, nome);
    liberareNomiPartite(nomiPartite, numeroPartite);

    if (leggereModalitaImpostazioni(leggereImpPartita(partita)) == 1) {
      avviarePartitaContinuata(&partita);
    } else if (leggereModalitaImpostazioni(leggereImpPartita(partita)) == 2) {
      int coloreGiocatore = leggereTurnoGiocatore(&partita); 
      avviarePartitaContinuataBot(&partita, coloreGiocatore);
    } else if (leggereModalitaImpostazioni(leggereImpPartita(partita)) == 3) {
      int coloreGiocatore = leggereTurnoGiocatore(&partita); 
      avviarePartitaContinuataBot(&partita, coloreGiocatore);
    }
  } else {
    liberareNomiPartite(nomiPartite, numeroPartite);
    avviareMenuCaricaPartita(); 
  }
}
