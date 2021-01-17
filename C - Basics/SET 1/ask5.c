#include <stdio.h>

float diagwnisma, ergasia, askisi, bathmos;

int main()
{
	printf("Dose to bathmo tou diagwnismatos: ");
	scanf("%f", &diagwnisma);
	printf("Dose to bathmo tis ergasias: ");
	scanf("%f", &ergasia);
	printf("Dose to bathmo tis askisis: ");
	scanf("%f", &askisi);

	bathmos = diagwnisma * 0.5 + ergasia * 0.3 + askisi * 0.2;
	printf("Telikos bathmos: %.2f\n", bathmos);
	// Ypologismos kai emfanhsh telikou bathmou me akribeia 2 dekadikwn.

	if (bathmos > 50) printf("Perasate to mathima!\n");
	else printf("Den perasate to mathima!\n");

	return 0;
}
