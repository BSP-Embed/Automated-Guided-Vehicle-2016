/* gsm.c:	interface program for GSM modem */
#include "gsm.h"

//GSM AT COMMANDS

const char ATCommand[] 	 = "AT\r"; 
const char ATCall[]  	 = "ATD";
const char SMSCode[]  	 = "AT+CMGF=1\r";
const char SMSNumber[] 	 = "AT+CMGS=\"0";
const char SMSSettings[]  = "AT+CNMI=2,2,2,0,0\r";
const char ATRxCall[]	  = "ATA\r";
const char ATDisCall[]	  = "ATH\r";

static void GSMerr		(void);
static int8u GSMmsgparam(void);
static int8u GSMRxResp	(void);
static int8u GSMsndphnum(const char *PhNum);
static void GSMrxack	(void);

void GSMsndmsg(const char *PhNum, const char *GSMMsg)
{
	lcdclrr(1);
	
	lcdws("Sending SMS:");
	if(GSMsndphnum(PhNum)) {
		puts(MSG_START);
		puts(GSMMsg);
		puts(MSG_END);
		putchar(0x1A);
		GSMrxack();
	} else	GSMerr();
	lcdws("OK");
	GSMRxResp();
	dlyms(1000);
	lcdclrr(1);
}
int8u GSMinit(void)
{
	lcdclrr(1);
	lcdws("GSM: ");
	if(GSMRxResp() && GSMmsgparam() ) {
		lcdws("OK");
		dlyms(1000);
		return 1;
	} else {
		GSMerr();
		return 0;
  } 
}
static void GSMerr(void)
{
	 lcdclrr(1);
	 lcdws("FAILED !"); 
}
static int8u GSMRxResp(void)
{
	puts(ATCommand);
	while(getchar() != 'K');
	return 1;
}
static int8u GSMmsgparam(void)
{
	puts(SMSCode);
  while(getchar() != 'K');
	puts(SMSSettings);
  while(getchar() != 'K');
	return 1;
}
static int8u GSMsndphnum(const char *PhNum)
{
	puts(SMSNumber);
	puts(PhNum);
	puts("\"\r");
	while (getchar() != '>');
	return 1;
}
static void GSMrxack(void)
{
	int8u x;
	do {
	 	x = getchar();
	 }while(x != 'K' && x != 'E');
	 if(x == 'E') if(! GSMRxResp() ) GSMerr();
}
int8u gsm_call_gen(const char *PhNum)
{
	puts(ATCall);
	puts(PhNum);
	puts(";\r");
	return 1;
}
void GSMRxCall(void)
{
	puts(ATRxCall);
}
void GSMDisCall(void)
{
	puts(ATDisCall);
}
