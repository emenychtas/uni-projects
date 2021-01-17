#include <stdio.h>
#include <math.h>

int Bytes,GB,MB,KB,B;

int main()
{
	printf("Dose bytes: ");
	scanf("%d", &Bytes);

	// Parakatw kanoume type casting epeidh h pow epistrefei timh typoy double.
	GB = Bytes/(int)pow(1024,3); // Diairoume ta Bytes me ena Gibibyte.
	B = Bytes%(int)pow(1024,3); // Anathetoume sthn B ta apomeinanta bytes.
	MB = B/(int)pow(1024,2); // Diairoume ta apomeinanta bytes me ena Mebibyte.
	B = B%(int)pow(1024,2); // Anathetoume sthn B ta apomeinanta bytes.
	KB = B/1024; // Diairoume ksana ta apomeinanta bytes me ena Kibibyte.
	B = B%1024; // Anathetoume sthn B ta apomeinanta bytes.

	printf("Ta %d bytes analyontai ws ekseis:\n", Bytes);
	printf("%d Gibibytes kai %d Mebibytes kai %d Kibibytes kai %d bytes\n", GB,MB,KB,B);

	return 0;
}
