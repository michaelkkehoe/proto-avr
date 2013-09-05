#include <stdio.h> // for size_t
#include <avr/eeprom.h>

uint8_t EEPROMRead(int);
void EEPROMWrite(unsigned char address, uint8_t value);
void EEPROMClear();



