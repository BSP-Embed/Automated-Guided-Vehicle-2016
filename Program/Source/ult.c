
#include "ult.h"

extern int8u lcdptr;
static int16u ultpulse;

/* Returns distance in meters */
float MeasDist(int8u disp)
{
	
	int8u i;
	char s[10];
	unsigned long cnt;
	float dist;
	
	cnt = 0;
	
	for (i = 0; i < 4; i++) {
		calcdist();
		cnt += ultpulse;
	}
	cnt >>= 2; 
	
	dist = (cnt * ULTRASONIC_CONST);

	if (disp != 0) {
		lcdptr = disp;
		lcdws("     ");
		ftoa(dist,s,2);
		lcdptr = disp;
		lcdws(s);
	} 
	
	return dist;
}
static void calcdist(void)
{
	ULTSEN_PORT		|= _BV(TRIG_PIN);
	dlyus(10);
	ULTSEN_PORT		&= ~_BV(TRIG_PIN);
	
	ultpulse = 0;

	while ((ULTSEN_PIN & _BV(ECHO_PIN)) == 0);
	StartTmr();
	while (ULTSEN_PIN & _BV(ECHO_PIN));
	StopTmr();
	
}
void ultinit(void)
{
	ULTSEN_DDR 		|= _BV(TRIG_PIN);
	ULTSEN_DDR 		&= ~_BV(ECHO_PIN);

	ULTSEN_PORT		&= ~_BV(TRIG_PIN);
	ULTSEN_PORT		|= _BV(ECHO_PIN);
	
	tmr0init();
}
static void tmr0init(void)
{
	TCNT0   =  167;
	TIMSK   |= _BV(TOIE0);			//ENABLE OVERFLOW INTERRUPT
	
}
/* OverFlows every 100us */
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 167;
	++ultpulse;
	
}