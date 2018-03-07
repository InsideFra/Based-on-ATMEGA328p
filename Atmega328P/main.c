/*
 * Atmega328P.c
 *
 * Created: 25/02/2018 00:15:28
 * Author : franc
 * Il programma è alla base del sistema Termostato-Wireless
 * È un concetto semplice e sicuramente ben sviluppato nell`industria moderna
 * Porta però con se nuovi concetti chiave come la codifica dei codici wireless
 * con token univoci rendendo impossibile l`hackeraggio da parte di man in the middle
 
 * Verrà sviluppato poi in seguito anche un programma che gestirà tutta le animazioni
 * dello schermo Oled, mantenendo al minimo l`utilizzo di memoria (compressione, azioni prestabilite)
 
 * Successivamente verranno rilasciati anche i sorgenti dell`hardware
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Utilities/functions.h"
#include "define.h"

extern int foo;

volatile uint16_t __ms = 0;
volatile unsigned long __lastTimerSeconds = 0; // Should atleast 136 years

ISR(TIMER0_COMPA_vect) // ISR Timer0 match COMPA, that`s used for counting milli seconds
{
	__ms++;
	if(__ms > 1000) { // All Functions every seconds
		__lastTimerSeconds++;
		__ms -= 1000;
		updateRTC();
	}
	// Tutte le funzioni ogni milli secondo
}

ISR(SPI_STC_vect) // ISR SPI finito
{
    
}

int main(void)
{
	// Enable Interrupts and configs
	(*(volatile uint8_t*) (0x5F)) |= (1 << 7); // Enable interrupts
	(*(volatile uint8_t*) (0x44)) |= (0b00000010); // Set the CTC mode
	(*(volatile uint8_t*) (0x45)) |= (0b00000011); // Set prescaler to 64
	(*(volatile uint8_t*) (0x6E)) |= (0x02); // enable interrupts
	(*(volatile uint8_t*) (0x47)) |= (0xFA); // Set comparator to 250
	// Enable Interrupts and configs
	set_pin(ButtonUP, 5, INPUT, 0);
	set_pin(ButtonDOWN, 6, INPUT, 0);
	set_pin(Speacker, 7, OUTPUT, 0);
	foo = 1;
    while (1) 
    {
		
    }
}



