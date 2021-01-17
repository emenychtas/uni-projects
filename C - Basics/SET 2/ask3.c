#include <stdio.h>

int i,j,x,N,P1=0,P2=0,P4=0;
float P3=1;

int main()
{
	printf("Dose akeraio megalutero tou 3: ");
	do{
		scanf("%d", &N);
	}while(N<=3);
	// Elegxoume o N na einai megaluteros tou 3.

	for(i=1; i<=N; i++) // Gia kathe arithmo apo to 1 mexri to N...
	{
		P1 += i; // Prosthetoume olous tous arithmous.
		if ((i%2)==1) P2 += i; // Mono tous perittous.
		P3 *= 1.0/i; // Vazoume ton aso san float wste
		             // na min xasoume ta dekadika.

		if (i==1) P4 += 1; // To 1 sti 0 to vazoume ksexwrista.
		else // Ta upoloipa...
		{
			x = i; // x einai o kathe oros, arxika isos me to i.
			for(j=1; j<=i-2; j++) // Gia i-2 fores...
			{
				x *= i; // ton pollaplasiazoume me to i...
			}
			P4 += x; // kai ton prosthetoume.
		}
	}

	printf("P1 = %d\n", P1);
	printf("P2 = %d\n", P2);
	printf("P3 = %f\n", P3);
	printf("P4 = %d\n", P4);

	return 0;
}
