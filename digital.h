#include <stdio.h> // for size_t
#include <avr/io.h>

#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1
#define WPIN0 (1<<0)
#define WPIN1 (1<<1)
#define WPIN2 (1<<2)
#define WPIN3 (1<<3)
#define WPIN4 (1<<4)
#define WPIN5 (1<<5)
#define WPIN6 (1<<6)
#define WPIN7 (1<<7)

void PinMode(uint8_t pin, uint8_t mode);
void PortMode(uint8_t, uint8_t);
void DigitalWrite(uint8_t pin, uint8_t val);
uint8_t PortRead(uint8_t);
void PortWrite(uint8_t, uint8_t);
uint8_t DigitalRead(uint8_t pin);



