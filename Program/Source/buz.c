/* buz.c: driver program for buzzer */
#include "buz.h"

void buzinit(void)
{
	BUZ_DDR 		|= _BV(BUZ_PIN);
	BUZ_PORT 		&= ~_BV(BUZ_PIN);
}
void beep(int8u nbeep, int16u ontime)
{
	while(nbeep--)	{
		buzon();
		dlyms(ontime);
		buzoff();
		dlyms(OFF_TIME);
	}
}


