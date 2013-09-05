#include <stdio.h> // for size_t
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


#define ClockCyclesPerMicrosecond() (F_CPU / 1000000L )
#define ClockCyclesToMicroseconds(a) ((a) / ClockCyclesPerMicrosecond() )
#define MicrosecondsToClockCycles(a) ((a) * ClockCyclesPerMicrosecond() )

void DelayMilliseconds(unsigned long ms);
void DelayMicroseconds(unsigned long us);

typedef void (*voidFuncPtr)(void);

void InitTimer(uint8_t noTimer,void (*userFunc)(void),  uint8_t prescaler,long OCR);


