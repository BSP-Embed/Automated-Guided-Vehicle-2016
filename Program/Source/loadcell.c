
#include "loadcell.h"

extern int8u lcdptr;

float measwt(int8u disp)
{
	int8u i;
	char s[10];
	unsigned long weight;
	float wtgms;

	weight = 0;

	for (i = 0; i < 8; i++)
			weight +=  HX711Read();
	
	weight >>= 3;
	
	wtgms =  (weight - 8294000) * 0.0046f;
		
	if (disp) {
			lcdptr = 0xc7;
			lcdws("        ");
			ftoa(wtgms,s,1);
			//ltoa(weight,s);
			lcdptr = 0xc7;
		lcdws(s);
	}
	
	return wtgms;
}