#include <stdio.h>

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
	// Edo akolouthei o algorithmos tou Euklidi.
	else
	{
		int Temp,MKD=-1;

		// An Y>X antimetatheto.
		if(Y>X)
		{
			Temp = X;
			X = Y;
			Y = Temp;
		}

		// Mexri na brethei o MKD.
		while(MKD==-1)
		{
			if(Y==0) MKD = X;
			else
			{
				Temp = Y;
				Y = X%Temp;
				X = Temp;
			}
		}

		printf("O megistos koinos diairetis einai to %d.\n", MKD);
	}

	return 0;
}
