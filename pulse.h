#include "time.h"
#include <inttypes.h>
#include <stdio.h> // for size_t

unsigned long PulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
void Pulse(uint8_t pin, int noTimes, long timeHigh, long timeLow);
