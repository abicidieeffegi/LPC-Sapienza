#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// aritmetica finita

void armonicaForward(long long int N, float* result) {
  *result = 0.0f;  
  for (long long int i=1; i<=N; i++) {
    *result += 1.0f/i;
  }
}

void armonicaBackward(long long int N, float* result) {
  *result = 0.0f;  
  for (long long int i=N; i>=1; i--) {
    *result += 1.0f/i;
  }
}

void lineBreak() {
  printf("------------------------------\n");
  return;
}

int main() {

  // ERRORE DI RAPPRESENTAZIONE
  float xFloat = 0.1f; // la f è per forzare il compilatore a trattare il numero come float
  // e non convertirlo in double
  double xDouble = 0.1;

  printf("0.1 in float: %.17f\n", xFloat);
  printf("0.1 in double: %.17lf\n", xDouble);
  // in un computer è impossibile rappresentare correttamente 0.1
  // analogamente a come in base 10 non si può rappresentare 1/3
  // con un numero finito di cifre.
  
  double epsilon = 1.0;
  // il seguente dovrebbe essere un ciclo infinito ma il computatore 
  // a un certo punto approssima epsilon=0
  while (1.0 + epsilon/2 > 1) {
    epsilon /= 2;
  }
  printf("epsilon (precisione della macchina) = %.17e\n", epsilon);
  // quanto la precisione della macchina viene raggiunta,
  // il computer aggiunge zero cifre significative a 1
  lineBreak();

  // CANCELLAZIONE NUMERICA
  double a = 1000000000000000.0;
  double b = 1000000000000000.1;
  double diffTeorica = 0.1;
  double diffCalcolata = b-a;
  printf("a = %.17lf\n", a);
  printf("b = %.17lf\n", b);
  printf("b-a = %.17lf\tteoricamente\n", diffTeorica);
  printf("b-a = %.17lf\tcalcolata\n", diffCalcolata);
  // non si può controllare con esattezza valori double
  if (diffTeorica == diffCalcolata)
    printf("Differenza calcolata esatta!\n");
  else 
    printf("Differenza calcolata non esatta!\n");
  // bisogna controllare in precisione (con una tolleranza)
  for(int i=1; i<6; i++) {
    if (fabs(diffTeorica - diffCalcolata) < pow(10, -i))
      printf("La differenza calcolata è in tolleranza 1e-%d\n", i);
    else {
      printf("La differenza calcolata NON è in tolleranza 1e-%d\n", i);
      break;
    }
  }
  lineBreak();

  // OVERFLOW / UNDERFLOW
  double veryBig = pow(10,400);
  double verySmall = pow(10, -400);
  printf("Overflow: %lf\n", veryBig);
  printf("Underflow: %lf\n", verySmall);

  // PROPAGAZIONE DELL'ERRORE
  float sommaAvanti, sommaIndietro;
  long long int N = 1e8;

  armonicaForward(N, &sommaAvanti);
  // la somma all'indietro è numericamente più stabile:
  // evito la cancellazione numerica aggiungendo prima i numeri piccoli
  armonicaBackward(N, &sommaIndietro);
  // verifico che la somma all'indietro sia numericamente più stabile 
  // calcolando la stima teorica della somma
  double gammaE = 0.5772156649;
  double stimaTeorica = log(N) + gammaE;
  printf("Somma in avanti dell'armonica: %.17f\n", sommaAvanti);
  printf("Somma all'indietro dell'armonica: %.17f\n", sommaIndietro);
  printf("La stima teorica vale: %.17lf\n", stimaTeorica);
  lineBreak();

  // LIMITE NOTEVOLE
  // lim x->0 (1-cos(x))/x^2 = 1/2
  double x = 1e-1;
  printf("Calcolo instabile del limite notevole\n");
  
  printf("X\t\tlim\t\terrAbs\t\terrRel\n");
  for (int i=0; i<12; i++) {
    double limit = (1.0-cos(x))/pow(x, 2);
    double erroreAbs = fabs(limit - 0.5);
    double erroreRel = fabs((limit - 0.5)/0.5);
    printf("%.6e\t%.6lf\t%.6e\t%.6e\n", x, limit, erroreAbs, erroreRel);
    x = x/10;
  }
  
  printf("Calcolo stabile del limite notevole\n");
  
  printf("X\t\tlim\t\terrAbs\t\terrRel\n");
  for (int i=0; i<12; i++) {
    double limit = pow(sin(0.5*x), 2)/(2*pow(0.5*x, 2));
    double erroreAbs = fabs(limit - 0.5);
    double erroreRel = fabs((limit - 0.5)/0.5);
    printf("%.6e\t%.6lf\t%.6e\t%.6e\n", x, limit, erroreAbs, erroreRel);
    x = x/10;
  }
  lineBreak();

  // SERIE DI LEIBNIZ
  double *leibniz;
  FILE* dump = fopen(".leibniz.txt", "w");
  if (dump == NULL) {
    perror("Errore apertura file");
    return 1;
  }
  N = 20;
  leibniz = malloc(20 * sizeof(*leibniz));
  if (leibniz == NULL) {
    perror("Errore di allocazione");
    return 1;
  }
  leibniz[0] = 4;
  fprintf(dump, "%lf", leibniz[0]);
  for (int i=1; i<N; i++) {
    leibniz[i] = leibniz[i-1] + 4*pow(-1, i)/(2*i + 1);
    fprintf(dump, "%lf\n", leibniz[i]);
  }
  fclose(dump);

  // plotto e cancello il file
  system("echo \"plot '.leibniz.txt' using :1 with lines lt rgb 'green', pi\" | gnuplot -p");
  system("rm .leibniz.txt");

  free(leibniz);
  
  return 0;
}
