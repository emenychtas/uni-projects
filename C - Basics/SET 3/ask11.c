#include <stdio.h>
#include <math.h>

float a(int n);
float S(int n);
float S_EPANALHPTIKH(int n);

int main()
{
	int n;

	// Diavazo to n.
	printf("Dose akeraio n: ");
	scanf("%d", &n);

	// Typono to a(n), kai 2 fores to S(n) mia me tin
	// anadromiki kai mia me tin epanalhptikh sunartisi.
	printf("a(n) = %.4f\n", a(n));
	printf("S(n) = %.4f\n", S(n));
	printf("S(n) = %.4f (Apo Epanalhptikh)\n", S_EPANALHPTIKH(n));

	return 0;
}

// Anadromiki sunartisi pou epistrefei to a(n).
float a(int n)
{
	if(n==0) return 1;
	else return (3*pow(a(n-1),2)-1)/a(n-1);
}

// Anadromiki sunartisi pou epistrefei to S(n).
float S(int n)
{
	if(n==0) return a(n);
	else return S(n-1)+a(n);
}

// Epanalhptikh sunartisi pou epistrefei to S(n).
float S_EPANALHPTIKH(int n)
{
	int i;
	float Sum=0;

	for(i=0; i<=n; i++) Sum += a(i);

	return Sum;
}
