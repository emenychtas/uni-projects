#include <stdio.h>
#include <string.h>
#define N 5

// Sunartisi sugkrisis gia tin qsort.
int Compare(const void *a, const void *b)
{
	const char (*p1)[256] = a;
	const char (*p2)[256] = b;

	if(strlen(*p1)<strlen(*p2)) return -1;
	else if(strlen(*p1)>strlen(*p2)) return 1;
	else return 0;
}

int main()
{
	int i;
	char Strings[N][256];

	// Diavazo ta strings.
	printf("Enter %d strings (256 characters max):\n", N);
	for(i=0; i<N; i++)
	{
		printf("Strings[%d] = ", i);
		gets(Strings[i]);
	}

	// Orizo san mikrotero to proto.
	int MinString = 0;
	int MinLength = strlen(Strings[0]);

	// Elegxo ta upoloipa kai brisko to pragmatiko mikrotero.
	for(i=1; i<N; i++)
	{
		if(strlen(Strings[i])<MinLength)
		{
			MinString = i;
			MinLength = strlen(Strings[i]);
		}
	}

	// Emfanizo to mikrotero.
	printf("The shortest string is Strings[%d].\n", MinString);

	qsort(Strings, N, 256*sizeof(char), Compare);

	// Emfanizo ta strings taksinomimena se auksousa seira.
	printf("The strings after sorting (ascending):\n");
	for(i=0; i<N; i++)
	{
		printf("Strings[%d] = %s\n", i,Strings[i]);
	}

	return 0;
}
