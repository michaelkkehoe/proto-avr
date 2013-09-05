#include "pulse.h"
#include "time.h"

#include "digital.h"


const uint8_t pins[8] = {
  WPIN0, WPIN1, WPIN2, WPIN3, WPIN4, WPIN5, WPIN6, WPIN7
};

void Pulse(uint8_t pin, uint8_t noTimes, long timeHigh, long timeLow)
{
	PinMode(pin, OUTPUT);
	for(long i =0; i < noTimes;i++)
	{
	DigitalWrite(pin, HIGH);
	DelayMilliseconds(timeHigh);
	DigitalWrite(pin, LOW);
	DelayMilliseconds(timeLow);
	}
}

unsigned long PulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
	// cache the port and bit of the pin in order to speed up the
	// pulse width measuring loop and achieve finer resolution.  callingu
	// digitalRead() instead yields much coarser resolution.
	//uint8_t bit = digitalPinToBitMask(pin);
	//uint8_t port = digitalPinToPort(pin);

	unsigned long width = 0; // keep initialization out of time critical area

	// convert the timeout from microseconds to a number of times through
	// the initial loop; it takes 16 clock cycles per iteration.
	unsigned long numloops = 0;
	unsigned long maxloops = MicrosecondsToClockCycles(timeout) / 16;

	// wait for any previous pulse to end
	while (DigitalRead(pin) == state)
		if (numloops++ == maxloops)
			return 0;

	// wait for the pulse to start
	while (DigitalRead(pin) != state)
		if (numloops++ == maxloops)
			return 0;

	// wait for the pulse to stop
	while (DigitalRead(pin) == state)
		width++;

	// convert the reading to microseconds. The loop has been determined
	// to be 10 clock cycles long and have about 16 clocks between the edge
	// and the start of the loop. There will be some error introduced by
	// the interrupt handlers.
	return ClockCyclesToMicroseconds(width * 10 + 16);
}
