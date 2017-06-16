/*
 * dlyms.c
 *
 * Created: 12/8/2015 12:37:33 PM
 *  Author: bsp
 */ 
#include "dly.h"

void dlyms(unsigned int x)
{
	unsigned int i;
	for (i = 0; i < x; i++) 
			_delay_ms(1);
}

void dlyus(unsigned int x)
{
	unsigned int i;
	for (i = 0; i < x; i++)
		_delay_us(1);
	
}