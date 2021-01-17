#include <stdio.h>

int x, NotOrdered=1;

int main()
{
	printf("Exete tis akolouthes 3 epiloges:\n");
	printf("1. Prwino\n");
	printf("2. Meshmeriano\n");
	printf("3. Vradino\n");
	printf("Parakaloume plhktrologhste 1, 2, h 3:\n");

	while(NotOrdered==1) // Mexri na dothei enas apo tous 3 arithmous.
	{
		scanf("%d", &x);
		NotOrdered = 0;
		switch (x)
		{
			case 1:
				printf("Paraggeilate Prwino.\n");
				break;
			case 2:
				printf("Paraggeilate Meshmeriano.\n");
				break;
			case 3:
				printf("Paraggeilate Vradino.\n");
				break;
			default:
				printf("Mh egkyrh epilogh. Plhktrologhste ksana:\n");
				NotOrdered = 1;
		}
	}

	return 0;
}
