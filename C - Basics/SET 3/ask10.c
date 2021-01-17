#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RLE(char *String);

int main()
{
	char *String = (char *)malloc(256*sizeof(char));

	// Diavazo to arxiko string.
	printf("Give string to encode with RLE:\n");
	scanf("%s", String);

	// An periexei pano apo 1 xaraktira to kwdikopoio me RLE.
	if(strlen(String)>1) RLE(String);

	// Emfanizo to teliko string.
	printf("New string after RLE encoding:\n");
	printf("%s\n", String);

	return 0;
}

// Sunartisi pou kwdikopoiei ena string me RLE.
void RLE(char *String)
{
	char *New = (char *)malloc(256*sizeof(char));
	int i,j=0,Count=1,Temp;
	char Buffer;

	// Ksekinontas apo ton 2o xaraktira sugkrino
	// kathe xaraktira me ton proigoumeno tou gia
	// na do an diaferei. An den diaferei auksano
	// to Count kata 1. An diaferei grafo sto neo
	// string to Count (an einai pano apo 1) kai
	// meta ton xaraktira pou sunantisa Count fores.
	// Meta kano to Count 1 kai sunexizo.
	for(i=1; i<strlen(String); i++)
	{
		Buffer = String[i-1];

		if(Buffer==String[i]) Count++;
		else
		{
			if(Count>1)
			{
				Temp = strlen(New);
				sprintf(New+j, "%d", Count);
				j += (strlen(New) - Temp);
			}
			New[j] = Buffer;
			j++;

			Count = 1;
		}
	}

	// Grafo mia teleftaia fora sto neo string
	// afou tora tha exo stin Buffer ena xaraktira
	// pou den exo grapsei, me Count eite 1 eite
	// parapano.
	if(Count>1)
	{
		Temp = strlen(New);
		sprintf(New+j, "%d", Count);
		j += (strlen(New) - Temp);
	}
	New[j] = Buffer;

	// Antigrafo to neo string sto arxiko.
	strcpy(String,New);

	return;
}
