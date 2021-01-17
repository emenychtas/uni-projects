#include <stdio.h>

int x=3, y=4, z=5, w=2, a=2, b=3;
float res;

int main()
{
	res = y+z*x;
	// Vriskei to ginomeno z epi x, to prosthetei
	// sto y kai anathetei to apotelesma stin res.
	printf("res = %f\n", res);
	x=3, y=4, z=5, w=2, a=2, b=3;	

	res = w*x/y*z;
	// Ektelei tous pollaplasiasmous kai tis diaireseis
	// apo ta aristera pros ta deksia me ti seira.
	printf("res = %f\n", res);
	x=3, y=4, z=5, w=2, a=2, b=3;

	res = w*x/++y+z/y;
	// Auksanei to y kata 1, ypologizei to w*x/y kai to z/y
	// kai sti sunexeia ta prosthethei.
	printf("res = %f\n", res);
	x=3, y=4, z=5, w=2, a=2, b=3;

	res = ++a, b++;
	// Auksanei to a kata 1, anathetei ti nea timi tou a
	// sti res, kai ustera auksanei tin timi tou b kata 1.
	printf("res = %f\n", res);
	x=3, y=4, z=5, w=2, a=2, b=3;
	
	res = (a++, b++);
	// Auksanei to a kata 1, anathetei tin timi tou b sti
	// res kai meta auksanei kai tin timi tou b kata 1.
	printf("res = %f\n", res);
	x=3, y=4, z=5, w=2, a=2, b=3;

	res = (a>b)?a:b;
	// Elegxei an to a einai megalutero tou b, kai epeidh
	// den einai anathetei sti res tin timi tou b.
	printf("res = %f\n", res);

	return 0;
}
