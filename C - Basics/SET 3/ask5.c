#include <stdio.h>
#include <stdlib.h>

int Diagonal(int *Array[], int Taksi);

int main()
{
	int i,j,Taksi;

	// Diavazo tin taksi tou tetragonikou pinaka.
	printf("Dose taksi tetragonikou pinaka: ");
	scanf("%d", &Taksi);

	// Dimiourgo ena monodiastato array me deiktes se
	// akeraious pou leitourgei san disdiastatos pinakas.
	int *Array[Taksi];

	// Desmevo mnimi gia tous parapano deiktes.
	for(i=0; i<Taksi; i++) Array[i] = (int *)malloc(Taksi*sizeof(int));

	// Gemizo ton disdiastato pinaka.
	for(i=0; i<Taksi; i++)
	{
		for(j=0; j<Taksi; j++)
		{
			printf("Array[%d][%d] = ", i,j);
			scanf("%d", Array[i]+j);
		}
	}

	// Emfanizo to athroisma tis diagoniou kalontas tin sunartisi Diagonal.
	printf("To athroisma tis diagoniou tou pinaka einai: %d\n", Diagonal(Array,Taksi));

	return 0;
}

// Sunartisi pou epistrefei to athroisma
// tis diagoniou enos tetragonikou pinaka.
int Diagonal(int *Array[], int Taksi)
{
	int i,Sum=0;

	// Prostheto ta stoixeia tis diagoniou.
	for(i=0; i<Taksi; i++)
	{
		Sum += Array[i][i];
	}

	return Sum;
}
