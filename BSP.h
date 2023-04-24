#ifndef PUNTO2D
#define PUNTO2D
#include "Punto2D.h"
#endif
typedef struct BSPNodo {
    struct BSPNodo* figlioSx;
    struct BSPNodo* figlioDx;
    Punto2D punto;
} BSPNodo;

void nearestSearchBSP(BSPNodo* root, double* distanzaMigliore, double* secondaDistanzaMigliore,
                      BSPNodo* nodoPiuVicino, BSPNodo* secondoNodoPiuVicino, Punto2D* puntoCercato,
                      char asse);
BSPNodo* buildBSP(Punto2D arrayCopia[], int nP, char asse);
void preOrder(const BSPNodo* root);
