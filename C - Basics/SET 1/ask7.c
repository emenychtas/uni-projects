#include <stdio.h>

int Arithmos, Ek, Dek, Mon, Sum;

int main()
{
	printf("Dose enan akeraio 3 psifiwn:\n");
	do{
		scanf("%d", &Arithmos);
	}while(Arithmos>999 || Arithmos<100);
	// Elegxoume wste o arithmos na einai sigoura 3 psifiwn.

	printf("O arithmos %d apoteleitai apo:\n", Arithmos);

	Ek = Arithmos/100; // Briskoume tis ekatontades diairwntas me to 100.
	Dek = (Arithmos%100)/10; // Tis dekades diairwntas oti menei me to 10.
	Mon = (Arithmos%100)%10; // Kai sto telos apomenoun oi monades.
	Sum = Ek + Dek + Mon; // Prosthetoume ta 3 psifia gia to athroisma.

	printf("%d Ekatontades\n", Ek);
	printf("%d Dekades\n", Dek);
	printf("%d Monades\n", Mon);
	printf("To a8roisma twn psifiwn tou einai %d.\n", Sum);

	return 0;
}
