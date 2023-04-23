/*De Gobbi Matteo*/
#include <stdlib.h>
#include <stdio.h>
#include "Punto2D.h"
#include <time.h>
/*sta roba va rimossa*/
#define MALLOC_NO
#define N_ITER 1

int main(void)
{
    int result;
    clock_t start_t, end_t;
    
    int nP,i;
    #ifdef MALLOC_SI
    Punto2D *aP;
    aP=allocateScanArrayPunto2D("etichetta",&nP);
    #endif

    #ifndef MALLOC_SI
    Punto2D aP[100]; 
    nP=scanSizeArrayPunto2D("",aP);
    #endif
    /*printf("distanza euclidea tra 0,0 e 0,4: %f\n\n",distanzaEuclidea(&aP[0],&aP[2]));*/
    /*printf("%f\n",distanzaMinima(aP,nP,0));*/
    start_t=clock();
    for (i = 0; i < N_ITER; i++)
    {
        result=trovaIsolato(aP,nP);
    }
    end_t = clock();
    printf("passati: %fs\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);

    start_t=clock();
    for (i = 0; i < N_ITER; i++)
    {   
        trovaIsolatoMigliore(aP,nP);
    }
    end_t = clock();
    
    printf("passati: %fs\n",(double)(end_t-start_t)/CLOCKS_PER_SEC);
    printf("Indice del isolato%d\n",result);
   
    /*trovaIsolato TODO*/
    /*stampa risultato TODO*/   
    /*free(aP);*/
    return 0;
}
