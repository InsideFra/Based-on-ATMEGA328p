/*
 * functions.c
 *
 * Created: 04/03/2018 11:54:15
 *  Author: franc
 */

#include "functions.h"
#include "../define.h"
#include <avr/io.h>
#include <string.h>

extern volatile uint16_t __ms;
extern volatile unsigned long __lastTimerSeconds; // Should atleast 136 years

volatile uint8_t Sending = 0;


void set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool LowHIGH) {
	int DDR = (PORT) - 0x01;
	if (INPOUT)  {
		// Pin output, default low
		(*(volatile uint8_t *)(DDR)) |= (1 << PINNumb); // Pin output
		(*(volatile uint8_t *)(PORT)) &= !(1 << PINNumb); // Pin Low
	} else (*(volatile uint8_t *)(DDR)) &= (0xFF^(1 << PINNumb)); // Pin input
	if(LowHIGH) {
		// Set Pin High, --> set pin output
		(*(volatile uint8_t *)(DDR)) |= (1 << PINNumb); // Pin Output
		(*(volatile uint8_t *)(PORT)) |= (1 << PINNumb); } // Pin High
}

void toggle_pin(int PORT, int PINNumb) {
	int DDR = (PORT) - 0x01;
	// uint8_t* PIN = (PORT) - 0x02;
	if( ((*(volatile uint8_t*)(DDR)) & (1 << PINNumb)) == (1 << PINNumb) ) { // Pin output
		(*(volatile uint8_t*)(PORT)) ^= (1 << PINNumb); // Pin Toggled
	}
}

_Bool getstatus_pin(int PORT, int PINNUmb) {
	// work ins progress
	return 0;
}

void start_SPI(int PORTMosi, int PORTMiso, int PORTSckl, _Bool MasterSlave, _Bool MSBLSBFirst, int clk, _Bool clkRisingFalling) {
	if(!MasterSlave) { // SPI as master
	set_pin(PORTSS,   2, OUTPUT, 0);
	set_pin(PORTMosi, 3, OUTPUT, 0);
	set_pin(PORTMiso, 4, INPUT,  0);
	set_pin(PORTSckl, 5, OUTPUT, 0); }
	SPCR = wRegister;
	// Setup as : Interrupt enabled (SPIE0 bit 7 set 1), Spi Enabled (SPE0 bit 6 set 1), MSB First (DORD bit 5 set 0),  Master Enabled (MSTR bit 4 set 1),
	// clk Rising ( CPOL bit 3 set 0), bit 2 not use, SPI Clock Rate set as fosc/64 ( SPR [0, 1])
	if(MasterSlave)     SPCR ^= (1 << MSTR);     // Setup as Slave , MSTR must be 0
	if(MSBLSBFirst)     SPCR ^= (1 << DORD);     // Setup as LSB First, DRDB must be 1
	if(clkRisingFalling) SPCR ^= (1 << CPOL); // Setup as Falling Edge, CPOL must be 1
}

_Bool sendoverspi(uint8_t _data, uint8_t action) {
	if(Sending == 0) {
		Sending = action;
		SPDR = _data;
		return 1;
	}
	return 0;
}

// Timers
void updateRTC() { // Funzione ogni secondo

}
// END

struct time functTime() {
	uint32_t allms =  __lastTimerSeconds;
};
