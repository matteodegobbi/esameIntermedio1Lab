/*De Gobbi Matteo*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Punto2D.h"

int main(void) {
    int result;
    int nP;
    Punto2D aP[100]; /*utilizzo un array a capacita' fissa 100 cosi' risparmio il malloc sappiamo
                        che nP<=100*/
    nP = scanSizeArrayPunto2D("", aP);
    result = trovaIsolato(aP, nP);
    printf("Indice isolato%d\n", result);
    return 0;
} /*main*/
