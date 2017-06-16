#ifndef GSM_H
#define GSM_H

//INCLUDE HEADER FILES
#include "includes.h"

//FUNCTION PROTOTYPES	
void 	GSMsndmsg		(const char *PhNum, const char *GSMMsg);
int8u 	GSMinit			(void);
int8u 	gsm_call_gen	(const char *PhNum);
void	GSMRxCall		(void);		
void	GSMDisCall		(void);	

#endif
