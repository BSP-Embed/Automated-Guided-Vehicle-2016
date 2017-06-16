#include "motor.h"

void motorinit(void)
{
	MOT_DDR	|= _BV(MOT1_AN) | _BV(MOT1_CA);
	MOT_PORT	&= ~(_BV(MOT1_AN) | _BV(MOT1_CA));
}

void  MotClk(void)
{
	MOT_PORT |= _BV(MOT1_AN);
}

void MotAclk(void)
{
	MOT_PORT |= _BV(MOT1_CA);
}

void MotStop(void)
{
	MOT_PORT &= ~(_BV(MOT1_AN));
	MOT_PORT &= ~(_BV(MOT1_CA));
}