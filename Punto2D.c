/*De Gobbi Matteo*/
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "Punto2D.h"
#include "assert.h"
#include <stdio.h>
#include "InOut.h"
/* Legge un Punto2D da tastiera.
IP etiche Etichetta per l'input da inserire mediante tastiera.
IK+OP p Punto2D letto da tastiera.
*/
void scanPunto2D(const char etiche[], Punto2D* p) {
    printf("%s", etiche);
    p->x = scanDouble("Inserisci la coordinata x: ");
    p->y = scanDouble("Inserisci la coordinata y: ");
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
        printf("Valore[%d]: ", i);
        scanPunto2D("", &a[i]);
    } /* for */
} /* scanArrayPunto2D */

/* Alloca e legge un array pieno di Punto2D da tastiera.
IP etiche Etichetta per l'input da inserire mediante tastiera.
IK+OP Grandezza di $a.
IK+OR a Array di Punto2D, da allocare e da leggere.
*/
Punto2D *allocateScanArrayPunto2D(const char etiche[], int *n)
{
    Punto2D *a;
    *n = scanInt("Grandezza dell'array pieno: ");
    a = malloc(*n * sizeof(Punto2D));
    assert(a != NULL);
    scanArrayPunto2D(etiche, a, *n);
    return a;
} /* allocateScanArrayPunto2D */

double distanzaEuclidea(const Punto2D *a, const Punto2D *b)
{
    return sqrt(pow((a->x) - (b->x), 2) + pow((a->y) - (b->y), 2));
}
int trovaIsolato(const Punto2D aP[], int nP){
    int i,indiceMax=-1;
    double dCorrente;
    double dMax=-1;
    for (i = 0; i < nP; i++)
    {
       dCorrente=distanzaMinima(aP,nP,i);
       if (dMax<dCorrente)/*minore e non minore o uguale così prende il primo nel caso ci siano due ugualmente isolati*/
       {
        dMax=dCorrente;
        indiceMax=i;
       }
        
    }
    
    return indiceMax;
}

double distanzaMinima(const Punto2D aP[],int nP, int iPunto){
    int i;
    double dMin=DBL_MAX;
    double dCorrente;
    for (i = 0; i < nP; i++){
        if (i!=iPunto && (dCorrente=distanzaEuclidea(&aP[i],&aP[iPunto]))<dMin)
        {
          dMin=dCorrente; 
        } 
    }
    return dMin;
}
