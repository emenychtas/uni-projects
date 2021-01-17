#include <stdio.h>
#include <string.h>

int main()
{
	int i,Option,PassLen,Key=0;
	char Filename[256],Password[256];

	printf("Program functions:\n");
	printf("1 - Encrypt File\n");
	printf("2 - Decrypt File\n");
	printf("0 - Exit\n");
	printf("Choose: ");
	scanf("%d", &Option);

	// Gia encryption kai decryption.
	if(Option==1 || Option==2)
	{
		// Diavazo to filename kai ton kwdiko.
		printf("Filename: ");
		scanf("%s", Filename);
		printf("Password: ");
		scanf("%s", Password);

		// Ypologizo to kleidi.
		PassLen = strlen(Password);
		for(i=0; i<PassLen; i++) Key += Password[i];

		// Anoigo to arxeio gia anagnosi kai epeksergasia.
		FILE *fp = fopen(Filename, "r+");

		// Diavazo olous tous xaraktires mexri to telos
		// ektelontas tis entoles mesa sto while gia ton
		// kathe ena.
		int Ch = getc(fp);
		while(Ch!=EOF)
		{
			// Gia encryption.
			if(Option==1)
			{
				// Prostheto to kleidi ston xaraktira.
				// Sti sunexeia afairo sunexeia 127 an
				// xreiastei mexri na ton fero sto
				// sunolo ton ASCII.
				Ch += Key;
				while(Ch>127) Ch -= 127;
			}
			// Gia decryption.
			else
			{
				// Kano akrivos to antitheto, auti ti
				// fora prostithontas 127 gia na fero
				// ton xaraktira sto sunolo ton ASCII.
				Ch -= Key;
				while(Ch<1) Ch += 127;
			}

			// Pao ton kairsora tou arxeiou mia thesi piso
			// afou pige mia thesi mprosta meta tin anagnosi.
			fseek(fp, -1, SEEK_CUR);
			// Antikathisto ton xaraktira me ton kainourio.
			putc(Ch, fp);
			// Diavazo ton epomeno.
			Ch = getc(fp);
		}

		// Kleino to arxeio.
		fclose(fp);

		printf("File operation complete.\n");
	}

	return 0;
}
