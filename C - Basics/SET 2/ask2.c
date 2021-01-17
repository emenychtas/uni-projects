#include <stdio.h>

int N,D1,D2,D3,D4,Count,Done;

int main()
{
	printf("Give N:\n");
	do{
		scanf("%d", &N);
	}while(N<4);
	// Elegxoume o N na einai megaluteros i isos tou 4.

	printf("Combinations of 4 on set [1...%d]:\n", N);

	D1 = 1; // Ta 4 stoixeia twn sundiasmwn, arithmimena
	D2 = 2; // apo to 1 mexri to 4 ksekinontas apo ta
	D3 = 3; // aristera kai pigainontas pros ta deksia.
	D4 = 4;
	Done = 0; // Boolean gia ton elegxo tis while.
	Count = 1; // Arithmisi sundiasmwn.

	while (Done==0)
	{
		printf("%d: %d,%d,%d,%d\n", Count,D1,D2,D3,D4);
		Count++;

		if (D4<N) D4++;
		else if (D3<D4-1)
		{
			D3++;
			D4 = D3 + 1;
		}
		else if (D2<D3-1)
		{
			D2++;
			D3 = D2 + 1;
			D4 = D2 + 2;
		}
		else if (D1<D2-1)
		{
			D1++;
			D2 = D1 + 1;
			D3 = D1 + 2;
			D4 = D1 + 3;
		}
		else Done = 1;
	}
	// Ypologizw ta 4 stoixeia kathe fora
	// sumfwna me ti diadikasia tou paradeigmatos.

	return 0;
}
