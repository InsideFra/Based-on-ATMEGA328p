/*
 * functions.c
 *
 * Created: 04/03/2018 11:54:15
 *  Author: franc
 */

#include "functions.h"
#include "../define.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "interrupts.h"
#include "drivers.h"

extern volatile uint16_t __ms;
extern volatile unsigned long __lastTimerSeconds; // Should at least 136 years

volatile uint8_t Sending = 0;
volatile _Bool 	 SPIMode = SLAVE;

extern volatile times Orario;


void set_pin(int PORT, int PINNumb, _Bool INPOUT, _Bool LowHIGH) {
	int DDR = (PORT) - 0x01;
	if (INPOUT)
	{
		// Pin output, default low
		     (*(volatile uint8_t *)(DDR))  |= (1 << PINNumb); // Pin output
		     (*(volatile uint8_t *)(PORT)) &= ~(1 << PINNumb); // Pin Low
	} else (*(volatile uint8_t *)(DDR))  &= ~(1 << PINNumb); // Pin input
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
	uint8_t DDR = (PORT) - 0x01;
	if (PORTA(DDR) ^ (1 << PINNUmb)) { // Configured as an Output Pin
		if(PORTA(PORT) ^ (1 << PINNUmb)) { return 1; } else return 0;
	} else { // as an input pin
		uint8_t PIN = (DDR) - 0x01;
		if ( PORTA(PIN) ^ (1 << PINNUmb)) { return 1; } else { return 0; }
	}
	return 0;
}

void start_SPI(spiconfig SPIC) {
	if(!SPIC.MasterSlave) { // SPI as master
		set_pin(PORTSS,   2, OUTPUT, 0);
		set_pin(PMosi, 3, OUTPUT, 0);
		set_pin(PMiso, 4, INPUT,  0);
		set_pin(PSckl, 5, OUTPUT, 0); SPIMode = MASTER; }
	else {
		set_pin(PORTSS, 2, INPUT, 0);
		set_pin(PMiso, 4,  OUTPUT,  0);
	}
	SPCR |= (1 << SPIE) || (1 << SPE);
	if(SPIC.MasterSlave)     SPCR ^= (1 << MSTR);     // Setup as Slave , MSTR must be 0
	if(SPIC.MSBLSBFirst)     SPCR ^= (1 << DORD);     // Setup as LSB First, DRDB must be 1
	if(SPIC.clkRisingFalling) SPCR ^= (1 << CPOL); // Setup as Falling Edge, CPOL must be 1
}

_Bool sendoverspi(uint8_t _data, uint8_t action) {
	if(Sending == 0) {
		Sending = action;
		SPDR = _data;
		return 1;
	}
	return 0;
}

// Orologio - Orario
void updateRTC() { // Funzione ogni secondo
		Orario.Secondi++;
		if(Orario.Secondi >= 60) {
			Orario.Minuti += Orario.Secondi/60;
			Orario.Secondi = Orario.Secondi%60;
			if(Orario.Minuti >= 60) {
				Orario.Ore =   Orario.Minuti/60;
				Orario.Minuti = Orario.Minuti%60;
				if(Orario.Ore >= 24) {
					Orario.Ore = 0;
				}
			}
		}
}
// Orologio - Orario

void updateEEPROM() {
	// User Custom Program
	EEPROM_write(0x00, Orario.Secondi);
	EEPROM_write(0x01, Orario.Minuti);
	EEPROM_write(0x02, Orario.Ore);
	EEPROM_write(0x03, Orario.Giorno);
	EEPROM_write(0x04, Orario.Mesi);
	EEPROM_write(0x05, Orario.Anno);
	// User Custom Program
}

void defineTimer(uint8_t TimerNumber, uint8_t Mode, uint8_t prescaler) {

}

void EEPROM_write(uint8_t address, uint8_t data) {
	cli(); // Disable interrupts
	while(EECR & (1 << EEPE)) {}
	EEARH = 0x00;
	EEARL = address;
	EEDR = data;
	EECR = 0x00;
	EECR = (1 << EERIE) | (1 << EEMPE) | (1 << EEPE);
	for(uint8_t i = 20; i != 0; i--) {} // Delay farlocco per evitare problemi con EEPROM
	sei(); // Enable interrupts
}
