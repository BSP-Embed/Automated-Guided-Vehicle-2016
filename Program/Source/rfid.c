
#include "rfid.h"


extern volatile struct  {
	volatile int8u Desti:1;
	volatile int8u WGoods:1;
	volatile int8u SMSObjDet:1;
	volatile int8u RFIDtag:1;
}Flags;


/* RFID Tags for guiding */
const  char *tag[] = { "",
	"0800883A70CA",
	"0800891A4AD1",
	"080089089019",
	"080088F54633",
	"0800882B47EC",
	"0800891B69F3",
	/* RFID Tags for GOODS */
	"0800884C38F4",
	"0800885C0ED2",
	"08008872B547",
};


int8u sbuf[25];

int8u readtag(void)
{
	int8u i, j;
	j = 0;
	Flags.RFIDtag = 0;
//	sbuf[0] = '\0';
	
//	EnUARTInt();
//	RFIDEn();
	
//	while (++j < 5 && !Flag.RFIDtag)
//		dlyms(100);
	
	#if defined DISPLAY_TAGNUMBER >= 1
		int8u tag_count ;
		lcdclrr(1);
		lcdws(sbuf);
		for(;;);
	#endif
	
	
	DisUARTInt();

	for (i = 1; i <= 9; i++)
		if(veritag(sbuf,tag[i])) {
			beep(1,100);
			return i;
		}

	return 0;
	
}
static int8u veritag(char *tag_temp, char *tag)
{
	int8u i;
	

	for( i = 0; i < 12 ;i++)
		if(*tag_temp++ != *tag++)
			return 0;
	
	return 1;
}

ISR(USART_RXC_vect)
{
	static int8u i,cnt;

	if ((sbuf[i++] = UDR) && ++cnt == 12) {
		Flags.RFIDtag = 1;
		sbuf[i] = '\0';
		i = 0;
		cnt = 0;
		DisUARTInt();
	}
}
