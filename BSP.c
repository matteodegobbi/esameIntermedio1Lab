/*De Gobbi Matteo*/
#ifndef PUNTO2D
#define PUNTO2D
#include "Punto2D.h"
#endif

#ifndef BSP
#define BSP
#include "BSP.h"
#endif

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*Costruisce l'albero binario secondo l'algoritmo di binary space partitioning, cioe' costruisce un
albero binario di ricerca alternando la relazione d'ordine ad ogni livello, ad esempio
livello 0 -> lungo asse x, livello 1 ->lungo asse y ...
IOP arrayCopia[] array contenente i Punti2D da cui si costruisce l'albero, non e' const perche'
verra' ordinato
IP nP grandezza di $arrayCopia
IP asse indica se la relazione d'ordine e' lungo l'asse x o y, puo' valere ASSE_X o ASSE_Y
definiti in  Punto2D.h, verra' alternata tra questi due valori ad ogni ricorsione
OR nodoCorrente ritorna il nodo allocato in questa ricorsione, alla fine delle ricorsioni ritornera'
la radice dell'albero
*/
BSPNodo *buildBSP(Punto2D arrayCopia[], int nP, char asse) {
    Punto2D mediana;
    int indiceMediana = (nP - 1) / 2;

    BSPNodo *nodoCorrente = malloc(sizeof(BSPNodo));
    if (nP == 0) {
        return NULL;
    }

    assert(nodoCorrente != NULL);
    quickSortPunti2D(arrayCopia, 0, nP - 1, asse);
    mediana = arrayCopia[indiceMediana];
    /*printPunto2D("",&mediana);*/
    nodoCorrente->punto = mediana;
    nodoCorrente->figlioSx = buildBSP(arrayCopia, indiceMediana, !asse);
    nodoCorrente->figlioDx =
        buildBSP(arrayCopia + indiceMediana + 1, nP - indiceMediana - 1, !asse);
    return nodoCorrente;
} /*buildBSP*/

/*Restituisce 1 se il puntoCercato si trova alla sinistra della root o 0 se si trova alla destra
considerando se usare la relazione d'ordine lungo le x o le y
IP root punto contenuto nella radice del sottoalbero che stiamo esaminando
IP puntoCercato punto di cui dobbiamo determinare se si trova nel sottoalbero sx o dx
IP asse indica se la relazione d'ordine considerata e' lungo l'asse x o y, puo' valere ASSE_X o
ASSE_Y definiti in  Punto2D.h
OR 1 se puntoCercato e' a sx di root 0 se e' a dx
*/
int isAllaSinistra(const Punto2D *root, const Punto2D *puntoCercato, char asse) {
    if (asse) /*asse x*/
    {
        return ((puntoCercato->x) > (root->x)) ? 0 : 1;
    } else { /*asse y*/
        return ((puntoCercato->y) > (root->y)) ? 0 : 1;
    }
} /*isAllaSinistra*/

/*funzione di appoggio per la nearestSearchBSP che determina se e' possibile ci sia un punto piu'
vicino del migliore finora nel sottoalbero non ancora esaminato e restituisce 1 o 0 a seconda del
caso IP asse indica se i confronti devono avvenire lungo l'asse x o y, puo' valere ASSE_X o ASSE_Y
definiti in  Punto2D.h
IP root, nodo di cui controlliamo il sottoalbero non ancora controllato (sx o dx in base a quale e'
gia' stato controllato)
IP puntoCercato, punto che stiamo cercando nell'albero BSP
IP secondaDistanzaMigliore puntatore al double che contiene la seconda distanza piu' piccola trovata
finora, considera la seconda perche' la prima sara' la distanza tra il punto e stesso (cioe' 0)
quando esso trova se stesso nell'albero
OR viene ritornato 1 se il sottoalbero non ancora controllato potrebbe contenere il punto piu vicino
oppure 0 se non e' possibile
*/
int isAltroRamoPiuVicino(char asse, const BSPNodo *root, const Punto2D *puntoCercato,
                         double *secondaDistanzaMigliore) {
    /*si potrebbe unificare in un unico return ma diventerebbe poco leggibile e
    non c'e' guadagno in velocita' apprezzabile*/
    if (asse && pow(root->punto.x - puntoCercato->x, 2) < *secondaDistanzaMigliore) {
        return 1;
    }
    if (!asse && pow(root->punto.y - puntoCercato->y, 2) < *secondaDistanzaMigliore) {
        return 1;
    }
    return 0;
}/*isAltroRamoPiuVicino*/

/*Cerca nel sottoalbero non ancora controllato se e' presente un punto piu' vicino dei due migliori
finora, questa funzione verra' chiamata solo se isAltroRamoPiuVicino ritorna 1
Le IS sono le stesse di nearestSearchBSP tranne:
IP allaSinistra indica quale sottoalbero e' gia stato controllato se e' quello sx allora verra
controllato il dx e viceversa
*/
void controllaAltroRamoBSP(BSPNodo *root, double *distanzaMigliore, double *secondaDistanzaMigliore,
                           BSPNodo *nodoPiuVicino, BSPNodo *secondoNodoPiuVicino,
                           Punto2D *puntoCercato, char asse, int allaSinistra) {
    if (allaSinistra) {
        if (root->figlioDx != NULL) {
            nearestSearchBSP(root->figlioDx, distanzaMigliore, secondaDistanzaMigliore,
                             nodoPiuVicino, secondoNodoPiuVicino, puntoCercato, !asse);
        }
    } else {
        if (root->figlioSx != NULL) {
            nearestSearchBSP(root->figlioSx, distanzaMigliore, secondaDistanzaMigliore,
                             nodoPiuVicino, secondoNodoPiuVicino, puntoCercato, !asse);
        }
    }
}/*controllaAltroRamoBSP*/

/*funzione di appoggio per nearestSearchBSP che aggiorna le due distanze migliori e i due nodi piu'
vicini nel caso in cui ne vengano trovati di piu vicini le IS sono le stesse di nearestSearchBSP
tranne:
IP distanzaRootPunto e' la distanza tra il nodo corrente della ricorsione e il punto cercato
nell'albero
*/
void aggiornaDistanzeSearchBSP(double distanzaRootPunto, double *distanzaMigliore,
                               double *secondaDistanzaMigliore, BSPNodo *nodoPiuVicino,
                               BSPNodo *secondoNodoPiuVicino, BSPNodo *root) {
    if (distanzaRootPunto < *distanzaMigliore) {
        *secondoNodoPiuVicino = *nodoPiuVicino;
        *secondaDistanzaMigliore = *distanzaMigliore;
        *nodoPiuVicino = *root;
        *distanzaMigliore = distanzaRootPunto;
    } else if (distanzaRootPunto <= *secondaDistanzaMigliore) {
        *secondoNodoPiuVicino = *root;
        *secondaDistanzaMigliore = distanzaRootPunto;
    }
}/*aggiornaDistanzeSearchBSP*/

/*Cerca nell'albero binario di radice $root i due punti piu vicini a $puntoCercato, il piu vicino
   sara' $puntoCercato stesso, il secondo sara' il punto che ci interessava trovare per computare la
   distanza minima. La ricerca ricorre fino alle foglie ceracando un migliore temporaneo e poi
   risalendo l'albero cerca anche nei sottoalberi non ancora controllati se e' possibile che esista
   un punto piu vicino dei due migliori correnti (Cerchera' nei vari sottoalberi non ancora
   controllati solo se isAltroRamoPiuVicino restituisce 1).
   Ad ogni ricorsione alterna tra considerare asse x o asse y in modo da rispettare la relazione
   d'ordine costruita in buildBSP
   IOP root, radice del sottoalbero su cui stiamo cercando
   IOP distanzaMigliore, secondaDistanzaMigliore sono le due distanze piu piccole trovate finora
   IOP nodoPiuVicino, secondoNodoPiuVicino i due nodi che contengono i punti piu vicini a
   $puntoCercato trovati finora
   IOP puntoCercato, il punto di cui stiamo cercando i due piu vicini nell'albero
   IP asse indica su quale asse stiamo confrontando al livello di ricorsione corrente, ad ogni
   ricorsione si alterna tra asse x e y per rispettare la relazione d'ordine definita in buildBSP
*/
void nearestSearchBSP(BSPNodo *root, double *distanzaMigliore, double *secondaDistanzaMigliore,
                      BSPNodo *nodoPiuVicino, BSPNodo *secondoNodoPiuVicino, Punto2D *puntoCercato,
                      char asse) {
    double distanzaRootPunto;
    int allaSinistra;
    if (root->figlioSx == NULL &&
        root->figlioDx == NULL) { /*caso base sono arrivato ad una foglia dell'albero*/
        distanzaRootPunto = distanzaEuclideaAlla2(&(root->punto), puntoCercato);
        aggiornaDistanzeSearchBSP(distanzaRootPunto, distanzaMigliore, secondaDistanzaMigliore,
                                  nodoPiuVicino, secondoNodoPiuVicino, root);
        return;
    }
    allaSinistra = isAllaSinistra(&(root->punto), puntoCercato,
                                  asse); /*determino se devo controllare a sx o a dx per prima*/
    if (root->figlioSx != NULL && allaSinistra) { /*cerco nel sottoalbero sx*/
        nearestSearchBSP(root->figlioSx, distanzaMigliore, secondaDistanzaMigliore, nodoPiuVicino,
                         secondoNodoPiuVicino, puntoCercato, !asse);
    }
    if (root->figlioDx != NULL && !allaSinistra) { /*cerco nel sottoalbero dx*/
        nearestSearchBSP(root->figlioDx, distanzaMigliore, secondaDistanzaMigliore, nodoPiuVicino,
                         secondoNodoPiuVicino, puntoCercato, !asse);
    }
    distanzaRootPunto = distanzaEuclideaAlla2(&(root->punto), puntoCercato);
    aggiornaDistanzeSearchBSP(distanzaRootPunto, distanzaMigliore, secondaDistanzaMigliore,
                              nodoPiuVicino, secondoNodoPiuVicino, root);
    /* se ci sono punti dall'altro lato dell'albero che potrebbero essere piu vicini controllo anche
    in quel lato*/
    if (isAltroRamoPiuVicino(asse, root, puntoCercato, secondaDistanzaMigliore)) {
        controllaAltroRamoBSP(root, distanzaMigliore, secondaDistanzaMigliore, nodoPiuVicino,
                              secondoNodoPiuVicino, puntoCercato, asse, allaSinistra);
    }
    return;
}/*nearestSearchBSP*/

/*libera la memoria allocata nella creazione dell'albero binario ramite una visita in PostOrder
IOP p nodo di cui va liberata la memoria
*/
void liberaBSP(BSPNodo *p) {
    if (p == NULL) {
        return;
    }
    liberaBSP(p->figlioDx);
    liberaBSP(p->figlioSx);
    free(p);
}/*liberaBSP*/

/*Funzione utile per il debug che printa i nodi dell'albero con una visita InOrder
IP root nodo da visitare in questa ricorsione
*/
void preOrder(const BSPNodo *root) {
    printPunto2D("", &(root->punto));
    if (root->figlioSx != NULL) {
        preOrder(root->figlioSx);
    }
    if (root->figlioDx != NULL) {
        preOrder(root->figlioDx);
    }
}/*preOrder*/