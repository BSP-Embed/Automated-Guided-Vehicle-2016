#include"uart.h"

void uartinit(void)
{
	UCSRB |= _BV(RXEN) | _BV(TXEN);					//Turn on transmission and reception
	UCSRC |= _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1); //use 8-bit character size, select the UCSRL
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}
void putchar(char ch)
{
	while((UCSRA & _BV(UDRE)) == 0) {};
	UDR = ch;
	
}
int8u getchar(void)
{
	while((UCSRA & _BV(RXC) ) == 0) {};
	return UDR;
}
void puts(const char *s)
{
	while(*s) {
		putchar(*s++);
		dlyms(1);
	}
}
void EnUARTInt(void)
{
	int8u tmp;
	tmp = UDR;
	tmp = UDR;
	tmp = UDR;
	UCSRB |= (1 << 7);	/* Enable receive complete INT */
}
void DisUARTInt(void)
{
	int8u tmp;
	tmp = UDR;
	tmp = UDR;
	tmp = UDR;
	UCSRB &= ~(1 << 7);	/* Disable receive complete INT  */
	
}