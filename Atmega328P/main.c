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
uint16_t Timer[MAXTIMERS];
uint16_t lastTimer[MAXTIMERS];
void     *pointerFunctionTimer[MAXTIMERS];
// END
ISR(TIMER2_COMPA_vect) // ISR Timer0 match COMPA, that`s used for counting milli seconds
{
	__ms++;
  for(uint8_t i = 0; i < MAXTIMERS; i++) {
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
volatile uint8_t lastPIND;
ISR(PCINT2_vect) {
	uint8_t changedBits = 0x00;
	changedBits = PIND ^ lastPIND;
	lastPIND = PIND;
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
	set_pin(SensorePorta, 5, INPUT,  0);
	set_pin(LedPWM,       6, OUTPUT, 0);
	// Enable Interrupts and configs
	(*(volatile uint8_t*) (0x5F)) |= (1 << 7); // Enable interrupts
	// PWM LED Timer 0
	(*(volatile uint8_t*) (0x44)) |= (0b01000001); // Set the Phase PWM Correct Mode, Toggle 0C0A (PWMLED) e Disconnect OC0B (Sensore Porta)
	(*(volatile uint8_t*) (0x45)) |= (0b00001100); // Set prescaler to 256, PWM Correct Mode

	(*(volatile uint8_t*) (0x6E)) |= (0x00); // NO interrupts
	(*(volatile uint8_t*) (0x47)) |= (0x00); // Set comparator to 0%
	// pwm lED Timer 0

	// Counter Millisecondi Timer 2
	(*(volatile uint8_t*) (0xB0)) |= (0x02); // Disconnect Timer 2 ports, SET CTC MODE
	(*(volatile uint8_t*) (0xB1)) |= (0b00000100); // Set prescaler to 64, CTC MODE

	(*(volatile uint8_t*) (0x70)) |= (0x02); // SI interrupts, only comp a
	(*(volatile uint8_t*) (0xB3)) |= (0xFA); // Set comparator to 250
	// Counter Millisecondi Timer 2

	// INTERRUPT Porta PCINT21
  (*PORTA(0x68)) = (0x08);
	// INTERRUPT PORTA
  lastPIND = PIND;
	// enable Wireless
    startWireless();
	// END

	// Enable interrupts and config
	/*set_pin(ButtonUP, 5, INPUT, 0);
	set_pin(ButtonDOWN, 6, INPUT, 0);
	set_pin(Speacker, 7, OUTPUT, 0);
	set_pin(0x25, 5, OUTPUT, 1);*/
	// END

	foo = 1;
    while (1)
    {

    }
}
