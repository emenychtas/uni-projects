#include <stdio.h>

int i, X, X1=0, X2=1, X3;

int main()
{
	printf("Dose arithmo stoixeiwn: ");
	do{
		scanf("%d", &X);
	}while(X<=0);
	if (X>50) X = 50;
	// Elegxoume wste o arithmos na einai toulaxiston 1
	// kai an einai megaluteros tou 50 ton kanoume 50.

	printf("\n%d ", X1); // To prwto stoixeio panta tupwnetai.
	if (X>1) printf("%d ", X2); // Gia to deutero elegxoume.

	for(i=3; i<=X; i++) // Gia ta ypoloipa...
	{
		X3 = X1 + X2; // Ypologizoume to epomeno.
		X1 = X2; // Petame to prwto, sti thesi tou bazoume
		X2 = X3; // to deutero, sti thesi tou opoiou paei
		         // to trito, k.o.k...

		printf("%d ", X3); // Emfanizoume  to epomeno.
		if (i%5==0 && i!=X) printf("\n");
		// Kathe 5 arithmous allazoume kai grammi.
		// (To i!=X to evala gia na min afinei 2 grammes sto telos.)
	}

	printf("\n\n");

	return 0;
}
