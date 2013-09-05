#include <avr/io.h>
#include <stdio.h>


#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

void println(void);
void printNumber(unsigned long, uint8_t);
void printFloat(double, uint8_t);

void write(const char *str);
void write(const uint8_t *buffer, size_t size);
void print(const char[]);

void print(char, int = BYTE);
void print(unsigned char, int = BYTE);
void print(int, int = DEC);
void print(unsigned int, int = DEC);
void print(long, int = DEC);
void print(unsigned long, int = DEC);
void print(double, int = 2);

void MoveCursor(uint8_t x, uint8_t y);
void ClearTerminal();
void CTEOF();

