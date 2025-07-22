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
*/

#include "../include/funzioniUtilita.h"
#include "../include/homepage.h"
#include "../include/partita.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITE 13
#define VERO 1

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
            nomiPartite[conteggio] = malloc(strlen(nomeFile) + 1);
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
 * DESCRIZIONE: Carica una partita Othello da file: prima riga dimensione, poi matrice scacchiera.
 * ARGOMENTI: partita: puntatore a Partita, percorso: path del file
 * RITORNO: nessuno
 */
void caricarePartita(Partita *partita, const char *percorso) {
    FILE *file;
    int dimensione;
    int riga;
    int colonna;
    int valore;

    file = fopen(percorso, "r");
    if (!file) {
        return;
    }
    fscanf(file, "%d", &dimensione);
    scrivereDimScacchieraPartita(partita, dimensione);
    inizializzareScacchieraPartita(partita, dimensione);
    riga = 0;
    while (riga < dimensione) {
        colonna = 0;
        while (colonna < dimensione) {
            fscanf(file, "%d", &valore);
            scrivereStatoScacchieraPartita(partita, valore, riga, colonna);
            colonna = colonna + 1;
        }
        riga = riga + 1;
    }
    fclose(file);
}

/**
 * DESCRIZIONE: Salva una partita Othello su file: prima riga dimensione, poi matrice scacchiera.
 * ARGOMENTI: partita: puntatore a Partita
 * RITORNO: nessuno
 */
void salvarePartita(Partita *partita) {
    FILE *file;
    char percorso[100];
    int dimensione;
    int riga;
    int colonna;
    int valore;

    dimensione = leggereDimScacchiera(leggereScacchieraPartita(partita));
    snprintf(percorso, sizeof(percorso), "database/partita_%s.txt", leggereNomePartita(partita));
    file = fopen(percorso, "w");
    if (!file) {
        return;
    }
    fprintf(file, "%d\n", dimensione);
    riga = 0;
    while (riga < dimensione) {
        colonna = 0;
        while (colonna < dimensione) {
            valore = leggereStatoScacchiera(leggereScacchieraPartita(partita), riga, colonna);
            fprintf(file, "%d ", valore);
            colonna = colonna + 1;
        }
        fprintf(file, "\n");
        riga = riga + 1;
    }
    fclose(file);
}

/**
 * DESCRIZIONE: Menu per caricare una partita Othello salvata.
 * ARGOMENTI: nessuno
 * RITORNO: nessuno
 */
void avviareMenuCaricaPartita() {
    char *nomiPartite[100];
    int numeroPartite;
    int input;
    int cursorePartite;
    char nomeVisualizzato[128];
    char percorso[256];
    Partita partita;
    char nome[128];

    pulireSchermo();
    printf("\n==== CARICA PARTITA OTHELLO ====");
    raccogliereNomiPartiteSalvate(nomiPartite);
    numeroPartite = contareNumeroPartiteSalvate();
    if (numeroPartite == 0) {
        printf("\nNessuna partita salvata.\n");
        liberareNomiPartite(nomiPartite, numeroPartite);
        printf("\nPremi invio per tornare al menu principale...");
        getchar();
        avviareMenuPrincipale();
        return;
    }
    printf("  [0] Torna al menu principale\n");
    cursorePartite = 0;
    while (cursorePartite < numeroPartite) {
        estrapolareNomeDaFile(nomiPartite[cursorePartite], nomeVisualizzato);
        printf("  [%d] %s\n", cursorePartite + 1, nomeVisualizzato);
        cursorePartite = cursorePartite + 1;
    }
    printf("\nScegli una partita: ");
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
        avviarePartitaContinuata(&partita);
    } else {
        liberareNomiPartite(nomiPartite, numeroPartite);
        printf("\nScelta non valida.\n");
        avviareMenuCaricaPartita();
    }
}




/*******************************************************
* FUNZIONE: caricareValoriGriglia                          *
*                                                        *
* DESCRIZIONE: Legge da file i valori della griglia      *
*              della partita Sudoku e li scrive nella    *
*              struttura della partita riga per riga.    *
*                                                        *
* ARGOMENTI:                                             *
* file: puntatore al file aperto in lettura              *
* partita: puntatore alla struttura della partita        *
* dimensione: dimensione della griglia                   *
*                                                        *
* RITORNO:                                               *
* partita: partita aggiornata
*********************************************************/
// (Rimuovo/ignoro la vecchia caricareValoriGriglia e ogni riferimento a difficoltà o Sudoku)

