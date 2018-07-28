/*
 * Atmega328P.c
 *
 * Created: 25/02/2018 00:15:28
 * Author : franc
 * Il programma � alla base del sistema Termostato-Wireless
 * � un concetto semplice e sicuramente ben sviluppato nell`industria moderna
 * Porta per� con se nuovi concetti chiave come la codifica dei codici wireless
 * con token univoci rendendo impossibile l`hackeraggio da parte di man in the middle

 * Verr� sviluppato poi in seguito anche un programma che gestir� tutta le animazioni
 * dello schermo Oled, mantenendo al minimo l`utilizzo di memoria (compressione, azioni prestabilite)

 * Successivamente verranno rilasciati anche i sorgenti dell`hardware
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Utilities/functions.h"
#include "Wireless/wThings.h"
#include "define.h"

extern int	foo;
volatile extern uint8_t	Sending;

volatile uint16_t      __ms = 0;
volatile unsigned long __lastTimerSeconds = 0; // Should atleast 136 years

FUSES =
{
	.low = 0xEF,
	.high = 0xDA,
	.extended = 0x05,
};

// Timers
uint16_t Timer[10];
uint16_t lastTimer[10];
void     *pointerFunctionTimer[10];
// END
ISR(TIMER0_COMPA_vect) // ISR Timer0 match COMPA, that`s used for counting milli seconds
{
	__ms++;
  for(uint8_t i = 0; i < 10; i++) {
		if(Timer[i] != 0) {
			if(lastTimer[i] < Timer[i]) {
				lastTimer[i]++;
			} else if(lastTimer[i] >= Timer[i]) {
				// Azione
				pointerFunctionTimer[i];
			}
		}
	}
	if(__ms > 1000) { // All Functions every seconds
		__lastTimerSeconds++;
		__ms -= 1000;
		updateRTC();
	}
	// Tutte le funzioni ogni milli secondo
}

// Variabili SPI Wireless
volatile extern uint32_t bufferDataToWrite32;
volatile extern uint8_t  bufferDataToWrite;
volatile extern _Bool	  bufferSize;
// Variabili SPI Wireless

ISR(SPI_STC_vect) // ISR SPI finito
{
	switch(Sending) {
		case 0:
		case 1:
		case 2:
			if(!bufferSize) { // 32 bit
				/*bufferDataToWrite_size -= 8;
				uint8_t splicing[4];
				*(uint32_t *)&splicing = bufferDataToWrite;
				(bufferDataToWrite >>= 8);
				sendoverspi(splicing[3], 2);*/
			} else { // 8 bit
				sendoverspi(bufferDataToWrite, 3);
			}
		case 3: bufferDataToWrite = 0; Sending = 0; toggle_pin(WCSN, 0); // Necessario per interrompere una trasmissione nel chip. // work in progress
		;
	}
	Sending = 0;
}

int main(void)
{
	// Enable Interrupts and configs
	(*(volatile uint8_t*) (0x5F)) |= (1 << 7); // Enable interrupts
	(*(volatile uint8_t*) (0x44)) |= (0b00000010); // Set the CTC mode
	(*(volatile uint8_t*) (0x45)) |= (0b00000011); // Set prescaler to 64
	(*(volatile uint8_t*) (0x6E)) |= (0x02); // enable interrupts
	(*(volatile uint8_t*) (0x47)) |= (0xFA); // Set comparator to 250 per il timer
	// END

	// enable Wireless
    startWireless();
	// END

	// Enable interrupts and config
	set_pin(ButtonUP, 5, INPUT, 0);
	set_pin(ButtonDOWN, 6, INPUT, 0);
	set_pin(Speacker, 7, OUTPUT, 0);
	set_pin(0x25, 5, OUTPUT, 1);
	// END

	foo = 1;
    while (1)
    {

    }
}
