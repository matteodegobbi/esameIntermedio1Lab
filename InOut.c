/** Autore: Antonio Giunta */

#include <stdio.h>
#include <stdbool.h>

/* Sospende l'esecuzione finche' l'utente non preme un tasto. */
void tasto(void) {
    printf("\nPremere un tasto qualsiasi per uscire.\n");
    fflush(stdin);
    getchar();
} /* tasto */

/* Legge un int da tastiera.
IP etiche Etichetta per l'input.
IK+OR Int letto.
*/
int scanInt(const char etiche[]) {
    int i;
    printf("%s", etiche);
    scanf("%d", &i);
    return i;
} /* scanInt */

/** Legge un intero entro un dato intervallo.
IP etiche Etichetta per l'input.
IP vaMini Valore minimo ammissibile.
IP vaMassi Valore massimo ammissibile.
IK+OR Int letto.
*/
int scanIntAmmissibile(const char etiche[], int vaMini, int vaMassi) {
    int v;
    do
        v = scanInt(etiche);
    while (v < vaMini || v > vaMassi);
    return v;
} /* leggiIntAmmissibile */

/* Legge due interi da tastiera.
IP etiche1 Etichetta per l'input 1.
IP etiche2 Etichetta per l'input 2.
IK+OP i1 Int 1 da leggere.
IK+OP i2 Int 2 da leggere.
*/
void scan2Int(const char etiche1[], const char etiche2[], int* i1, int* i2) {
    *i1 = scanInt(etiche1);
    *i2 = scanInt(etiche2);
} /* scan2Int */

/* Legge un double da tastiera.
IP etiche Etichetta per l'input.
IK+OR Double da leggere.
*/
double scanDouble(const char etiche[]) {
    double d;
    printf("%s", etiche);
    scanf("%lf", &d);
    return d;
} /* scanDouble */

/* Legge due double da tastiera.
IP etiche1 Etichetta per l'input 1.
IP etiche2 Etichetta per l'input 1.
IK+OP d1 Double 1 da leggere.
IK+OP d2 Double 2 da leggere.
*/
void scan2Double(const char etiche1[], const char etiche2[], double* d1, double* d2) {
    *d1 = scanDouble(etiche1);
    *d2 = scanDouble(etiche2);
} /* scan2Double */

/* Legge un booleano da tastiera.
IP etiche Etichetta per l'input.
IK+OR Bool da leggere.
*/
bool scanBool(const char etiche[]) {
    printf("[Usa: 0 per il valore false; 1 per true] ");
    return scanInt(etiche);
} /* scanBool */

/* Legge un carattere da tastiera.
IP etiche Etichetta per l'input.
IK+OR Char  da leggere.
*/
char scanChar(const char etiche[]) {
    char c;
    printf("%s", etiche);
    fflush(stdin);
    scanf("%c", &c);
    return c;
} /* scanChar */

/* Legge una stringa da tastiera.
IP etiche Etichetta per l'input.
IK+OP Stringa da leggere.
*/
void scanStringa(const char etiche[], char s[]) {
    printf("%s", etiche);
    scanf("%s", s);
} /* scanStringa */

/* Legge due stringe da tastiera.
IP etiche1 Etichetta per l'input 1.
IP etiche2 Etichetta per l'input 1.
IK+OP s1 Stringa da leggere.
IK+OP s2 Stringa da leggere.
*/
void scan2Stringhe(const char etiche1[], const char etiche2[], char s1[], char s2[]) {
    scanStringa(etiche1, s1);
    scanStringa(etiche2, s2);
} /* scan2Stringhe */

/* Stampa un booleano su video.
IP etiche Etichetta per l'output.
IP b Booleano da stampare.
OV Stampa $b su video.
*/
void printBool(const char etiche[], bool b) {
    printf("%s", etiche);
    if (b)
        printf("true");
    else
        printf("false");
    printf("\n");
} /* printBool */
