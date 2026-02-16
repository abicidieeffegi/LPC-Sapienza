#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INTEGRAL -0.122122604618968
#define MAX 10000
// DA FARE:
// plot errore

typedef enum {
  INT,
  CHAR,
  DOUBLE,
  FLOAT
} varType;

// funzione integranda
double f(double x) {
  return x*exp(-x)*cos(2*x);
}

// INPUT:   intervallo [a, b]
//          campioni M
// OUTPUT:  integrale numerico

// metodo dei rettangoli
double integrateRectangles(double a, double b, int M) {
  double result = 0.0;
  double h = (b-a)/M;
  for (int i=0; i<M; i++) {
    double xLeft = a + h*i;
    result += f(xLeft);
  }
  result *= h;

  return result;
}

// metodo del punto medio
double integrateMidPoint(double a, double b, int M) {
  double result = 0.0;
  double h = (b-a)/M;
  double xMid = a - h*0.5; // diminuisco a di mezza ampiezza così poi ogni step aggiungo h
  for (int i=0; i<M; i++) {
    xMid += h;
    result += f(xMid);
  }
  result *= h;

  return result;
}

// metodo dei trapezi
double integrateTrapeziums(double a, double b, int M) {
  double result = 0.0;
  double h = (b-a)/M;
  for (int i=0; i<M; i++) {
    double xLeft = a + h*i;
    double xRight = a + h*(i+1);
    result += f(xLeft) + f(xRight);
  }
  result *= 0.5*h;

  return result;
}

// metodo di Gauss (2 punti)
double integrateGauss(double a, double b, int M) {
  double result = 0.0;
  double h = (b-a)/M;
  for (int i=0; i<M; i++) {
    double gamma1 = (a + h*i) + (1 - 1/sqrt(3))*h*0.5;
    double gamma2 = (a + h*i) + (1 + 1/sqrt(3))*h*0.5;
    result += f(gamma1) + f(gamma2);
  }
  result *= 0.5*h;

  return result;
}

// metodo di Simpson
double integrateSimpson(double a, double b, int M) {
  double result = 0.0;
  double h = (b-a)/M;
  for (int i=0; i<M; i++) {
    double xLeft = a + h*i;
    double xRight = a + h*(i+1);
    double xMid = 0.5*(xLeft + xRight);
    result += f(xLeft) + 4*f(xMid) + f(xRight);
  }
  result *= h/6;

  return result;
}

// funzione che integra in base al metodo scelto
double integrateFunc(double a, double b, int M, int choice) {
  double (*integrate[])(double, double, int) = {
    &integrateRectangles,
    &integrateMidPoint,
    &integrateTrapeziums,
    &integrateGauss,
    &integrateSimpson
  };
  double result = integrate[choice](a, b, M);

  return result;
}

// funzione per prendere input da utente
// in realtà nell'esercizio non è richiesto
void getData(const char* str, void* ptr, varType tipo) {
  printf("%s", str);
  switch (tipo) {
    case INT:
      scanf("%d", (int*)ptr);      
      break;
    case CHAR:
      scanf("%c", (char*)ptr);      
      break;
    case DOUBLE:
      scanf("%lf", (double*)ptr);      
      break;
    case FLOAT:
      scanf("%f", (float*)ptr);      
      break;
  }
  return;
}

// funzion per controllare i pointer
void checkPtr(void* ptr) {
  if (ptr == NULL) {
    printf("NULL Pointer error\n");
    exit(1);
  }
  return;
}

void compareMethods(double a, double b) {
  char buffer[MAX];
  FILE* data = fopen("integrals.txt", "w");
  checkPtr((void*)data);
  int M, k=0;
  k += sprintf(buffer+k, "samples\tR\terrR\tEOCR\tM\terrM\tEOCM\tT\terrT\tEOCT\tG\terrG\tEOCG\tS\terrS\tEOCS\n");
  double integralResult;
  // questo è il punto che fa il lavoro:
  // vengono calcolati gli integrali, l'errore e l'EOC
  // tutti i dati vengono scritti in un buffer
  // che poi viene stampato su file
  double temp[5] = {1.0, 1.0, 1.0, 1.0, 1.0}; // serve per calcolare EOC
  for (int i=0; i<20; i++) {
    M = (int)pow(2, i+1);
    k += sprintf(buffer+k, "%d\t", M);
    // chiamo tutti i metodi di integrazione
    for (int j=0; j<5; j++) {
      integralResult = integrateFunc(a, b, M, j);
      // scrivo a mano a mano i risultati su file
      double error = fabs(integralResult - INTEGRAL);
      k += sprintf(buffer+k, "%.9lf\t%.9lf\t%.9lf\t", integralResult, error, -log(error/temp[j])/log(2));
      temp[j] = error;
    }
    k += sprintf(buffer+k, "\n");
  }
  fprintf(data, "%s", buffer);
  fclose(data);
  // svuoto il buffer e azzero il contatore
  sprintf(buffer, "");
  k=0;

  FILE* plot = fopen("integrals.gnp", "w");
  checkPtr((void*)plot);

  // PLOT SETTINGS
  // output settings
  k += sprintf(buffer+k, "set term pngcairo size 1600,1000\n");
  k += sprintf(buffer+k, "set output 'E0.png'\n");
  k += sprintf(buffer+k, "set multiplot layout 2,2 columns\n");
  // plotto la funzione integranda
  k += sprintf(buffer+k, "set title 'Funzione integranda'\n");
  k += sprintf(buffer+k, "set xrange[0:%lf]\n", M_PI);
  k += sprintf(buffer+k, "p x*exp(-x)*cos(2*x) w l t 'f(x)'\n");
  // plotto i risultati dei vari metodi al variare del numero di intervalli
  k += sprintf(buffer+k, "set title 'Integrali numerici con diversi metodi'\n");
  k += sprintf(buffer+k, "set xrange[0:%d]\n", (int)pow(2,20));
  k += sprintf(buffer+k, "set logscale x\n");
  k += sprintf(buffer+k, "p 'integrals.txt' u :(column('R')) w l t 'Rettangoli', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('M')) w l t 'MidPoint', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('T')) w l t 'Trapezi', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('G')) w l t 'Gauss', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('S')) w l t 'Simpson'\n");
  // plotto gli errori dei diversi metodi di integrazione
  k += sprintf(buffer+k, "set title 'Errori di integrali numerici con diversi metodi'\n");
  k += sprintf(buffer+k, "set logscale y\n");
  k += sprintf(buffer+k, "p 'integrals.txt' u (column('samples')):(column('errR')) w l t 'Errore Rettangoli', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('errM')) w l t 'Errore MidPoint', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('errT')) w l t 'Errore Trapezi', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('errG')) w l t 'Errore Gauss', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('errS')) w l t 'Errore Simpson'\n");
  k += sprintf(buffer+k, "unset logscale y\n");
  // plotto l'EOC dei vari metodi
  // NB: dopo una certa gauss e simpson superano la precisione della macchina
  // e l'EOC inizia a sbarellare
  k += sprintf(buffer+k, "set title 'EOC di diversi metodi'\n");
  k += sprintf(buffer+k, "p 'integrals.txt' u :(column('EOCR')) w l t 'Rettangoli', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('EOCM')) w l t 'MidPoint', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('EOCT')) w l t 'Trapezi', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('EOCG')) w l t 'Gauss', ");
  k += sprintf(buffer+k, "'' u (column('samples')):(column('EOCS')) w l t 'Simpson'\n");
  k += sprintf(buffer+k, "unset multiplot\n");
  fprintf(plot, "%s", buffer);
  fclose(plot);

  // plottiamo ed apriamo l'immagine
  system("gnuplot -p integrals.gnp && xdg-open E0.png &");
}


int main() {
  double a = 0;
  double b = 2*M_PI;
  int choice;
  printf("Metodi disponibili:\n1. Rettangoli\n2. Punto medio\n3. Trapezi\n4. Gauss (2 punti)\n5. Simpson\n6. Confrontare metodi\n");
  getData("Inserire opzione disponibile (1-6): ", &choice, INT);
  choice--;

  double integralResult;
  int M;
  if (choice == 5) {
    compareMethods(a, b);
  }
  else {
    getData("Inserire numero intervalli: ", &M, INT);
    integralResult = integrateFunc(a, b, M, choice);
    printf("Il risultato dell'integrale è:\n%.10lf\n", integralResult);
  }
  // p 'integrals.txt' u :(column("Rettangoli")) w l t "Rettangoli"
  return 0;
}
