#ifndef CARICAPARTITA_H 
#define CARICAPARTITA_H

#include "../include/funzioniUtilita.h"
#include "../include/tipiDiDato.h"


#define MAX_NOME_FILE 50

void avviareMenuCaricaPartita();
void stampareTitoloCaricaPartita();

void salvarePartita(Partita *partita, int turnoCorrente);
void salvareValoriGriglia(FILE *file, Partita *partita);
void caricarePartita(Partita *partita, const char *percorso);
void caricareValoriGriglia(FILE *file, Partita *partita);
void estrapolareNomeDaFile(const char *nomeFile, char *nome);

#endif


