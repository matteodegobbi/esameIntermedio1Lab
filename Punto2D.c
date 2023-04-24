/*De Gobbi Matteo*/
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "InOut.h"
#include "assert.h"

#ifndef PUNTO2D
#define PUNTO2D
#include "Punto2D.h"
#endif

#ifndef BSP
#define BSP
#include "BSP.h"
#endif

/* Stampa un Punto2D su video.
IP etiche Etichetta per l'output da stampare su video.
IP+OV p Punto2D da stampare.
*/
void printPunto2D(const char etiche[], const Punto2D *p) {
    printf("%s", etiche);
    printf("(%f, %f)\n", p->x, p->y);
} /* printPunto2D */

/* Stampa un array di Punto2D su video.
IP etiche Etichetta per l'output da stampare su video.
IP a Array da stampare.
IP n Grandezza di $a.
OV Stampa $a su video.
*/
void printArrayPunto2D(const char etiche[], const Punto2D a[], int n) {
    int i;
    printf("%s", etiche);
    for (i = 0; i < n; i++) {
        printf("a[%d]: ", i);
        printPunto2D("", &a[i]);
    } /* for */
} /* printArrayPunto2D */

/* Legge un Punto2D da tastiera.
IP etiche Etichetta per l'input da inserire mediante tastiera.
IK+OP p Punto2D letto da tastiera.
*/
void scanPunto2D(const char etiche[], Punto2D *p) {
    printf("%s", etiche);
    p->x = scanDouble("coordinata x: ");
    p->y = scanDouble("coordinata y: ");
} /* scanPunto2D */

/* Legge un array di Punto2D da tastiera.
IP etiche Etichetta per l'input da inserire mediante tastiera.
IK+OP a Array di Punto2D, precedentemente allocato, da leggere.
IP Grandezza di $a.
*/
void scanArrayPunto2D(const char etiche[], Punto2D a[], int n) {
    int i;
    printf("%s", etiche);
    for (i = 0; i < n; i++) {
        printf("a[%d]: ", i);
        scanPunto2D("", &a[i]);
    } /* for */
} /* scanArrayPunto2D */

/* Alloca e legge un array pieno di Punto2D da tastiera.
IP etiche Etichetta per l'input da inserire mediante tastiera.
IK+OP Grandezza di $a.
IK+OR a Array di Punto2D, da allocare e da leggere.
*/
Punto2D *allocateScanArrayPunto2D(const char etiche[], int *n) {
    Punto2D *a;
    *n = scanInt("Grandezza dell'array pieno: ");
    a = malloc(*n * sizeof(Punto2D));
    assert(a != NULL);
    scanArrayPunto2D(etiche, a, *n);
    return a;
} /* allocateScanArrayPunto2D */

int scanSizeArrayPunto2D(const char etiche[], Punto2D a[]) {
    int n = scanInt("Grandezza array: ");
    scanArrayPunto2D(etiche, a, n);
    return n;
} /* scanSizeArrayPunto2D */
/*Scambia due punti 2D
IOP a,b puntatori ai due punti da scambiare
*/
void swapPunti2D(Punto2D *a, Punto2D *b) {
    Punto2D temp = *a;
    *a = *b;
    *b = temp;
}
/*calcola la distanza euclidea al quadrato tra due punti, calcolo il quadrato così evito di fare una
sqrt che rallenta di molto l'esecuzione
IP a,b due puntatori ai punti tra cui devo calcolare la distanza
OR distanza al quadrato tra i due punti
*/
double distanzaEuclideaAlla2(const Punto2D *a, const Punto2D *b) {
    return (pow((a->x) - (b->x), 2) + pow((a->y) - (b->y), 2));
}
/*Trova l'indice del punto più isolato con una ricerca lineare tra tutte le distanze tra le coppie
di punti, ha complessita $nP^2 ma e' piu' veloce per $nP sotto una certa soglia
IP aP[] e' l'array di punti tra cui cercare l'isolato
IP nP e' la grandezza dell'array $aP
OR indiceMax e' l'indice in $aP del Punto2D piu' isolato
*/
int trovaIsolatoLineare(const Punto2D aP[], int nP) {
    int i, indiceMax = -1;
    double dCorrente;
    double dMax = -1;
    for (i = 0; i < nP; i++) {
        dCorrente = distanzaMinima(aP, nP, i);
        if (dMax < dCorrente) /*minore e non minore o uguale così prende il primo nel caso ci siano
                                 due ugualmente isolati*/
        {
            dMax = dCorrente;
            indiceMax = i;
        }
    }
    return indiceMax;
}
/*Trova la distanza minima tra un Punto2D e gli altri punti in un array, e' una funzione di appoggio
per trovaIsolatoLineare
IP aP[] e' l'array di punti tra cui la distanza minima IP nP e' la grandezza
dell'array $aP
IP iPunto e' l'indice in $aP del Punto2D di cui va trovata la distanza minima
OR dMin e' la distanza minima di $aP[$iPunto] dagli altri punti di $aP
*/
double distanzaMinima(const Punto2D aP[], int nP, int iPunto) {
    int i;
    /*lo inizializzo a DBL_MAX cosi' la prima distanza sara' sempre minore */
    double dMin = DBL_MAX;
    double dCorrente;
    for (i = 0; i < nP; i++) {
        if (i != iPunto && (dCorrente = distanzaEuclideaAlla2(&aP[i], &aP[iPunto])) < dMin) {
            dMin = dCorrente;
        }
    }
    return dMin;
}
/*e' una funzione di appoggio per partitionPunti2D per poter scegliere se fare il confronto lungo
l'asse x o y
IP aP e' l'array che stiamo partizionando
IOP lPt e' un puntatore all'indice sinistro del partition da scorrere
IOP rPt e' un puntatore all'indice destro del partition da scorrere
IP asse indica se i confronti devono avvenire lungo l'asse x o y asse puo' valere ASSE_X o ASSE_Y
definiti in  Punto2D.h
IP pivot e' il Punto2D rispetto al quale stiamo partizionando l'array
*/
void scorriIndiciPartition(const Punto2D aP[], int *lPt, int *rPt, char asse, const Punto2D pivot) {
    if (asse == ASSE_X) { /*sort lungo asse x*/
        while (((*lPt) <= (*rPt)) && (aP[(*lPt)].x <= pivot.x)) {
            (*lPt)++;
        }
        while (((*lPt) <= (*rPt)) && (aP[(*rPt)].x >= pivot.x)) {
            (*rPt)--;
        }
    } else { /*sort lungo l'asse y*/
        while (((*lPt) <= (*rPt)) && (aP[(*lPt)].y <= pivot.y)) {
            (*lPt)++;
        }
        while (((*lPt) <= (*rPt)) && (aP[(*rPt)].y >= pivot.y)) {
            (*rPt)--;
        }
    }
}
/*esegue il partizionamento dell'array e restituisce l'indice finale del pivot,va usata in
quickSortPunti2D
IP aP e' l'array che dobbiamo partizionare
IP a,b sono gli indici sx e dx dell'array da partizionare $aP
IP asse indica se i confronti devono avvenire lungo l'asse x o y, puo' valere ASSE_X o ASSE_Y
definiti in  Punto2D.h
OR l viene ritornato l'indice finale del pivot
*/
int partitionPunti2D(Punto2D aP[], int a, int b, char asse) {
    Punto2D pivot = aP[b];
    int l = a;
    int r = b - 1;
    while (l <= r) {
        scorriIndiciPartition(aP, &l, &r, asse, pivot);
        if (l < r) {
            swapPunti2D(&aP[l], &aP[r]);
        }
    }
    swapPunti2D(&aP[l], &aP[b]);
    return l;
}
/*una versione modificata dell'algoritmo di quickSort che puo' ordinare lungo l'asse x o l'asse y
IOP aP e' l'array da ordinare
IP l,r sono gli indici sx e dx dell'array da partizionare $aP
IP asse indica se l'ordinamento deve avvenire lungo l'asse x o y, puo' valere ASSE_X o ASSE_Y
definiti in  Punto2D.h
*/
void quickSortPunti2D(Punto2D aP[], int l, int r, char asse) {
    int pivot;
    if (l >= r) {
        return;
    }
    pivot = partitionPunti2D(aP, l, r, asse);
    quickSortPunti2D(aP, l, pivot - 1, asse);
    quickSortPunti2D(aP, pivot + 1, r, asse);
}
/*Trova l'indice del punto più isolato con un algoritmo di binary space partitioning piu' efficiente
per valori di $nP alti di quello lineare (e' nP*log^2(nP))
IP aP[] e' l'array di punti tra cui cercare l'isolato
IP nP e' la grandezza dell'array $aP
OR indiceMax e' l'indice in $aP del Punto2D piu' isolato
*/
int trovaIsolatoMigliore(const Punto2D aP[], int nP) {
    Punto2D arrayCopia[100];
    BSPNodo *root;
    BSPNodo *nodoPiuVicino = malloc(sizeof(BSPNodo));
    BSPNodo *secondoNodoPiuVicino = malloc(sizeof(BSPNodo));
    Punto2D *puntoCercato = malloc(sizeof(Punto2D));
    double distanzaCandidataMax = DBL_MAX, secondaDistanzaCandidataMax = DBL_MAX, distanzaMax = -1;
    int indiceMax = -1, i;
    for (i = 0; i < nP; i++) {
        arrayCopia[i] = aP[i];
    }
    root = buildBSP(arrayCopia, nP, ASSE_X); /*costruisce l'albero binario*/

    for (i = 0; i < nP; i++) { /*ciclo che trova indiceMax=argmax_i{min_j{distanza(aP[i],aP[j])}}*/
        distanzaCandidataMax = DBL_MAX;
        secondaDistanzaCandidataMax = DBL_MAX;
        puntoCercato->x = aP[i].x;
        puntoCercato->y = aP[i].y;
        nearestSearchBSP(root, &distanzaCandidataMax, &secondaDistanzaCandidataMax, nodoPiuVicino,
                         secondoNodoPiuVicino, puntoCercato, ASSE_X);
        if (secondaDistanzaCandidataMax > distanzaMax) {
            distanzaMax = secondaDistanzaCandidataMax;
            indiceMax = i;
        }
    }
    /*printPunto2D("nodo piu vicino", &nodoPiuVicino->punto);
    printf("distanza al quadrato %f\n", distanzaCandidata);*/
    free(nodoPiuVicino);
    free(puntoCercato);
    return indiceMax;
}
