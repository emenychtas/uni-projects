#include <stdio.h>

int i,m,b,Sum=0,Min=0,Max=0;
float Mesos;

int main()
{
	printf("Dose ton arithmo twn mathitwn: ");
	do{
		scanf("%d", &m);
	}while(m<1 || m>25);
	// Elegxoume wste o arithmos na einai apo 1 ews kai 25.

	for(i=1; i<=m; i++) // Gia kathe mathiti...
	{
		printf("Dose ton teliko bathmo tou mathiti %d: ", i);
		do{
			scanf("%d", &b);
		}while(b<1 || b>20);
		// Diabazoume ton bathmo tou kai elegxoume an einai sto apodekto euros.

		Sum += b; // Prosthetoume ton bathmo tou sto synoliko a8roisma.
		if (i==1) // An einai o prwtos bathmos pou diabazoume...
		{
			Min = b;
			Max = b;
		}
		else // An einai opoiosdhpote allos...
		{
			if (b<Min) Min = b;
			else if (b>Max) Max = b;
		}
	}

	Mesos = (float)Sum/m; // Type casting gia na min xasoume ta dekadika psifia.
	printf("Min: %d Max: %d Mesos: %.2f\n", Min,Max,Mesos);
	// Emfanizoume ta min kai max kai ton meso oro me akriveia 2 dekadikwn psifiwn.

	return 0;
}
