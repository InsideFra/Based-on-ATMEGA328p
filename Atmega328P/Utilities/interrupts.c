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

volatile uint8_t RichiestaOrario = 0;
volatile uint8_t _bufferStatusSPI = 0;

extern volatile times 	 Orario;
extern volatile _Bool SPIMode;

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
        OCR0A = ( Reverse ? (OCR0A + 3) : (OCR0A - 3) );
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
    if(lastTimerLedOn >= MAXTIMELED && StatusPorta == 0) {
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
			StatusPorta = APERTA;
			if(!LedOn == 0) startLed = 1; Reverse = 0;
		} else { // Pin 5 is LOW
			StatusPorta = CHIUSA;
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

volatile _Bool StatusPorta = 0;
volatile uint8_t SensoreUmidita = 0;
volatile uint8_t SensoreTemperatura = 0;
volatile _Bool VentolaONOFF = LOW;

ISR(SPI_STC_vect) // ISR SPI finito
{
	if(SPIMode == SLAVE) {
		if(Sending == 0) {
			// Read SPDR
			switch(SPDR) {
				case 10: // Richiesta Orario
					switch(RichiestaOrario) {
						case 0: RichiestaOrario++; SPDR = Orario.Secondi;
						case 1: RichiestaOrario++; SPDR = Orario.Minuti;
						case 2: RichiestaOrario++; SPDR = Orario.Ore;
						case 3: RichiestaOrario++; SPDR = Orario.Giorno;
						case 4: RichiestaOrario++; SPDR = Orario.Mesi;
						case 5: RichiestaOrario++; SPDR = Orario.Anno;
						case 6: RichiestaOrario = 0; SPDR = ACK;
					;}
				case 20: // Stato Porta
					SPDR = StatusPorta ? 0x01 : 0x00;
				case 30: // Valore Sensore Umidità
					SPDR = SensoreUmidita;
				case 40: // Valore Sensore Temperatura
					SPDR = SensoreTemperatura;
				case 50: // Stato Ventola
					SPDR = VentolaONOFF ? 0x01 : 0x00;
				case 60: // Modifica Stato Ventola in 1
					VentolaONOFF = HIGH;
				case 70: // Modifica Stato Led in FULLON
					OCR0A = 255; startLed = 0; Reverse = 1; tempTimerLed = 25;
				case 80: // Modifica Stato Led in FULLOFF
					OCR0A = 0; 	 startLed = 0; Reverse = 0; tempTimerLed = 25;
				case 90: // Doppio Transfer -> Avvio Procedura Led con tempTimerLed
					if(!_bufferStatusSPI) { _bufferStatusSPI = 1;}
					else if(_bufferStatusSPI) { _bufferStatusSPI = 0; OCR0A = 0; tempTimerLed = SPDR; startLed = 1; Reverse = 0;}
			;}
		} else if (Sending == 1) {
			// Write SPDR
		}
	} else if(SPIMode == MASTER) {
		switch(Sending) {
			case 0:
			case 1:
			case 2:
				if(!bufferSize) { // 32 bit

				} else { // 8 bit
					sendoverspi(bufferDataToWrite, 3);
				}
			case 3: bufferDataToWrite = 0; Sending = 0; toggle_pin(WCSN, 0); // Necessario per interrompere una trasmissione nel chip. // work in progress
		;}
		Sending = 0;
	}
}
