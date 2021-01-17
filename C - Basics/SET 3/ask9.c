#include <stdio.h>
#include <time.h>

void random_vector(int array[], int N);
void calculate_hist(int array[], int N, int hist[10]);
void print_hist(int hist[10]);

int main()
{
	int N;

	// Diavazo to N.
	printf("Doste to N: ");
	scanf("%d", &N);

	// Dimiourgo ena monodiastato pinaka megethous N pou ystera gemizo
	// me tuxaious arithmous apo to 0 mexri to 9 meso tis random_vector.
	int array[N];
	random_vector(array, N);

	// Dimiourgo enan monodiastato pinaka pou sti sunexeia gemizo meso
	// tis calculate_hist me ton arithmo emfaniseon gia kathe arithmo
	// apo to 0 mexri to 9.
	int hist[10];
	calculate_hist(array, N, hist);

	// Emfanizo stin othoni to istogramma meso tis print_hist.
	print_hist(hist);

	return 0;
}

void random_vector(int array[], int N)
{
	int i;

	// Dino ena simeio anaforas (ksexoristo kathe fora) basismeno
	// sto roloi tou sustimatos, gia tin paragogi tuxaion arithmon
	// apo tin rand.
	srand((int)time(NULL));

	// Gemizo ton pinaka array me tyxaious arithmous pou kovo sto
	// sunolo [0,9] (me to %10).
	// Oi arithmoi autoi den akolouthoun tin kanoniki katanomi.
	for(i=0; i<N; i++) array[i] = rand()%10;

	return;
}

void calculate_hist(int array[], int N, int hist[10])
{
	int i;

	// Arxikopoio ton pinaka hist me midenika.
	for(i=0; i<10; i++) hist[i] = 0;
	// Auksano to antistoixo stoixeio tou pinaka
	// hist kata ena gia kathe arithmo pou sunantao.
	for(i=0; i<N; i++) hist[array[i]]++;

	return;
}

void print_hist(int hist[10])
{
	int i,j;

	// Emfanizo to istogramma sumfona me tin ekfonisi.
	for(i=0; i<10; i++)
	{
		printf("%d: ", i);
		for(j=0; j<hist[i]; j++) printf("*");
		printf(" (%d)\n", hist[i]);
	}

	return;
}
