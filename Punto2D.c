/*De Gobbi Matteo*/
#include <math.h>
#include <stdlib.h>
#include <float.h>

#include "assert.h"
#include <stdio.h>
#include "InOut.h"

#ifndef PUNTO2D
#define PUNTO2D
#include "Punto2D.h"
#endif

#ifndef BSP
#define BSP
#include "BSP.h"
#endif 



void printPunto2D(const char etiche[], const Punto2D *p)
{
    printf("%s", etiche);
    printf("(%f, %f)\n", p->x, p->y);
} /* printPunto2D */

/* Stampa un array di Punto2D su video.
IP etiche Etichetta per l'output da stampare su video.
IP a Array da stampare.
IP n Grandezza di $a.
OV Stampa $a su video.
*/
void printArrayPunto2D(const char etiche[], const Punto2D a[], int n)
{
    int i;
    printf("%s", etiche);
    for (i = 0; i < n; i++)
    {
        printf("a[%d]: ", i);
        printPunto2D("", &a[i]);
    } /* for */
} /* printArrayPunto2D */

void swapPunti2D(Punto2D *a, Punto2D *b)
{
    Punto2D temp = *a;
    *a = *b;
    *b = temp;
}
/* Legge un Punto2D da tastiera.
IP etiche Etichetta per l'input da inserire mediante tastiera.
IK+OP p Punto2D letto da tastiera.
*/
void scanPunto2D(const char etiche[], Punto2D *p)
{
    printf("%s", etiche);
    p->x = scanDouble("coordinata x: ");
    p->y = scanDouble("coordinata y: ");
} /* scanPunto2D */

/* Legge un array di Punto2D da tastiera.
IP etiche Etichetta per l'input da inserire mediante tastiera.
IK+OP a Array di Punto2D, precedentemente allocato, da leggere.
IP Grandezza di $a.
*/
void scanArrayPunto2D(const char etiche[], Punto2D a[], int n)
{
    int i;
    printf("%s", etiche);
    for (i = 0; i < n; i++)
    {
        printf("a[%d]: ", i);
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

int scanSizeArrayPunto2D(const char etiche[], Punto2D a[])
{
    int n = scanInt("Grandezza array: ");
    scanArrayPunto2D(etiche, a, n);
    return n;
} /* scanSizeArrayPunto2D */

/*
invece di calcolare la distanza calcolo il quadrato della distanza cosi evito di fare la sqrt
tanto per i confronti e' uguale quindi meglio fare cosi, risparmio circa 10ms suun array di 500 punti
*/
double distanzaEuclideaAlla2(const Punto2D *a, const Punto2D *b)
{
    return (pow((a->x) - (b->x), 2) + pow((a->y) - (b->y), 2));
}
int trovaIsolato(const Punto2D aP[], int nP)
{
    int i, indiceMax = -1;
    double dCorrente;
    double dMax = -1;
    for (i = 0; i < nP; i++)
    {
        dCorrente = distanzaMinima(aP, nP, i);
        if (dMax < dCorrente) /*minore e non minore o uguale così prende il primo nel caso ci siano due ugualmente isolati*/
        {
            dMax = dCorrente;
            indiceMax = i;
        }
    }
    return indiceMax;
}

double distanzaMinima(const Punto2D aP[], int nP, int iPunto)
{
    int i;
    double dMin = DBL_MAX;
    double dCorrente;
    for (i = 0; i < nP; i++)
    {
        if (i != iPunto && (dCorrente = distanzaEuclideaAlla2(&aP[i], &aP[iPunto])) < dMin)
        {
            dMin = dCorrente;
        }
    }
    return dMin;
}
void scorriIndiciPartition(Punto2D aP[], int *lPt, int *rPt, char asse, Punto2D pivot)
{
    /*sort lungo asse x*/
    if (asse == ASSE_X)
    {
        while (((*lPt) <= (*rPt)) && (aP[(*lPt)].x <= pivot.x)) 
        {
            (*lPt)++;
        }
        while (((*lPt) <= (*rPt)) && (aP[(*rPt)].x >= pivot.x)) 
        {
            (*rPt)--;
        }
    }else{/*sort lungo l'asse y*/
      while (((*lPt) <= (*rPt)) && (aP[(*lPt)].y <= pivot.y)) 
        {
            (*lPt)++;
        }
        while (((*lPt) <= (*rPt)) && (aP[(*rPt)].y >= pivot.y)) 
        {
            (*rPt)--;
        }  
    }
}
int partitionPunti2D(Punto2D aP[], int a, int b, char asse)
{
    Punto2D pivot = aP[b];
    int l = a;
    int r = b - 1;
    while (l <= r)
    {
        scorriIndiciPartition(aP, &l, &r, asse, pivot);
        if (l < r)
        {
            swapPunti2D(&aP[l], &aP[r]);
        }
    }
    swapPunti2D(&aP[l], &aP[b]);
    return l;
}
void quickSortPunti2D(Punto2D aP[], int l, int r, char asse)
{
    int pivot;
    if (l >= r)
    {
        return;
    }
    pivot = partitionPunti2D(aP, l, r, asse);
    quickSortPunti2D(aP, l, pivot - 1, asse);
    quickSortPunti2D(aP, pivot + 1, r, asse);
}

int trovaIsolatoMigliore(const Punto2D aP[], int nP){
    Punto2D arrayCopia[100];
    BSPNodo* root;
    BSPNodo* nodoPiuVicino;
    Punto2D* puntoCercato;
    double distanzaMigliore=DBL_MAX;
    int i;
    for (i = 0; i < nP; i++)
    {
        arrayCopia[i] = aP[i];
    }
    root= buildBSP(arrayCopia,nP,ASSE_X);
    
    /*preOrder(root);*/
    puntoCercato->x=0;
    puntoCercato->y=0;
    nearestSearchBSP(root,&distanzaMigliore,nodoPiuVicino,puntoCercato,ASSE_X);
    
    return root->punto.x;
}
