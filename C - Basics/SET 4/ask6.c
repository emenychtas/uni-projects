#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// To struct pou tha xrisimopoio
// gia tis lekseis sto paixnidi.
typedef struct Word {
	char *String;
	int *OpenLetters;
	int OpenLettersCount;
} Word;

int LoadWords(Word **WordList);
int RandomInt(int Low, int High);

int main()
{
	int i,WordCount,WordID,Option1,Option2,Found=0,Back=0,Exit=0;
	Word *WordList=NULL;
	char Letter;

	// Dimiourgo ti lista me tis lekseis meso tis LoadWords
	// kai tautoxrona exo ton arithmo ton lekseon afou mou
	// ton epistrefei i sunartisi.
	WordCount = LoadWords(&WordList);
	// Ftiaxno enan pinaka pou tha simeiono poies lekseis exo brei
	// ton opoio kai arxikopoio me 0 afou xrisimopoio tin calloc.
	int *WordsFound = (int *)calloc(WordCount, sizeof(int));

	printf("Loaded words: %d\n", WordCount);
	printf("Revealed three letters for each word.\n");

	while(Exit==0)
	{
		printf("Type 1 to play a new word (%d available words).\n", WordCount);
		printf("Type 2 to exit.\n");
		printf("Choose: ");
		scanf("%d", &Option1);

		if(Option1==2) Exit = 1;
		else if(Option1==1)
		{
			// Ama den yparxoun alles lekseis kleinei.
			if(WordCount==0)
			{
				printf("No available words. Exiting.\n");
				Exit = 1;
			}
			else
			{
				// Travaei tuxaia lekseis mexri
				// na vrei mia pou den exei luthei.
				do{
					WordID = RandomInt(0, WordCount-1);
				}while(WordsFound[WordID]==1);
				Word XWord = WordList[WordID];

				// Se kathe epanalipsi emfanizontai ta grammata tis
				// leksis pou exoun brethei kai episis ena menu.
				while(Back==0 && Found==0)
				{
					// Emfanizetai i leksi me ta gnosta grammata.
					printf("    Word is \"");
					for(i=0; i<strlen(XWord.String); i++)
					{
						if(XWord.OpenLetters[i]==0) printf("_");
						else printf("%c", XWord.String[i]);
					}
					printf("\".\n");
					printf("    Type 1 to give letter.\n");
					printf("    Type 2 to go back to menu.\n");
					printf("    Choose: ");
					scanf("%d", &Option2);

					if(Option2==2) Back = 1;
					else if(Option2==1)
					{
						// Diavazei ena gramma apo ton paikti.
						printf("    Letter: ");
						scanf("%*c%c", &Letter);

						// Elegxei ta grammata tis leksis kai an to vrei
						// kapou to faneronei an den einai idi faneromeno.
						for(i=0; i<strlen(XWord.String); i++)
						{
							if(XWord.String[i]==Letter && XWord.OpenLetters[i]==0)
							{
								XWord.OpenLetters[i] = 1;
								XWord.OpenLettersCount++;
							}
						}

						// Elegxei an vrethikan ola ta grammata tis leksis.
						if(strlen(XWord.String)==XWord.OpenLettersCount)
						{
							Found = 1;
							WordCount--;
							WordsFound[WordID] = 1;
							printf("You found the word: \"%s\". Removed from word list.\n", XWord.String);
						}
					}
				}
				Back = 0;
				Found = 0;
			}
		}
	}

	return 0;
}

// Sunartisi pou diavazei to arxeio words.txt,
// dimiourgei mia lista apo lekseis kai episis
// epistrefei ton arithmo ton lekseon.
int LoadWords(Word **WordList)
{
	char *Buffer = (char *)malloc(256*sizeof(char));
        FILE *fp = fopen("words.txt", "r");
        int i,Ch,WordCount=0;

	// Dinoume ena ksexoristo seed gia tin rand.
        srand((int)time(NULL));

	// Diavazoume enan-enan tous xaraktires tou arxeiou.
        Ch = getc(fp);
        while(Ch!=EOF)
        {
		// An einai gramma (mikro) to prosthetei sto Buffer.
                if(Ch>=97 && Ch<=122) Buffer[strlen(Buffer)] = Ch;
		// An sunantisei nea grammi ftiaxnei mia leksi me to Buffer.
                else if(Ch==10)
                {
                        WordCount++;
			// Epektinei ti desmevmeni mnimi gia ti lista me tis lekseis.
                        *WordList = (Word *)realloc(*WordList, WordCount*sizeof(Word));

			// Desmevei mnimi gia tous pointers tis leksis kai arxikopoiei ton akeraio.
                        (*WordList)[WordCount-1].String = (char *)malloc(strlen(Buffer)*sizeof(char));
                        (*WordList)[WordCount-1].OpenLetters = (int *)calloc(strlen(Buffer), sizeof(int));
                        (*WordList)[WordCount-1].OpenLettersCount = 0;

			// Pernaei to Buffer sto string tou struct tis leksis.
                        strcpy((*WordList)[WordCount-1].String, Buffer);
			// Metraei tis anoixtes theseis kai tis simeionei.
                        while((*WordList)[WordCount-1].OpenLettersCount<3)
                        {
                                int Random = RandomInt(0, strlen(Buffer)-1);
                                if((*WordList)[WordCount-1].OpenLetters[Random]==0)
                                {
                                        (*WordList)[WordCount-1].OpenLetters[Random] = 1;
                                        (*WordList)[WordCount-1].OpenLettersCount++;
                                }
                        }

			// Adeiazei to Buffer.
                        for(i=0; i<256; i++) Buffer[i]=0;
                }

		// Diavazei ton epomeno xaraktira.
                Ch = getc(fp);
        }
	// Kleinei to arxeio.
	fclose(fp);

	// Epistrefei ton arithmo ton lekseon.
	return WordCount;
}

// Sunartisi paragogis tuxaion arithmon
// pou akolouthoun tin kanoniki katanomi.
int RandomInt(int Low, int High)
{
        int k;
        double d;

        d = (double)rand() / ((double)RAND_MAX + 1);
        k = (int)(d * (High - Low + 1));

        return (Low + k);
}
