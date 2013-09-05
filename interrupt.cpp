
#include "interrupt.h"

volatile static voidFuncPtr_INT intFunc[EXTERNAL_NUM_INTERRUPTS];
volatile static voidFuncPtr_PC PCFunc[PC_NUM_INTERRUPTS];

void AttachExtInterrupt(uint8_t interruptNum, void (*userFunc)(void), uint8_t mode)
{
	intFunc[interruptNum] = userFunc;
	switch(interruptNum)
	{
	case 0:
		EIMSK |= _BV(INT0);  //Enable INT0
		EICRA |= (mode << ISC00);
	case 1:
		EIMSK |= _BV(INT1);  //Enable INT0
		EICRA |= (mode << ISC10);
	}
	  sei();
}

void AttachPCInterrupt(uint8_t interruptNum, uint8_t pcNum, void (*userFunc)(void))
{
	PCFunc[interruptNum] = userFunc;
	switch(interruptNum)
	{
	case 0:
		PCICR |= _BV(PCIE0);  //Enable PCINT0
		PCMSK0 |= (1 << pcNum);
	case 1:
		PCICR |= _BV(PCIE1);;  //Enable PCINT1
		PCMSK1 |= (1 << pcNum);
	case 2:
		PCICR |= _BV(PCIE2);   //Enable PCINT2
		PCMSK2 |= (1 << pcNum);
	}
	  sei();
}

void DetachExtInterrupt(uint8_t interruptNum)
{
	 switch (interruptNum) {
	    case 0:
	      EIMSK &= ~(1 << INT0);
	      break;
	    case 1:
	      EIMSK &= ~(1 << INT1);
	      break;
	    }
	    intFunc[interruptNum] = 0;
 }
void DetachPCInterrupt(uint8_t interruptNum)
{
	 switch (interruptNum) {
	    case 0:
	    	PCICR &= ~(1 << PCIE0);
	      break;
	    case 1:
	    	PCICR &= ~(1 << PCIE1);
	      break;
	    case 2:
	   	    	PCICR &= ~(1 << PCIE2);
	   	      break;
	    }
	    PCFunc[interruptNum] = 0;
 }

ISR(INT0_vect)
{
	  if(intFunc[EXTERNAL_INT_0])
	    intFunc[EXTERNAL_INT_0]();
}
ISR(INT1_vect) {
  if(intFunc[EXTERNAL_INT_1])
    intFunc[EXTERNAL_INT_1]();
}

ISR(PCINT0_vect) {
  if(PCFunc[EXTERNAL_INT_0])
    PCFunc[EXTERNAL_INT_0]();
}
ISR(PCINT1_vect) {
  if(PCFunc[EXTERNAL_INT_1])
    PCFunc[EXTERNAL_INT_1]();
}

ISR(PCINT2_vect) {
  if(PCFunc[EXTERNAL_INT_2])
    PCFunc[EXTERNAL_INT_2]();
}




