#ifndef _MOTOR_H
#define _MOTOR_H

#include "includes.h"

#define mot1on()			MOT_PORT |= _BV(MOT1_AN)
#define mot1off()			MOT_PORT &= ~_BV(MOT1_AN)

#define mot2on()			MOT_PORT |= _BV(MOT2_AN)
#define mot2off()			MOT_PORT &= ~_BV(MOT2_AN)

void	motorinit	(void);
void	MotClk		(void);
void	MotAclk	(void);
void	MotStop		(void);

#endif
