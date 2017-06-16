#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define GSM_RFID_DDR		DDRC
#define GSM_RFID_PORT		PORTC
#define GSM_RFID_PIN		PC7

#define RLY_DDR				DDRC
#define RLY_PORT			PORTC
#define RLY_PIN				PC6

//DEFINE CONSTANT
#define DIST_THRESHOLD		0.5f
#define NORMAL_LOAD			500		/* in gms */


//DEFINE MACROS
#define StartTmr()			TCCR0  	|= _BV(CS01)
#define StopTmr()			TCCR0  	&= ~_BV(CS01)


#define EnGSM()				do {									\
								GSM_RFID_PORT &= ~_BV(GSM_RFID_PIN); \
								dlyms(250);						\
							} while(0)

#define EnRFID()			do {									\
							GSM_RFID_PORT |= _BV(GSM_RFID_PIN);		\
							EnUARTInt();							\
							} while(0)

#define sendSMS(x)			do {						\
							DisUARTInt();				\
							EnGSM();					\
							GSMsndmsg(OPhNum, MSG[x-1]);	\
							dlyms(1000);				\
							EnRFID();					\
							} while(0)

#define EnUnRFID()			do {						\
							RLY_PORT |= _BV(RLY_PIN); 	\
							dlyms(500);					\
							EnUARTInt();				\
							} while(0)					\

#define DisUnRFID()			do {						\
							RLY_PORT &= ~_BV(RLY_PIN); 	\
							dlyms(100);					\
							} while(0)					\

//FUNCTION PROTOTYPES
static void		init		(void);
static void 	disptitl 	(void);
static void 	tmr1init	(void);
static void 	tmr2init	(void);
static void  	gpioinit	(void);
static void		flagsinit	(void);
static void		Move		(void);
static void 	stop		(void);
static void 	Right		(void);
static void 	Left		(void);
static void 	TaskMove	(void);
static void		TaskDesti	(void);
static void 	TestOVLoad	(void);

#endif
