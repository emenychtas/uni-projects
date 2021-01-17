#include <stdio.h>

// Se auti tin askisi ypotheto oti oi arithmoi tis parastasis pros ypologismo einai
// thetikoi akeraioi.
// Episis logo mias idiotropias tis ANSI C me tin scanf mesa se while/do...while
// (diabazei to enter san xaraktira) kai epeidh dokimasa tin fflush(stdin) xwris
// apotelesmata (kai sto diogeni alla kai sto netbins) anagkastika na xrisimopoihso
// diko mou buffer and ti sunartisi sscanf.


float Result;
int X=-1,Y=-1; // An dothei gramma i symbolo sti thesi enos apo tous 2 i timi tou paramenei -1.
char OP,Finish,Buffer[1];

int main()
{
	do{
		printf("Pros ypologismo parastash:   ");
		scanf("%d%c%d%*c", &X,&OP,&Y);
		// Diabazo tin parastasi paraleipontas to ENTER sto telos.

		// Elegxo gia eisagwgi mi arithmwn, allwn symbolwn, kai gia diairesh me to 0.
		if(X!=-1 && Y!=-1 && (OP=='+' || OP=='-' || OP=='*' || (OP=='/' && Y!=0)))
		{
			switch(OP)
			{
				case '+': Result = X + Y; break;
				case '-': Result = X - Y; break;
				case '*': Result = X * Y; break;
				case '/': Result = (float)X / Y; break;
			}
			printf("   ->%d%c%d = %.2f\n", X,OP,Y,Result);
			// Emfanizo to apotelesma me akriveia 2 dekadikwn psifiwn.
		}
		else printf("Mh egkyrh eisodos.\n");

		printf("Piese 'x' gia telos:   ");

		gets(Buffer);
		sscanf(Buffer, "%c", &Finish);

	}while(Finish!='x'); // Mexri na dothei to x.

	return 0;
}
