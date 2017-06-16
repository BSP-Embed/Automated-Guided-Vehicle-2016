#ifndef _BUZ_H
#define _BUZ_H

//INCLUDES
#include "includes.h"

// define constants


// DEFINE PORTS



//DEFINE MACRO
#define	buzon()			BUZ_PORT |= _BV(BUZ_PIN)
#define	buzoff()		BUZ_PORT &= ~_BV(BUZ_PIN)

//FUNCTION PROTOTYPES
void beep		(int8u nbeep, int16u ontime);
void buzinit	(void);
#endif

