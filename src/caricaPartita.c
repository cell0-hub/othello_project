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

// Utility: legge la prossima voce in una cartella
struct dirent* leggereProssimaVoce(DIR* cartella) {
    return readdir(cartella);
}

// Utility: ottiene il nome di un file/voce
const char* ottenereNomeFile(struct dirent* voce) {
    return voce->d_name;
}

// Raccoglie i nomi delle partite salvate (file che iniziano con "partita_")
void raccogliereNomiPartiteSalvate(char *nomiPartite[]) {
    DIR *cartella = opendir("database");
    struct dirent *voce;
    int conteggio = 0;
    if (!cartella) return;
    while ((voce = leggereProssimaVoce(cartella)) != NULL && conteggio < MAX_PARTITE) {
        const char *nomeFile = ottenereNomeFile(voce);
        if (confrontarePrefisso(nomeFile, "partita_") == VERO) {
            nomiPartite[conteggio] = malloc(strlen(nomeFile) + 1);
            strcpy(nomiPartite[conteggio], nomeFile);
            conteggio++;
        }
    }
    closedir(cartella);
}

// Libera la memoria dei nomi delle partite
void liberareNomiPartite(char *nomiPartite[], int numero) {
    for (int i = 0; i < numero; i++) {
        free(nomiPartite[i]);
    }
}

// Conta il numero di partite salvate
int contareNumeroPartiteSalvate() {
    DIR *cartella = opendir("database");
    struct dirent *voce;
    int conteggio = 0;
    if (!cartella) return 0;
    while ((voce = leggereProssimaVoce(cartella)) != NULL && conteggio < MAX_PARTITE) {
        const char *nomeFile = ottenereNomeFile(voce);
        if (confrontarePrefisso(nomeFile, "partita_") == VERO) {
            conteggio++;
        }
    }
    closedir(cartella);
    return conteggio;
}

// Estrae il nome "umano" da un file partita (toglie prefisso e suffisso)
void estrapolareNomeDaFile(const char *nomeFile, char *nome) {
    int cursNome = 0, cursNomeFile = 8;
    while(nomeFile[cursNomeFile] != '.' && nomeFile[cursNomeFile] != '\0') {
        nome[cursNome++] = nomeFile[cursNomeFile++];
    }
    nome[cursNome] = '\0';
}

// === SOLO OTHELLO ===
// Carica una partita Othello da file: prima riga dimensione, poi matrice scacchiera
void caricarePartita(Partita *partita, const char *percorso) {
    FILE *file;
    int dimensione;
    file = fopen(percorso, "r");
    if (!file) return;
    fscanf(file, "%d", &dimensione);
    scrivereDimScacchieraPartita(partita, dimensione);
    inizializzareScacchieraPartita(partita, dimensione);
    for (int r = 0; r < dimensione; r++) {
        for (int c = 0; c < dimensione; c++) {
            int val;
            fscanf(file, "%d", &val);
            scrivereStatoScacchieraPartita(partita, val, r, c);
        }
    }
    fclose(file);
}

// Salva una partita Othello su file: prima riga dimensione, poi matrice scacchiera
void salvarePartita(Partita *partita) {
    FILE *file;
    char percorso[100];
    int dimensione = leggereDimScacchiera(leggereScacchieraPartita(partita));
    snprintf(percorso, sizeof(percorso), "database/partita_%s.txt", leggereNomePartita(partita));
    file = fopen(percorso, "w");
    if (!file) return;
    fprintf(file, "%d\n", dimensione);
    for (int r = 0; r < dimensione; r++) {
        for (int c = 0; c < dimensione; c++) {
            int val = leggereStatoScacchiera(leggereScacchieraPartita(partita), r, c);
            fprintf(file, "%d ", val);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Menu per caricare una partita Othello salvata
void avviareMenuCaricaPartita() {
    char *nomiPartite[100];
    int numeroPartite;
    int input;
    int cursPartite;
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
    for (cursPartite = 0; cursPartite < numeroPartite; cursPartite++) {
        estrapolareNomeDaFile(nomiPartite[cursPartite], nomeVisualizzato);
        printf("  [%d] %s\n", cursPartite + 1, nomeVisualizzato);
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

