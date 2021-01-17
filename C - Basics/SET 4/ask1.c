#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// To struct pou tha xrhsimopoihthei stis listes.
typedef struct Node {
	int Value;
	struct Node *Next;
} Node;

Node* InitList(int N);

int main()
{
	int i,N;

	// Diavazo to N.
	printf("How many elements in the list? ");
	scanf("%d", &N);

	// Ftiaxno tis 2 listes apoteloumenes apo N structs kai enan
	// epipleon pointer gia tin kathe mia oste na tis epeksergasto.
	Node *Head1 = InitList(N);
	Node *Head2 = InitList(N);
	Node *Current1 = Head1;
	Node *Current2 = Head2;

	// Toses epanalipseis oste na epeksergasto oloklires tis listes.
	for(i=1; i<=N; i++)
	{
		// Diavazo ena-ena ta stoixeia tis protis listas.
		printf("Element %d: ", i);
		scanf("%d", &(Current1->Value));

		// Ypologizo ena-ena ta stoixeia tis deuteris.
		Current2->Value = pow(Current1->Value,3);

		// An teleioso epanafero tous boithitikous pointers.
		// Kata tin epeksergasia tous pao mia thesi mprosta.
		if(i==N)
		{
			Current1 = Head1;
			Current2 = Head2;
		}
		else
		{
			Current1 = Current1->Next;
			Current2 = Current2->Next;
		}
	}

	// Typono tis 2 listes.
	printf("List L1:");
	for(i=1; i<=N; i++)
	{
		printf(" %d", Current1->Value);
		Current1 = Current1->Next;
	}
	printf("\nList L2:");
	for(i=1; i<=N; i++)
	{
		printf(" %d", Current2->Value);
		Current2 = Current2->Next;
	}
	printf("\n");

	return 0;
}

// Sunartisi pou dimiourgei mia lista apo N structs.
Node* InitList(int N)
{
	int i;
	Node *Head=NULL, *Current=NULL;

	// N fores...
        for(i=0; i<N; i++)
        {
		// Tin proti fora arxikopoio ton deikti Head.
		// Meta ena ena ta kommatia tis listas meso Next.
                if(Head==NULL)
                {
                        Head = (Node *)malloc(sizeof(Node));
                        Current = Head;
                }
                else
                {
                        Current->Next = (Node *)malloc(sizeof(Node));
                        Current = Current->Next;
                }
        }

	// Epistrefo tin lista. (enan deikti sto proto tis stoixeio)
	return Head;
}
