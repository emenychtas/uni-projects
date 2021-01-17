#include <stdio.h>
#include <math.h>

float AC,AB,CD,AD,BC,h;

int main()
{
        printf("Dose mikos AC: ");
        scanf("%f", &AC);
        printf("Dose mikos AB: ");
        scanf("%f", &AB);
        printf("Dose mikos CD: ");
        scanf("%f", &CD);

        if (AB>AC && CD>AC)
        {
                AD = sqrt(pow(CD,2)-pow(AC,2)); // Py8agoreio
                BC = sqrt(pow(AB,2)-pow(AC,2)); // 8ewrhma.

		h = AD*(BC*CD/(AD+BC))/CD;

		printf("h = %f\n", h);
        }
        else printf("Oi times den sumfwnoun me to sxhma.\n");

	return 0;
}

