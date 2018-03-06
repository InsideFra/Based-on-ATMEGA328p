/*
 * functions.c
 *
 * Created: 04/03/2018 11:54:15
 *  Author: franc
 */ 

#include "functions.h"
#include "../define.h"
#include <avr/io.h>


void set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool INOUT) {
	int DDR = (PORT) - 0x01;
	if (INPOUT)  {
		// Pin output, default low
		(*(volatile uint8_t *)(DDR)) |= (1 << PINNumb); // Pin output
		(*(volatile uint8_t *)(PORT)) &= (255^(1 << PINNumb) ); // Pin Low
	} else (*(volatile uint8_t *)(DDR)) &= (0xFF^(1 << PINNumb)); // Pin input
	if(INOUT) {
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

void start_SPI(int PORTMosi, int PORTMiso, int PORTSckl, _Bool MasterSlave, _Bool MSBLSBFirst, int clk, _Bool clkRisingFalling) {
	if(MasterSlave) { // SPI as master
	set_pin(PORTSS,   2, OUTPUT, 0);
	set_pin(PORTMosi, 3, OUTPUT, 0);
	set_pin(PORTMiso, 4, INPUT,  0);
	set_pin(PORTSckl, 5, OUTPUT, 0); }
	uint8_t fool = 0b01010000; 
	// Setup as : Interrupt disabled (SPIE0 bit 7 set 0), Spi Enabled (SPE0 bit 6 set 1), MSB First (DORD bit 5 set 0),  Master Enabled (MSTR bit 4 set 1),
	// clk Rising ( CPOL bit 3 set 0), bit 2 not use, SPI Clock Rate set as fosc/4 ( SPR [0, 1])
	if(!MasterSlave) fool ^= (1 << MSTR);     // Setup as Slave , MSTR must be 0
	if(!MSBLSBFirst) fool ^= (1 << DORD);     // Setup as LSB First, DRDB must be 1
	if(clkRisingFalling) fool ^= (1 << CPOL); // Setup as Falling Edge, CPOL must be 1
}

// Timers
void updateRTC() {
	
}