#include <stdio.h>

int main()
{
	char Filename[256];

	// Diavazo to filename.
	printf("Dwse to onoma tou arxeiou:\n");
	scanf("%s", Filename);

	// Anoigo to arxeio se duadiko read mode.
	FILE *fp = fopen(Filename,"rb");
	// Pigaino ton kairsora sto telos tou arxeiou.
	fseek(fp,0,SEEK_END);

	// Typono to megethos tou arxeiou se
	// bytes me ti xrisi tis sunartisis ftell.
	printf("To arxeio periexei %d bytes.\n", ftell(fp));

	return 0;
}
