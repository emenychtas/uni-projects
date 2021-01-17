// Theoro oti ta arxeia eisodou sti leitourgia -diff
// exoun ton idio arithmo grammon. An kai me kapoies
// tropopoiiseis den tha xreiazotan auto.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Lines;
FILE *fpOne,*fpTwo,*fpNew;
char *BufferOne,*BufferTwo;

void Diff(char *filenameOne, char *filenameTwo);
void Patch();

int main(int argc, char *argv[])
{
	// Desmevo mnimi gia ta 2 buffers.
	BufferOne = (char *)malloc(256*sizeof(char));
	BufferTwo = (char *)malloc(256*sizeof(char));

	// Anoigo ta 2 arxeia pou dinei o xristis
	// meso ton arguements gia diavasma.
	fpOne = fopen(argv[2], "r");
	fpTwo = fopen(argv[3], "r");

	// Metrao tis grammes tou protou arxeiou
	// kai epanafero ton kairsora tou arxeiou.
	Lines=0;
	while(fgets(BufferOne, 256, fpOne)!=NULL)
	{
		Lines++;
	}
	fseek(fpOne, 0, SEEK_SET);

	// Analoga tin leitourgia pou zitise o xristis meso
	// tou protou arguement kalo tin antistoixi sunartisi.
	if(!strcmp(argv[1],"-diff")) Diff(argv[2], argv[3]);
	else if(!strcmp(argv[1], "-patch")) Patch();

	// Apodesmevo ta arxeia.
	fclose(fpOne);
	fclose(fpTwo);
	fclose(fpNew);

	return 0;
}

// Sunartisi pou analamvanei to -diff mode.
void Diff(char *filenameOne, char *filenameTwo)
{
	int i;

	// Ftiaxno to arxeio diff.txt me tis diafores.
	fpNew = fopen("diff.txt", "w");

	// To gemizo.
	for(i=0; i<Lines; i++)
	{
		// Diavazo mia grammi apo kathe arxeio.
		fgets(BufferOne, 256, fpOne);
		fgets(BufferTwo, 256, fpTwo);

		// An diaferoun grafo...
		if(strcmp(BufferOne,BufferTwo)!=0)
		{
			char TempBuffer[100];
			sprintf(TempBuffer, "---Line %d\n", i+1);

			fputs(TempBuffer, fpNew);
			fputs(filenameOne, fpNew);
			fputs("\n", fpNew);
			fputs(BufferOne, fpNew);
			fputs(filenameTwo, fpNew);
			fputs("\n", fpNew);
			fputs(BufferTwo, fpNew);
		}
	}

	return;
}

// Sunartisi pou analamvanei to -patch mode.
void Patch()
{
	int i,j;
	char TempBuffer[100];

	// Ftiaxno to arxeio file_new.txt.
	fpNew = fopen("file_new.txt", "w");

	// To gemizo.
	for(i=0; i<Lines; i++)
	{
		// Diavazo mia grammi apo to proto arxeio
		// kai alli mia apo to arxei me tis diafores.
		fgets(BufferOne, 256, fpOne);
		fgets(BufferTwo, 256, fpTwo);

		// An to arxeio me tis diafores den exei simeiomeni
		// kapoia diafora gia ti sugkekrimeni grammi tote
		// grafo ti grammi pou diavasa apo to proto arxeio
		// sto kainourio, kai pao ton kairsora tou arxeiou
		// diaforon piso toses theseis oses proxorisa.
		sprintf(TempBuffer, "---Line %d\n", i+1);
		if(strcmp(BufferTwo,TempBuffer)!=0)
		{
			fputs(BufferOne, fpNew);
			fseek(fpTwo, -(strlen(BufferTwo)), SEEK_CUR);
		}
		// An vrethike simeiomeni diafora sto arxeio diaforon
		// tote diavazo alles 4 fores apo to arxeio diaforon
		// gia na ftaso sti grammi tou file_new.txt (simfona
		// me tin ierarxia pou uiothetisame sto arxeio diff.txt)
		// kai tin grafo sto neo arxeio.
		else
		{
			for(j=0; j<4; j++) fgets(BufferTwo, 256, fpTwo);
			fputs(BufferTwo, fpNew);
		}
	}

	return;
}
