#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char Colors[6] = { 'R','B','G','Y','P','W' };

char* RandomCode(int CodeLen);
int RandomInt(int Low, int High);

int main()
{
	int i,j,CodeLen,GuessLen,Tries=0,Won=0,Surrendered=0;

	// Diavazo to mikos tou krufou kwdikou mexri na anoikei sto [1,100].
	do{
		printf("Please define secret code length: ");
		scanf("%d", &CodeLen);
		if(CodeLen<1 || CodeLen>100) printf("Secret code length must belong to [1,100].\n");
	}while(CodeLen<1 || CodeLen>100);

	// Dimiourgo ton krufo kwdiko, kai desmevo mnimi gia to string sto
	// opoio tha apothikeuontai oi sundiasmoi pou tha dokimazei o paiktis.
	char *Code = RandomCode(CodeLen);
	char *Guess = (char *)malloc(256*sizeof(char));

	// Mexri na kerdisei i na paradothei o paiktis.
	// Kathe epanalipsi einai mia prospatheia.
	while(Won==0 && Surrendered==0)
	{
		Tries++;

		// Diavazo tin prospatheia tou paikti.
		printf("Try %d: ", Tries);
		scanf("%s", Guess);

		// Elegxo an paradinetai i oxi.
		if(!strcmp(Guess,"SURRENDER")) Surrendered = 1;
		else
		{
			// Elegxo an edose perissotera i ligotera xromata.
			GuessLen = strlen(Guess);
			if(GuessLen!=CodeLen)
			{
				printf("Code sequence has to be exactly %d colors.\n", CodeLen);
				Tries--;
			}
			else
			{
				// Elegxo an edose mi egkura xromata.
				int ValidCount = 0;
				for(i=0; i<GuessLen; i++)
				{
					for(j=0; j<6; j++) if(Guess[i]==Colors[j]) ValidCount++;
				}
				if(ValidCount!=GuessLen)
				{
					printf("Error sequence, please try again.\n");
					Tries--;
				}
				else
				{
					// Egkuri prospatheia, aksiologo loipon.
					// CNP: Xroma kai thesi sosta.
					// CO: Mono xroma sosto.
					int CNP=0,CO=0;

					// Dimiourgo antigrafa tou kwdikou kai tis prospatheias
					// oste na ta epeksergasto kai na aksiologiso sosta.
					char GuessCopy[GuessLen],CodeCopy[CodeLen];
					strcpy(GuessCopy, Guess);
					strcpy(CodeCopy, Code);

					// Elegxos gia ta CNP.
					for(i=0; i<GuessLen; i++)
					{
						if(GuessCopy[i]==CodeCopy[i])
						{
							GuessCopy[i]='X';
							CodeCopy[i]='X';
							CNP++;
						}
					}
					// Elegxos gia ta CO.
					for(i=0; i<GuessLen; i++)
					{
						if(GuessCopy[i]!='X')
						{
							for(j=0; j<CodeLen; j++)
							{
								if(GuessCopy[i]==CodeCopy[j])
								{
									GuessCopy[i]='X';
									CodeCopy[j]='X';
									CO++;

									j = CodeLen;
								}
							}
						}
					}

					// Emfanisi aksiologisis.
					printf("  Color and position correct: %d\n", CNP);
					printf("  Only color correct:         %d\n", CO);

					// Elegxos nikis.
					if(CNP==GuessLen) Won = 1;
				}
			}
		}
	}

	// Emfanizo to analogo minima sumfona me to an kerdise i paradothike o paiktis.
	if(Surrendered==1) printf("You have lost the game. The secret code was %s.\n", Code);
	else if(Won==1) printf("Congratulations! You have won the game after %d tries.\n", Tries);

	return 0;
}


// Sunartisi pou dimiourgei krufo kwdiko
// mikous CodeLen me ti xrisi tis RandomInt.
char* RandomCode(int CodeLen)
{
	int i;
	// Desmevo mnimi gia ton kwdiko.
	char *Code = (char *)malloc(CodeLen*sizeof(char));
	// Dino ena ksexoristo seed sti rand
	// gia tin paragogi tuxaion arithmon.
	srand((int)time(NULL));
	// Parago ena ena ta xromata gia ton kwdiko.
	for(i=0; i<CodeLen; i++) Code[i] = Colors[RandomInt(0,5)];
	// Epistrefo ton kwdiko.
	return Code;
}

// Sunartisi gia paragogi tuxaion arithmon
// pou akolouthoun tin kanoniki katanomi.
// (DINETAI STHN EKFWNHSH)
int RandomInt(int Low, int High)
{
	int k;
	double d;

	d = (double)rand() / ((double)RAND_MAX + 1);
	k = (int)(d * (High - Low + 1));

	return (Low + k);
}
