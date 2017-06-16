#include "main.h"

const char *MSG[] = { "Object Detected",
					  "Destination Reached",
					  "Wrong goods Detected"
					};

volatile struct  {
	volatile int8u Desti:1;
	volatile int8u WGoods:1;
	volatile int8u SMSObjDet:1;
	volatile int8u RFIDtag:1;
}Flags;

extern int8u lcdptr;

int main(void)
{
	init();
	
	while (TRUE) {
		TaskMove();
		TaskDesti();
	}
	
	return 0;
}
static void TaskMove(void)
{
	Move();
	EnRFID();

	while (!Flags.Desti) {
		
		if (MeasDist(0) <= DIST_THRESHOLD) {
			if (Flags.SMSObjDet == TRUE) {
				stop();
				sendSMS(1);
				lcdclrr(1);
				Flags.SMSObjDet = FALSE;
			}
		} else { 
			Move();
			Flags.SMSObjDet = TRUE;
		}
					
		if (Flags.RFIDtag) {				
			switch(readtag()) {
				case 1: case 2: case 5:	Move(); break;
				case 3: Left(); break;
				case 4: Right(); break;
				case 6: stop(); Flags.Desti = 1; break;
			}
			Flags.RFIDtag = 0; //Flags.SBUF = 0;
			EnUARTInt();
		} 
	}
}	
static void TaskDesti(void)
{
	lcdclr();
	lcdws("Desti'n Reached");
	beep(1,100);
	dlyms(1000);
	sendSMS(2);
	lcdclrr(1);
	EnUnRFID();

	while (TRUE) {
		if (Flags.RFIDtag) {				
			switch(readtag()) {
				case 8: beep(1,250);
						lcdr2();
						lcdws("  Wrong Goods");
						DisUnRFID();
						dlyms(1000);
						sendSMS(3);
						lcdclrr(1);
						break;
			}
			Flags.RFIDtag = 0;
			EnUnRFID();

		}
	}	
}
	
static void init(void)
{
	buzinit();
	beep(2,100);
	ledinit();
	gpioinit();
	flagsinit();	
	lcdinit();
	uartinit();
	HX711init();
	EnGSM();
	GSMinit();
	tmr2init();
	ultinit();
	servoinit();
	motorinit();
	TestOVLoad();
	disptitl();
	sei();
}
static void flagsinit(void)
{
	Flags.Desti = FALSE;
	Flags.WGoods = FALSE;
	Flags.RFIDtag= FALSE;
	Flags.SMSObjDet = TRUE;
	
}
static void TestOVLoad(void)
{
	static flag = 0;
	lcdclr();
	lcdws("  Testing Load");
	
	lcdr2();
	dlyms(1000);
	
	while (measwt(0) > NORMAL_LOAD) {
			if (!flag) {
				lcdws("OverLoad in Vehi");
				flag = 1;
			}
			beep(1,75);
	}
	dlyms(1000);
	
	lcdclr();
	lcdws("  Vehicle Will");
	lcdr2();
	lcdws("Move in 5Seconds");
	dlyms(5000);
}
		
static void gpioinit(void)
{
	
	GSM_RFID_DDR |= _BV(GSM_RFID_PIN);
	GSM_RFID_DDR &= ~_BV(GSM_RFID_PIN);
	
	RLY_DDR		|= _BV(RLY_PIN);
	RLY_PORT 	&= ~_BV(RLY_PIN);

}
static void disptitl(void)
{
	lcdclr();
	lcdws("Auto Guided Vehi");
}
static void tmr2init(void)
{
	TCNT2   = 75;
	TIMSK   |= _BV(TOIE2);			//ENABLE OVERFLOW INTERRUPT
	TCCR2  |=  _BV(CS22) | _BV(CS21) | _BV(CS20); /* PRESCALAR BY 256 */
}

/* overflows at every 25msec */
ISR(TIMER2_OVF_vect)
{
	static int8u i,j,k;
	TCNT2 = 75;

	if (++i >= 200) i = 0;
	switch(i) {
		case 0: case 5: ledon(); break;
		case 1: case 6: ledoff(); break;
	}
}

static void Left(void)
{
	lcdr2();
	lcdws("  MOVING LEFT   ");
	beep(1,100);
	TurnLeft();
}
static void Right(void)
{
	lcdr2();
	lcdws("  MOVING RIGHT  ");
	beep(1,100);
	TurnRight();
}
static void Move(void)
{
	MotClk();
	lcdr2();
	lcdws(" MOVING FORWARD ");

}
static void stop(void)
{
	lcdr2();
	lcdws("VEHICLE STOPPED ");
	MotStop();
	beep(2,250);
	dlyms(DISP_DLY);
}

