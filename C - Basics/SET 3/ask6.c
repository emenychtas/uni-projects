#include <stdio.h>
#include <string.h>

int NumCharToInt(char NumChar);
void NumToMorse();
void MorseToNum();

char *Morse[10], Buffer[256];

int main()
{
	Morse[0] = "-----";
	Morse[1] = ".----";
	Morse[2] = "..---";
	Morse[3] = "...--";
	Morse[4] = "....-";
	Morse[5] = ".....";
	Morse[6] = "-....";
	Morse[7] = "--...";
	Morse[8] = "---..";
	Morse[9] = "----.";

	// Epanalipsi mexri na bgei me break.
	while(1)
	{
		printf("1 - Ari8mos se kwdika Morse\n");
		printf("2 - Kwdikas Morse se ari8mo\n");
		printf("0 - Eksodos\n");
		gets(Buffer);

		if(!strcmp(Buffer,"1")) NumToMorse();
		else if(!strcmp(Buffer,"2")) MorseToNum();
		else if(!strcmp(Buffer,"0")) break;
	}

	return 0;
}

// Sunartisi pou metatrepei enan arithmo se kwdika Morse.
void NumToMorse()
{
	int i;

	// Diavazo ton arithmo.
	printf("Dwse ari8mo: ");
	gets(Buffer);

	printf("O isodynamos kwdikas Morse einai:");

	// Gia kathe noumero ksexorista typono ta 5 symvola
	// pou tou antistoixoun ston kwdika Morse.
	for(i=0; i<strlen(Buffer); i++)
	{
		printf(" %s", Morse[NumCharToInt(Buffer[i])]);
	}
	printf("\n");

	return;
}

// Sunartisi pou metatrepei ena kommati kwdika Morse se arithmo.
void MorseToNum()
{
	int i,j;
	char MiniBuffer[5];

	// Diavazo ton kwdika Morse.
	printf("Dwse kwdika Morse: ");
	gets(Buffer);

	printf("O isodynamos ari8mos einai: ");

	// Epanalipsi toses fores oses einai kai oi 5ades symvolon.
	// Kathe 5ada tin fortono sto MiniBuffer kai sugkrino me ton
	// pinaka Morse gia na do se poion arithmo antistoixei.
	for(i=0; i<(strlen(Buffer)/5); i++)
	{
		for(j=0; j<5; j++) MiniBuffer[j] = Buffer[(i*5)+j];

		for(j=0; j<10; j++) if(!strcmp(MiniBuffer,Morse[j])) printf("%d", j);
	}
	printf("\n");

	return;
}

// Sunartisi pou pairnei enan arithmo se morfi
// xaraktira kai epistrefei tin timi tou se int.
int NumCharToInt(char NumChar)
{
	// Afairo apo tin timi ASCII tou xaraktira
	// tin timi ASCII tou xaraktira '0' poy einai
	// o protos arithmos sto ASCII table.
	return (int)NumChar-(int)'0';
}
