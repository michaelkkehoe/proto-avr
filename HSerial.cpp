#include "HSerial.h"


void HSerialBegin(uint16_t baud, uint8_t data, uint8_t parity, uint8_t stop)
{
	/* Set Baud rate(Async Normal) */
	uint8_t ubrr = F_CPU/16/baud -1;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	/* Enable transmitter and receiver*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	/*Set frame format*/
	UCSR0C = (stop <<USBS0)|((data-5) <<UCSZ00)|(parity << UPM00);


}
void HSerialSend(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
unsigned char HSerialRecieve()
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

void HSerialFlush()
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}






