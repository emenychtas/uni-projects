#include <stdio.h>

int i;

int main()
{
	// Ksekiname apo to 65 (ASCII A) kai stamatame sto 122 (ASCII z).
	for(i=65; i<=122; i++)
	{
		// "Pidame" to keno apo 91 mexri 96 epeidh den antistoixoun se grammata.
		if ((i>=65 && i<=90)||(i>=97 && i<=122)) printf("%c (%d)\n", i,i);
	}

	return 0;
}
