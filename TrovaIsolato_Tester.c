/*De Gobbi Matteo*/
#include <stdlib.h>
#include <stdio.h>
#include "Punto2D.h"
int main(void)
{
    int nP;
    Punto2D *aP;
    aP=allocateScanArrayPunto2D("etichetta",&nP);  
    /*printf("distanza euclidea tra 0,0 e 0,4: %f\n\n",distanzaEuclidea(&aP[0],&aP[2]));*/
    /*printf("%f\n",distanzaMinima(aP,nP,0));*/
    printf("Indice del isolato%d\n",trovaIsolato(aP,nP));
    /*trovaIsolato TODO*/
    /*stampa risultato TODO*/   
    free(aP);
    return 0;
}
