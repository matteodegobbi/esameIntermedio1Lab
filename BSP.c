#ifndef PUNTO2D
#define PUNTO2D
#include "Punto2D.h"
#endif

#ifndef BSP
#define BSP
#include "BSP.h"
#endif

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

BSPNodo *buildBSP(Punto2D arrayCopia[], int nP, char asse)
{
    Punto2D mediana;
    int indiceMediana = (nP - 1) / 2;

    BSPNodo *nodoCorrente = malloc(sizeof(BSPNodo));
    if (nP == 0)
    {

        return NULL;
    }

    assert(nodoCorrente != NULL);
    quickSortPunti2D(arrayCopia, 0, nP - 1, asse);
    mediana = arrayCopia[indiceMediana];
    /*printPunto2D("",&mediana);*/
    nodoCorrente->punto = mediana;
    nodoCorrente->figlioSx = buildBSP(arrayCopia, indiceMediana, !asse);
    nodoCorrente->figlioDx = buildBSP(arrayCopia + indiceMediana + 1, nP - indiceMediana - 1, !asse);
    return nodoCorrente;
}
void preOrder(BSPNodo *root)
{
    printPunto2D("", &(root->punto));
    if (root->figlioSx != NULL)
    {
        preOrder(root->figlioSx);
    }
    if (root->figlioDx != NULL)
    {
        preOrder(root->figlioDx);
    }
}
int isAllaSinistra(Punto2D *root, Punto2D *puntoCercato, char asse)
{
    if (asse) /*asse x*/
    {
        return ((puntoCercato->x) > (root->x)) ? 0 : 1;
    }
    else
    { /*asse y*/
        return ((puntoCercato->y) > (root->y)) ? 0 : 1;
    }
}
void nearestSearchBSP(BSPNodo *root, double *distanzaMigliore, double *secondaDistanzaMigliore, BSPNodo *nodoPiuVicino, BSPNodo *SecondoNodoPiuVicino, Punto2D *puntoCercato, char asse)
{
    double distanzaRootPunto;
    int allaSinistra;
    if (root->figlioSx == NULL && root->figlioDx == NULL)
    {
        distanzaRootPunto = distanzaEuclideaAlla2(&(root->punto), puntoCercato);
        if (distanzaRootPunto < *distanzaMigliore)
        {
            *SecondoNodoPiuVicino = *nodoPiuVicino;
            *secondaDistanzaMigliore=*distanzaMigliore;
            *nodoPiuVicino = *root;
            *distanzaMigliore = distanzaRootPunto;
        }
        else if (distanzaRootPunto <= *secondaDistanzaMigliore)
        {
            *SecondoNodoPiuVicino = *root;
            *secondaDistanzaMigliore = distanzaRootPunto;
        }

        return;
    }
    allaSinistra = isAllaSinistra(&(root->punto), puntoCercato, asse);
    if (root->figlioSx != NULL && allaSinistra)
    {
        nearestSearchBSP(root->figlioSx, distanzaMigliore, secondaDistanzaMigliore,nodoPiuVicino, SecondoNodoPiuVicino, puntoCercato, !asse);
    }
    if (root->figlioDx != NULL && !allaSinistra)
    {
        nearestSearchBSP(root->figlioDx, distanzaMigliore, secondaDistanzaMigliore,nodoPiuVicino, SecondoNodoPiuVicino, puntoCercato, !asse);
    }
    distanzaRootPunto = distanzaEuclideaAlla2(&(root->punto), puntoCercato);
    if (distanzaRootPunto < *distanzaMigliore)
    {
        *SecondoNodoPiuVicino = *nodoPiuVicino;
        *secondaDistanzaMigliore=*distanzaMigliore;
        *nodoPiuVicino = *root;
        *distanzaMigliore = distanzaRootPunto;
    }
    else if (distanzaRootPunto <= *secondaDistanzaMigliore)
    {
        *SecondoNodoPiuVicino = *root;
        *secondaDistanzaMigliore = distanzaRootPunto;
    }

    /*ci sono punti dall'altro lato dell'albero che potrebbero essere piu vicini?*/
    if (asse)
    {
        if (pow(root->punto.x - puntoCercato->x, 2) < *secondaDistanzaMigliore)
        {
            if (allaSinistra)
            {
                if (root->figlioDx!=NULL)
                {
                    nearestSearchBSP(root->figlioDx, distanzaMigliore, secondaDistanzaMigliore,nodoPiuVicino, SecondoNodoPiuVicino, puntoCercato, !asse);
                }
            }
            else
            {
                if (root->figlioSx!=NULL)
                {
                    nearestSearchBSP(root->figlioSx, distanzaMigliore, secondaDistanzaMigliore,nodoPiuVicino, SecondoNodoPiuVicino, puntoCercato, !asse);
                }
            }
        }
    }
    else
    {
        if (pow(root->punto.y - puntoCercato->y, 2) < *secondaDistanzaMigliore)
        {
            if (allaSinistra)
            {
                if (root->figlioDx!=NULL)
                {
                    nearestSearchBSP(root->figlioDx, distanzaMigliore, secondaDistanzaMigliore,nodoPiuVicino, SecondoNodoPiuVicino, puntoCercato, !asse);
                }
            }
            else
            {
                if (root->figlioSx!=NULL)
                {
                    nearestSearchBSP(root->figlioSx, distanzaMigliore, secondaDistanzaMigliore,nodoPiuVicino, SecondoNodoPiuVicino, puntoCercato, !asse);
                }
            }
        }
    }
    return;
}
void liberaBSP(BSPNodo *p)
{
    if (p == NULL)
    {
        return;
    }
    liberaBSP(p->figlioDx);
    liberaBSP(p->figlioSx);

    free(p);
}