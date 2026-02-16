#include <stdio.h>

int main() {
	/* esistono diversi tipi di variabili:
	 * tipo    specificatore
	 * void    
	 * char    %c
	 * int     %d
	 * float   %f
	 * double  %f
	 */
	int x;
	char y;
	float z;
	double v;

	x = 34;
	y = 'c';
	z = 2.73;
	v = 3.333333;

	printf("X è una variabile intera: x=%d\n",x);
	printf("Y è una variabile char: y=%c\n", y);
	printf("Z è una variabile float: z=%f\n", z);
	printf("V è una variabile double: v=%f\n\n", v);
	
	//specifico il numero di cifre decimali da stampare
	printf("Il numero di Eulero è circa pari a %.2f\n", z);

	//se provo a stampare più decimali di quelli supportati dal tipo float sbarella:
	printf("ma guarda come sbarello se me ne chiedi di più: z=%.15f\n\n", z);

	float pi_float;
	double pi_double;

	pi_float = 3.14159265358979323846;
	pi_double = 3.14159265358979323846;

	printf("Pi in float vale %.20f\nmentre in double vale %.20f\n\n", pi_float, pi_double);
	
	// utilizzo la funzione sizeof per vedere la grandezza delle variabili (%lu)
	printf("Memoria occupata dalle variabili (in byte):\nx (int): %lu\ny (char) %lu\nz (float) %lu\nv (double) %lu\n\n", sizeof(x), sizeof(y), sizeof(z), sizeof(v));

	/* indirizzo di memoria: inizializzo una variabile e stampo l'indirizzo di memoria su cui è salvata
	 * l'indirizzo di memoria ha come specificatore %p (numero esadecimale)
	 */
	int numero_int = 8;
	printf("La variabile numero_int=%d è salvata all'indirizzo di memoria %p\n", numero_int, &numero_int);
	
	numero_int = 10;
	printf("La variabile numero_int=%d è salvata all'indirizzo di memoria %p\n", numero_int, &numero_int);
	
	// scanf, ovvero l'input da tastiera
	printf("Inserisci un numero intero: ");
	scanf("%d", &numero_int);
	printf("Il numero che hai scelto è %d\n", numero_int);

	return 0;
}
