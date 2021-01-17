#include <stdio.h>

int Hours,Minutes,MinDekades,MinYpoloipo,HrDekades,HrYpoloipo,Wra,Peripou;

int main()
{
	printf("Dose Wra: ");
	do{
		scanf("%d", &Hours);
	}while(Hours<0 || Hours>23);
	printf("Dose Lepta: ");
	do{
		scanf("%d", &Minutes);
	}while(Minutes<0 || Minutes>59);
	// Eisodos wras kai leptwn me elegxo egkyrothtas.

	MinDekades = Minutes/10;
	MinYpoloipo = Minutes%10;
	HrDekades = Hours/10;
        HrYpoloipo = Hours%10;
	// Diaxwrismos dekadwn kai monadwn sta lepta kai stis wres.
                        
        printf("Dwthike Wra: %d%d:%d%d\n", HrDekades,HrYpoloipo,MinDekades,MinYpoloipo);	
	// Emfanhsh dotheisas wras.

	if (MinYpoloipo!=0 && MinYpoloipo!=5)
	{
		Peripou = 1; // Boolean gia na gnwrizoume oti einai sto peripou.
		if (MinYpoloipo==1 || MinYpoloipo==2) MinYpoloipo = 0;
		else if (MinYpoloipo>=3 && MinYpoloipo<=7) MinYpoloipo = 5;
		else if (MinYpoloipo==8 || MinYpoloipo==9)
		{
			MinYpoloipo = 0;
			if (MinDekades==5)
			{
				MinDekades = 0;
				if (Hours==23) Hours = 0;
				else Hours++;
			}
			else MinDekades++;
		}
	} // Stroggylopoihsh.

	Minutes = MinDekades*10 + MinYpoloipo; // Stroggylopoihmena lepta.

	Wra = Hours;
	if (Minutes>30) Wra++;
	if (Wra>12) Wra -= 12;
	else if (Wra==0) Wra = 12;
	// H wra prosarmosmeni sto euros apo 1 mexri 12 gia thn proforikh omilia parakato.

	printf("H wra einai ");
	if (Peripou==1) printf("peripou ");

	if (Wra==1) printf("mia ");
	else if (Wra==2) printf("dyo ");
	else if (Wra==3) printf("treis ");
	else if (Wra==4) printf("tesseris ");
	else if (Wra==5) printf("pente ");
	else if (Wra==6) printf("eksi ");
	else if (Wra==7) printf("epta ");
	else if (Wra==8) printf("okto ");
	else if (Wra==9) printf("ennea ");
	else if (Wra==10) printf("deka ");
	else if (Wra==11) printf("enteka ");
	else if (Wra==12) printf("dwdeka ");

	if (Minutes==0) printf("akrivws ");
	else
	{
		if (Minutes<=30) printf("kai ");
		else printf("para ");
		
		if (Minutes==5 || Minutes==55) printf("pente ");
		else if (Minutes==10 || Minutes==50) printf("deka ");
		else if (Minutes==15 || Minutes==45) printf("tetarto ");
		else if (Minutes==20 || Minutes==40) printf("eikosi ");
		else if (Minutes==25 || Minutes==35) printf("eikosi pente ");
		else if (Minutes==30) printf("misi ");
	}

	if (Hours<12) printf("pro mesimvrias.\n");
	else printf("meta mesimvrias.\n");

	return 0;
}
