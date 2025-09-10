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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// costanti utili per la stampa
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

/**
 * DESCRIZIONE: Raccoglie i nomi delle partite salvate (file che iniziano con "partita_").
 * ARGOMENTI: char* [] nomiPartite: array di stringhe da riempire
 * RITORNO: char* [] nomiPartite: array di stringhe riempito con i nomi dei file.
 */
void raccogliereNomiPartiteSalvate(char *nomiPartite[]) {
    DIR *cartella;
    struct dirent *voce;
    int conteggio;
    const char *nomeFile;

    cartella = opendir(DATABASE);
    conteggio = 0;
    voce = leggereProssimaVoce(cartella);
    while (voce != NULL && conteggio < MAX_PARTITE) {
        nomeFile = ottenereNomeVoce(voce);
        if (confrontarePrefisso(nomeFile, "partita_") == VERO) {
            nomiPartite[conteggio] = malloc(lunghezza(nomeFile) + 1);
            copiareStringa(nomiPartite[conteggio], nomeFile);
            conteggio = conteggio + 1;
        }
        voce = leggereProssimaVoce(cartella);
    }
    closedir(cartella);
}


/**
 * DESCRIZIONE: Libera la memoria dei nomi delle partite.
 * ARGOMENTI: char*[] nomiPartite: array di stringhe, numero: quanti elementi liberare
 *            int numero: numero di partite salvate nell' array
 * RITORNO: memoria liberata dall' array
 */
void liberareNomiPartite(char *nomiPartite[], int nPartiteSalvate) {
    //
    // la funzione non e' presente nello pseudocodice, 
    // perche' l' allocazione della memoria
    // non fa parte dei ambiti dello pseudocodice
    //
    int indice;
    indice = 0;
    while (indice < nPartiteSalvate) {
        free(nomiPartite[indice]);
        indice = indice + 1;
    }
}

/**
 * DESCRIZIONE: Conta il numero di partite salvate nella cartella database.
 * ARGOMENTI: nessuno
 * RITORNO: int conteggio: numero di partite trovate
 */
int contareNumeroPartiteSalvate() {
    DIR *cartella;
    struct dirent *voce;
    int conteggio;
    const char *nomeFile;

    cartella = opendir(DATABASE);
    conteggio = 0;

    voce = leggereProssimaVoce(cartella);
    while (voce != NULL && conteggio < MAX_PARTITE) {
        nomeFile = ottenereNomeVoce(voce);
        if (confrontarePrefisso(nomeFile, "partita_") == VERO) {
            conteggio = conteggio + 1;
        }
        voce = leggereProssimaVoce(cartella);
    }
    closedir(cartella);
    return conteggio;
}

/*
* DESCRIZIONE: Mostra a schermo il titolo      
*              della schermata di caricamento 
*              delle partite salvate.                   
* ARGOMENTI: Nessuno                                    
* RITORNO: Terminale aggiornato                         
*/
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
 * DESCRIZIONE: Estrae il nome da un file partita (toglie prefisso e suffisso).
 * ARGOMENTI: nomeFile char: nome del file (con partita_ e .txt)
 *            char *nome: buffer di output
 * RITORNO: char *nome: nome estrapolato (senza prefisso e suffisso)
 */
void estrapolareNomeDaFile(const char *nomeFile, char *nome) {
    int cursNome;
    int cursNomeFile;
    cursNome = 0;
    cursNomeFile = lunghezza(PREFISSO_PARTITA);
    while(nomeFile[cursNomeFile] != CARATTERE_INIZIO_ESTENSIONE && nomeFile[cursNomeFile] != '\0') {
        nome[cursNome] = nomeFile[cursNomeFile];
        cursNome = cursNome + 1;
        cursNomeFile = cursNomeFile + 1;
    }
    nome[cursNome] = CARATTERE_FINE_STRINGA;
}

/**
 * DESCRIZIONE: Salva una partita Othello completa su file: 
 *              dimensione, modalità, turno corrente, poi scacchiera.
 * ARGOMENTI: Partita *partita: partita di gioco
 * RITORNO: file aggiornato con i valori della griglia di partita, FILE 
 */
void salvarePartita(Partita *partita) {
    FILE *file;
    char percorso[100];
    int dimensione;
    int riga;
    int colonna;
    int casella;
    int turnoCorrente;

    dimensione = leggereDimScacchieraImp(leggereImpPartita(*partita));
    turnoCorrente = leggereTurnoGiocatore(partita);
    snprintf(percorso, sizeof(percorso), "%s/partita_%s.txt", DATABASE, leggereNomePartita(partita));
    file = fopen(percorso, "w");

    // Salva le informazioni della partita
    if(dimensione == 16) {
        fprintf(file, "G\n");
    } else {
        fprintf(file, "%d\n", dimensione);
    }
    fprintf(file, "%d\n", leggereModalitaImpostazioni(leggereImpPartita(*partita)));
    fprintf(file, "%d\n", turnoCorrente);

    // Salva la scacchiera
    riga = 0;
    while (riga < dimensione) {
        colonna = 0;
        while (colonna < dimensione) {
            casella = leggereCellaScacchiera(leggereScacchieraPartita(partita), riga, colonna);
            fprintf(file, "%d ", casella);
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
 * ARGOMENTI: Partita partita: partita da caricare 
 *            char* percorso: path del file 
 * RITORNO: Partita partita: partita caricata dal file, 
 */
void caricarePartita(Partita *partita, const char *percorso) {
    FILE *file;
    int dimensione;
    int modalita;
    int riga;
    int colonna;
    int valore;
    int turnoCorrente;
    // la variabile c non e' presente nello pseudocodice,
    // perche' superflua.
    char c;
    Impostazioni *impPartita;

    file = fopen(percorso, "r");

    if (fscanf(file, " %c", &c) == 1) {
        if (c == 'G') {
            dimensione = 16;
        } else {
            ungetc(c, file); 
            fscanf(file, "%d", &dimensione);
        }
    } 
    fscanf(file, "%d", &modalita);          
    fscanf(file, "%d", &turnoCorrente);    

    // Inizializza la partita
    impPartita = inizializzareImpostazioni(modalita, dimensione);
    scrivereImpPartita(partita, *impPartita);
    //questa funzione non la includiamo nello pseudo perche
    //la gestione della memoria non fa parte dei suoi ambiti;
    free(impPartita);
    scrivereTurnoGiocatorePartita(partita, turnoCorrente);
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

/**
 * DESCRIZIONE: mostra a schermo un menu' interattivo
 *              che permette al giocatore di scegliere quale partita 
 *              caricare
 * ARGOMENTI: nessuno
 * RITORNO: menu interattivo stampato a schermo
 * */

void avviareMenuCaricaPartita() {
    char *nomiPartite[100];
    int numeroPartite;
    int input;
    int cursPartite;
    char nomeVisualizzato[128];
    char percorso[256];
    Partita partita;
    char nome[128];
    int coloreGiocatore;

    pulireSchermo();
    stampareTitoloCaricaPartita();
    raccogliereNomiPartiteSalvate(nomiPartite);
    numeroPartite = contareNumeroPartiteSalvate();
    if (numeroPartite == 0) {
        stampareCentrato("Nessuna partita salvata.");
        liberareNomiPartite(nomiPartite, numeroPartite);
        tornareHomepage(RIGA_ERRORE, COLONNA - 10);
    }
    printf("  [0] Torna al menu principale\n");
    cursPartite = 0;
    while (cursPartite < numeroPartite) {
        estrapolareNomeDaFile(nomiPartite[cursPartite], nomeVisualizzato);
        printf("  [%d] %s\n", cursPartite + 1, nomeVisualizzato);
        cursPartite = cursPartite + 1;
    }

    printf("\n Scegli una partita: ");
    scanf("%d", &input);
    pulireBuffer();

    if (input == 0) {
        liberareNomiPartite(nomiPartite, numeroPartite);
        cursPartite = numeroPartite; //terminiamo il ciclo...
        avviareMenuPrincipale(); 
    } else if (input > 0 && input <= numeroPartite) {
        snprintf(percorso, sizeof(percorso), "%s/%s", DATABASE, nomiPartite[input-1]);
        caricarePartita(&partita, percorso);
        estrapolareNomeDaFile(nomiPartite[input-1], nome);
        scrivereNomePartita(&partita, nome);
        liberareNomiPartite(nomiPartite, numeroPartite);

        if (leggereModalitaImpostazioni(leggereImpPartita(partita)) == VS_AMICO) {
            avviarePartita(NULL, NULL, &partita, 0, 0);
            liberareNomiPartite(nomiPartite, numeroPartite);
        } else if (leggereModalitaImpostazioni(leggereImpPartita(partita)) == VS_BOT_NERO) {
            coloreGiocatore = leggereTurnoGiocatore(&partita); 
            avviarePartita(NULL, NULL, &partita, 1, coloreGiocatore);
            liberareNomiPartite(nomiPartite, numeroPartite);
        } else if (leggereModalitaImpostazioni(leggereImpPartita(partita)) == VS_BOT_BIANCO) {
            coloreGiocatore = leggereTurnoGiocatore(&partita); 
            avviarePartita(NULL, NULL, &partita, 1, coloreGiocatore);
            liberareNomiPartite(nomiPartite, numeroPartite);
        }
    } else {
        liberareNomiPartite(nomiPartite, numeroPartite);
        avviareMenuCaricaPartita(); 
    }
}
