#ifndef FUNZIONIUTILITA_H
#define FUNZIONIUTILITA_H

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

void stampareCentrato(const char *testo); /* centra una stringa quando viene stampata sul terminale. */
void stampareASinistra(const char *testo) ; /* Centra una stringa quando stampata sul terminale. */
void spostareCursore(int x, int y);
 
void reimpostareZonaInput(int posRiga, int posColonna);
void pulireBuffer();
void mostrareMessaggioErrore(const char *testo, int posRiga, int posColonna);
void tornareHomepage(int *input, int posRiga, int posColonna);
void pulireSchermo();
int lunghezza(const char stringa[]);
void concatenareDueStringhe(const char stringa1[], const char stringa2[], char stringaFinale[]);
int confrontarePrefisso(const char *stringa1, const char *prefisso);
int modulo(int dividendo, int divisore);
void copiareDueStringhe( char* stringa1, const char* stringa2);

#endif

