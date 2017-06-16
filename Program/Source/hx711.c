#include <hx711.h>

void HX711init(void)
{
	HX711_DDR |= _BV(HX711_CLK_PIN);
	HX711_DDR &= ~_BV(HX711_DIN_PIN);

	HX711_PORT |= _BV(HX711_DIN_PIN);

	HX711_PORT |= _BV(HX711_CLK_PIN);
}

unsigned long HX711Read(void)
{
	
	int8u i;
	unsigned long Count = 0;


	HX711_PORT |= _BV(HX711_DIN_PIN);
	HX711_PORT &= ~_BV(HX711_CLK_PIN);

	while (HX711_INPIN & _BV(HX711_DIN_PIN)) ;

	for (i = 0; i < 24; i++)	{
		HX711_PORT |= _BV(HX711_CLK_PIN);
		dlyus(2);
		Count = Count << 1;

		HX711_PORT &= ~_BV(HX711_CLK_PIN);
		dlyus(1);

		if (HX711_INPIN & _BV(HX711_DIN_PIN))
		Count++;

		dlyus(1);
	}
	
	HX711_PORT |= _BV(HX711_CLK_PIN);

	Count = Count ^ 0x800000;
	dlyus(2);
	
	HX711_PORT &= ~_BV(HX711_CLK_PIN);
	
	return Count;
}