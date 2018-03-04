/*
 * functions.c
 *
 * Created: 04/03/2018 11:54:15
 *  Author: franc
 */ 

#include "functions.h"


void set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool INOUT) {
	int DDR = (PORT) - 0x01;
	if (INPOUT)  {
		// Pin output, default low
		(*(volatile uint8_t *)(DDR)) |= (1 << PINNumb); // Pin output
		(*(volatile uint8_t *)(PORT)) |= (0 << PINNumb); // Pin Low
	} else (*(volatile uint8_t *)(DDR)) |= (0 << PINNumb); // Pin input
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