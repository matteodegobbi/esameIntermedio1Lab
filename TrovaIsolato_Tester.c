/*De Gobbi Matteo*/
#include <stdlib.h>
#include "Punto2D.h"
int main(void)
{
    int nP=0;
    Punto2D *aP=0;
    /*leggi nP TODO*/
    aP=allocateScanArrayPunto2D("etichetta",&nP);   
/*leggi aP array di punti prima x poi y TODO*/
    
    /*trovaIsolato TODO*/
    /*stampa risultato TODO*/   
    free(aP);
    return 0;
}
