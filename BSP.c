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

BSPNodo* buildBSP(Punto2D arrayCopia[], int nP, char asse)
{   
    Punto2D mediana;
    int indiceMediana=(nP - 1) / 2;
    
    BSPNodo* nodoCorrente=malloc(sizeof(BSPNodo));
    if (nP==0)
    {
        
        return NULL;
    }
      
    assert(nodoCorrente != NULL);
    quickSortPunti2D(arrayCopia, 0, nP - 1, asse);
    mediana = arrayCopia[indiceMediana];
    /*printPunto2D("",&mediana);*/
    nodoCorrente->punto=mediana;
    nodoCorrente->figlioSx=buildBSP(arrayCopia,indiceMediana,!asse);
    nodoCorrente->figlioDx=buildBSP(arrayCopia+indiceMediana+1,nP-indiceMediana-1,!asse);
    return nodoCorrente;
}
void preOrder(BSPNodo* root){
    printPunto2D("",&(root->punto));
    if (root->figlioSx!=NULL)
    {
        preOrder(root->figlioSx);
    }
    if (root->figlioDx!=NULL)
    {
        preOrder(root->figlioDx);
    }
}

void nearestSearchBSP(BSPNodo* root,double* distanzaMigliore,BSPNodo* nodoPiuVicino,Punto2D* puntoCercato,char asse){
    double distanzaRootPunto;
    if (root->figlioSx==NULL && root->figlioDx==NULL)
    {
        distanzaRootPunto=distanzaEuclideaAlla2(&(root->punto),puntoCercato);
        if (distanzaRootPunto<*distanzaMigliore)
        {
            nodoPiuVicino=root;
            *distanzaMigliore=distanzaRootPunto;
        }
        
        
        return;
    }
    
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