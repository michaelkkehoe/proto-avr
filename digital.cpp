#include "digital.h"

const uint8_t pins[8] = {
  WPIN0, WPIN1, WPIN2, WPIN3, WPIN4, WPIN5, WPIN6, WPIN7
};

volatile uint8_t * ports[3] = {
  &PORTD, &PORTB, &PORTC
};

volatile uint8_t * portsddr[3] = {
  &DDRD, &DDRB, &DDRC
};

volatile uint8_t * portspin[3] = {
  &PIND, &PINB, &PINC
};

void PinMode(uint8_t pin, uint8_t mode) {
  if(mode == OUTPUT) {
    uint8_t oldSREG = SREG;
    *portsddr[pin/8] |= pins[pin%8];
    SREG = oldSREG;
  } else {
    uint8_t oldSREG = SREG;
    *portsddr[pin/8] &= ~pins[pin%8];
    SREG = oldSREG;
  }
}

void PortMode(uint8_t port, uint8_t mode) {
  if(mode == OUTPUT) {
    *portsddr[port] = 0xff;
  } else {
    *portsddr[port] = 0x00;
  }
}

uint8_t DigitalRead(uint8_t pin) {
  if(*portspin[pin/8] & pins[pin%8])
    return 1;
  return 0;
}

uint8_t PortRead(uint8_t port) {
  return *portspin[port];
}

void DigitalWrite(uint8_t pin, uint8_t val) {
  if(val == HIGH) {
    uint8_t oldSREG = SREG;
    *ports[pin/8] |= pins[pin%8];
    SREG = oldSREG;
  } else {
    uint8_t oldSREG = SREG;
    *ports[pin/8] &= ~pins[pin%8];
    SREG = oldSREG;
  }
}

void PortWrite(uint8_t port, uint8_t val) {
  *ports[port] = val;
}



















