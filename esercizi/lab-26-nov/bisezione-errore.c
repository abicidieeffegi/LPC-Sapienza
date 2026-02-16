#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// salvare su array stima della radice x_n ed errore stimato e_n
// verificare che la tolleranza è raggiunta all'iterazione n stimata
// salvare iterazione, x_n, e_n, p_n (velocità sperimentale di convergenza)
// generare grafici con gnuplot

// funzione di cui trovare radice
double f(double x) {
  return x*x - 2;
}

// derivata numerica di f
double df(double x) {
  double step = 1e-6; 
  return (f(x+step) - f(x))/step;
}

// funzione da usare per il punto fisso
double g(double x) {
  double lambda = -1e-1;
  return x + lambda*f(x);
}

// metodo di bisezione
int bisezione(double a, double b, double tol, int iterMax, double* x, double* err){
  printf("Metodo di bisezione chiamato correttamente\n");
  for (int i=0; i<iterMax; i++) {
    x[i] = (a+b)*0.5;
    // controllo i criteri di arresto
    err[i] = fabs(b-a)*0.5;
    if (err[i] < tol) {
      printf("Soluzione trovata per errore dopo %d iterazioni.\n", i++);
      return i;
    }
    if (fabs(f(x[i])) < tol) {
      printf("Soluzione trovata per residuo dopo %d iterazioni\n", i++);
      return i;
    }
    // altrimenti continuo
    if (f(a) * f(x[i]) < 0)
      b = x[i];
    else 
      a = x[i];
  }
  printf("Numero massimo di iterazioni raggiunto.\n");
  return iterMax;
}

// punto fisso
// si noti che b è un placeholder per tenere la funzione nell'array (cfr risolviEquazioni())
int puntoFisso(double xzero, double b, double tol, int iterMax, double* x, double* err) {
  printf("Metodo del punto fisso chiamato correttamente\n");
  x[0] = g(xzero);
  err[0] = x[0];
  for (int i=1; i<iterMax; i++) {
    x[i] = g(x[i-1]);
    // considero come "errore" la distanza tra iterate
    err[i] = x[i] - x[i-1];
    // controllo i criteri di arresto
    if (err[i] < tol) {
      printf("Soluzione trovata per errore dopo %d iterazioni.\n", i++);
      return i;
    }
    if (fabs(f(x[i])) < tol) {
      printf("Soluzione trovata per residuo dopo %d iterazioni\n", i++);
      return i;
    }
    // altrimenti continuo
  }
  printf("Numero massimo di iterazioni raggiunto.\n");
  return iterMax;

}

// newton con warm-start
int newton(double a, double b, double tol, int iterMax, double* x, double* err) {
  // ritorna numero di iterazioni necessario
  printf("Metodo di Newton con warm-start chiamato correttamente\n");
  // chiamo il warm-start (3 iter di bisezione)
  bisezione(a, b, tol, 3, x, err);
  for (int i=3; i<iterMax; i++) {
    x[i] = x[i-1] - (f(x[i-1])/df(x[i-1]));
    // considero come "errore" la distanza tra iterate
    err[i] = x[i] - x[i-1];
    // controllo i criteri di arresto
    if (err[i] < tol) {
      printf("Soluzione trovata per errore dopo %d iterazioni.\n", i++);
      return i;
    }
    if (fabs(f(x[i])) < tol) {
      printf("Soluzione trovata per residuo dopo %d iterazioni\n", i++);
      return i;
    }
    // altrimenti continuo
  }
}

// funzione per scrivere su file
void scriviDati(double* x, double* err, double* eoc, int size, FILE* dump) {
  for (int i=0; i<size; i++) {
    fprintf(dump, "%lf\t%lf\t%lf\n", x[i], err[i], eoc[i]);
  }
  fflush(dump);
  return;
}

// funzione per calcolare EOC
void calcolaEOC(double* eoc, double* err, int size) {
  size--;
  for (int i=1; i<size; i++) {
    eoc[i] = log(err[i+1]/err[i])/log(err[i]/err[i-1]);
  }
  return;
}

// controlla l'esistenza degli zeri e chiama il metodo scelto
int risolviEquazioni(double a, double b, int choice, double tol, int iterMax, double* x, double* err) {
  if (f(a) * f(b) > 0){
    printf("Errore. Radici non trovate nell'intervallo desiderato\n");
    return 0;
  }
  choice--;
  int (*risolvi[])(double, double, double, int, double*, double*) = {&bisezione, &puntoFisso, &newton};
  
  // chiamo il metodo scelto dall'utente
  return risolvi[choice](a, b, tol, iterMax, x, err);
}

// questa mostra le opzioni disponibili 
void welcomeMessage(double* a, double* b, int* choice, double* tol, int* iterMax) {
  printf("---------------------------------------\n");
  printf("| Risolutore di equazioni non lineari |\n");
  printf("---------------------------------------\n");
  printf("Opzioni disponibili:\n1. Metodo di bisezione\n2. Metodo del punto fisso\n3. Metodo di Newton\n");
  do {
    printf("Inserire opzione desiderata (1-3): ");
    scanf("%d", choice);
  } while (*choice < 1 || *choice > 3);
  printf("Inserire [a,b] in cui cercare soluzioni: ");
  scanf("%lf %lf", a, b);
  printf("Inserire tolleranza: ");
  scanf("%lf", tol);
  printf("Inserire iterazioni massime: ");
  scanf("%d", iterMax);
}

void checkallocazione(void* ptr) {
  if (ptr == NULL) {
    perror("Errore di allocazione");
    exit(1);
  }
}


//--------------//
//-----MAIN-----//
//--------------//

int main() {
  double a, b, tol, *x, *err, *eoc;
  int choice, iterMax;

  welcomeMessage(&a, &b, &choice, &tol, &iterMax);
  
  x = malloc(iterMax * sizeof(*x));
  err = malloc(iterMax * sizeof(*err));
  checkallocazione((void*)x);
  checkallocazione((void*)err);

  // risolvo l'equazione
  int iterNecessarie = risolviEquazioni(a, b, choice, tol, iterMax, x, err);
  eoc = calloc(iterNecessarie, sizeof(*eoc));
  checkallocazione((void*)eoc);
  printf("La soluzione trovata vale %lf\n", x[iterNecessarie-1]);

  // calcolo eoc
  calcolaEOC(eoc, err, iterNecessarie);

  // scrivo dati su file
  FILE* dump = fopen("equazione.txt", "w");
  checkallocazione((void*)dump);
  scriviDati(x, err, eoc, iterNecessarie, dump);
  fclose(dump);

  printf("Elaborazioni grafici in corso\n");
  // plotto tutto
  // Generare due grafici con gnuplot:
  // 1. x_n vs iterazione,
  // 2. grafico in scala log su asse y e_n vs iterazione,
  // 3. p_n vs iterazione.
  FILE* plotErr = fopen("err.gnp", "w");
  fprintf(plotErr, "set logscale y\n");
  fprintf(plotErr, "set xlabel 'iter'\n");
  fprintf(plotErr, "set ylabel 'errore'\n");
  fprintf(plotErr, "set terminal pngcairo size 900,600\n");
  fprintf(plotErr, "set output 'errore.png'\n");
  fprintf(plotErr, "plot 'equazione.txt' using :2 with lines title 'Errore' lt rgb 'red'\n");
  fprintf(plotErr, "set output\n");
  fprintf(plotErr, "exit\n");
  fclose(plotErr);

  FILE* plotEOC = fopen("eoc.gnp", "w");
  fprintf(plotEOC, "set xlabel 'iter'\n");
  fprintf(plotEOC, "set ylabel 'EOC'\n");
  fprintf(plotErr, "set terminal pngcairo size 900,600\n");
  fprintf(plotErr, "set output 'eoc.png'\n");
  fprintf(plotEOC, "plot 'equazione.txt' using :3 with lines title 'EOC' lt rgb 'blue'\n");
  fprintf(plotErr, "set output\n");
  fprintf(plotErr, "exit\n");
  fclose(plotEOC);

  FILE* plotSol = fopen("sol.gnp", "w");
  fprintf(plotSol, "set xlabel 'iter'\n");
  fprintf(plotSol, "set ylabel 'x_n'\n");
  fprintf(plotErr, "set terminal pngcairo size 900,600\n");
  fprintf(plotErr, "set output 'soluzione.png'\n");
  fprintf(plotSol, "plot 'equazione.txt' using :1 with lines title 'Soluzione' lt rgb 'green'\n");
  fprintf(plotErr, "set output\n");
  fprintf(plotErr, "exit\n");
  fclose(plotSol);

  // libero memoria
  free(x); free(err); free(eoc);

  // esporto immagini con system
  system("gnuplot sol.gnp");
  system("gnuplot err.gnp");
  system("gnuplot eoc.gnp");
  printf("Grafici esportati correttamente\n");

  return 0;
}
