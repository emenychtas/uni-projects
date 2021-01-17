#include <stdio.h>

char x;
float MO;
int Sum=0,TempSum=0,Count=0;

int main()
{
	printf("Dose ba8mous: ");

	do{ // Diabazei kai analyei ta grammata mexri na paththei to ENTER.
		scanf("%c", &x);

		// Osa prosthetoun bathmo prosteithontai sto TempSum, eno to F anebazei to Count.
		// Ta A ews E anebazoun to count meta, gia eksoikonomish grammwn, afou ginetai.
		if (x=='A') TempSum += 5;
		else if (x=='B') TempSum += 4;
		else if (x=='C') TempSum += 3;
		else if (x=='D') TempSum += 2;
		else if (x=='E') TempSum += 1;
		else if (x=='F') Count++;

		if (Sum!=TempSum)
		{
			Count++;
			Sum = TempSum;
		}
	}while(x!='\n');

	if (Count==0) printf("Den dosate kapoion bathmo.\n");
	else
	{
		MO = (float)Sum/Count; // Type casting gia na mi xathun ta dekadika psifia.
		printf("O mesos oros einai %.2f, to a8roisma %d kai to pli8os %d.\n", MO,Sum,Count);
		// O mesos oros emfanizetai me akriveia 2 dekadikwn.
	}

	return 0;
}
