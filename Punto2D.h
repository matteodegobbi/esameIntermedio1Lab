/*De Gobbi Matteo*/
#define ASSE_X 1
#define ASSE_Y 0
/*punto sul piano cartesiano in 2 Dimensioni*/
typedef struct {
    double x,y;
} Punto2D;

int trovaIsolato(const Punto2D aP[], int nP);
double distanzaMinima(const Punto2D aP[],int nP,int indicePunto);
double distanzaEuclideaAlla2(const Punto2D* a,const Punto2D* b);
void scanPunto2D(const char etiche[], Punto2D* p);
void scanArrayPunto2D(const char etiche[], Punto2D a[], int n);
int scanSizeArrayPunto2D(const char etiche[], Punto2D a[]);
Punto2D *allocateScanArrayPunto2D(const char etiche[], int *n);
void printPunto2D(const char etiche[], const Punto2D *p);
void quickSortPunti2D(Punto2D aP[], int l, int r, char asse);
int trovaIsolatoMigliore(const Punto2D aP[], int nP);
void printArrayPunto2D(const char etiche[], const Punto2D a[], int n);