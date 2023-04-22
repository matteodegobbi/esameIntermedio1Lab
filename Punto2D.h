/*De Gobbi Matteo*/

/*punto sul piano cartesiano in 2 Dimensioni*/
typedef struct {
    double x,y;
} Punto2D;

int trovaIsolato(const Punto2D aP[], int nP);
double distanzaMinima(const Punto2D aP[],int nP,int indicePunto);
double distanzaEuclidea(const Punto2D* a,const Punto2D* b);
void scanPunto2D(const char etiche[], Punto2D* p);
void scanArrayPunto2D(const char etiche[], Punto2D a[], int n);
int scanSizeArrayPunto2D(const char etiche[], Punto2D a[]);
Punto2D *allocateScanArrayPunto2D(const char etiche[], int *n);