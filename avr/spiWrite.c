/* AVR software SPI routines
 * @author: Ralph Doncaster 2015
 */

#include <avr/io.h>

#define SPIPORT PORTB
#define SPIPIN PINB
#define MOSI 4
#define CLK 5
const uint8_t mosipinmask = (1<<MOSI);
const uint8_t clkpinmask = (1<<CLK);

void spiWrite(uint8_t data)
{
 uint8_t bit;
 for(bit = 0x80; bit; bit >>= 1) {
  SPIPORT &= ~clkpinmask;
  if(data & bit) SPIPORT |= mosipinmask;
  else SPIPORT &= ~mosipinmask;
  SPIPORT |= clkpinmask;
 }
}


void spi_byte(uint8_t byte){

	uint8_t i = 8;
	
	do{
		SPIPORT &= ~mosipinmask;
		if(byte & 0x80) SPIPORT |= mosipinmask; 
		SPIPORT |= clkpinmask;  // clk hi
		byte <<= 1;
		SPIPORT &=~ clkpinmask; // clk lo
	
	}while(--i);

	return;
}

void spi_bytePIN(uint8_t byte){

	uint8_t i = 8;
	
	do{
		SPIPORT &= ~mosipinmask;
		if(byte & 0x80) SPIPIN = mosipinmask; 
		SPIPIN = clkpinmask;     // clk hi
		byte <<= 1;
		SPIPIN = clkpinmask;     // clk lo
	
	}while(--i);

	return;
}

void spi_byteFast(uint8_t byte){

	uint8_t i = 8;
	uint8_t portbits = (SPIPORT & ~(mosipinmask | clkpinmask) );
	
	do{
		SPIPORT = portbits;      // clk and data low
		if(byte & 0x80) SPIPIN = mosipinmask; 
		SPIPIN = clkpinmask;     // toggle clk
		byte <<= 1;
	}while(--i);

	return;
}

