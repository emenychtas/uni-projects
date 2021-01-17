#include <stdio.h>
#include <math.h>

int num,new,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10;

int main()
{
	printf("Dose arithmo sto [0,1023]:\n");
	do
	{
		scanf("%d", &num);
	}while(num<0 || num>1023);
	// Elegxoume wste o arithmos na einai apo 0 mexri kai 1023.

	// Fernoume ton arithmo se duadikh morfh, me ton ekseis algorithmo:
	// Gemizoume ena ena ta 10 psifia apo deksia pros ta aristera
	// anathetontas kathe fora to ypoloipo tis diairesis me to 2
	// kai allazontas tin timh toy arithmou sto akeraio phliko
	// tis diairesis toy me to 2.
	d10 = num%2;
	num /= 2;
	d9 = num%2;
	num /= 2;
	d8 = num%2;
        num /= 2;
        d7 = num%2;
        num /= 2;
        d6 = num%2;
        num /= 2;
        d5 = num%2;
        num /= 2;
        d4 = num%2;
        num /= 2;
        d3 = num%2;
        num /= 2;
        d2 = num%2;
        num /= 2;
        d1 = num%2;

	// Ftiaxnoume ton neo arithmo sumfwna me tin ekfwnhsh.
	new = d6*pow(2,9) + d7*pow(2,8) + d8*pow(2,7) + d9*pow(2,6) + d10*pow(2,5) + d1*pow(2,4) + d2*pow(2,3) + d3*pow(2,2) + d4*pow(2,1) + d5*pow(2,0);
	printf("%d\n", new);

	return 0;
}
