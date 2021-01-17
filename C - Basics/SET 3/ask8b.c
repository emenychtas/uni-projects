#include <stdio.h>

int MKD(int X, int Y);

int main()
{
	int X,Y;

	// Diavazo ta X kai Y.
	printf("Dose to X:\n");
	scanf("%d", &X);
	printf("Dose to Y:\n");
	scanf("%d", &Y);

	// An einai arnitika ta kano thetika afou o megistos
	// koinos diairetis einai panta thetikos arithmos.
	// Episis auto dieukolunei ton algorithmo.
	if(X<0) X *= -1;
	if(Y<0) Y *= -1;

	// An einai isa tote o MKD einai isos me to X kai Y.
	// An omos ta X kai Y einai 0 tote o MKD einai to apeiro.
	if(X==Y)
	{
		if(X==0) printf("O megistos koinos diairetis einai to apeiro.\n");
		else printf("O megistos koinos diairetis einai to %d.\n", X);
	}
	else
	{
		// An Y>X antimetatheto.
		if(Y>X)
		{
			int Temp;

			Temp = X;
			X = Y;
			Y = Temp;
		}

		printf("O megistos koinos diairetis einai to %d.\n", MKD(X,Y));
	}

	return 0;
}

// Anadromiki sunartisi pou ulopoiei ton algorithmo tou Euklidi.
int MKD(int X, int Y)
{
	if(Y==0) return X;
	else
	{
		int Temp;

		Temp = Y;
		Y = X%Temp;
		X = Temp;

		// Anadromi.
		return MKD(X,Y);
	}
}
