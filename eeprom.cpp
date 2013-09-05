#include "EEPROM.h"

//ifdef atmega 48
//#define size 256
//elif #define size 512

uint8_t EEPROMRead(int address)
{
	return eeprom_read_byte((unsigned char *) address);
}

void EEPROMWrite(unsigned char address, uint8_t value)
{
	eeprom_write_byte((unsigned char *) address, value);
}

void EEPROMClear()
{
	for (int i = 0; i < 512; i++)
	{
		eeprom_write_byte((unsigned char *) i, 0);
	}
}




