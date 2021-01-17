#include <stdio.h>

int x, km, m, cm;

int main()
{
	printf("Insert centimeters: ");
	scanf("%d", &x);

	km = x/100000; // Diairoume ta ekatosta me ena xiliometro.
	m = (x-km*100000)/100; // Diairoume oti emeine me ena metro.
	cm = x-km*100000-m*100; // Kai sto telos menoun ta ekatosta.

	printf("\nThe %d centimeters are:\n\n", x);
	printf("%d kilometers, %d meters, %d centimeters\n", km, m, cm);

	return 0;
}
