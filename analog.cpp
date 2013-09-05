/*
Copyright (C) 2012 Michael Kehoe

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation 
the rights touse, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "analog.h"

void AnalogBegin(uint8_t mode){
	ADMUX = (mode << REFS0);
	ADCSRA = _BV(ADEN) | _BV(ADPS0) | _BV(ADPS1);
}

int AnalogRead(uint8_t channel,uint8_t read_times){
	long total = 0;
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

	for(int i=0; i < read_times;i++){
		// Tell the microcontroller to start conversion
		ADCSRA |= _BV(ADSC);

		while ((ADCSRA & _BV(ADIF)) == 0);
		unsigned char low_byte, high_byte;
		low_byte = ADCL;
		high_byte = ADCH;

		// Clear the ADIF bit so that ADC is ready for the next conversion
		ADCSRA |= _BV(ADIF);

		// Return the value read
		total += (int) (high_byte * 255 + low_byte);
	}
	return (int) total/read_times;
}

void AnalogWrite(uint8_t pin, uint8_t value){
	switch(pin)	{
		case 3:
			TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
			TCCR2B = _BV(CS22);
			OCR2B = value;
			break;
		case 5:
			TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
			TCCR0B = _BV(CS02);
			OCR0B = value;
			break;
		case 6:
			TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
			TCCR0B = _BV(CS02);
			OCR0A = value;
			break;
		case 9:
			TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
			TCCR1B = _BV(CS12);
			OCR1A = value;
			break;
		case 10:
			TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
			TCCR1B = _BV(CS12);
			OCR1B = value;
			break;
		case 11:
			TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
			TCCR2B = _BV(CS22);
			OCR2A = value;
			break;
	}
}
