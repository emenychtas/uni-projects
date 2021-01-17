#include <stdio.h>

int i,j,N;

int main()
{
	while(1) // Mexri na bgoume xeirokinita me break...
	{
		do{
			printf("Dose mono ari8mo megalutero h iso tou 5: ");
			scanf("%d", &N);
			if (N==0) break; // An dothei to 0 termatizoume tin do...while.
			if (N%2!=1) printf("Den einai monos.\n");
			if (N<5) printf("Den einai megaluteros h isos tou 5.\n");
		}while(N<5 || N%2!=1);

		if (N==0) break; // Kai episis termatizoume tin while kai ara to programma.

		printf("\n");

		for(i=1; i<=N; i++) // TRIGWNO 1
		{
			for(j=1; j<=i; j++) printf("*");
			printf("\n");
		}

		printf("\n");

		for(i=N; i>=1; i--) // TRIGWNO 2
		{
			for(j=1; j<=N-i; j++) printf(" ");
			for(j=1; j<=i; j++) printf("*");
			printf("\n");
		}

		printf("\n");

		for(i=1; i<=N; i++) // TETRAGWNO
		{
			for(j=1; j<=N; j++)
			{
				printf("*");
			}
			printf("\n");
		}

		printf("\n");

		for(i=1; i<=N; i++) // Z
		{
			if (i==1 || i==N) for(j=1; j<=N; j++) printf("*");
			else
			{
				for(j=1; j<=N-i; j++) printf(" ");
				printf("*");
			}
			printf("\n");
		}
	}

	return 0;
}
