#include <stdio.h>
#include <stdlib.h>
#define N 5

void Add(int *A, int *B, int *C);
void Subtract(int *A, int *B, int *C);

int main()
{
	int i,*A,*B,*C;

	// Desmevo mnimi gia tous 3 pinakes.
	A = (int *)malloc(N*sizeof(int));
	B = (int *)malloc(N*sizeof(int));
	C = (int *)malloc(N*sizeof(int));

	// Gemizo ton pinaka A.
	printf("Dose tis times gia ton pinaka A:\n");
	for(i=0; i<N; i++)
	{
		printf("A[%d] = ", i);
		scanf("%d", A+i);
	}

	// Gemizo ton pinaka B.
	printf("Dose tis times gia ton pinaka B:\n");
	for(i=0; i<N; i++)
	{
		printf("B[%d] = ", i);
		scanf("%d", B+i);
	}

	// Prostheto tous pinakes A kai B, me ta apotelesmata
	// na kataxorountai ston pinaka C, poy ystera typonetai.
	Add(A,B,C);
	printf("Oi times tou pinaka C meta tin prosthesi einai:\n");
	for(i=0; i<N; i++) printf("C[%d] = %d\n", i,*(C+i));

	// Afairo tous pinakes A kai B, me ta apotelesmata na
	// kataxorountai ston pinaka C, poy ystera typonetai.
	Subtract(A,B,C);
	printf("Oi times tou pinaka C meta tin afairesi einai:\n");
	for(i=0; i<N; i++) printf("C[%d] = %d\n", i,*(C+i));

	return 0;
}

// Sunartisi pou athroizei duo pinakes kai
// kataxorei ta apotelesmata se allon pinaka.
void Add(int *A, int *B, int *C)
{
	int i;

	// Bazo kathe stoixeio tou C iso me to
	// athroisma ton 2 antistoixwn ton A,B.
	for(i=0; i<N; i++) *(C+i) = *(A+i) + *(B+i);

	return;
}

// Sunartisi pou afairei duo pinakes kai
// kataxorei ta apotelesmata se allon pinaka.
void Subtract(int *A, int *B, int *C)
{
	int i;

	// Bazo kathe stoixeio tou C iso me ti
	// diafora ton 2 antistoixwn ton A,B.
	for(i=0; i<N; i++) *(C+i) = *(A+i) - *(B+i);

	return;
}
