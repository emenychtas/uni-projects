#include <stdio.h>

float Poso,Epitokio,Tokos;
int i,Eth;

int main()
{
	printf("Dose arxiko poso: ");
	scanf("%f", &Poso);
	printf("Dose epitokio: ");
	scanf("%f", &Epitokio);
	printf("Dose ari8mo etwn: ");
	scanf("%d", &Eth);

	for(i=1; i<=Eth; i++) // Gia kathe etos...
	{
		Tokos = Poso * Epitokio / 100;
		Poso += Tokos;

		// O tokos kai to kefalaio emfanizontai me akriveia 2 dekadikwn.
		printf("Meta to etos %d, o tokos einai %.2f kai to neo kefalaio einai %.2f.\n", 
i,Tokos,Poso);
	}

	return 0;
}
