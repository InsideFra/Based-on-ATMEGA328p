#include <avr/io.h>
#include <avr/interrupt.h>
#include "functions.h"
#include "../define.h"
#include "../Wireless/wThings.h"

volatile uint16_t __ms = 0;
volatile unsigned long __lastTimerSeconds = 0; // Should at least 136 years

volatile uint16_t Timer[MAXTIMERS];
volatile uint8_t  Timer8[MAXTIMERS];

volatile uint8_t Ocrlast = 0;
volatile _Bool   LedOn = 0;
volatile _Bool   Reverse = 0;
volatile _Bool   startLed = 0;
volatile uint8_t tempTimerLed = 10;

extern volatile times 	 Orario;

void main1() {
	// Counter Millisecondi Timer 2
	TCCR2A = (0x02);
	(*(volatile uint8_t*) (0xB1)) |= (0b00000100); // Set prescaler to 64, CTC MODE
	(*(volatile uint8_t*) (0x70)) |= (0x02); // SI interrupts, only comp a
	(*(volatile uint8_t*) (0xB3)) |= (0xFA); // Set comparator to 250
	// Counter Millisecondi Timer 2
}

ISR(TIMER2_COMPA_vect) // ISR Timer0 match COMPA, that`s used for counting milli seconds
{
  __ms++;
	checkTemperature(0);
  if(__ms >= 1000) { // One second passed
    __ms -= 1000;
    __lastTimerSeconds++;
    if(!lastTimerLedOn) lastTimerLedOn++;
		refreshEEPROM++; if(refreshEEPROM >= 250) refreshEEPROM = 0; updateEEPROM();
    updateRTC();
  }
  if(startLed) {
      delayTimerPWM++;
      if(delayTimerPWM >= tempTimerLed) {
        delayTimerPWM = 0;
        OCR0A = ( Reverse ? (OCR0A - 3) : (OCR0A + 3) );
        Ocrlast = OCR0A;
        if(Ocrlast >= 240 && Reverse == 0) { // 225 viene scelto per evitare l'overflow, con valore massimo 255
          startLed = 0; Reverse = 1;
          lastTimerLedOn = 1;
          LedOn = 1;
        } else if(Ocrlast <= 20 && Reverse == 1) {
          startLed = 0; Reverse = 0; LedOn = 0; lastTimerLedOn = 0;
        }
      }
  } else {
    if(lastTimerLedOn >= MAXTIMELED) {
      lastTimerLedOn = 0; startLed = 1; Reverse = 1;
    }
  }
}

volatile uint8_t lastPIND = 0x00;

ISR(PCINT2_vect) { // INTERRUPT PCINT2
	uint8_t changedBits = 0x00;
	changedBits = PIND ^ lastPIND; // changedBits ti dice se e quale porta sia cambiata
	lastPIND = PIND; // aggiorna variabile lastPIND

	if(changedBits & (1 << 5)) { // Cambiato pin 5
		if(PIND & ( 1 << 5)) { // Pin 5 is HIGH
			if(LedOn == 0) {
        startLed = 1;
      } else if(LedOn == 0) {

      }
		} else { // Pin 5 is LOW
			//
		}
	}
}

// Variabili SPI Wireless
volatile extern uint32_t bufferDataToWrite32;
volatile extern uint8_t  bufferDataToWrite;
volatile extern _Bool	 bufferSize;
volatile extern uint8_t  Sending;
// Variabili SPI Wireless

ISR(SPI_STC_vect) // ISR SPI finito
{
	// Funzioni necessarie per lo SPI
	switch(Sending) {
		case 0:
		case 1:
		case 2:
			if(!bufferSize) { // 32 bit

			} else { // 8 bit
				sendoverspi(bufferDataToWrite, 3);
			}
		case 3: bufferDataToWrite = 0; Sending = 0; toggle_pin(WCSN, 0); // Necessario per interrompere una trasmissione nel chip. // work in progress
		;
	}
	Sending = 0;
}
