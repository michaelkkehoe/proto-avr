/*
 * spi.cpp
 *
 *  Created on: 01/02/2011
 *      Author: build
 */
#include "spi.h"
#include "digital.h"

#define LSBFIRST 0
#define MSBFIRST 1

void SPI_MasterBegin(uint8_t Pin,uint8_t BitOrder, uint8_t DataMode, uint8_t ClockSpeed)
{
	/* Set MOSI and SCK output, all others input */
	//DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	  PinMode(SCK, OUTPUT);
	  PinMode(MOSI, OUTPUT);
	  PinMode(SS, OUTPUT);

	  DigitalWrite(SCK, LOW);
	  DigitalWrite(MOSI, LOW);
	  DigitalWrite(SS, HIGH);


	 if(BitOrder == LSBFIRST) {
	    SPCR |= _BV(DORD);
	  } else {
	    SPCR &= ~(_BV(DORD));
	  }

	 SPCR = (SPCR & ~SPI_MODE_MASK) | DataMode;
	 SPCR = (SPCR & ~SPI_CLOCK_MASK) | (ClockSpeed & SPI_CLOCK_MASK);
	 SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | (ClockSpeed & SPI_2XCLOCK_MASK);

	/* Enable SPI, Master*/
	SPCR = (1<<SPE)|(1<<MSTR);
}
void SPI_SlaveBegin(void)
{
	/* Set MISO output, all others input */
	//DDR_SPI = (1<<DD_MISO);
	PinMode(MISO, OUTPUT);

	/* Enable SPI */
	SPCR = (1<<SPE);
}

void SPI_End(void)
{
	  SPCR &= ~_BV(SPE);
}
char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
		;
	/* Return Data Register */
	return SPDR;
}
void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
		;
}

void AttachInterrupt() {
  SPCR |= _BV(SPIE);
}
void DetachInterrupt() {
  SPCR &= ~_BV(SPIE);
}
