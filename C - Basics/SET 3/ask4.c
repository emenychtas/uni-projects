#include <stdio.h>

int MisthoiMax(int Misthoi[]);
float MisthoiMO(int Misthoi[]);

int main()
{
	int i,Misthoi[10];

	// Diavazo tous 10 misthous.
	printf("Dose tous misthous ton 10 upallilon:\n");
	for(i=0; i<10; i++)
	{
		printf("Misthos #%d = ", i+1);
		scanf("%d", &(Misthoi[i]));
	}

	// Emfanizo ta zitoumena.
	printf("O megaluteros misthos einai o misthos %d.\n", MisthoiMax(Misthoi)+1);
	printf("O mesos oros misthodosias einai %.3f.\n", MisthoiMO(Misthoi));

	return 0;
}

// Sunartisi pou epistrefei to index tou megaluterou misthou.
int MisthoiMax(int Misthoi[])
{
	int i,Max,MaxMisthos;

	// Orizo san megalutero ton proto.
	Max = 0;
	MaxMisthos = Misthoi[0];

	// Elegxo tous upoloipous gia na bro ton pragmatiko megalutero.
	for(i=1; i<10; i++)
	{
		if(Misthoi[i]>MaxMisthos)
		{
			Max = i;
			MaxMisthos = Misthoi[i];
		}
	}

	// Epistrefo to index tou megaluterou.
	return Max;
}

// Sunartisi pou epistrefei ton meso oro misthodosias.
float MisthoiMO(int Misthoi[])
{
	int i,Sum=0;

	// Prostheto olous tous misthous.
	for(i=0; i<10; i++) Sum += Misthoi[i];

	// Epistrefo se float to piliko tis diairesis tou athrismatos me to plithos.
	return (float)Sum/10;
}
