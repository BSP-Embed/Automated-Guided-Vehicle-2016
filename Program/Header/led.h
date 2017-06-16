#ifndef _LED_H
#define _LED_H

#include"includes.h"


//DEFINE LED PORT


//DEFINE MACRO
#define	ledon()			LED_PORT |= _BV(LED_PIN)
#define	ledoff()		LED_PORT &= ~_BV(LED_PIN)


//FUNCTION PROTOTYPES
void blink		(int8u nblink, int8u ontime);
void ledinit	(void);
#endif
