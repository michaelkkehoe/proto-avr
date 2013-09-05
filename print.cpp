#include "print.h"

/* default implementation: may be overridden */

void send(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void write(const char *str)
{
  while (*str)
    send(*str++);
}

/* default implementation: may be overridden */
void write(const uint8_t *buffer, size_t size)
{
  while (size--)
    send(*buffer++);
}

void print(const char str[])
{
  write(str);
}

void print(char c, int base)
{
  print((long) c, base);
}

void print(unsigned char b, int base)
{
  print((unsigned long) b, base);
}

void print(int n, int base)
{
  print((long) n, base);
}

void print(unsigned int n, int base)
{
  print((unsigned long) n, base);
}

void print(long n, int base)
{
  if (base == 0) {
    send(n);
  } else if (base == 10) {
    if (n < 0) {
      print('-');
      n = -n;
    }
    printNumber(n, 10);
  } else {
    printNumber(n, base);
  }
}

void print(unsigned long n, int base)
{
  if (base == 0) send(n);
  else printNumber(n, base);
}

void print(double n, int digits)
{
  printFloat(n, digits);
}

void println(void)
{
  print('\r');
  print('\n');
}


// Private Methods /////////////////////////////////////////////////////////////

void printNumber(unsigned long n, uint8_t base)
{
  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
  unsigned long i = 0;

  if (n == 0) {
    print('0');
    return;
  }

  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--)
    print((char) (buf[i - 1] < 10 ?
      '0' + buf[i - 1] :
      'A' + buf[i - 1] - 10));
}

void printFloat(double number, uint8_t digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
     print('-');
     number = -number;
  }
  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print(".");

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint;
  }
}


void MoveCursor(uint8_t x, uint8_t y)
{
	 print(27,BYTE);
	 print('[');
	 print(y,DEC);
	 print(';');
	 print(x,DEC);
	 print('H');
}
void ClearTerminal()
{
	 print(27,BYTE);
	 print("[2J");
}
void CTEOF()
{
	print(27,BYTE);
	print("[K");
}


