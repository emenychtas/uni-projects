#include <stdio.h>
#define N 20

void PrintArray(int Array[]);

int main()
{
	int i,Pinakas[N];

	// Gemizo ton pinaka.
	for(i=0; i<N; i++) Pinakas[i] = i;

	PrintArray(Pinakas);

	return 0;
}

void PrintArray(int Array[])
{
	int i,j,Temp;

	// Typono ton arxiko pinaka.
	printf("Original Array:");
	for(i=0; i<N; i++)
	{
		printf(" %d", Array[i]);
	}
	printf("\n");

	// j: To index mexri kai to opoio tha antimetatethei
	// me to summetriko tou os pros to kentro tou pinaka.
	if(N%2==1) j = N/2; // Gia Monous. (stroggulopoieitai)
	else j = (N/2)-1;   // Gia Zugous.

	// Antimetatheto stoixeia tou pinaka.
	for(i=0; i<=j; i++)
	{
		Temp = Array[i];
		Array[i] = Array[(N-1)-i];
		Array[(N-1)-i] = Temp;
	}

	// Typono ton antestrammeno pinaka.
	printf("Inverted Array:");
        for(i=0; i<N; i++)
        {
                printf(" %d", Array[i]);
        }
	printf("\n");

	return;
}
