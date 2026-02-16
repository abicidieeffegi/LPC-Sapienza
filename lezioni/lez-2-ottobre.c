#include <stdio.h>
#include <math.h>
/* include funzioni matematiche come per esempio
 * sqrt(x)
 * pow(x, n)
 * fabs(x)
 * sin(x), cos(x), tan(x)
 * log(x), log10(x)
 * ceil(x), floor(x)
 */
#define PI 3.14159

int main() {
	/*
	//Dichiaro alcune variabili
	int x;
	float y;
	double z;
	char c;

	printf("Dammi un intero: ");
	scanf("%d", &x);

	printf("Dammi un float: ");
	scanf("%f", &y);

	printf("Dammi un double: ");
	scanf("%lf", &z); // nel dubbio usa sempre %lf come specificatore di formato per i double

	printf("Dammi un carattere: ");
	scanf(" %c", &c); // qua ci va lo spazio se no prende l'invio del comando sopra come carattere

	printf("L'utente ha inserito un intero (%d), un float (%f), un double (%lf), e un carattere (%c)\n", x, y, z, c);

	printf("Pi è approssimativamente uguale a %f\n", PI);
	*/

	/* operazioni matematiche 
	 * + addizione
	 * - sottrazione 
	 * * moltiplicazione
	 * / divisione
	 * % modulo 
	 * ++ incremento (++x equivale a x = x + 1)
	 * -- decremento (--x equivale a x = x - 1)
	 */
	
	/*
	// calcolo l'area di un rettangolo
	float base, altezza;
	printf("Inserire la base:\nb = ");
	scanf("%f", &base);
	printf("Inserire l'altezza:\nh = ");
	scanf("%f", &altezza);
	// float area = base * altezza;
	printf("L'area del rettangolo è %f\n", base*altezza);
	*/

	/*
	// calcolo la base di un rettangolo 
	double base;
	int area altezza;
	printf("Inserire l'area:\nb = ");
	scanf("%f", &area);
	printf("Inserire l'altezza:\nh = ");
	scanf("%f", &altezza);
	base = (double)area/altezza; // faccio un'operazione di cast
	printf("La base del rettangolo è %f\n", base);
	*/

	//calcolo l'area del cerchio
	float raggio;
	printf("Calcolatore dell'area del cerchio online (facile e veloce, 100% garantito)\n");
	printf("Inserire il valore del raggio:\nr = ");
	scanf("%f", &raggio);
	float area = PI * pow(raggio, 2);
	printf("L'area del cerchio di raggio %f vale %f\n", raggio, area);
	return 0;
}
