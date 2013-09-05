#include <stdio.h> // for size_t
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define CHANGE 1
#define FALLING 2
#define RISING 3
#define EXTERNAL_NUM_INTERRUPTS 2
#define PC_NUM_INTERRUPTS 3
#define EXTERNAL_INT_0 0
#define EXTERNAL_INT_1 1
#define EXTERNAL_INT_2 2

typedef void (*voidFuncPtr_INT)(void);
typedef void (*voidFuncPtr_PC)(void);

void AttachExtInterrupt(uint8_t intNum, void (*userFunc)(void), uint8_t mode);
void DetachExtInterrupt(uint8_t interruptNum);

void AttachPCInterrupt(uint8_t interruptNum, uint8_t pcNum, void (*userFunc)(void));
void DetachPCInterrupt(uint8_t interruptNum);






