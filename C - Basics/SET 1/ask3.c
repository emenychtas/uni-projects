#include <stdio.h>
#include <math.h>

float pleura, ypsos, embadon;

int main()
{
	printf("Dose pleura isopleurou trigwnou: ");
	scanf("%f", &pleura);

	ypsos = sqrt(pow(pleura,2)-pow(pleura/2,2)); // Py8agoreio 8ewrhma.
	embadon = pleura*ypsos/2; // Gewmetrikos typos.

	printf("To embadon tou trigwnou einai: %f\n", embadon);

	return 0;
}
