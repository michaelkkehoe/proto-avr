#include <stdio.h> // for size_t
#include <avr/io.h>


#define EVEN 2
#define ODD 3
#define NO 0

void HSerialBegin(uint16_t baud = 9600, uint8_t data= 8, uint8_t parity =0, uint8_t stop=1);
void HSerialSend(unsigned char data);
unsigned char HSerialRecieve();
void HSerialFlush();


