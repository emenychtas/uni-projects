#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5

typedef struct Employee {
	char *FirstName;
	char *LastName;
	int Age;
} Employee;

Employee* Create(int *Top);
void Add(Employee* List, int *Top, Employee* New);
void Delete(Employee* List, int *Top);
void Print(Employee* List, int Top);
void Sort(Employee* List, int Top, char *Field, int Direction);
int Difference(Employee* A, Employee* B, char *Field);
void Swap(Employee* A, Employee* B);

int main()
{
	char *CharBuffer = (char *)malloc(256*sizeof(char));
	int Top, Option, Field, Direction, Exit=0;

	// Dimiourgo ton pinaka me ti xrisi tis Create.
	Employee* List = Create(&Top);

	while(Exit==0)
	{
		printf("1. Add Employee Info\n");
		printf("2. Remove Employee Info\n");
		printf("3. Print Employee Catalog\n");
		printf("4. Sort Employee Catalog\n");
		printf("5. Exit Program\n");
		printf("Choose: ");
		scanf("%d", &Option);

		if(Option==1)
		{
			if(Top==N) printf("Employee catalog full.\n");
			else
			{
				// Dimiourgo neo struct kai diavazo tis plirofories tou.
				Employee New;

				printf("First Name: ");
				scanf("%s", CharBuffer);
				New.FirstName = (char *)malloc(strlen(CharBuffer)*sizeof(char));
				strcpy(New.FirstName, CharBuffer);

				printf("Last Name: ");
				scanf("%s", CharBuffer);
				New.LastName = (char *)malloc(strlen(CharBuffer)*sizeof(char));
				strcpy(New.LastName, CharBuffer);

				printf("Age: ");
				scanf("%d", &(New.Age));

				// To prostheto ston pinaka me ti sunartisi Add.
				Add(List, &Top, &New);
			}
		}
		else if(Option==2)
		{
			if(Top==0) printf("Employee catalog already empty.\n");
			else Delete(List, &Top);
		}
		else if(Option==3)
		{
			if(Top==0) printf("Employee catalog empty.\n");
			else Print(List, Top);
		}
		else if(Option==4)
		{
			if(Top==0) printf("Employee catalog empty.\n");
			else
			{
				// Zitao apo ton xristi na prosdiorisei
				// to kritirio taksinomisis kai ti fora.
				printf("Sort By:\n");
				printf("1. First Name\n");
				printf("2. Last Name\n");
				printf("3. Age\n");
				printf("Choose: ");
				scanf("%d", &Field);

				printf("Direction:\n");
				printf("1. Ascending\n");
				printf("2. Descending\n");
				printf("Choose: ");
				scanf("%d", &Direction);

				// An o xristis dialeksei fthinousa seira kano to
				// Direction -1 opos ypodykneiei kai i ekfonisi.
				if(Direction==2) Direction = -1;

				// Analogos to kritirio taksinomisis stelno
				// to katallilo string san orisma sti Sort.
				if(Field==1) Sort(List, Top, "first", Direction);
				else if(Field==2) Sort(List, Top, "last", Direction);
				else if(Field==3) Sort(List, Top, "age", Direction);
			}
		}
		else if(Option==5)
		{
			printf("Exiting...\n");
			Exit = 1;
		}
	}

	return 0;
}

// Sunartisi pou dimiourgei ton pinaka kai desmevei mnimi gia auton.
Employee* Create(int *Top)
{
	Employee* List = (Employee*)malloc(N*sizeof(Employee));
	*Top = 0;

	printf("Employee catalog created.\n");

	return List;
}

// Sunartisi pou prosthetei ena struct sto telos tou pinaka.
void Add(Employee* List, int *Top, Employee* New)
{
	List[(*Top)].FirstName = (char *)malloc(strlen(New->FirstName)*sizeof(char));
	strcpy(List[(*Top)].FirstName, New->FirstName);

	List[(*Top)].LastName = (char *)malloc(strlen(New->LastName)*sizeof(char));
	strcpy(List[(*Top)].LastName, New->LastName);

	List[(*Top)].Age = New->Age;

	(*Top)++;
	printf("Employee added to catalog.\n");

	return;
}

// Sunartisi pou diagrafei to teleftaio struct tou pinaka.
void Delete(Employee* List, int *Top)
{
	(*Top)--;
	printf("Employee removed from catalog.\n");

	return;
}

// Sunartisi pou typonei tis plirofories ton structs tou pinaka.
void Print(Employee* List, int Top)
{
	int i;

	for(i=0; i<Top; i++)
	{
		printf("First Name: %s\n", List[i].FirstName);
		printf("Last Name:  %s\n", List[i].LastName);
		printf("Age:        %d\n", List[i].Age);
	}

	return;
}

// Sunartisi pou taksinomei ta structs tou pinaka sumfona me ena
// kritirio taksinomisis, xrisimopoiontas ton algorithmo taksinomisis
// Bubblesort kai tis sunartiseis Difference kai Swap.
void Sort(Employee* List, int Top, char *Field, int Direction)
{
	int i,j;

	for(i=1; i<Top; i++)
	{
		for(j=Top-1; j>=i; j--)
		{
			if(Direction*Difference(&(List[j-1]),&(List[j]),Field)>0)
			{
				Swap(&(List[j-1]),&(List[j]));
			}
		}
	}

	printf("Employee catalog sorted.\n");

	return;
}

// Epistrefei ti diafora tou struct B apo to A os pros ena stoixeio.
int Difference(Employee* A, Employee* B, char *Field)
{
	if(!strcmp(Field,"age")) return (A->Age - B->Age);
	else
	{
		int i,SA=0,SB=0;
		char **a,**b;

		if(!strcmp(Field,"first"))
		{
			a = &(A->FirstName);
			b = &(B->FirstName);
		}
		else
		{
			a = &(A->LastName);
			b = &(B->LastName);
		}

		// Prostheto tin timi ASCII olon ton xaraktiron.
		for(i=0; i<strlen(*a); i++) SA += (*a)[i];
		for(i=0; i<strlen(*b); i++) SB += (*b)[i];

		return (SA - SB);
	}
}

// Antimetathetei 2 structs.
void Swap(Employee* A, Employee* B)
{
	Employee Temp;

	Temp.FirstName = (char *)malloc(strlen(A->FirstName)*sizeof(char));
	Temp.LastName = (char *)malloc(strlen(A->LastName)*sizeof(char));
	strcpy(Temp.FirstName, A->FirstName);
	strcpy(Temp.LastName, A->LastName);
	Temp.Age = A->Age;

	A->FirstName = (char *)malloc(strlen(B->FirstName)*sizeof(char));
	A->LastName = (char *)malloc(strlen(B->LastName)*sizeof(char));
	strcpy(A->FirstName, B->FirstName);
	strcpy(A->LastName, B->LastName);
	A->Age = B->Age;

	B->FirstName = (char *)malloc(strlen(Temp.FirstName)*sizeof(char));
	B->LastName = (char *)malloc(strlen(Temp.LastName)*sizeof(char));
	strcpy(B->FirstName, Temp.FirstName);
	strcpy(B->LastName, Temp.LastName);
	B->Age = Temp.Age;

	return;
}
