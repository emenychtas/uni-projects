#include <stdio.h>
#include <stdlib.h>

void ArrayInfo(int *Array, int Length);

// Sunartisi sugkrisis gia tin qsort.
int Compare(const void *a, const void *b)
{
	const int *p1 = a;
	const int *p2 = b;

	if(*p1<*p2) return -1;
	else if(*p1>*p2) return 1;
	else return 0;
}

int main()
{
	int i,Buffer,Count=0,*Array=NULL;

	// Zitaei thetikous akeraious mexri na dothei arnitikos
	// kai tautoxrona tous apothikeuei dunamika se ena array.
	do{
		printf("Enter a positive integer value (give negative to end): ");
		scanf("%d", &Buffer);

		if(Buffer>=0)
		{
			Count++;
			Array = (int *)realloc(Array, Count*sizeof(int));
			Array[Count-1] = Buffer;
		}
	}while(Buffer>=0);

	// An dothike toulaxiston enas thetikos akeraios sunexizei
	// emfanizontas tis plirofories pou zitountai, taksinomontas
	// to array me tous arithmous kai ksanaemfanizontas tis
	// plirofories.
	if(Count==0) printf("No positive numbers entered.\n");
	else
	{
		printf("Numbers entered:\n");
		ArrayInfo(Array, Count);

		qsort(Array, Count, sizeof(int), Compare);

		printf("Sorted Numbers:\n");
		ArrayInfo(Array, Count);
	}

	return 0;
}

// Sunartisi pou emfanizei tis zitoumenes plirofories tou array.
void ArrayInfo(int *Array, int Length)
{
	int i;

	for(i=0; i<Length; i++)
        {
        	printf("Numbers[%d] = %d\n", i,Array[i]);
        }
        printf("Length Of Array: %d\n", Length);
        printf("Array Address: 0x%X\n", Array);
        printf("First Element Address: 0x%X\n", &(Array[0]));
        printf("Last Element Address: 0x%X\n", &(Array[Length-1]));
        printf("Array holds %d bytes.\n", Length*sizeof(int));

	return;
}
