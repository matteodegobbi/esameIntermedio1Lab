/*De Gobbi Matteo*/
#include <stdlib.h>
#include <stdio.h>
#include "Punto2D.h"
#include <time.h>
int main(void)
{
    int result;
    clock_t start_t, end_t;
    
    int nP,i;
    /*Punto2D *aP;
    aP=allocateScanArrayPunto2D("etichetta",&nP);*/
    
    Punto2D aP[100]; 
    nP=scanSizeArrayPunto2D("",aP);

    /*printf("distanza euclidea tra 0,0 e 0,4: %f\n\n",distanzaEuclidea(&aP[0],&aP[2]));*/
    /*printf("%f\n",distanzaMinima(aP,nP,0));*/
    start_t = clock();
    for (i = 0; i < 1000; i++)
    {
        result=trovaIsolato(aP,nP);
    }
    
    
    end_t = clock();
    printf("passati: %fs\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);
    printf("Indice del isolato%d\n",result);
   
    /*trovaIsolato TODO*/
    /*stampa risultato TODO*/   
    /*free(aP);*/
    return 0;
}
