#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* Replace(char *Input, char *Initial, char *Replacement);

main()
{
	int N;

	// Diavazo to N. (megisto mikos string)
	printf("Dwse megisto mege8os string:\n");
	scanf("%d", &N);

	// Desmevo mnimi gia ta 3 strings analogi me to N.
	char *Input = (char *)malloc(N*sizeof(char));
	char *Initial = (char *)malloc(N*sizeof(char));
	char *Replacement = (char *)malloc(N*sizeof(char));

	// Diavazo ta 3 strings.
	printf("Dwse string eisodou (mege8os to poly %d):\n", N);
	scanf("%s", Input);
	printf("Dwse string pros antikatastasi (mege8os to poly %d):\n", N);
	scanf("%s", Initial);
	printf("Dwse neo string (mege8os to poly %d):\n", N);
	scanf("%s", Replacement);

	// Dimiourgo to neo string pou tha epistrefei i Replace.
	char *New = Replace(Input, Initial, Replacement);

	// Typono to neo string.
	printf("To string eisodou meta tis antikatastaseis:\n");
	printf("%s\n", New);

	return 0;
}

char* Replace(char *Input, char *Initial, char *Replacement)
{
	//P1: Index gia to string Input.
	//P2: Index gia to string New.
	int i,P1=0,P2=0;
	int InputLength = strlen(Input);
	int InitialLength = strlen(Initial);
	int ReplacementLength = strlen(Replacement);
	char *Buffer = (char *)malloc(InitialLength*sizeof(char));

	char *New = NULL;

	// Mexri na epeksergastoume olo to string Input...
	while(P1<InputLength)
	{
		// An o trexon xaraktiras tou string Input einai isos me ton
		// proto xaraktira tou Initial pou psaxnoume, kai tautoxrona
		// uparxoun arketoi akoma xaraktires sto Input oste na emfanistei
		// olokliro to Initial...
		if((Input[P1]==Initial[0]) && ((InputLength-P1)>=InitialLength))
		{
			// Pername sto Buffer tosous xaraktires apo to Input
			// osous exei kai to Initial, apo to index P1 tou Input
			// kai meta, oste na tous sugkrinoume.
			for(i=0; i<InitialLength; i++) Buffer[i] = Input[P1+i];

			// An brikame to Initial sto Input (diladi to Buffer kai
			// to Initial tairiazoun) proektinoume ti desmevmeni mnimi
			// gia to New toso oste na xoraei to Replacement, pername
			// to Replacement sto index P2 tou New kai pera, kai
			// auksanoume tous deiktes tou Input kai tou New.
			if(!strcmp(Buffer,Initial))
			{
				New = (char *)realloc(New,(P2+ReplacementLength)*sizeof(char));
				for(i=0; i<ReplacementLength; i++) New[P2+i] = Replacement[i];
				P1 += InitialLength;
				P2 += ReplacementLength;
			}
			// An den tairiazei to Buffer me to Initial, aplos
			// proektinoume ti desmevmeni mnimi kata 1 kai pername
			// ena xaraktira apo to Input sto New.
			else
			{
				New = (char *)realloc(New,(P2+1)*sizeof(char));
				New[P2] = Input[P1];
				P1++;
				P2++;
			}
		}
		// Edo kanoume to idio me to else apo pano.
		else
		{
			New = (char *)realloc(New,(P2+1)*sizeof(char));
			New[P2] = Input[P1];
			P1++;
			P2++;
		}
	}

	// Epistrefoume to neo string, agnostou megethous fusika,
	// pou desmevei tosi mnimi osi akrivos xrisimopoiei.
	return New;
}
