#include "time.h"

volatile static voidFuncPtr intFunc[2];

void DelayMilliseconds(unsigned long ms)
{
	_delay_ms(ms);
}
void DelayMicroseconds(unsigned long us)
{
	_delay_us(us);
}

void InitTimer(uint8_t noTimer,void (*userFunc)(void), uint8_t prescaler,long OCR)
{
	intFunc[noTimer] = userFunc;
	switch(noTimer)
	{
	case 0:
		TCCR0A = 0;
		TCCR0B = (1<<WGM02)|(prescaler << CS00);
		OCR0A = OCR;
		TIMSK0 = (1<<OCIE0A);
		 break;
	case 1:
		TCCR1A = 0;
		TCCR1B = (1<<WGM12)|(prescaler << CS10);
		OCR1A = OCR;
		TIMSK1 = (1<<OCIE1A);
		break;
	case 2:
		TCCR2A = 0;
		TCCR2B = (1<<WGM22)|(prescaler << CS20);
		OCR2A = OCR;
		TIMSK2 = (1<<OCIE2A);
		break;
	}
	sei();
}

ISR(TIMER0_COMPA_vect)
{
	if(intFunc[0])
		    intFunc[0]();
}
ISR(TIMER1_COMPA_vect)
{
	if(intFunc[1])
		intFunc[1]();
}
ISR(TIMER2_COMPA_vect)
{
	if(intFunc[2])
		intFunc[2]();
}


