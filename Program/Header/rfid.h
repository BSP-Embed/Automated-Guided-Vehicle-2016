#ifndef RFID_H
#define RFID_H

#include "includes.h"



#define RFIDEn()			do {										\
								GSM_GPS_PORT &= ~_BV(RFID_GSMP_PIN);	\
								dlyms(500);								\
							} while(0)

/******** DEFINE FUNCION PROTOTYPES ********/
int8u readtag(void);
static int8u veritag(char *tag_temp, char *tag);

#endif