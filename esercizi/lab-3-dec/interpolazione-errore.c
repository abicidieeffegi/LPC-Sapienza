#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  INT,
  DOUBLE,
  CHAR,
  FLOAT
} varType;

// funzione da interpolare
double f(double x) {
  // return exp(x) * sin(1.5*M_PI*x);
  return (x>=0 && x<=1);
}

// funzione che trova basi di lagrange
// Input:   ptr a f da interpolare
//          x in cui valutare la base
//          array con posizione dei nodi
//          numero di nodi
//          numero del polinomio da calcolare
// Output:  valutazione della base in x
double lagrangeBasis(double (*f)(double), double x, double* xNodes, int nNodes, int i){
  double lagrangeBasis = 1.0;
  int j=0;
  do {
    if (j != i)
      lagrangeBasis *= (x - xNodes[j])/(xNodes[i] - xNodes[j]);
    j++;
  } while (j < nNodes);
  return lagrangeBasis;
}

// funzione che trova l'interpolata
// Input:   ptr a f da interpolare
//          x in cui valutare l'interpolata
//          array con posizione dei nodi
//          numero di nodi
// Output:  interpolata in x
double lagrangeInterpolate(double (*f)(double), double x, double* xNodes, int nNodes, double* error) {
  double interpolated = 0.0;
  int i=0;
  do {
    interpolated += f(xNodes[i]) * lagrangeBasis(f, x, xNodes, nNodes, i);
    *error = fabs(interpolated - f(x));
    i++;
  } while (i<nNodes);
  return interpolated;
}

// funzione che prende i dati in input
// sono pigro, non voglio usare printf e scanf ogni volta
void getData (const char* str, void* ptr, varType type) {
  printf("%s", str);
  switch (type) {
    case INT:
      scanf(" %d", (int*)ptr);
      break;
    case DOUBLE:
      scanf(" %lf", (double*)ptr);
      break;
    case CHAR:
      scanf(" %c", (char*)ptr);
      break;
    case FLOAT:
      scanf(" %f", (float*)ptr);
      break;
  }
  return;
}

void checkAllocation (void* ptr) {
  if (ptr == NULL) {
    perror("Memory allocation error");
    exit(1);
  }
}

void eqNodes (double a, double b, double* xNodes, int nNodes) {
  int i=0;
  do {
    xNodes[i] = a + i*(b - a)/(nNodes-1);
    i++;
  } while (i<nNodes);
  return;
}


void chebyshevNodes (double a, double b, double* xNodes, int nNodes) {
  for (int i=0; i<nNodes; i++) {
    // xNodes[i] = 0.5*(a + b) + 0.5*(b-a)*cos(((2*i + 1)/(2*i + 2))*M_PI);
    xNodes[i] = 0.5*(a + b) + 0.5*(b-a)*cos(((double)(2*i + 1)/(2*nNodes + 2))*M_PI);
  }
  return; 
}

      // Scrivere il main() che:
      // – definisce un intervallo [a, b] a scelta dell’utente;
      // – costruisce un insieme di nodi equispaziati x0, . . . , xn;
      // – calcola i valori f (xi);
      // – costruisce una griglia fitta di punti (100–200 punti) e vi valuta l’interpo-
      // lante P(x);
      // – calcola l’errore punto-punto
      // E(x) = | f (x) − P(x)|.
int main() {
  double *xNodes, a, b, error;
  int degree, choice;
  // richiedo dati in input dall'utente
  getData("Inserire gli estremi dell'intervallo [a,b]\na = ", &a, DOUBLE);
  getData("b = ", &b, DOUBLE);
  getData("Inserire grado del polinomio: ", &degree, INT);
  printf("Opzioni disponibili:\n1. Nodi equispaziati\n2. Nodi di Chebyshev\n");
  getData("Selezionare opzione (1-2): ", &choice, INT); choice--;
  int nNodes = degree+1;
  // alloco memoria
  xNodes = malloc(nNodes * sizeof(*xNodes));
  checkAllocation((void*)xNodes);
  // dichiaro ptr a fn per scegliere il modo in cui prendere i nodi
  void (*makeNodes[])(double, double, double*, int) = {&eqNodes, &chebyshevNodes};

  // creo i nodi
  makeNodes[choice](a, b, xNodes, nNodes);
  // valuto l'interpolata, scrivendo su file
  FILE* data = fopen(".interpolated.txt", "w");
  FILE* nodes = fopen(".nodes.txt", "w");
  checkAllocation((void*)data);
  int resolution = (b-a)*100, i=0;
  double *x, interpolated;
  // alloco memoria
  x = malloc(resolution * sizeof(*x));
  // inizializzo le x da usare nel grafico
  eqNodes(a, b, x, resolution);
  printf("Inizializzando interpolazione...\n");
  do {
    interpolated = lagrangeInterpolate(f, x[i], xNodes, nNodes, &error);
    fprintf(data, "%lf\t%lf\t%lf\t%lf\n", x[i], f(x[i]), interpolated, error); 
    i++;
  } while (i<resolution);
  // scrivo le coordinate dei nodi
  for (i=0; i<nNodes; i++) {
    fprintf(nodes, "%lf\t%lf\n", xNodes[i], f(xNodes[i]));
  }
  printf("Interpolazione completata con successo\n");

  fclose(data); fclose(nodes);
  printf("Inizializzando plot...\n");
  system("echo \"p '.interpolated.txt' u 1:2 w l lt rgb '#357446', '' u 1:3 w l lt rgb 'red' lw 1.5, '.nodes.txt' u 1:2 w p lt rgb 'black'\" | gnuplot -p"); 
  printf("Plot completato con successo\n");
  // chiudo file, libero memoria
  free(xNodes);
  free(x);
  return 0;
}
